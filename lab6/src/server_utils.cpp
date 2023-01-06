#include "server_utils.hpp"
#include "node_attributes.hpp"
#include <zmq_utils.hpp>

#include <exception>
#include <mutex>
#include <string>
#include <zmq.hpp>

std::map<std::string, Node*> nodeMap;

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

std::string CreateNode(std::string &id)
{
    std::string result;

    if (nodeMap.count(id))
    {
        result = "Error: Already exists";
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
    
        result = "Created: pid - " + std::to_string(pid) + ", id - " + id;

        nodeMap.insert(std::make_pair(id, new Node(port)));
    }
    catch(std::exception &exc)
    {
        result = "Error" + (std::string)exc.what();

        std::cerr << "Error while creating computing node with id - " \
            << id << std::endl << exc.what() << std::endl; 
    }

    return result;
}

std::string RemoveNode(std::string &id)
{
    std::string result;

    std::map<std::string, Node*>::iterator it = nodeMap.find(id);
    
    if (it == nodeMap.end())
    {
        result = "Error: Not found";
        return result;
    }
        
    std::string request = "PID";
    std::string response = it->second->SendRequest(request);

    try
    {  
        request = "END_OF_INPUT";
        it->second->SendRequest(request);

        kill(std::stoi(response), SIGKILL);
    }
    catch(std::exception &exc)
    {
        std::cerr << "Error while killing process with id - " \
            << id << std::endl << exc.what() << std::endl;

        result = "Error: uncallable pid";
    }

    try
    {
        delete it->second;
        nodeMap.erase(it);

        result = "Removed: pid - " + response + ", id - " + id;
    }
    catch(std::exception &exc)
    {
        std::cerr << "Error while removing node with id - " \
            << id << " from map\n" << exc.what() << std::endl;

        result = "Error: I broke map ;(";
    }

    return result;
}

void ExecNode(std::string id, std::vector<int> args, std::promise<std::string> &&result)
{
    std::string resultStr;

    std::map<std::string, Node*>::iterator it = nodeMap.find(id);

    if (!nodeMap.count(id))
    {
        resultStr = "Error: " + id + ": Not found";
        result.set_value(resultStr);

        return;
    }

    try
    {
        std::string request = "exec";
        std::string response = it->second->SendRequest(request);
    }
    catch(std::exception &exc)
    {
        std::cerr << "Error while accesing node with id - " \
            << id << std::endl << exc.what() << std::endl;

        resultStr = "Error: " + id + ": Node is unavaliable";
        result.set_value(resultStr);       
    }

    try
    {
        std::string request;

        for (int &elem : args){
            request += std::to_string(elem) + " ";
        }
        
        std::string response = it->second->SendRequest(request);

        resultStr = "Executed: id - " + id + ", sum - " + response;
    }
    catch(std::exception &exc)
    {
        std::cerr << "Error while accesing node with id - " \
            << id << std::endl << exc.what() << std::endl;

        resultStr = "Error: " + id + ": Node is unavaliable";
        result.set_value(resultStr);
    }

    result.set_value(resultStr);
}

std::string PingAll(void)
{
    std::string result = "ping";

    for (std::map<std::string, Node*>::iterator it = nodeMap.begin(); it != nodeMap.end(); ++it)
    {
    }

    return result;
}

