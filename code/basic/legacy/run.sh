#!/bin/bash

g++ -std=c++17 -O2 -g -fsanitize=undefined,address "$1" && echo DONE COMPILE || exit 1

if [[ $2 == "-stdio" ]]; then
    echo ===== RUN =====
    ./a.out
else
    for input in testcases/*.in; do
        id=${input%.in}
        echo ===== INPUT =====
        cat $input
        echo ===== STDERR =====
        ./a.out <$input >$id.ot
        echo ===== OUTPUT =====
        cat $id.ot
    done
fi
