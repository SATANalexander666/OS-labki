#include <cstdlib>
#include <string>
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

    std::cout << "[node] " << address << std::endl;

    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.bind(address);

    while (true)
    {
        zmq::message_t request;
        zmq::recv_result_t requestStatus = socket.recv(request, zmq::recv_flags::none);
        std::string requestStr = request.to_string();

        std::cout << "[node recieved] " << requestStr << std::endl;

        std::string responseStr = requestStr;
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
