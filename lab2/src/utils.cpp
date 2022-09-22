#include<iostream>

void Out()
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j){
            std::cout << 10 * i + j << " ";
        }
        std::cout << std::endl;
    }
}