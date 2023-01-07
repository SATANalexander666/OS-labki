#include "game_utils.hpp"
#include "allias.hpp"
#include <random>
#include <sstream>
#include <string>
#include <vector>

Canvas::Canvas(int size, int ships)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);

    this->body = std::vector< std::vector<pss> >(size, std::vector<pss>(size, {"*", "0"}));
    this->alive = 0;

    for (int i = 0; i < ships; ++i)
    {
        int j = dist(mt);
        int k = dist(mt);

        if (this->body[j][k].second.compare("0")){
            ++this->alive;
        }

        this->body[dist(mt)][dist(mt)].second = "1";
    }
}

int Canvas::Kill(int i, int j)
{
    if (!this->body[i][j].second.compare("0")){
        this->body[i][j].first = "0";
    }

    if (!this->body[i][j].second.compare("2")){
        this->body[i][j].first = "2";
    }
    
    if (this->body[i][j].second.compare("1"))
    {
        this->body[i][j].first = this->body[i][j].second = "2";
        --this->alive;
    }

    return alive;
}

void Canvas::Print()
{
    std::cout << "___________\n";
    
    for (int i = 0; i < this->body.size(); ++i)
    {
        std::cout << "|" << i << "|";

        for (int j = 0; j < this->body[i].size(); ++j){
            std::cout << this->body[i][j].first << " ";
        }

        std::cout << '\n';
    }

    std::cout << "___________\n| |A B C D|\n___________\n";
}

std::string Canvas::ToString()
{
    std::string str;

    str += "___________\n";
    
    for (int i = 0; i < this->body.size(); ++i)
    {
        str + "|" + std::to_string(i) + "|";

        for (int j = 0; j < this->body[i].size(); ++j){
            str += this->body[i][j].first + " ";
        }

        str += '\n';
    }

    str += "___________\n| |A B C D|\n___________\n"; 

    return str;
 }

Canvas::~Canvas(){
}

