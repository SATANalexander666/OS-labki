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
            
            void SendMessage(const std::string &requestStr);
            std::string RecieveMessage();
            std::string SendRequest(const std::string &requestStr);
            std::string SendResponse(const std::string &responseStr);

            ~Socket();
        
        private:
            std::string address;
            std::string socketType;

            zmq::context_t context;
            zmq::socket_t socket;

            struct Private;
    };
}


#endif

