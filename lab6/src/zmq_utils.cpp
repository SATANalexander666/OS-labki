#include "zmq_utils.hpp"
#include <exception>

std::string RecieveMessage(zmq::socket_t &socket)
{
    std::string result;

    try
    {
        zmq::message_t request;
        zmq::recv_result_t requestStatus = socket.recv(request, zmq::recv_flags::none);
        result = request.to_string();
    }
    catch(std::exception &exc){
        std::cerr << exc.what() << std::endl;
    }
    
    return result;
}

void SendMessage(zmq::socket_t &socket, std::string &responseStr)
{
    try
    {
        zmq::message_t response(responseStr.data(), responseStr.length());
        zmq::send_result_t responseStatus = socket.send(response, zmq::send_flags::none);
    }
    catch(std::exception &exc){
        std::cerr << exc.what() << std::endl;
    }
}

