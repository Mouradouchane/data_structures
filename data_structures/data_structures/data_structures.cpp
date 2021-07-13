#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "singly_LinkedList.hpp"
#include "doubly_LinkedList.hpp"
#include "circly_singly_LinkedList.hpp"

using namespace linkedlist;

int main() {

    doubly_LinkeList<int> firstOne;

    firstOne.push_front(60);
    firstOne.push_front(3);
    firstOne.push_front(6);


    firstOne.sort();

    firstOne.showAll();
    std::cout << firstOne.length() << std::endl;

    return 0;
}

