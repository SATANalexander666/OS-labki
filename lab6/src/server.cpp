#include <string>
#include <unistd.h>
#include <zmq.hpp>

#include <string>
#include <iostream>

int main (int argc, char const *argv[]) 
{
    zmq::context_t context;
    zmq::socket_t socket(context, ZMQ_REP);

    std::string address = "tcp://*:4040";
    socket.bind(address);

    zmq::message_t message;
    std::cout << message.size() << " ";
    auto res = socket.recv(message, zmq::recv_flags::none);

    std::cout << message.size() << std::endl;

    socket.close();
    context.close();

    return 0;
}

