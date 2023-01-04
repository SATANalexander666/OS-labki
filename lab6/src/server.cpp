#include "server_utils.hpp"
#include <algorithm>
#include <functional>
#include <zmq.hpp>

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <future>
#include <unistd.h>

int main (int argc, char const *argv[]) 
{
    zmq::context_t clientContext;
    zmq::socket_t clientSocket(clientContext, zmq::socket_type::pair);

    std::string clientAddress = "tcp://*:4040";
    clientSocket.bind(clientAddress);

    std::vector<std::thread> workers;
    std::vector<std::promise <std::string> > workersProms;

    while (true)
    {
        zmq::message_t clientRequest;
        auto clientRequestStatus = clientSocket.recv(clientRequest, zmq::recv_flags::none);
        std::string clientCommand = clientRequest.to_string();
        
        if (!clientCommand.compare("END_OF_INPUT"))
        {
            std::for_each(workers.begin(), workers.end(), [](std::thread &worker){
                worker.join();
            });

            for (std::string &elem : threadsRes){
                std::cout << elem << std::endl;
            }

            break;
        }

        std::promise<std::string> workerProm;
        std::thread worker = std::thread(&ExecCommand, clientCommand, std::ref(port));
        
        workers.push_back(std::move(worker));
        threadsRes.push_back(port);

        std::cout << "[Server] " << clientCommand << std::endl;
    }

    clientSocket.close();
    clientContext.close();

    return 0;
}

