#!/bin/bash


main_dir="/home/axr/prog/study/OS/main/lab6"
build_dir="${main_dir}/build"
exec_dir="${main_dir}/executables"

mkdir ${exec_dir}
mkdir ${build_dir}
cd ${build_dir}

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ${main_dir}
make

cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
gdb build-debug/simple_examplemake

