#include <cstdlib>
#include <string>
#include <zmq.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "[Node] too few arguments.\n";
        exit(EXIT_FAILURE);
    }

    std::string port = argv[1];
    std::string adress = "tcp://*:" + port;

    return 0;
}
