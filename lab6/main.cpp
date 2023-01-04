#include "server_utils.hpp"

#include <iostream>

int main()
{
    TArgs result;
    std::string str;

    while (std::getline(std::cin, str)) 
    {
        result = UnpackCommand(str);
    
        std::cout << result.command << std::endl;
        std::cout << result.id << std::endl;

        for (int elem : result.args){
            std::cout << elem << " ";
        }
    }
    return 0;
}
