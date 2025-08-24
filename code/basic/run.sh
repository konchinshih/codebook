#!/bin/bash

g++ -std=c++17 -O2 -g -fsanitize=undefined,address $1 && echo DONE COMPILE || exit 1
./a.out
