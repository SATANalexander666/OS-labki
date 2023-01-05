#include "server_utils.hpp"
#include <algorithm>
#include <functional>
#include <zmq.hpp>

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
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
    std::vector<std::future <std::string> > workersProms;

    while (true)
    {
        zmq::message_t clientRequest;
        auto clientRequestStatus = clientSocket.recv(clientRequest, zmq::recv_flags::none);
        std::string clientCommand = clientRequest.to_string();
        
        if (!clientCommand.compare("END_OF_INPUT"))
        {
            for (int i = 0; i < (int)std::min(workers.size(), workersProms.size()); ++i){
                workers[i].join();
                //std::cout << workersProms[i].get() << std::endl;
            }

            break;
        }

        std::promise<std::string> workerProm;
        std::future<std::string> futureValue = workerProm.get_future();
        std::thread worker(&ExecCommand, clientCommand, std::move(workerProm));
        
        workers.push_back(std::move(worker));
        workersProms.push_back(std::move(futureValue));
    }

    clientSocket.close();
    clientContext.close();

    return 0;
}

