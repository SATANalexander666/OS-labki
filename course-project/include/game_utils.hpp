#ifndef GAME_UTILS_HPP
#define GAME_UTILS_HPP

#include <vector>
#include <iostream>

using pss = std::pair<std::string, std::string>;

class Canvas
{
    public:
        std::vector< std::vector<pss> > body;
        
        Canvas(int size, int ships);
        int Kill(int x, int y);
        void Print();
        std::string ToString();
        ~Canvas();

    private:
        int alive;
};

#endif

