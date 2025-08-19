#!/bin/bash

g++ -std=c++17 -O2 -Wall -Wextra -g -fsanitize=undefined,address $1
echo DONE COMPILE
for input in testcases/*.in; do
    id=$(basename $input .in)
    echo ===========================
    cat $input
    echo ===========================
    ./a.out < $input 1> testcases/$id.ot
    echo ===========================
    cat testcases/$id.ot
done

