cmake_minimum_required(VERSION 3.22)

project(lab2)

add_executable(lab2 main.c
    include/parent.h src/parent.c
    include/child.h src/child.c)

target_include_directories(lab2 PRIVATE include)