#include <sstream>
#include <string>

int Unpack(std::string &str)
{
    std::string resultStr;
    int result;

    std::stringstream strStream;
    strStream << str;

    std::getline(strStream, resultStr, ' ');
    std::getline(strStream, str, ' ');

    result = std::atoi(resultStr.data());

    return result; 
}


