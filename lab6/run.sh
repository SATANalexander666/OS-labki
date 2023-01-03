#!/bin/bash

./server &
server_pid=$!

./client < in1.txt &
client_pid=$!

echo ${server_pid}
echo ${client_pid}

wait ${client_pid}
kill ${server_pid}
