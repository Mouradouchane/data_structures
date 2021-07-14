#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "singly_LinkedList.hpp"
#include "doubly_LinkedList.hpp"
#include "circly_singly_LinkedList.hpp"

using namespace linkedlist;

int main() {

    circly_singly_LinkedList<int> linkedList_A;
    linkedList_A.push_back(4);
    /*
    linkedList_A.push_back(3);
    linkedList_A.push_back(45);
    */

    circly_singly_LinkedList<int> linkedList_B;
    linkedList_B.push_back(2);
    /*
    linkedList_B.push_back(1);
    linkedList_B.push_back(10);
    */
    
    std::vector<int> testV = {};

    linkedList_A += linkedList_B;

    c_node<int> Af = linkedList_A.getFirstElement();
    c_node<int> Al = linkedList_A.getLastElement();

    linkedList_A.showAll();
    std::cout << "first  : " << linkedList_A.getFirstValue() << std::endl;
    std::cout << "last   : " << linkedList_A.getLastValue() << std::endl;
    std::cout << "length : " << linkedList_A.length() << std::endl;


    return 0;
}

