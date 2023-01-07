#include "allias.hpp"
#include "zmq_utils.hpp"
#include <cstdlib>
#include <iostream>

#include <game_utils.hpp>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "[room] Too few arguments\n";
        exit(EXIT_FAILURE);
    }

    std::string port = argv[1];
    std::string address = "tcp://*:" + port;
    
    //zus::Socket socket(address, utl::SERVER);

    Canvas cnv(8, 9);
    std::cout << cnv;

    return 0;
}

