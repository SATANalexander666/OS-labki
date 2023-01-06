#ifndef ZMQ_UTILS_HPP
#define ZMQ_UTILS_HPP

#include <string>
#include <iostream>
#include <zmq.hpp>

std::string RecieveMessage(zmq::socket_t &socket);
void SendMessage(zmq::socket_t &socket, std::string responseStr);

#endif

