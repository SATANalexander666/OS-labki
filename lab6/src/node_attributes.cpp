#include <exception>
#include <node_attributes.hpp>

#include <stdexcept>
#include <zmq.hpp>

struct Node::PrivateMethods
{
    static void SendMessage(Node &self, std::string &messageStr)
    {
        try
        {
            zmq::message_t request(messageStr.data(), messageStr.length());
            zmq::send_result_t requestStatus = self.socket.send(request, zmq::send_flags::none);
        }
        catch(std::exception &exc){
            std::cerr << "Error while sending message from address: " << self.address \
                << std::endl << exc.what() << std::endl;
        }
    }

    static std::string RecieveMessage(Node &self)
    {
        zmq::message_t response;
        
        try {   
            zmq::recv_result_t responseStatus = self.socket.recv(response, zmq::recv_flags::none);
        }
        catch (std::exception &exc){
            std::cerr << "error" << std::endl;
        }
        
        return response.to_string();
    }
   
};

Node::Node(std::string &port)
{
    try 
    {
        this->socket = (zmq::socket_t(context, zmq::socket_type::req));
        
        this->address = "tcp://localhost:" + port;
        this->socket.connect(this->address);
    }
    catch (std::exception &exc){
        std::cerr << "Error while connecting from address: " << this->address \
            << std::endl << exc.what() << std::endl;
    }
}

std::string Node::SendRequest(std::string &messageStr)
{
    PrivateMethods::SendMessage(*this, messageStr);
    return PrivateMethods::RecieveMessage(*this);
}

Node::~Node()
{
    std::string terminate = "END_OF_INPUT";
    //SendMessage(terminate);

    socket.disconnect(address);
    socket.close();
    context.close();
}

