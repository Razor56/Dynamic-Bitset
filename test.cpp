/*
test the bitset.cpp

types of test:
- test the constructor
- test the resize
- test the set
- test the get
- test the op_and
- test the op_or
- test the op_xor
- test the popcount
- test the ffs

use different functions to test the bitset.cpp
- test the constructor
- test the resize
- test the set
- test the get
- test the op_and
- test the op_or
- test the op_xor
- test the popcount
- test the ffs
*/
#include <cassert>
#include <iostream>
#include "bitset.cpp"

void test_constructor() {
    DynamicBitset bs0;
    assert(bs0.size() == 0);

    DynamicBitset bs10(10);
    assert(bs10.size() == 10);
    for (size_t i = 0; i < 10; ++i) {
        assert(!bs10.get(i));
    }

    DynamicBitset bs64(64);
    assert(bs64.size() == 64);

    DynamicBitset bs65(65);
    assert(bs65.size() == 65);

    std::cout << "test_constructor: passed\n";
}

void test_resize() {
    DynamicBitset bs(10);
    bs.set(3, true);
    bs.resize(20);
    assert(bs.size() == 20);
    assert(bs.get(3));
    assert(!bs.get(19));

    bs.resize(5);
    assert(bs.size() == 5);
    assert(bs.get(3));
    assert(!bs.get(5));

    DynamicBitset bs2(100);
    bs2.set(99, true);
    bs2.resize(50);
    assert(bs2.size() == 50);
    assert(!bs2.get(99));

    std::cout << "test_resize: passed\n";
}

void test_set() {
    DynamicBitset bs(10);
    bs.set(0, true);
    assert(bs.get(0));
    bs.set(0, false);
    assert(!bs.get(0));

    bs.set(9, true);
    assert(bs.get(9));

    bs.set(10, true);
    assert(bs.size() == 10);
    assert(!bs.get(10));

    std::cout << "test_set: passed\n";
}

void test_get() {
    DynamicBitset bs(128);
    for (size_t i = 0; i < 128; i += 17) {
        bs.set(i, true);
    }
    for (size_t i = 0; i < 128; ++i) {
        assert(bs.get(i) == (i % 17 == 0));
    }
    assert(!bs.get(128));

    std::cout << "test_get: passed\n";
}

void test_op_and() {
    DynamicBitset a(8);
    DynamicBitset b(8);
    a.set(0, true);
    a.set(1, true);
    a.set(2, true);
    b.set(0, true);
    b.set(2, true);
    b.set(3, true);
    a.op_and(b);
    assert(a.get(0));
    assert(!a.get(1));
    assert(a.get(2));
    assert(!a.get(3));
    assert(a.popcount() == 2);

    DynamicBitset c(100);
    DynamicBitset d(50);
    c.set(10, true);
    c.set(60, true);
    d.set(10, true);
    c.op_and(d);
    assert(c.get(10));
    assert(!c.get(60));

    std::cout << "test_op_and: passed\n";
}

void test_op_or() {
    DynamicBitset a(8);
    DynamicBitset b(8);
    a.set(1, true);
    b.set(2, true);
    a.op_or(b);
    assert(!a.get(0));
    assert(a.get(1));
    assert(a.get(2));

    std::cout << "test_op_or: passed\n";
}

void test_op_xor() {
    DynamicBitset a(8);
    DynamicBitset b(8);
    a.set(0, true);
    a.set(1, true);
    b.set(0, true);
    b.set(2, true);
    a.op_xor(b);
    assert(!a.get(0));
    assert(a.get(1));
    assert(a.get(2));

    std::cout << "test_op_xor: passed\n";
}

void test_popcount() {
    DynamicBitset bs(100);
    assert(bs.popcount() == 0);

    bs.set(0, true);
    bs.set(63, true);
    bs.set(64, true);
    bs.set(99, true);
    assert(bs.popcount() == 4);

    std::cout << "test_popcount: passed\n";
}

void test_ffs() {
    DynamicBitset bs(100);
    assert(bs.ffs() == -1);

    bs.set(5, true);
    assert(bs.ffs() == 5);

    bs.set(0, true);
    assert(bs.ffs() == 0);

    bs.set(70, true);
    bs.set(0, false);
    bs.set(5, false);
    assert(bs.ffs() == 70);

    std::cout << "test_ffs: passed\n";
}

int main() {
    test_constructor();
    test_resize();
    test_set();
    test_get();
    test_op_and();
    test_op_or();
    test_op_xor();
    test_popcount();
    test_ffs();
    std::cout << "All tests passed.\n";
    return 0;
}
