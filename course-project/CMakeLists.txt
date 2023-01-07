add_executable(client src/client.cpp
    include/allias.hpp
    src/zmq_utils.cpp include/zmq_utils.hpp
    src/utils.cpp include/utils.hpp
)

add_executable(server src/server.cpp
    include/allias.hpp
    src/zmq_utils.cpp include/zmq_utils.hpp
    src/utils.cpp include/utils.hpp
)

add_executable(test main.cpp
    include/allias.hpp
    src/zmq_utils.cpp include/zmq_utils.hpp
)

target_include_directories(client PRIVATE include)
target_include_directories(server PRIVATE include)
target_include_directories(test PRIVATE include)

target_link_libraries(client zmq)
target_link_libraries(server zmq)
target_link_libraries(test zmq)

