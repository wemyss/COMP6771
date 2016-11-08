#include <iostream>
#include <vector>
#include <list>
#include <cassert>

#include "EuclideanVector.h"


void testFriends() {
    using namespace evec;

    EuclideanVector a {1,2,3,4};
    EuclideanVector b {4,3,2,1};
    EuclideanVector c {1,1};
    EuclideanVector d {1,2,3,4,5};
    EuclideanVector e;
    EuclideanVector f {1,2,3,4};
    bool allPassed = true;

    if (a != a) {
        std::cout << "error: a != a\n";
        allPassed = false;
    }
    if (a == b) {
        std::cout << "error: a == b\n";
        allPassed = false;
    }
    if (a != f) {
        std::cout << "error: a != f\n";
        allPassed = false;
    }
    if (a == c) {
        std::cout << "error: a == c\n";
        allPassed = false;
    }
    if (d == a) {
        std::cout << "error: d == a\n";
        allPassed = false;
    }
    if (d == c) {
        std::cout << "error: d == c\n";
        allPassed = false;
    }
    if (e == c) {
        std::cout << "error: e == c\n";
        allPassed = false;
    }
    if (a+b != b+a) {
        std::cout << "error: a+b != b+a\n";
        allPassed = false;
    }

    if (allPassed) {
        std::cout << "All friend tests PASSed!!\n";
    }
}

int main() {

    testFriends();
    evec::EuclideanVector a(2);

	std::list<double> l {1,2,3};
	evec::EuclideanVector b{l.begin(),l.end()};

	std::vector<double> v2 {4,5,6,7};
	evec::EuclideanVector c{v2.begin(),v2.end()};

	std::vector<double> a1 {5,4,3,2,1};
	evec::EuclideanVector d{a1.begin(),a1.end()};

	std::list<double> a2 {9,0,8,6,7};
	evec::EuclideanVector e{a2.begin(),a2.end()};

	// use the copy constructor
	evec::EuclideanVector f{e};

	std::cout << a.getNumDimensions() << ": " << a << std::endl;
	std::cout << "D1:" << b.get(1) << " " << b << std::endl;
	std::cout << c << " Euclidean Norm = " << c.getEuclideanNorm() << std::endl;
	std::cout << d << " Unit Vector: " << d.createUnitVector() << " L = " << d.createUnitVector().getEuclideanNorm() << std::endl;
	std::cout << e << std::endl;
	std::cout << f << std::endl;

	// test the move constructor
	evec::EuclideanVector g = std::move(f);
	std::cout << g << std::endl;
	std::cout << f << std::endl;

	// try operator overloading
	e += d;
	std::cout << e << std::endl;

	evec::EuclideanVector h = e - g;
	std::cout << h * g << std::endl;

	// test scalar multiplication
	h *= 2;
	std::cout << h << std::endl;

	evec::EuclideanVector j = b / 2;
	std::cout << j << std::endl;

	std::cout << "dot product = " << j * b << std::endl;

	if (g == (e - d)) std::cout << "true" << std::endl;
	if (j != b ) std::cout << "false" << std::endl;

	j[0] = 1;
	std::cout << j << std::endl;

	// type cast from EuclideanVector to a std::vector
	std::vector<double> vj = j;

	// type cast from EuclideanVector to a std::vector
	std::list<double> lj = j;

	for (auto d : lj) {
		std::cout << d << std::endl;
	}

	// list initialisation
    evec::EuclideanVector k {1, 2, 3};
    std::cout << k << std::endl;




    using vec=evec::EuclideanVector;

    auto v1 = vec{1, 2, 3}; // move constructor?

    auto v22 = vec{v1}; // copy constructor


    assert(v1 == v22);
    assert((v1 == vec{1, 2, 3}));
    assert((v1 != vec{1, 2, 4}));
    assert((v1 != vec{1, 2}));
    assert((v1 * 10 == vec{10, 20, 30}));
    assert((v1 * -1 == vec{-1, -2, -3}));
    assert((v1 / 2 == vec{0.5, 1.0, 1.5}));
    assert((v1 + vec{5, 7, 9} == vec{6, 9, 12}));
    assert((v1 - vec{5, 7, 9} == vec{-4, -5, -6}));
    // assert(almost_eq(v1.getEuclideanNorm(), sqrt(14)));
    v1[0] = 3;
    // assert(v1[0] == 3 && v1.get(0) == 3);
    std::cout << v1 << '\n';
    // assert(almost_eq(v1.getEuclideanNorm(), sqrt(22)));
    std::cout << v1.getEuclideanNorm() << '\n';
}
