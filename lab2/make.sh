#!/bin/bash

exe_file1="lab2"
exe_file2="child"
main_dir="/home/axr/prog/study/OS/main/lab2"
tmp_dir="${main_dir}/build"

mkdir ${tmp_dir}
cd ${tmp_dir}

cmake ${main_dir}
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ${main_dir}
make

mv ${exe_file1} ${main_dir}
mv ${exe_file2} ${main_dir}
mv compile_commands.json ${main_dir}

