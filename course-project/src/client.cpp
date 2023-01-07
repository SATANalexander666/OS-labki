#include "zmq_utils.hpp"
#include "utils.hpp"
#include "allias.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <regex>


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Too few arguments\n";
        exit(EXIT_FAILURE);
    }

    std::string hostName = argv[1];
    std::string address = "tcp://" + hostName + ":4040";
    zus::Socket socket(address, utl::CLIENT);

    socket.SendMessage(msg::INIT_CLIENT);
    std::string response = socket.RecieveMessage();

    std::string command;
//    std::cout << "[Game] Choose action:\n 1 - Create room;\n 2 - Connect to room.\n Command: ";
    std::getline(std::cin, command);
//    std::cout << '\n';
//    std::cout << "[Game] Give room's name\n Room's name: ";
//    std::getline(std::cin, room);
//    std::cout << '\n';

    /*if (!command.compare(msg::CREATE)) {
        socket.SendMessage(msg::CREATE);
    }

    if (!command.compare(msg::CONNECT)) {
        socket.SendMessage(msg::CONNECT);
    }*/

    socket.SendMessage(command);
    response = socket.RecieveMessage();

    RoomName room;
    std::cin >> room;

    socket.SendMessage(room.formatted);
    std::string port = socket.RecieveMessage();

    if (!port.compare(msg::ROOM_NOT_FOUND)){
        std::cout << "Couldn't find room with such name\n";
    }
    else if (!port.compare(msg::ROOM_EXISTS)){
        std::cout << "Room with such name already exists\n";
    }
    else {
        std::cout << port << '\n';
    }

    return 0;
}

