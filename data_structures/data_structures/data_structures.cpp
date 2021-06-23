#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "singly_Linked_List.hpp"

using namespace singlyLinkedList;

int main() {

    singly_linkedList<int> firstOne;

    firstOne.push_back(14);
    firstOne.push_back(77);
    firstOne.push_back(88);
    firstOne.push_back(99);
    
    firstOne.showAll();

    firstOne.clear();

    firstOne.push_back(5);
    firstOne.push_back(9);

    firstOne.showAll();

    return 0;
}

