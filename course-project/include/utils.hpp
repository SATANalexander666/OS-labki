#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <regex>
#include <set>

class RoomName
{
    public:
        RoomName();
        RoomName(std::string &name);

        std::string data;
        std::string formatted;

        ~RoomName();
    private:
        ;
};

std::istream &operator >> (std::istream &in,  RoomName &obj);






class Room
{
    public:
        RoomName name;
        std::string port;

        Room(std::string &line);
        Room(std::string &name, std::string &port);
        ~Room();

    private:
        ;
};





class RoomsManager
{
    public:
        RoomsManager();

        bool Member(std::string &name);
        std::string GetPort(std::string &name);
        std::string AddRoom(std::string &name);
        void StartRoom(std::string &name); 

        ~RoomsManager();
    private:
        std::set<Room> rooms;
};

#endif
