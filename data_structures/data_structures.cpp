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
#include "trees/binary_tree.hpp"

using namespace linkedlist;
using namespace stacks;
using namespace queue;
using namespace hash_tables;
using namespace trees;

        /*
            ===> just cpp file for testing 
        */

int main() {

    DynamicTree<int> dt("root",1);
    if(!dt.current_node->insert("a2",2)) std::cout << "insert error !!! \n";
    if(!dt.current_node->insert("a3",1)) std::cout << "insert error !!! \n";
    dt.go_to("a2");
    if(!dt.current_node->insert("a4",2)) std::cout << "insert error !!! \n";
    if(!dt.current_node->insert("a5",2)) std::cout << "insert error !!! \n";

    dt.current_node->removeChildren();
    dt.go_to("a5");
    std::cout << '[' << dt.current_node->name << ']' << '\n';

    std::cout << "press anything to exit : "; std::cin.get();
    return 0;
}
