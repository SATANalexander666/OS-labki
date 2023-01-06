#include "node_attributes.hpp"

WrappedNode::WrappedNode(std::string port){
    Node *node = new Node(port);
}

std::string WrappedNode::SendRequest(std::string &messageStr){
   return node->SendRequest(messageStr);
}

WrappedNode::~WrappedNode(){
    delete node;
}

