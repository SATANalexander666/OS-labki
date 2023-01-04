#ifndef SERVER_UTILS_HPP
#define SERVER_UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <utility>

struct TArgs
{
    std::string command;
    std::string id;
    std::vector<int> args;
};

TArgs UnpackCommand(std::string &str);
std::string CreateNode(std::string &id);
void ExecCommand(std::string clientCommand, std::string &port);
//std::string ExecCommand(std::string command);

#endif
