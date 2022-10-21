set(CMAKE_C_STANDARD 11)

add_executable(lab2 main.c
    src/parent.c include/parent.h
    include/utils.h
)

add_executable(child src/child.c
    include/utils.h include/child.h
)

target_include_directories(lab2 PRIVATE include)

target_include_directories(child PRIVATE include)

add_dependencies(lab2 child)