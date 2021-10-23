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

#include "trees/dynamic_tree.hpp"

using namespace linkedlist;
using namespace stacks;
using namespace queue;
using namespace hash_tables;
using namespace trees;

int main() {
   
    dynamic_tree<int> dt("rot", 100);
    
    
    dt.addNode("rtx", 55);
    dt.addNode("gtx", 55);
 
    dt.move_to("rtx");
    std::cout << dt.getName() << '\n';

    dt.addNode("child_1", 10);
    dt.addNode("child_2", 20);

    dt.move_to("child_1");

    dt.move_to("parent");
    std::cout << dt.getName() << '\n';

    return 0;

}
