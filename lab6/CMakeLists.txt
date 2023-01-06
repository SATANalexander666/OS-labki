cmake_minimum_required(VERSION 3.2)
project(lab6-8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)


add_executable(server src/server.cpp
    src/server_utils.cpp include/server_utils.hpp
    src/node_attributes.cpp include/node_attributes.hpp
    src/zmq_utils.cpp include/zmq_utils.hpp
)

add_executable(client src/client.cpp
    src/zmq_utils.cpp include/zmq_utils.hpp
)

add_executable(computing_node src/computing_node.cpp
    src/zmq_utils.cpp include/zmq_utils.hpp
)


target_include_directories(server PRIVATE include)
target_include_directories(client PRIVATE include)
target_include_directories(computing_node PRIVATE include)


target_link_libraries(server zmq)
target_link_libraries(client zmq)
target_link_libraries(computing_node zmq)

