#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "linkedlists/singly_LinkedList.hpp"
#include "linkedlists/doubly_LinkedList.hpp"
#include "linkedlists/circly_singly_LinkedList.hpp"

#include "stacks/dynamic_stack.hpp"

using namespace linkedlist;
using namespace stacks;

int main() {
    
    dynamic_stack<int> stack;
    /*
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    */

    
    stack.print();

    std::cout << "search : " << stack.search(3) << '\n';
    std::cout << "search : " << stack.search(39) << '\n';

    return 0;
}

