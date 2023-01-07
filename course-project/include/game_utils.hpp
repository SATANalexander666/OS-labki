#ifndef GAME_UTILS_HPP
#define GAME_UTILS_HPP

#include <vector>
#include <iostream>

class Canvas
{
    public:
        std::vector< std::vector<char> > body;
        
        Canvas(int size, int ships);

        ~Canvas();

    private:
        int alive;
};

std::ostream &operator << (std::ostream &out, Canvas &obj);

#endif

