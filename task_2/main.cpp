#include "sort.h"
#include <iostream>

namespace {
struct A1 {};

struct A2 : A1 {};

struct A3 : A1 {};

struct B1 {};

struct B2 : B1 {};

struct B3 : B1 {};

struct B4 : B2 {};

struct B5 : B2 {};

struct B6 : B2, B3 {};

struct B7 : B4, B6 {};
}

int main() {
    using namespace top_sort;
    // A2, A3, A1, B7, B4, B5, B6, B2, B3, B1
    std::cout << typeid(SortT<TypeList<A1, A2, A3, B1, B2, B3, B4, B5, B6, B7>>).name();
    return EXIT_SUCCESS;
}
