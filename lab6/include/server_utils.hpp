#ifndef SERVER_UTILS_HPP
#define SERVER_UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <utility>

using PStrVec = std::pair<std::string, std::vector<int>>;

PStrVec UnpackCommand(std::string str);

#endif
