#include "zmq_utils.hpp"
#include "utils.hpp"
#include "allias.hpp"

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <zmq.hpp>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Too few arguments\n";
        exit(EXIT_FAILURE);
    }

    std::string hostName = argv[1];
    std::string id = argv[2];
    id += " ";

    std::string address = "tcp://" + hostName + ":4040";
    zus::Socket socket(address, utl::CLIENT);

    std::string request = id + msg::INIT_CLIENT;

    std::string response = socket.SendRequest(request);

    std::string command;
    std::getline(std::cin, command);

    request = id + command; 
    response = socket.SendRequest(request);

    RoomName room;
    std::cin >> room;

    request = id + room.formatted;
    socket.SendRequest(request);

    request = id + msg::DUMP;
    std::string port = socket.SendRequest(request);

    if (!port.compare(msg::ROOM_NOT_FOUND)){
        std::cout << "Couldn't find room with such name\n";
    }
    else if (!port.compare(msg::ROOM_EXISTS)){
        std::cout << "Room with such name already exists\n";
    }

    request = id + msg::START_GAME;
    socket.SendRequest(request);

    request = id + room.formatted;
    socket.SendRequest(request);

    request = id + msg::DUMP;
    socket.SendRequest(request);

    request = id + utl::TERMINATOR;
    socket.SendRequest(request);

    std::string gameAddress = "tcp://localhost:" + port;
    zus::Socket gameSocket(gameAddress, utl::CLIENT);

    std::string input;

    while (std::getline(std::cin, input))
    {
        if (input.length() > 0)
        {
            request = id + input;
            response = gameSocket.SendRequest(request);
        }
    }

    request = id + game::QUIT;
    gameSocket.SendRequest(request);
    
    return 0;
}

