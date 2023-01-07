#include "utils.hpp"
#include "zmq_utils.hpp"
#include "allias.hpp"
#include "server_utils.hpp"

#include <cstdio>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <zmq.hpp>
#include <unistd.h>
#include <queue>
#include <set>

using pii = std::pair<int, int>;

class StatChecker
{
    private:

    public:
        std::map<std::string, int> data;
        StatChecker()
        {
            std::ifstream fin(room::PATH_TO_USERS_DB);

            std::string name;
            fin >> name;

            int record;
            fin >> record;

            data[name] = record;
        }
        bool Member(std::string &key){
            return data.count(key);
        }
        ~StatChecker()
        {
            std::ofstream fout(room::PATH_TO_USERS_DB);

            for (std::map<std::string, int>::iterator it = data.begin(); it != data.end(); ++it){
                fout << it->first << " " << it->second << '\n'; 
            }           
        }
}stat;

struct TArgs
{
    int id;
    std::string command;
    std::string arg;
};

TArgs GetCommand(std::string &str)
{
    TArgs result;

    std::stringstream strm;
    strm << str;
    std::string str1;
    
    std::cout << sym::BOLDBLACK;

    std::getline(strm, str1, ' ');
    result.id = std::atoi(str.data());
    std::getline(strm, str1, ' ');
    result.command = str1;

    if (!str1.compare(msg::KILL)){
        std::getline(strm, str1);
    }
    else {
        std::getline(strm, str1, ' ');
    }
    result.arg = str1;

    return result;
}

int GetRandom(int min, int max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    
    return dist(mt);
}

struct Game
{
    pii me;
    pii enemy;
    bool used{0};
    bool active{0};

    void Gen(int min, int max)
    {
        me = std::make_pair(GetRandom(min, max), GetRandom(min, max));
        enemy = std::make_pair(GetRandom(min, max), GetRandom(min, max));
    }

    void Swap(){
        std::swap(me, enemy);
    }
    
    std::string ToString()
    {
        std::string result = std::to_string(me.first) + " " + std::to_string(me.second);
        return std::string();
    }

}gm;

static std::set<std::string> logged;

std::string RunCommand(std::string &srcStr)
{
    std::string result;
    TArgs cmd = GetCommand(srcStr);

    RoomsManager manager;

    if (!cmd.command.compare(msg::INIT_CLIENT))
    {
        if (!logged.count(cmd.arg)){
            result = msg::NO_SUCH_USER; 
        }
        else 
        {
            logged.insert(cmd.arg);
            result = msg::SUCCES;
        }
    }

    if (!cmd.command.compare(msg::CREATE))
    {
        if (manager.Member(cmd.arg)){
            result = msg::ROOM_EXISTS;
        }
        else {
            result = manager.AddRoom(cmd.arg);
        }
    }

    if (!cmd.command.compare(msg::CONNECT))
    {
        if (!manager.Member(cmd.arg)){
            result = msg::ROOM_NOT_FOUND;
        }
        else {
            result = manager.GetPort(cmd.arg);
        }
    }

    if (!cmd.command.compare(msg::START_GAME))
    {
        if (gm.used)
        {
            result = gm.ToString();
            gm.used = 0;
        }
        else 
        {
            gm.Gen(0, 10);
            result = gm.ToString();
            gm.Swap();
            gm.used = 1;
            gm.active = 1;
        }
    }

    if (!cmd.command.compare(msg::STAT))
    {
        if (!stat.Member(cmd.arg)){
            result = "0";
        }
        else 
        {
            std::map<std::string, int>::iterator it = stat.data.find(cmd.arg);
            result = std::to_string(it->second);
        }
    }

    if (!cmd.command.compare(msg::KILL))
    {
        if (gm.active)
        {
            std::stringstream strm;
            std::string name;
            strm << cmd.arg.data();

            std::getline(strm, name, ' ');
            std::string num = name;
            getline(strm, name, ' ');

            if (std::atoi(num.data()) > std::max(gm.enemy.first, gm.enemy.second))
            {
                result = "VICTORY";

                if (stat.Member(name))
                {
                    std::map<std::string, int>::iterator it = stat.data.find(name);
                    it->second += 1;
                }
                else {
                    stat.data.insert(std::make_pair(name, 1));
                }

                gm.active = 0;
            }
            else {
                result = "U R LOOSER";
            }    
        }
        else {
            result = "WE ARE NOT PLAYING";
        }
    }

    if (!result.length()){
    }

    return result;
}

int main(int argc, char* argv[])
{
    std::string port = argv[1];
    std::string address = "tcp://*:" + port;
    zus::Socket socket(address, utl::SERVER);

    int numOfClients = 2;

    while (true)
    {
        std::string requestStr = socket.RecieveMessage();
        
        
        if (!requestStr.compare(utl::TERMINATOR))
        {
            --numOfClients;
            socket.SendMessage(requestStr);
            if (numOfClients < 1){
                break;
            }
        }
        else {
            socket.SendMessage(RunCommand(requestStr)); 
        }
    }

    return 0;
}

