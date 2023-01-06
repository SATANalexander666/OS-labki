cmake_minimum_required(VERSION 3.2)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(client src/client.cpp
    src/zmq_utils.cpp include/zmq_utils.hpp
)

target_include_directories(client PRIVATE include)

target_link_libraries(client zmq)
