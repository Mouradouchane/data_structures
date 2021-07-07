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

    firstOne.push_back(66);
    firstOne.push_back(88);
    firstOne.push_back(99);
    firstOne.push_back(100);

    //firstOne.clear();
    std::cout << firstOne.has(66) << '\n';
    std::cout << firstOne.has(88) << '\n';
    std::cout << firstOne.has(77) << '\n';

    firstOne.showAll();

    return 0;
}

