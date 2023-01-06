#include "node_attributes.hpp"
#include "zmq_utils.hpp"

Node::Node(std::string &port)
{
    try 
    {
        this->socket = (zmq::socket_t(context, zmq::socket_type::pair));
        this->address = "tcp://localhost:" + port;
        this->socket.connect(address);
    }
    catch (std::exception &exc){
        std::cerr << "Error while connecting from address: " << address \
            << std::endl << exc.what() << std::endl;
    }
}

Node::~Node()
{
    socket.disconnect(address);
    socket.close();
    context.close();
}

std::string Node::SendRequest(std::string &messageStr)
{
    std::string result;

    this->locker.try_lock();
    
    SendMessage(this->socket, messageStr);
    result = RecieveMessage(this->socket);

    this->locker.unlock();

    return result;
}

bool Node::Ping()
{
    std::string request = "PING";
    std::string response = SendRequest(request);

    if (!response.compare("ALIVE")){
        return 1;
    }


    return 0;
}


