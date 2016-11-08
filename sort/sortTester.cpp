#include <iostream>
#include <fstream>
#include <random>
#include <thread>

#include "BucketSort.h"

// void getFirstDigitTest() {
//     std::cout << "Testing getFirstDigit()...\n";
//     auto b = BucketSort{};
//     assert(b.getFirstDigit(0) == 0);
//     assert(b.getFirstDigit(1) == 1);
//     assert(b.getFirstDigit(2) == 2);
//     assert(b.getFirstDigit(3) == 3);
//     assert(b.getFirstDigit(4) == 4);
//     assert(b.getFirstDigit(5) == 5);
//     assert(b.getFirstDigit(7) == 7);
//     assert(b.getFirstDigit(8) == 8);
//     assert(b.getFirstDigit(9) == 9);
//     assert(b.getFirstDigit(10) == 1);
//     assert(b.getFirstDigit(11) == 1);
//     assert(b.getFirstDigit(12) == 1);
//     assert(b.getFirstDigit(13) == 1);
//     assert(b.getFirstDigit(14) == 1);
//     assert(b.getFirstDigit(24) == 2);
//     assert(b.getFirstDigit(50) == 5);
//     assert(b.getFirstDigit(100) == 1);
//     assert(b.getFirstDigit(123456789) == 1);
//     assert(b.getFirstDigit(987654321) == 9);
//     assert(b.getFirstDigit(999) == 9);
//     std::cout << "...Well it fucking works!\n";
// }
// void checkSortOrderCorrect() {
//     std::cout << "Testing that all numbers are sorted in correct order!\n";
//     const auto numCores = std::thread::hardware_concurrency();
//     auto multiCoreBucket = BucketSort{};
//     auto singleCoreBucket = BucketSort{};
//     auto controlBucket = BucketSort{};
//
//     const unsigned int million = 1000000;
//     const unsigned int totalNumbers = 10 * million;
//
//     auto mt = std::mt19937{totalNumbers};
//     auto dist = std::uniform_int_distribution<unsigned int>{1, 100 * million};
//
//     for (auto i = 0U; i < totalNumbers; ++i) {
//         auto num = dist(mt);
//         multiCoreBucket.numbersToSort.push_back(num);
//         singleCoreBucket.numbersToSort.push_back(num);
//         controlBucket.numbersToSort.push_back(num);
//     }
//
//     multiCoreBucket.sort(numCores);
//     singleCoreBucket.sort(1);
//     controlBucket.sortOld(0);
//
//     auto mIt = multiCoreBucket.numbersToSort.cbegin();
//     auto sIt = singleCoreBucket.numbersToSort.cbegin();
//     auto cIt = controlBucket.numbersToSort.cbegin();
//
//     while (mIt != multiCoreBucket.numbersToSort.cend() &&
//             sIt != singleCoreBucket.numbersToSort.cend() &&
//             cIt != controlBucket.numbersToSort.cend()) {
//         assert(*mIt == *cIt);
//         assert(*sIt == *cIt);
//         ++mIt;
//         ++sIt;
//         ++cIt;
//     }
//     assert(mIt == multiCoreBucket.numbersToSort.cend());
//     assert(sIt == singleCoreBucket.numbersToSort.cend());
//     assert(cIt == controlBucket.numbersToSort.cend());
//     std::cout << "Multi-core and single-core buckets return the exact same result as the control bucket... All tests PASSED!\n";
// }

int main() {
    // getFirstDigitTest();
    // checkSortOrderCorrect();
    // return 0;
    const unsigned int million = 1000000;

    // const unsigned int totalNumbers = 500000;
    const unsigned int totalNumbers = 50 * million;
    const unsigned int printIndex = 25900;

    // use totalNumbers required as the seed for the random number generator.
    auto mt = std::mt19937{totalNumbers};
    auto dist = std::uniform_int_distribution<unsigned int>{1, 100 * million};

    // create a sort object
    auto pbs = BucketSort{};

    // insert random numbers into the sort object
    for (auto i = 0U; i < totalNumbers; ++i) {
        pbs.numbersToSort.push_back(dist(mt));
    }
    std::cout << "size of numbersToSort: " << pbs.numbersToSort.size() << "\n";

    // call sort giving the number of cores available.
    const auto numCores = std::thread::hardware_concurrency();
    pbs.sort(numCores);

    std::cout << "number of cores used: " << numCores << "\n";

    // print certain values from the buckets
    std::cout << "Demonstrating that all the numbers that start with 1 come first\n";
    std::cout << pbs.numbersToSort[0] << " " << pbs.numbersToSort[printIndex - 10000]
              << " " << pbs.numbersToSort[printIndex] << " " << pbs.numbersToSort[pbs.numbersToSort.size() - 1]
              << "\n";

}
