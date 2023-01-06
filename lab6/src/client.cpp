#include <sstream>
#include <zmq.hpp>

#include "node_attributes.hpp"
#include "zmq_utils.hpp"

#include <string>
#include <iostream>
#include <stdexcept>

int main (int argc, char const *argv[]) 
{
    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::pair);
  
    const std::string address = "tcp://localhost:4040";
    socket.connect(address);

    std::string str;

    while (std::getline(std::cin, str))
    {
        if (str.length() > 0)
        {
            try 
            {
                SendMessage(socket, str);
            }
            catch (std::exception &exc){
                std::cerr << exc.what() << std::endl;
            }
        }
    }

    str = "END_OF_INPUT";
    SendMessage(socket, str);

    while (true)
    {
        zmq::message_t response;
        zmq::recv_result_t responseStatus = socket.recv(response, zmq::recv_flags::none);
        
        if (!response.to_string().compare("END_OF_INPUT")){
            break;
        }

        std::cout << response.to_string() << std::endl;
    }

    socket.disconnect(address);
    socket.close();
    context.close();
    
    return 0;
}
