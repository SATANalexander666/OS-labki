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
        zmq::socket_t socket;

        struct PrivateMethods;

    public:
        Node(std::string &port);
        std::string SendRequest(std::string &messageStr);
        ~Node();
    };

#endif
