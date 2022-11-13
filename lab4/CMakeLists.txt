add_executable(lab4 main.c
    src/parent.c include/parent.h
    src/utils.c include/utils.h 
)

add_executable(child src/child.c
    src/utils.c include/utils.h
)

target_include_directories(lab4 PRIVATE include)

target_include_directories(child PRIVATE include)

add_dependencies(lab4 child)