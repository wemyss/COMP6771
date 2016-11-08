#!/bin/bash

clear

rm tests/Graph.h
rm tests/Graph.tem
cp Graph.h tests/Graph.h
cp Graph.tem tests/Graph.tem

FILES=tests/test*.cpp

for test_file in $FILES
do
    result_file="$(echo "$test_file" | sed 's/\/test/\/result/' | sed 's/cpp/txt/')"
    out_file="$(echo "$test_file" | sed 's/test?s/out/' | sed 's/cpp/txt/')"
    echo "Test: $test_file Result: $result_file"
    g++ -std=c++14 -Wall -Werror -O2 "$test_file" || exit
    ./a.out > "$out_file"
    (diff -y "$out_file" "$result_file" > .diff && echo "PASSED") || (echo "FAILED"; cat .diff; exit)
    rm ./a.out
done
