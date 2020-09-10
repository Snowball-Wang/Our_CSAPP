#!/bin/bash

# delete tsh.out if it exists
if [ -e tsh.out ]; then
    echo "delete the existing tsh.out..."
    rm tsh.out
fi

# execute make test and append the result
# to tsh.out
number=1
while [ "$number" -le 16 ]; do
    if [ "$number" -lt 10 ]; then
        echo "make test0$number"
        make test0$number >> tsh.out
    else
        echo "make test$number"
        make test$number >> tsh.out
    fi
    let number++
done
