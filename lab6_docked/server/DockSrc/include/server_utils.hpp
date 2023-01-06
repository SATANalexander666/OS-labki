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
#include <signal.h>
#include <zmq.hpp>
#include <map>

struct TCmdArgs
{
    std::string command;
    std::string id;
    std::vector<int> args;
};

TCmdArgs UnpackCommand(std::string &str);
std::string CreateNode(std::string &id);
std::string RemoveNode(std::string &id);
void ExecNode(std::string id, std::vector<int> args, std::promise<std::string> &&result);
std::string PingAll(void);

#endif
