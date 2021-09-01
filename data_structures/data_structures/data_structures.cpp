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

#include "hash tables/hash_table.hpp"
#include "hash tables/key_value_linkedlist.hpp"

using namespace linkedlist;
using namespace stacks;
using namespace queue;

using namespace hash_tables;
using namespace key_value_linkedlist;

int main() {
   
    hash_table<int> hasht(14);

    hasht.set(14);
    hasht.set(16);
    hasht.set(8);
    hasht.set(4);
    hasht.set(20);
    hasht.set(10);
    hasht.set(7);
    hasht.set(2);

    hasht.print();

    std::cout << "table length \t" << hasht.length() << '\n';
    std::cout << "table size \t" << hasht.size() << '\n';
   
    return 0;
}

