#include <node_attributes.hpp>

Node::Node(std::string &port)
{
    address = "tcp://localhost:" + port;

}

Node::~Node()
{
    std::cout << address << std::endl;
}

