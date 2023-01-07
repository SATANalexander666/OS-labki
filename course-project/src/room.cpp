#include "allias.hpp"
#include "zmq_utils.hpp"
#include "server_utils.hpp"

#include <cstdlib>
#include <iostream>

#include <game_utils.hpp>
#include <queue>
#include <map>

std::string Confirm(std::string &jobs, Canvas &cnv)
{
    std::string result;

    return result;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "[room] Too few arguments\n";
        exit(EXIT_FAILURE);
    }

    std::string port = argv[1];
    std::string address = "tcp://*:" + port;
    
    std::string request, response;
    std::map<int, std::string > jobs;

    int numOfClients = 2;
    bool flag = 0;
    int sid;

    Canvas cnv1(4, 2);
    Canvas cnv2(4, 2);

    zus::Socket socket(address, utl::SERVER);
    
    while (true)
    {
        request = socket.RecieveMessage();
        socket.SendMessage(request);

        std::cout << request << '\n';

        int id = Unpack(request);

        if (!flag)
        {
            sid = id;
            flag = 1;
        }

        if (!request.compare(game::QUIT))
        {
            //socket.SendMessage(utl::TERMINATOR);
            
            --numOfClients;
            if (numOfClients < 1){
                break;
            }
        }
        else if (!request.compare(game::CONFIRM)) 
        {   
            if (sid == id){
                //socket.SendMessage(Confirm(jobs.find(id)->second, cnv1));
            }
            else {
                //socket.SendMessage(Confirm(jobs.find(id)->second, cnv2));
            }

            //socket.SendMessage(request);
        }
        else
        {
            jobs[id] = request;

            //socket.SendMessage(response);
        }

        //socket.SendMessage(request);
    }

    return 0;
}

