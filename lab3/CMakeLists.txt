add_executable(lab3 main.cpp 
    src/body.cpp include/body.hpp
    src/utils.cpp include/utils.hpp
)

target_include_directories(lab3 PRIVATE include)

target_link_libraries(lab3 PRIVATE Threads::Threads)