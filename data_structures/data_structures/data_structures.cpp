#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "singly_Linked_List.hpp"

using namespace singlyLinkedList;

int main() {

    linkedList<int> firstOne;

    firstOne.push_back(14);

    firstOne.showAll();
    std::cout << "===================" << std::endl;

    firstOne.push_back(77);

    firstOne.showAll();
    std::cout << "===================" << std::endl;

    firstOne.push_back(88);
    firstOne.push_back(99);

    firstOne.showAll();
    std::cout << "===================" << std::endl;

    return 0;
}

