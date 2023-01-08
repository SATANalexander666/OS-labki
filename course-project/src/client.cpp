#include "zmq_utils.hpp"
#include "utils.hpp"
#include "allias.hpp"

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <zmq.hpp>

std::string WithId(std::string &id, std::string &str){
    return std::string(id + " " + str);
}

int main(int argc, char* argv[])
{
    std::string port = argv[1];
    std::string id = argv[2];

    std::string address = "tcp://localhost:" + port;
    zus::Socket socket(address, utl::CLIENT);

    ClientCommand cmd(id);

    std::string input, response, request = cmd.INIT_CLIENT;

    std::cout << "Log in -> ";
    std::cin >> input;
    request += " " + input + " ";

    response = socket.SendRequest(request);
    request = id + " ";

    std::cout << "\nCREATE - create room,\n CONNECT - connect to the room.\n-> ";
    std::cin >> input;
    request += input;

    std::cout << "\nEnter lobby name ->";
    std::cin >> input;
    request += " " + input;

    std::cout << request << '\n';
    response = socket.SendRequest(request);

    std::cout << "\nCommands:\n0 - start game;\n" \
        << "1 <number> - choose <number>\n" \
        << "2 <user> - print stat of <user>\n";

    while (std::getline(std::cin, input))
    {
        if (input.length())
        {
            if (input.compare(msg::START_GAME)){
                execl("./gamer", "gamer", argv[1], "5555");
            }

            request = id + " " + input;
            response = socket.SendRequest(request);
        }

        if (response.length()){
            std::cout << response << '\n';
        }

    }

    request = cmd.TERMINATOR;
    socket.SendRequest(request);

    return 0;
}

