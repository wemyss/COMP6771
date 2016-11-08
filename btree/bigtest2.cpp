#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "btree.h"

int main(void) {
    btree<long> testContainer(99);
    std::set<long> stableContainer;
    std::ifstream infile("randNums.txt");
    long a;
    while (infile >> a) {
        auto result = testContainer.insert(a);
        if (result.second) {
            stableContainer.insert(a);
        }
    }


    for(auto iter = testContainer.begin(); iter != testContainer.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << '\n';

    for(auto iter = stableContainer.begin(); iter != stableContainer.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << '\n';
    return 0;
}
