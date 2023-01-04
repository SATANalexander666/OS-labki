//#include "server_utils.hpp"

#include <iostream>
#include <typeinfo>
#include <future>

int main()
{
    std::promise<int> a;
    auto b = a.get_future();

    return 0;
}
