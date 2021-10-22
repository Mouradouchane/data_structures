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
   
    dynamic_tree<int> dt("rt", 100);

    dt.addNode("rtx", 55);
    dt.addNode("rtx", 55);
    dt.addNode("gtx", 55);
  
    dt.print();

    dt.move_to("rtx");
    dt.addNode("child of rtx 1", 10);
    dt.addNode("child of rtx 2", 20);
    dt.addNode("child of rtx 1", 30);

    dt.move_to("child of rtx 1");
    dt.print();

    return 0;

}
