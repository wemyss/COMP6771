g++ -std=c++14 -Wall -Werror -pedantic -O2 -o bigtest2 bigtest2.cpp
./bigtest2 > bigtest.txt
./bigtest.pl
diff bigtest0.txt bigtest1.txt
