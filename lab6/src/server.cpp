#include "server_utils.hpp"
#include <zmq.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <future>

int main (int argc, char const *argv[]) 
{
    zmq::context_t clientContext;
    zmq::socket_t clientSocket(clientContext, zmq::socket_type::pair);

    std::string clientAddress = "tcp://*:4040";
    clientSocket.bind(clientAddress);

    std::vector<std::thread> workers;
    std::vector<std::future <TCmdReturn> > workersProms;
    std::queue<TCmdReturn> responseQueue;

    while (true)
    {
        zmq::message_t clientRequest;
        auto clientRequestStatus = clientSocket.recv(clientRequest, zmq::recv_flags::none);
        std::string clientCommand = clientRequest.to_string();
        
        if (!clientCommand.compare("END_OF_INPUT"))
        {
            for (int i = 0; i < (int)std::min(workers.size(), workersProms.size()); ++i){
                workers[i].join();
                responseQueue.push(workersProms[i].get());
            }

            break;
        }

        std::promise<TCmdReturn> workerProm;
        std::future<TCmdReturn> futureValue = workerProm.get_future();
        std::thread worker(&ExecCommand, clientCommand, std::move(workerProm));
        
        workers.push_back(std::move(worker));
        workersProms.push_back(std::move(futureValue));
    }

    while (!responseQueue.empty()){
        std::cout << "[queue] " << responseQueue.front().command << std::endl;
        responseQueue.pop();
    }

    clientSocket.close();
    clientContext.close();

    return 0;
}

