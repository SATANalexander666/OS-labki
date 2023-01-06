#include <cstdlib>
#include <ostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <zmq.hpp>
#include <iostream>

#include "zmq_utils.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "[Node] too few arguments.\n";
        exit(EXIT_FAILURE);
    }

    std::string port = argv[1];
    std::string address = "tcp://*:" + port;

    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::pair);
    socket.bind(address);

    std::string requestStr;
    std::string responseStr;

    auto countSum = [](std::string strArg) -> int
    {   
        std::stringstream strStream;
        std::string strNum;
        int num = 0;
        strStream << strArg;

        while (std::getline(strStream, strNum, ' ')){
            num += std::stoi(strNum);
        }

        return num;
    };

    while (true)
    {
        requestStr = RecieveMessage(socket);

        if (!requestStr.compare("PID"))
        {
            responseStr = std::to_string(getpid());
            SendMessage(socket, responseStr);

            break;
        }
        else if (!requestStr.compare("exec"))
        {
            responseStr = "accept";
            SendMessage(socket, responseStr); 
            std::string arguments = RecieveMessage(socket);
            responseStr = std::to_string(countSum(arguments));
        }
        else if (!requestStr.compare("ping")){
            responseStr = "alive";
        }
        else if (!requestStr.compare("END_OF_INPUT")){
            break;
        }
        else {
            std::cerr << "[node: " << port << "] Unknown command\n";
        }
            
        SendMessage(socket, responseStr);
    }

    socket.close();
    context.close();

    return 0;
}
