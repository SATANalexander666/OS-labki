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


add_executable(gamer src/gamer.c
    src/game_utils.c include/game_utils.h
)

add_executable(room src/room.c
    src/game_utils.c include/game_utils.h
)

target_include_directories(client PRIVATE include)
target_include_directories(server PRIVATE include)
target_include_directories(gamer PRIVATE include)
target_include_directories(room PRIVATE include)

target_link_libraries(client zmq)
target_link_libraries(server zmq)
target_link_libraries(gamer zmq)
target_link_libraries(room zmq)

