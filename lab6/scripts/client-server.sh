#!/bin/bash

exec_dir="/home/axr/prog/study/OS/main/lab6/executables"
cd ${exec_dir}

./server &
server_pid=$!

./client < "../input/${1}.txt" &
client_pid=$!

for i in {1..5};
do

    status=0

    if [ -n "$(ps -p ${client_pid} -o pid=)" ]; then
        status=1
    fi

    if [ -n "$(ps -p ${server_pid} -o pid=)" ]; then
        status=1
    fi

    if [[ ${status} == 1 ]]; then
        #echo "Waiting..."
        sleep 1
    else
        break
    fi

done

if [ -n "$(ps -p ${client_pid} -o pid=)" ]; then
    kill ${client_pid}
    echo "Client terminated."
fi

if [ -n "$(ps -p ${server_pid} -o pid=)" ]; then
    kill ${server_pid}
    echo "Server terminated."
fi

idx=1
port=1024

for i in {1..11}
do
    port=$((port + idx))
    fuser -k "${port}/tcp"
    idx=$((port * 2))
done

#fuser -k 1033/tcp

