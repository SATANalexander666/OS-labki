add_executable(server src/server.cpp
    src/server_utils.cpp include/server_utils.hpp
)

add_executable(client src/client.cpp
    src/client_utils.cpp include/client_utils.hpp
)

add_executable(test main.cpp
    src/server_utils.cpp include/server_utils.hpp
    src/client_utils.cpp include/client_utils.hpp
)

target_include_directories(test PRIVATE include)

#find_package(cppzmq)

target_include_directories(server PRIVATE include)
target_link_libraries(server zmq)

target_include_directories(client PRIVATE include)
target_link_libraries(client zmq)

