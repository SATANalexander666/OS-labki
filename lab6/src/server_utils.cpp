#include "server_utils.hpp"

TArgs UnpackCommand(std::string &str)
{
    TArgs result;

    std::stringstream strStream;
    strStream << str;

    std::string command;
    std::getline(strStream, command, ' ');
    
    result.command = command;
   
    std::string elem;
    std::vector<int> args;

    if (!command.compare("create") || !command.compare("remove"))
    {
        std::getline(strStream, elem, ' ');
        result.id = elem;
    }

    if (!command.compare("exec"))
    {
        std::getline(strStream, elem, ' ');
        result.id = elem;

        while (std::getline(strStream, elem, ' ')){
            args.push_back(std::stoi(elem));
        }
        
        result.args = args;
    }
    
    return result;
}

std::string CreateNode(std::string &id)
{
    const int MIN_PORT = 1024;
    std::string port = std::to_string(MIN_PORT + std::stoi(id));

    char* argv[3];

    argv[0] = (char*)malloc(5);
    strcpy(argv[0], "computing_node");
    argv[1] = (char*)malloc(port.length() + 1);
    strcpy(argv[1], port.data());
    argv[2] = NULL;

    int pid = fork();

    if (!pid){
        execv(argv[0], argv);
    }

    free(argv[0]);
    free(argv[1]);

    return port;
}

void ExecCommand(std::string clientCommand, std::promise<std::string> &&port)
{
    TArgs args = UnpackCommand(clientCommand); 
    
    if (!(args.command).compare("create")){
        port.set_value(CreateNode(args.id));
    }
    else if (!(args.command).compare("remove"))
    {
        port.set_value("remove");
    }
    else if (!(args.command).compare("exec"))
    {
        port.set_value("exec");
    }

    std::cout << "[Worker]" << std::endl;
}

