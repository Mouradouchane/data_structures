#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "singly_LinkedList.hpp"
#include "doubly_LinkeList.hpp"

using namespace linkedlist;

int main() {

    doubly_LinkeList<int> firstOne;

    firstOne.push_back(11);
    firstOne.push_back(44);
    firstOne.push_back(77);
    firstOne.push_back(88);
    firstOne.push_back(99);

    std::cout << firstOne.length() << '\n';
    firstOne.showAll();

    return 0;
}

