#include "server_utils.hpp"
#include "node_attributes.hpp"
#include <exception>
#include <string>

std::map<std::string, WrappedNode> nodeMap;

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

TCmdCrtReturn CreateNode(std::string &id)
{
    TCmdCrtReturn result;

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
    
        result.comment = "Ok: " + std::to_string(pid);

        nodeMap.insert(std::make_pair(id, WrappedNode(port)));
    }
    catch(std::exception &exc)
    {
        result.comment = "Error" + (std::string)exc.what();

        std::cout << "Error while creating computing node with id - " \
            << id << std::endl << exc.what() << std::endl; 
    }

    return result;
}

std::string RemoveNode(std::string &id)
{
    std::string result;
    std::map<std::string, WrappedNode>::iterator it = nodeMap.find(id);
    
    if (it == nodeMap.end())
    {
        result = "Error: Not found";
        return result;
    }

    try
    {  
        std::string request = "PID";
        std::string response = it->second.SendRequest(request);

        std::cout << "[worker]\n";
        std::cout << response << std::endl;
        kill(std::stoi(response), SIGKILL);
    }
    catch(std::exception &exc)
    {
        std::cerr << "Error while killing process with id - " \
            << id << std::endl << exc.what() << std::endl;

        result = "Error: uncallable pid";
    }

    try{
        nodeMap.erase(it); 
    }
    catch(std::exception &exc)
    {
        std::cerr << "Error while removing node with id - " \
            << id << " from map\n" << exc.what() << std::endl;

        result = "Error: I broke map ;(";
    }

    return result;
}

void ExecNode(std::string &id, std::vector<int> &args, std::promise<TCmdExecReturn> &&result)
{
    TCmdExecReturn localResult;

    std::map<std::string, WrappedNode>::iterator it = nodeMap.find(id);

    if (it == nodeMap.end())
    {
        localResult.comment = "Error: " + id + ": Not found";
        result.set_value(localResult);

        return;
    }

    try
    {
        std::string request;

        for (int &elem : args){
            request += std::to_string(elem) + " ";
        }

        std::cout << request << std::endl;
    }
    catch(std::exception &exc)
    {
        std::cerr << "Error while accesing node with id - " \
            << id << std::endl << exc.what() << std::endl;

        localResult.comment = "Error: " + id + ": Node is unavaliable";
        result.set_value(localResult);

        return;
    }

}

