#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "singly_Linked_List.hpp"

using namespace singlyLinkedList;

int main() {

    linkedList<int> firstOne;
    linkedList<std::string> names;
    linkedList<float> floats;

    firstOne.push_back(14);
    firstOne.push_back(16);

    floats.push_back(1.44);
    floats.push_back(5.44);
    floats.push_back(1.99f);
    floats.push_back(-14.9909);


    firstOne.showAll();
    floats.showAll();

    return 0;
}

