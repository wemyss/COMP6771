#!/bin/sh

#cp "Graph.h" ./tests
#cp "Graph.tem" ./tests

#cd tests
file="testResult.txt"

for i in *.cpp;
do
    name="${i%%.*}"
    echo $name
    g++ -std=c++14 -Wall -Werror -O2 -o test $i
    ./test > $file
    if cmp -s "$file" "filename"
    then
        echo "The files match"
    else
        echo "The files are different"
    fi
done

#rm "Graph.h" "Graph.tem"
#cd ..
rm test
