#!/bin/bash

exe_file="lab4"
main_dir=$(pwd)
build_dir="${main_dir}/build"

mkdir ${build_dir}
cd ${build_dir}

cmake ${main_dir}
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ${main_dir}
make

mv ${exe_file} ${main_dir}
mv ${build_dir}/compile_commands.json ${main_dir}/compile_commands.json

cd ${main_dir}
