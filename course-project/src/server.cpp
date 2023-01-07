#include "zmq_utils.hpp"
#include "utils.hpp"
#include "allias.hpp"
#include <zmq.hpp>

void RedirectClient(zus::Socket &socket)
{
    RoomsManager manager;
    
    std::string request = socket.RecieveMessage();
    socket.SendRequest(request);
    std::string roomName = socket.RecieveMessage();

    if (!request.compare(msg::CREATE)){
        if (manager.Member(roomName)){
            socket.SendMessage(msg::ROOM_EXISTS);
        }
        else {
            socket.SendMessage(manager.AddRoom(roomName));
        }
    }

    if (!request.compare(msg::CONNECT)){
        if (!manager.Member(roomName)){
            socket.SendMessage(msg::ROOM_NOT_FOUND);
        }
        else {
            socket.SendMessage(manager.GetPort(roomName));  
        }
    }
}

int main()
{
    std::string address = "tcp://*:4040";
    zus::Socket socket(address, utl::SERVER);

    while (true)
    {
        std::string request = socket.RecieveMessage();
        socket.SendMessage(request);
        
        std::cout << request << '\n';

        if (!request.compare(msg::INIT_CLIENT)){
            RedirectClient(socket);
        }
        else if (!request.compare(utl::TERMINATOR)){
            break;
        }
    }

    return 0;
}

