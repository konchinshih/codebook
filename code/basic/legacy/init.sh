#!/bin/bash

for c in {A..P}; do
    mkdir -p $c/testcases
    if [ ! -s $c/$c.cpp ]; then
        cp template.cpp $c/$c.cpp
        cp run.sh $c/run.sh
    fi
done
