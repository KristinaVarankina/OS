#!/usr/bin/env bash
gcc -D_GNU_SOURCE -lpthread main.c -o main

echo "Near:"
time ./main 1
echo "Far:"
time ./main 20