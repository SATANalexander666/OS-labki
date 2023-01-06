#ifndef NODE_ATTRIBUTES_HPP
#define NODE_ATTRIBUTES_HPP

#include <zmq.hpp>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <mutex>

class Node
{
    private:
        std::string address;
        std::mutex locker;
        
        zmq::context_t context;
        zmq::socket_t socket{this->context, zmq::socket_type::pair};

    public:

        Node(std::string &port);
        ~Node();

        std::string SendRequest(std::string &messageStr);
        bool Ping();
};

class WrappedNode
{
    private:
        Node *node;
    public:
        WrappedNode(std::string port);
        std::string SendRequest(std::string &messageStr);
        ~WrappedNode();
};

#endif

