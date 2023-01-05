#include <zmq.hpp>

#include <node_attributes.hpp>

#include <string>
#include <iostream>
#include <stdexcept>

int main (int argc, char const *argv[]) 
{
    /*std::string port = "4040";
    Node node(port);

    std::string message = "remove 0";
    std::string response = node.SendRequest(message);
 
    std::cout << "[client recieved] " << response << std::endl;
    
    message = "END_OF_INPUT";
    response = node.SendRequest(message);

    std::cout << "[client recieved] " << response << std::endl;
    */
    
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
                zmq::message_t request(str.data(), str.length());
                //std::cout << "[Client] " << request.str() << std::endl; 

                auto requestStatus = socket.send(request, zmq::send_flags::none);
            }
            catch (std::exception &exc){
                std::cerr << exc.what() << std::endl;
            }
        }
    }

    str = "END_OF_INPUT";
    zmq::message_t request(str.data(), str.length());

    auto requestStauts = socket.send(request, zmq::send_flags::none);

    socket.disconnect(address);
    socket.close();
    context.close();

    return 0;
}
