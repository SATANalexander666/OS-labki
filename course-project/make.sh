#!/bin/bash

main_dir="/home/axr/prog/study/OS/main/course-project"
build_dir="${main_dir}/build"
exec_dir="${main_dir}/executables"

mkdir ${exec_dir}
mkdir ${build_dir}
cd ${build_dir}

cmake ${main_dir}
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ${main_dir}
make

mv ${build_dir}/compile_commands.json ${main_dir}/compile_commands.json
mv server ${exec_dir}
mv client ${exec_dir}
mv room ${exec_dir}
mv gamer ${exec_dir}

