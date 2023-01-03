#include "server_utils.hpp"

#include <iostream>
#include <sstream>

using PStrVec = std::pair<std::string, std::vector<int> >;

int StrToInt(std::string str)
{
    int result = 0;
    int digit = 1;

    for (int i = str.length() - 1; i >= 0; --i)
    {
        result += (str[i] - '0') * digit;
        digit *= 10;   
    }

    return result;
}

PStrVec UnpackCommand(std::string str)
{
    PStrVec result;

    std::stringstream strStream;
    strStream << str;

    std::string command;
    std::getline(strStream, command, ' ');
    
    result.first = command;
   
    std::string elem;
    std::vector<int> args;

    if (!command.compare("create") || !command.compare("remove"))
    {
        std::getline(strStream, elem, ' ');
        args.push_back(StrToInt(elem));

        result.second = args;

        return result;
    }
    else
    {
        while (std::getline(strStream, elem, ' ')){
            args.push_back(StrToInt(elem));
        }
        
        result.second = args;

        return result;
    }
}



