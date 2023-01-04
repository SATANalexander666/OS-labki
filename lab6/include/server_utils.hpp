#ifndef SERVER_UTILS_HPP
#define SERVER_UTILS_HPP

#include <string>
#include <sstream>
#include <vector>

#include <cstdlib>
#include <iostream>
#include <future>
#include <string.h>
#include <unistd.h>
#include <zmq.hpp>
#include <map>

struct TArgs
{
    std::string command;
    std::string id;
    std::vector<int> args;
};

TArgs UnpackCommand(std::string &str);
std::string CreateNode(std::string &id);
void ExecCommand(std::string clientCommand, std::promise<std::string> &&port);

#endif
