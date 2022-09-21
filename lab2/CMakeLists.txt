set(CMAKE_C_STANDARD 11)

add_executable(
    lab2
    main.cpp
    src/lab2.cpp
    include/lab2.h
)

target_include_directories(lab2 PRIVATE include)