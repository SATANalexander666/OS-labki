#include "server_utils.hpp"
#include "zmq_utils.hpp"
#include <ostream>
#include <vector>
#include <zmq.hpp>

#include <queue>
#include <thread>
#include <future>
#include <set>

struct TWorker
{
    std::string id;
    std::future<std::string> prom;
    std::thread trd;
};

int FindById(std::vector<TWorker> &arr, std::string &id)
{
    for (int i = 0; i < (int)arr.size(); ++i){
        if (!id.compare(arr[i].id)){
            return i;
        }
    }

    return -1;
}

int main (int argc, char const *argv[]) 
{
    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::pair);

    std::string address = "tcp://*:4040";
    socket.bind(address);

    std::vector<TWorker> workers;
    std::queue<std::string> responseQueue;

    while (true)
    {
        std::string requestStr = RecieveMessage(socket);
        TCmdArgs arguments = UnpackCommand(requestStr);

        if (!arguments.command.compare("create")){
            responseQueue.push(CreateNode(arguments.id));
        }
        
        if (!arguments.command.compare("exec"))
        {
            TWorker worker;

            std::promise<std::string> workerProm;
            std::future<std::string> futureValue = workerProm.get_future();
            std::thread trd(&ExecNode, arguments.id, arguments.args, std::move(workerProm));
            
            worker.id = arguments.id;
            worker.prom = std::move(futureValue);
            worker.trd = std::move(trd);

            workers.push_back(std::move(worker));
        }
       
        if (!arguments.command.compare("remove"))
        {
            int idx = FindById(workers, arguments.id);

            if (idx != -1)
            {
                workers[idx].trd.join();
                responseQueue.push(workers[idx].prom.get());

                workers.erase(workers.begin() + idx);
            }

            responseQueue.push(RemoveNode(arguments.id));
        }
        
        if (!arguments.command.compare("pingall")){
            responseQueue.push(PingAll());
        }

        if (!requestStr.compare("END_OF_INPUT"))
        {
            for (TWorker &elem : workers)
            {
                if (elem.trd.joinable()){
                    elem.trd.join();
                }

                responseQueue.push(elem.prom.get());
            }

            break;
        }
    }

    while (!responseQueue.empty())
    {
        zmq::message_t response(responseQueue.front().data(), responseQueue.front().length());
        zmq::send_result_t responseStatus = socket.send(response, zmq::send_flags::none);

        responseQueue.pop();
    }

    std::string terminate = "END_OF_INPUT";
    zmq::message_t response(terminate.data(), terminate.length());
    zmq::send_result_t responseStatus = socket.send(response, zmq::send_flags::none);

    socket.close();
    context.close();
        
    return 0;
}

