#!/bin/bash

main_dir="/home/axr/prog/study/OS/main"
build_dir="$(pwd)/build"

#rm -rf ${build_dir}
mkdir ${build_dir}
cd ${build_dir}

cmake ../
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ${main_dir}
#make
cmake --build . --target child
cmake --build . --target lab2_test
cmake --build . --target lab3_test
cmake --build . --target lab4_test
cmake --build . --target lab5_1_test
cmake --build . --target lab5_2_test

ctest -V

mv compile_commands.json ${main_dir}

