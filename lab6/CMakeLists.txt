add_executable(server src/server.cpp
    src/server_utils.cpp include/server_utils.hpp
    src/node_attributes.cpp include/node_attributes.hpp
)

add_executable(test main.cpp
    src/server_utils.cpp include/server_utils.hpp
    src/node_attributes.cpp include/node_attributes.hpp
)

add_executable(client src/client.cpp
    src/node_attributes.cpp include/node_attributes.hpp
)
add_executable(computing_node src/computing_node.cpp)

target_include_directories(server PRIVATE include)
target_include_directories(test PRIVATE include)
target_include_directories(client PRIVATE include)

target_link_libraries(server zmq)
target_link_libraries(client zmq)
target_link_libraries(computing_node zmq)
target_link_libraries(test zmq)
