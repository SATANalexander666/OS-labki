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

    std::queue<std::thread> workers;
    std::queue<std::future <std::string> > workersProms;
    std::queue<std::string> responseQueue;

    while (true)
    {
        zmq::message_t request;
        auto requestStatus = socket.recv(request, zmq::recv_flags::none);
        std::string requestStr = request.to_string();
        
        std::string activeThreadId;
        
        if (!requestStr.compare("END_OF_INPUT"))
        {
            while (!workers.empty())
            {
                workers.front().join();
                workers.pop();

                responseQueue.push(workersProms.front().get());
                workersProms.pop();
            }

            break;
        }

        TCmdArgs arguments = UnpackCommand(requestStr);

        if (!arguments.command.compare("exec"))
        {
            std::promise<std::string> workerProm;
            std::future<std::string> futureValue = workerProm.get_future();
            std::thread worker(&ExecNode, arguments.id, arguments.args, std::move(workerProm));
            
            workers.push(std::move(worker));
            workersProms.push(std::move(futureValue)); 
        }

        if (!arguments.command.compare("create")){
            responseQueue.push(CreateNode(arguments.id));
        }

        if (!arguments.command.compare("remove"))
        {
            while (!workers.empty())
            {
                workers.front().join();
                workers.pop();

                responseQueue.push(workersProms.front().get());
                workersProms.pop();
            }

            responseQueue.push(RemoveNode(arguments.id));
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

