#include "game_utils.hpp"

Canvas::Canvas(int size, int ships){
    this->body = std::vector< std::vector<char> >(size, std::vector<char>(size, '0'));
}

Canvas::~Canvas(){

}

std::ostream &operator << (std::ostream &out, Canvas &obj)
{
    out << "---------------\n";

    for (std::vector<char> &vec : obj.body)
    {
        for (char symbol : vec){
            out << symbol << ' ';
        }

        out << '\n';
    }

    out << "---------------\n";

    return out;
}

