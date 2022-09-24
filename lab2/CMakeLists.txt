cmake_minimum_required(VERSION 3.22)

project(lab2)

file(GLOB SOURCES
    include/*.hpp
    src/*.cpp
)

add_executable(lab2 main.cpp ${SOURCES})

target_include_directories(lab2 PRIVATE include)