#include "server_utils.hpp"
#include "node_attributes.hpp"
#include <exception>
#include <ostream>
#include <string>
#include <utility>
#include <mutex>
#include <signal.h>

static std::map<std::string, WrappedNode> nodeMap;

std::mutex nodeLocker;

const int MIN_PORT = 1024;

TCmdArgs UnpackCommand(std::string &str)
{
    TCmdArgs result;

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

TCmdReturn CreateNode(std::string &id)
{
    TCmdReturn result;

    if (nodeMap.count(id))
    {
        result.comment = "Error: Already exists";
        return result;
    }

    try
    {
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
    
        result.pid = pid;
        result.comment = "Ok: " + std::to_string(pid);

        nodeLocker.try_lock();
        nodeMap.insert(std::make_pair(id, WrappedNode(port)));
        nodeLocker.unlock();
    }
    catch(std::exception &exc)
    {
        result.comment = "Error" + (std::string)exc.what();

        std::cout << "Error while creating computing node with id - " \
            << id << std::endl << exc.what() << std::endl; 
    }

    return result;
}

TCmdReturn RemoveNode(std::string id)
{
    TCmdReturn result;
    std::map<std::string, WrappedNode>::iterator it = nodeMap.find(id);

    if (it == nodeMap.end())
    {
        result.comment = "Error: Not found";
        return result;
    }

    try
    {  
        WrappedNode node = it->second;

        std::string request = "PID";
        std::string response = node.SendRequest(request);

        kill(std::stoi(response), SIGKILL);
    }
    catch(std::exception &exc)
    {
        std::cerr << "Error while killing process with id - " \
            << id << std::endl << exc.what() << std::endl;

        result.comment = "Error: uncallable pid";
    }

    try
    {
        nodeLocker.try_lock();
        nodeMap.erase(it); 
        nodeLocker.unlock();
    }
    catch(std::exception &exc)
    {
        std::cerr << "Error while removing node with id - " \
            << id << " from map\n" << exc.what() << std::endl;

        result.comment = "Error: I broke map ;(";
    }

    return result;
}

void ExecCommand(std::string clientCommand, std::promise<TCmdReturn> &&port)
{
    TCmdArgs args = UnpackCommand(clientCommand); 
    TCmdReturn result;

    if (!(args.command).compare("create"))
    {
        result = CreateNode(args.id);    
        result.command = "create";
    }
    else if (!(args.command).compare("remove"))
    {
        result = RemoveNode(args.id);
        result.command = "remove";
    }
    else if (!(args.command).compare("exec"))
    {
        result.command = "exec";
    }

    port.set_value(result);
}

