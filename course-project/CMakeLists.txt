add_executable(client src/client.cpp
    include/allias.hpp
    src/zmq_utils.cpp include/zmq_utils.hpp
    src/utils.cpp include/utils.hpp
)

add_executable(server src/server.cpp
    include/allias.hpp
    src/zmq_utils.cpp include/zmq_utils.hpp
    src/utils.cpp include/utils.hpp
    src/server_utils.cpp include/server_utils.hpp
)

add_executable(room src/room.cpp
    include/allias.hpp
    src/zmq_utils.cpp include/zmq_utils.hpp
    src/utils.cpp include/utils.hpp
    src/game_utils.cpp include/game_utils.hpp
    src/server_utils.cpp include/server_utils.hpp
)

add_executable(test main.cpp
    include/allias.hpp
    src/zmq_utils.cpp include/zmq_utils.hpp
)

target_include_directories(client PRIVATE include)
target_include_directories(server PRIVATE include)
target_include_directories(room PRIVATE include)
target_include_directories(test PRIVATE include)

find_package(cppzmq)

target_link_libraries(client cppzmq)
target_link_libraries(server cppzmq)
target_link_libraries(room cppzmq)
target_link_libraries(test cppzmq)

#target_link_libraries(client zmq)
#target_link_libraries(server zmq)
#target_link_libraries(room zmq)
#target_link_libraries(test zmq)

