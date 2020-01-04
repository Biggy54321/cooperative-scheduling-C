#! /bin/bash

# Create the binary directory
mkdir -p ../bin

# Compile the source code
gcc ../lib/task_queue/queue.c ../lib/scheduler/sch.c ../src/main.c -o ../bin/main

