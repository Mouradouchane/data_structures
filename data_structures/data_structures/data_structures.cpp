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

    firstOne.remove_first();
    firstOne.remove_first();
    
    firstOne.showAll();
    std::cout << firstOne.getLastValue() << std::endl;

    return 0;
}

