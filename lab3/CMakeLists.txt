cmake_minimum_required(VERSION 3.22)

project(lab3)

file(GLOB SOURCES
    include/*.hpp
    src/*.cpp
)

add_executable(lab3 main.cpp ${SOURCES})

target_include_directories(lab3 PRIVATE include)

include(FindThreads)

target_link_libraries(lab3 PRIVATE Threads::Threads)