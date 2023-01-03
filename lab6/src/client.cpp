#include <cstdlib>
#include <unistd.h>
#include <zmq.h>
#include <zmq.hpp>

#include <string>
#include <iostream>

int main (int argc, char const *argv[]) 
{
    zmq::context_t context;
    zmq::socket_t socket(context, ZMQ_REQ);
  
    const std::string address = "tcp://localhost:4040";
    socket.connect(address);

    std::string str;
    zmq::message_t message(str.data(), str.length());

    auto res = socket.send(message, zmq::send_flags::none);

    if (res.value())
    {
        std::cerr << "Sending message error\n";
        exit(EXIT_FAILURE);
    }

    socket.close();
    context.close();

    return 0;
}
