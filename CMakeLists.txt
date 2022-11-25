cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDART 17)

project(OS_LABS)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(lab2)

include(FindThreads)

add_subdirectory(lab3)

add_subdirectory(lab4)

add_subdirectory(tests)
