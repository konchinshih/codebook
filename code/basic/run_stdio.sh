#!/bin/bash

g++ -std=c++17 -O2 -Wall -Wextra -g -fsanitize=undefined,address $1
echo DONE COMPILE
./a.out

