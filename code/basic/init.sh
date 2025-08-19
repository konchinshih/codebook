#!/bin/bash

for c in {A..K}; do
    mkdir -p $c/testcases
    if [ ! -s $c/$c.cpp ]; then
        cp template.cpp $c/$c.cpp
        cp run.sh $c/run.sh
        cp run_stdio.sh $c/run_stdio.sh
    fi
done
