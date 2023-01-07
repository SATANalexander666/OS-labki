#include "allias.hpp"
#include "zmq_utils.hpp"
#include "server_utils.hpp"

#include <cstdlib>
#include <iostream>

#include <game_utils.hpp>
#include <queue>
#include <map>

int main(int argc, char* argv[])
{
    std::cout << "[room]\n";

    if (argc < 2)
    {
        std::cerr << "[room] Too few arguments\n";
        exit(EXIT_FAILURE);
    }

    std::string port = argv[1];
    std::string address = "tcp://*:" + port;
    
    zus::Socket socket(address, utl::SERVER);

    std::string request, response;
    std::map<int, std::queue<std::string> > jobs;

    while (true)
    {
        request = socket.RecieveMessage();

        int id = Unpack(request);

        if (!request.compare(game::QUIT))
        {
            socket.SendMessage(utl::TERMINATOR);
        }
        else 
        {
            if (jobs.count(id)){
                jobs[id] = std::queue<std::string>();
            }


        }


    }

    return 0;
}

