#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <set>

#include "btree.h"
const long kMinInteger = 1000000;
const long kMaxInteger = 100000000;

void findBtree(size_t size = 40) {
    auto b = btree<long>{size};
    auto s = std::set<long>{};

    std::ifstream infile("randNums.txt");
    long num;
    while (infile >> num) {
        auto result = b.insert(num);
        if (result.second) {
            s.insert(num);
        }
    }

    for (auto i = kMinInteger; i <= kMaxInteger; ++i) {
        auto foundInTree = (b.find(i) != b.end());
        auto foundInSet = (s.find(i) != s.end());
        if (foundInTree != foundInSet) {
            std::cout << "FAILED - btree and set don't contain the same data!" << "\n";
            std::cout << "Mismatch at element: " << i << "\n";
            break;
            // return false;
        }
    }
}

void printTree(const btree<int> &b) {
    for(auto iter = b.cbegin(); iter != b.cend(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << '\n';
}
void printForwards(const btree<int> &b) {
    std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
void printForwardsAndBack(const btree<int> &b) {
    auto iter = b.begin();
    while(iter != b.end()) {
        std::cout << *iter << " ";
        ++iter;
    }
    --iter;
    std::cout << *iter << " ";
    --iter;
    std::cout << *iter << " ";
    --iter;
    std::cout << *iter << " ";
    --iter;
    std::cout << *iter << "\n";
}
void printBackwards(const btree<int> &b) {
    auto iter = b.rbegin();
    while(iter != b.rend()) {
        std::cout << *iter << " ";
        ++iter;
    }
    std::cout<<'\n';
}
void printBackwardsAndForward(const btree<int> &b) {
    auto iter = b.rbegin();
    while(iter != b.rend()) {
        std::cout << *iter << " ";
        ++iter;
    }
    --iter;
    std::cout << *iter << " ";
    --iter;
    std::cout << *iter << " ";
    --iter;
    std::cout << *iter << " ";
    --iter;
    std::cout << *iter << "\n";
}

void intBtree() {
    auto b = btree<int>{3};
    b.insert(1);
    b.insert(8);
    b.insert(9);
    // b.printRoot();

    std::cout << "numbers:\n";
    for(auto i = 0; i <= 10; ++i) {
        std::cout << i << " ";
        b.insert(i);
    }
    std::cout << '\n';

    std::cout << "printTree:\n";
    printTree(b);
    std::cout << "printForwards:\n";
    printForwards(b);
    std::cout << "printBackwards:\n";
    printBackwards(b);
    std::cout << "printForwardsAndBack:\n";
    printForwardsAndBack(b);
    std::cout << "printBackwardsAndForward:\n";
    printBackwardsAndForward(b);
    std::cout << "operator<<:\n";
    std::cout << b << "\n";
}

void stressTest() {
    std::cout << "\nSTRESS TESTING...\n";
    findBtree(1);
    std::cout << "1 done... maybe get some coffee while you wait :)\n";
    findBtree(99);
    // findBtree(2);
    // findBtree(40);
    std::cout << "...all done\n";
}

void copyControl() {
    auto c = btree<char>{3};
    c.insert('a');
    c.insert('f');
    c.insert('m');

    c.insert('b');
    c.insert('c');
    c.insert('d');
    c.insert('e');

    c.insert('g');
    c.insert('h');
    c.insert('i');
    c.insert('j');
    c.insert('k');
    c.insert('l');
    c.insert('n');
    c.insert('o');
    c.insert('p');
    c.insert('q');
    c.insert('r');
    c.insert('s');
    c.insert('t');
    c.insert('u');
    c.insert('v');
    c.insert('w');
    c.insert('x');
    c.insert('y');
    c.insert('z');

    std::cout << "\nTESTING COPY CONSTRUCTOR:\n";
    std::cout << "Original tree:\n";
    std::cout << c << "\n";

    auto c1 = btree<char>{c};

    std::cout << "Copy contructor tree:\n";
    std::cout << c1 << "\n";

    std::cout << "Inserting new elements into copied tree...\n";
    c1.insert('#');
    c1.insert('1');
    c1.insert('Q');

    std::cout << "New c1 tree:\n";
    std::cout << c1 << "\n";

    std::cout << "Original tree after:\n";
    std::cout << c << "\n";



    std::cout << "\nTESTING COPY ASSIGNMENT:\n";
    auto c2 = btree<char>{};
    c2 = c;

    std::cout << "Copy assignment tree:\n";
    std::cout << c2 << "\n";

    std::cout << "Inserting new elements into copied tree...\n";
    c2.insert(')');
    c2.insert('(');
    c2.insert('(');
    c2.insert('@');
    c2.insert('(');
    c2.insert('0');

    std::cout << "New c2 tree:\n";
    std::cout << c2 << "\n";

    std::cout << "Original tree after:\n";
    std::cout << c << "\n";
}

void moveControl() {
    auto c = btree<char>{3};
    c.insert('a');
    c.insert('f');
    c.insert('m');

    c.insert('b');
    c.insert('c');
    c.insert('d');
    c.insert('e');

    c.insert('g');
    c.insert('h');
    c.insert('i');
    c.insert('j');
    c.insert('k');
    c.insert('l');
    c.insert('n');
    c.insert('o');
    c.insert('p');
    c.insert('q');
    c.insert('r');
    c.insert('s');
    c.insert('t');
    c.insert('u');
    c.insert('v');
    c.insert('w');
    c.insert('x');
    c.insert('y');
    c.insert('z');

    std::cout << "\nTESTING MOVE CONSTRUCTOR:\n";
    std::cout << "Original tree:\n";
    std::cout << c << "\n";

    auto c1 = std::move(c);

    std::cout << "Original tree after move:\n";
    std::cout << c << "\n";

    std::cout << "Move contructor tree:\n";
    std::cout << c1 << "\n";

    std::cout << "Checking you can still insert into original tree... after insert:\n";
    c.insert('#');
    c.insert('1');
    c.insert('Q');
    std::cout << c << "\n";

    std::cout << "\nTESTING MOVE ASSIGNMENT:\n";
    std::cout << "Moving c1 into c2:\n";
    auto c2 = btree<char>{};
    c2 = std::move(c1);

    std::cout << "Move constructor tree (c1) after move:\n";
    std::cout << c1 << "\n";

    std::cout << "Move assignment tree (c2) after move:\n";
    std::cout << c2 << "\n";

    std::cout << "Inserting new elements into moved tree...\n";
    c2.insert(')');
    c2.insert('(');
    c2.insert('(');
    c2.insert('@');
    c2.insert('(');
    c2.insert('0');

    std::cout << "New c2 tree:\n";
    std::cout << c2 << "\n";
}

void stdDistance() {
    btree<int> b{3};
    b.insert(66);
    b.insert(1);
    b.insert(20);
    b.insert(40);
    b.insert(0);
    std::cout << "distance(first, last) = "
              << std::distance(b.begin(), b.end()) << '\n'
              << "distance(last, first) = undefined, since it's not a random-access iterator...\n";
}

int main(void) {
    intBtree();
    stressTest();
    copyControl();
    moveControl();
    stdDistance();
    return 0;
}
