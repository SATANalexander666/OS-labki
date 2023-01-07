#ifndef ZMQ_UTILS_HPP
#define ZMQ_UTILS_HPP

#include <string>
#include <iostream>
#include <zmq.hpp>

namespace zus
{
    class Socket
    {
        public:
            Socket(const std::string &address, const std::string &socketType);

            std::string SendRequest(const std::string &requestStr);

            void SendMessage(const std::string &requestStr);
            std::string RecieveMessage();

            ~Socket();
        
        private:
            std::string address;
            std::string socketType;

            zmq::context_t context;
            zmq::socket_t socket{context, zmq::socket_type::pair};

            struct PrivateMethods;
    };
}


#endif

