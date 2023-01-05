#include "server_utils.hpp"
#include <zmq.hpp>

#include <queue>
#include <thread>
#include <future>

int main (int argc, char const *argv[]) 
{
    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::pair);

    std::string address = "tcp://*:4040";
    socket.bind(address);

    std::vector<std::thread> workers;
    std::vector<std::future <TCmdExecReturn> > workersProms;
    std::queue<TCmdExecReturn> responseQueue;

    while (true)
    {
        zmq::message_t request;
        auto requestStatus = socket.recv(request, zmq::recv_flags::none);
        std::string requestStr = request.to_string();
        
        if (!requestStr.compare("END_OF_INPUT"))
        {
            for (int i = 0; i < (int)std::min(workers.size(), workersProms.size()); ++i){
                workers[i].join();
                responseQueue.push(workersProms[i].get());
            }

            break;
        }

        TCmdArgs arguments = UnpackCommand(requestStr);

        if (!arguments.command.compare("exec"))
        {
            std::promise<TCmdExecReturn> workerProm;
            std::future<TCmdExecReturn> futureValue = workerProm.get_future();
            std::thread worker(&ExecNode, std::ref(arguments.id), std::ref(arguments.args), std::move(workerProm));
            
            workers.push_back(std::move(worker));
            workersProms.push_back(std::move(futureValue)); 
        }

        if (!arguments.command.compare("create")){
            TCmdCrtReturn nodeInfo = CreateNode(arguments.id);
            std::cout << nodeInfo.comment << std::endl;
        }

        if (!arguments.command.compare("remove")){
            std::string result = RemoveNode(arguments.id);
            std::cout << result << std::endl;
        }
    }

    while (!responseQueue.empty()){
        std::cout << "[queue] " << responseQueue.front().comment << std::endl;
        responseQueue.pop();
    }

    socket.close();
    context.close();

    return 0;
}

