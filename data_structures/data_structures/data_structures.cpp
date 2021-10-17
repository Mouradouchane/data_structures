#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include "linkedlists/singly_LinkedList.hpp"
#include "linkedlists/doubly_LinkedList.hpp"
#include "linkedlists/circly_singly_LinkedList.hpp"

#include "stacks/dynamic_stack.hpp"
#include "stacks/static_stack.hpp"

#include "queues/static_queue.hpp"
#include "queues/dynamic_queue.hpp"

#include "hash tables/hash_table.hpp"
#include "hash tables/hash_table_openAddressing.hpp"
#include "hash tables/key_value_linkedlist.hpp"
#include "hash tables/hash_table_chaining.hpp"

using namespace linkedlist;
using namespace stacks;
using namespace queue;
using namespace hash_tables;

int main() {
   
    std::vector<int> r = { 1,4,8 };

    r.insert(r.begin()+2, 6);
  
    for (int e : r) {
        std::cout << e << '\n';
    }


    return 0;
}

