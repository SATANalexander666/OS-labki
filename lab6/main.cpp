#include "server_utils.hpp"

#include <iostream>

int main()
{
    PStrVec result;
    std::string str;

    while (std::getline(std::cin, str)) 
    {
        result = UnpackCommand(str);
    
        std::cout << result.first << std::endl;

        for (int elem : result.second){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
