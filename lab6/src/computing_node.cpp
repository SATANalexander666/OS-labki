#include <cstdlib>
#include <sstream>
#include <string>
#include <unistd.h>
#include <zmq.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "[Node] too few arguments.\n";
        exit(EXIT_FAILURE);
    }

    std::string port = argv[1];
    std::string address = "tcp://*:" + port;

    //std::cout << "[node] " << address << std::endl;

    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::pair);
    socket.bind(address);

    while (true)
    {
        zmq::message_t request;
        zmq::recv_result_t requestStatus = socket.recv(request, zmq::recv_flags::none);
        std::string requestStr = request.to_string();

        std::string responseStr;

        if (!requestStr.compare("PID")){
            responseStr = std::to_string(getpid());
        }
        else if (requestStr.compare("END_OF_INPUT"))
        {
            std::stringstream strStream;
            strStream << requestStr;
            std::string str;
            int num = 0;

            while (std::getline(strStream, str, ' ')){
                num += std::stoi(str);
            }

            responseStr = std::to_string(num);
        }
            
        zmq::message_t response(responseStr.data(), responseStr.length());
        zmq::send_result_t responseStatus = socket.send(response, zmq::send_flags::none);
         
        if (!requestStr.compare("END_OF_INPUT")){
            break;
        }
    }

    socket.close();
    context.close();

    return 0;
}
