#include "zmq_utils.hpp"
#include "allias.hpp"
#include <exception>
#include <zmq.hpp>

struct zus::Socket::Private
{
    static void SendMessage(zus::Socket &self, const std::string &requestStr)
    {
        try
        {
            zmq::message_t response(requestStr.data(), requestStr.length());
            zmq::send_result_t responseStatus = self.socket.send(response, zmq::send_flags::none);
        }
        catch(std::exception &exc){
            std::cerr << "[socket: " << self.address << "] " << exc.what() << std::endl;
        }
    }

    static std::string RecieveMessage(zus::Socket &self)
    {
        std::string result;

        try
        {
            zmq::message_t request;
            zmq::recv_result_t requestStatus = self.socket.recv(request, zmq::recv_flags::none);
            result = request.to_string();
        }
        catch(std::exception &exc){
            std::cerr << exc.what() << std::endl;
        }
        
        return result;
    }    
};





zus::Socket::Socket(const std::string &address, const std::string &socketType)
{
    this->socketType = socketType;
    this->address = address;

    if (!socketType.compare(utl::SERVER)){
        this->socket = zmq::socket_t(this->context, zmq::socket_type::rep);
    }

    if (!socketType.compare(utl::CLIENT)){
        this->socket = zmq::socket_t(this->context, zmq::socket_type::req);
    }

    try 
    {
        if (!this->socketType.compare(utl::SERVER)){
            this->socket.bind(address);
        }

        if (!this->socketType.compare(utl::CLIENT)){
            this->socket.connect(address);
        }
    }
    catch (std::exception &exc){
        std::cerr << sym::RED << "[Error:]" << sym::RESET \
            << " socket: " << address << ": " \
            << exc.what() << std::endl;
    }
}

void zus::Socket::SendMessage(const std::string &requestStr)
{
    try
    {
        zmq::message_t response(requestStr.data(), requestStr.length());
        zmq::send_result_t responseStatus = this->socket.send(response, zmq::send_flags::none);
    }
    catch(std::exception &exc){
        std::cerr << "[socket: " << this->address << "] " << exc.what() << std::endl;
    }
}

std::string zus::Socket::RecieveMessage()
{
    std::string result;

    try
    {
        zmq::message_t request;
        zmq::recv_result_t requestStatus = this->socket.recv(request, zmq::recv_flags::none);
        result = request.to_string();
    }
    catch(std::exception &exc){
        std::cerr << exc.what() << std::endl;
    }
    
    return result;
}

std::string zus::Socket::SendRequest(const std::string &requestStr)
{
    //Private::SendMessage(*this, requestStr);
    //return Private::RecieveMessage(*this);
    SendMessage(requestStr);
    std::string responseStr = RecieveMessage();

    return responseStr;
}

std::string zus::Socket::SendResponse(const std::string &responseStr)
{
    std::string requestStr = RecieveMessage();
    SendMessage(responseStr);

    return responseStr;
}

zus::Socket::~Socket()
{
    if (!this->socketType.compare(utl::CLIENT)){
        this->socket.disconnect(this->address);
    }

    this->socket.close();
    this->context.close();
}

