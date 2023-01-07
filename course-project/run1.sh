#!/bin/bash

exec_dir="/home/axr/prog/study/OS/main/course-project/executables"
cd ${exec_dir}

./room 4040 &
server_pid=$!

./client localhost 1 < "../input/${1}.txt" &
client1_pid=$!

./client localhost 2 < "../input/${2}.txt" &
client2_pid=$!

for i in {1..5};
do

    status=0

    if [ -n "$(ps -p ${client1_pid} -o pid=)" ]; then
        status=1
    fi

    if [ -n "$(ps -p ${client2_pid} -o pid=)" ]; then
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

if [ -n "$(ps -p ${client1_pid} -o pid=)" ]; then
    kill ${client1_pid}
    echo "Client 1 terminated."
fi

if [ -n "$(ps -p ${client2_pid} -o pid=)" ]; then
    kill ${client2_pid}
    echo "Client 2 terminated."
fi

if [ -n "$(ps -p ${server_pid} -o pid=)" ]; then
    kill ${server_pid}
    echo "Server terminated."
fi


