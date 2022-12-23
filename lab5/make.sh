#!/bin/bash

main_dir=$(pwd)
build_dir="${main_dir}/build"

mkdir ${build_dir}
cd ${build_dir}

cmake ${main_dir}
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ${main_dir}
make

mv ${build_dir}/compile_commands.json ${main_dir}/compile_commands.json

cd ${main_dir}

