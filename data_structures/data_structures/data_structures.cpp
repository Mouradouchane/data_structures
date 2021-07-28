#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "linkedlists/singly_LinkedList.hpp"
#include "linkedlists/doubly_LinkedList.hpp"
#include "linkedlists/circly_singly_LinkedList.hpp"

#include "stacks/dynamic_stack.hpp"
#include "stacks/static_stack.hpp"

#include "queues/static_queue.hpp"
#include "queues/dynamic_queue.hpp"

using namespace linkedlist;
using namespace stacks;
using namespace queue;

int main() {
   
    static_queue<int> sq(4);
    dynamic_queue<int> dq;
    
    dq.push(4);

    std::cout << dq.isEmpty();
   
    return 0;
}

