#include "node_attributes.hpp"

#include <string>

int main()
{
    std::string s = "1024";
    Node a(s);

    a.SendMessage(s);

    return 0;
}
