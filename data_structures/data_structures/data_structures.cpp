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

using namespace linkedlist;
using namespace stacks;
using namespace queue;

int main() {
   
    static_queue<int> qe(4);
   
    qe.add(4);
    qe.add(8);
    qe.add(12);
    qe.add(18);
    qe.add(20);

    qe.print();

    qe.remove();
    qe.remove();
    qe.remove();
  

    qe.print();

    std::cout << qe.length() << '\n';
    std::cout << '\n';

    return 0;
}

