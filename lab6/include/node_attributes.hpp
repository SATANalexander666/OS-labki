#ifndef NODE_ATTRIBUTES_HPP
#define NODE_ATTRIBUTES_HPP

#include <zmq.hpp>
#include <iostream>

class Node
{
    private:
        std::string address;

        zmq::context_t context;
        zmq::socket_t socket;

    public:
        Node(std::string &port);
        ~Node();
    };

#endif
