#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "singly_LinkedList.hpp"
#include "doubly_LinkedList.hpp"
#include "circly_singly_LinkedList.hpp"

using namespace linkedlist;

int main() {

    circly_singly_linkedList<int> firstOne;

    firstOne.push_back(11);
    firstOne.push_back(66);

    firstOne.clear();
    //std::cout << fst.value << '\n';

    firstOne.showAll();

    return 0;
}

