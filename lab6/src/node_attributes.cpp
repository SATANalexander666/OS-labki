#include <exception>
#include <node_attributes.hpp>

#include <stdexcept>
#include <zmq.hpp>

Node::Node(std::string &port)
{
    try 
    {
        this->socket = (zmq::socket_t(context, zmq::socket_type::pair));
        
        this->address = "tcp://localhost:" + port;
        this->socket.connect(this->address);
    }
    catch (std::exception exc){
        std::cerr << "Error while connecting from address: " << this->address << std::endl;
    }
}

void Node::SendMessage(std::string &message)
{
    try
    {
        zmq::message_t request(message.data(), message.length());
        zmq::send_result_t requestStatus = this->socket.send(request, zmq::send_flags::none);
    }
    catch(std::exception exc){
        std::cerr << "Error while sending message from address: " << this->address << std::endl;
    }
}

std::string Node::RecieveMessage(void)
{
    zmq::message_t response;
    zmq::recv_result_t responseStatus = this->socket.recv(response, zmq::recv_flags::none);

    return response.to_string();
}

Node::~Node()
{
    std::string terminate = "END_OF_INPUT";
    SendMessage(terminate);

    socket.disconnect(address);
    socket.close();
    context.close();
}

