#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "singly_Linked_List.hpp"

using namespace singlyLinkedList;

int main() {

    linkedList<int> firstOne;

    firstOne.push_back(14);
    firstOne.push_back(77);
    firstOne.push_back(88);
    firstOne.push_back(99);

    //std::cout << "===================" << std::endl;

    std::vector<int> lints = firstOne.toVector();
    int *arr = firstOne.toArray();
    
    for (int x = 0; x < firstOne.length(); x += 1 ) {
        std::cout << *(arr + x) << std::endl;
    }


    return 0;
}

