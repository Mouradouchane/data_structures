#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "singly_LinkedList.hpp"
#include "doubly_LinkeList.hpp"

using namespace singly_linkedlist;
using namespace doubly_linkedlist;


int main() {

    doubly_LinkeList<int> firstOne;

    firstOne.push_back(11);
    firstOne.push_back(44);
    firstOne.push_back(77);
    firstOne.push_back(88);
    firstOne.push_back(99);

    firstOne.reverse();
    firstOne.showAll();


    return 0;
}

