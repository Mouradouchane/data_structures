#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "linkedlists/singly_LinkedList.hpp"
#include "linkedlists/doubly_LinkedList.hpp"
#include "linkedlists/circly_singly_LinkedList.hpp"

#include "stacks/dynamic_stack.hpp"
#include"stacks/static_stack.hpp"

using namespace linkedlist;
using namespace stacks;

int main() {
    
    //dynamic_stack<int> stack;
    static_stack<int> stack(4);
    
    stack.print();

    stack.peek();

    std::cout << "EMPTY : " << stack.isEmpty() << '\n';
    std::cout << "FULL  : " << stack.isFull() << '\n';

    return 0;
}

