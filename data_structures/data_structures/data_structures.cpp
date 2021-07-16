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

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.print();

    stack.pop();
    stack.pop();
    stack.pop();
    stack.print();

    stack.push(8);
    stack.push(6); 
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    return 0;
}

