#include "utils.hpp"
#include "allias.hpp"

#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

#include <unistd.h>

RoomName::RoomName(){

}

RoomName::RoomName(std::string &name)
{
    this->data = name;
    this->formatted = std::regex_replace(name, std::regex(" "), "_");
}

RoomName::~RoomName(){

}

std::istream &operator >> (std::istream &in,  RoomName &obj)
{
    std::string input;
    std::getline(in, input);
    obj = RoomName(input);

    return in;
}





Room::Room(std::string &line)
{
    std::string str;
    std::stringstream strStream;
    strStream << line;

    std::getline(strStream, str, ' ');
    this->name = RoomName(str);

    std::getline(strStream, str, ' ');
    
    this->port = str;
}

Room::Room(std::string &name, std::string &port)
{
    this->port = port;
    this->name = RoomName(name);
}

Room::~Room(){

}





RoomsManager::RoomsManager()
{
    std::ifstream fin(room::PATH_TO_DB);
    std::string str;

    while (std::getline(fin, str)){
        if (str.length() > 2)
            this->rooms.insert(Room(str));
    }

    fin.close();
}

bool operator<(Room const &room1, Room const &room2){
    return room1.name.formatted < room2.name.formatted;
}

bool RoomsManager::Member(std::string &name){
    return rooms.count(name); 
}

std::string RoomsManager::GetPort(std::string &name)
{
    std::set<Room>::iterator it = rooms.find(name);
    
    return it->port;
}

std::string RoomsManager::AddRoom(std::string &name)
{
    std::string port;
    int maxPort = utl::MIN_PORT;

    for (Room const &elem : rooms){
        maxPort = std::max(maxPort, std::atoi(elem.port.data()));
    }

    port = std::to_string(maxPort + 1);
    rooms.insert(Room(name, port));

    return port;
}

void RoomsManager::StartRoom(std::string &name)
{
    std::set<Room>::iterator it = rooms.find(name);
    
    char* argv[3];
    argv[0] = (char*)malloc(6);
    strcpy(argv[0], "./room");
    argv[1] = (char*)malloc(it->port.length());
    strcpy(argv[1], it->port.data());
    argv[2] = NULL;

    int pid = fork();

    if (!pid){
        execv(argv[0], argv);
    }

    free(argv[0]);
    free(argv[1]);
}

RoomsManager::~RoomsManager()
{
    std::ofstream fout(room::PATH_TO_DB);

    for (const Room &elem : rooms){
        fout << elem.name.formatted << " " << elem.port << '\n';
    }

    fout.close();
}









