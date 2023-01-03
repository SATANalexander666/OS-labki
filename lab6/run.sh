#!/bin/bash

./server &
server_pid=$!

./client < in.txt &
client_pid=$!

sleep 1

kill ${client_pid}
kill ${server_pid}

return 0
