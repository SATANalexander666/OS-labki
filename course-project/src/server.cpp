#include "zmq_utils.hpp"
#include "utils.hpp"
#include "allias.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <zmq.hpp>

#include <queue>

std::string RedirectClient(std::queue<std::string> jobs)
{
    std::string result;

    RoomsManager manager;

    while (!jobs.empty())
    {
        std::string command = jobs.front();
        jobs.pop();

        if (!command.compare(msg::CREATE))
        {
            if (manager.Member(jobs.front())){
                result = msg::ROOM_EXISTS;
            }
            else {
                result = manager.AddRoom(jobs.front());
            }

            jobs.pop();
        }
        else if (!command.compare(msg::CONNECT))
        {
            if (!manager.Member(jobs.front())){
                result = msg::ROOM_NOT_FOUND;
            }
            else {
                result = manager.GetPort(jobs.front());
            }

            jobs.pop();
        }
        else if (!command.compare(msg::START_GAME))
        {
            manager.StartRoom(jobs.front());

            jobs.pop();
        }
    }

    return result;
}

int Unpack(std::string &str)
{
    std::string resultStr;
    int result;

    std::stringstream strStream;
    strStream << str;

    std::getline(strStream, resultStr, ' ');
    std::getline(strStream, str, ' ');

    result = std::atoi(resultStr.data());

    return result; 
}

int main()
{
    std::string address = "tcp://*:4040";
    zus::Socket socket(address, utl::SERVER);

    std::map<int, std::queue<std::string> > jobs;
    int numOfClients = 0;

    while (true)
    {
        std::string request = socket.RecieveMessage();
        int id = Unpack(request);

        if (!request.compare(utl::TERMINATOR))
        {
            socket.SendMessage(request);
           --numOfClients;
            
            if (numOfClients < 1){
                break;
            }
        }
        else if (!request.compare(msg::DUMP)){
            std::map<int, std::queue<std::string> >::iterator it = jobs.find(id);
            std::string response = RedirectClient(it->second);

            socket.SendMessage(response);
        }
        else 
        {
            socket.SendMessage(request);

            if (!request.compare(msg::INIT_CLIENT))
            {
                ++numOfClients;
                jobs[id] = std::queue<std::string>();
            }

            std::map<int, std::queue<std::string> >::iterator it = jobs.find(id);
            it->second.push(request);
        }
    }

    return 0;
}

