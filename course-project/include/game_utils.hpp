#ifndef GAME_UTILS_HPP
#define GAME_UTILS_HPP

#include <vector>
#include <iostream>

class Canvas
{
    public:
        std::vector< std::vector<std::string> > body;
        
        Canvas(int size, int ships);
        void Print();
        std::string ToString();
        ~Canvas();

    private:
        int alive;
};

#endif

