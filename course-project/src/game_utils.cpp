#include "game_utils.hpp"
#include <random>
#include <sstream>
#include <string>

Canvas::Canvas(int size, int ships)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);

    for (int i = 0; i < size; ++i)
    {
        std::vector<std::string> line;
        std::string elem("0");

        for (int j = 0; j < size; ++j){
            line.push_back(elem);
        }

        this->body.push_back(line);
    }

    for (int i = 0; i < ships; ++i){
        this->body[dist(mt)][dist(mt)] = "1";
    }
}

void Canvas::Print()
{
    for (std::vector<std::string> &vec : this->body)
    {
        for (std::string symbol : vec){
            std::cout << symbol << " ";
        }

        std::cout << '\n';
    }
}

std::string Canvas::ToString()
{
    std::string str;

    str += "--------\n";

    for (std::vector<std::string> &vec : this->body)
    {
        for (std::string &symbol : vec){
            str += symbol + " ";
        }

        str += '\n';
    }

    str += "--------\n";

    return str;
}

Canvas::~Canvas(){
}

