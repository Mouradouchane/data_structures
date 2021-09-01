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
#include "hash tables/key_value_linkedlist.hpp"

using namespace linkedlist;
using namespace stacks;
using namespace queue;

using namespace hash_tables;
using namespace key_value_linkedlist;

int main() {
   
    hash_table<std::string,int> hasht(14);

    hasht.set("gx", 14);
    hasht.set("grey",16);
    hasht.set("re",8);
    hasht.set("sara",4);
    hasht.set("tvr",20);
    hasht.set("name",10);
    hasht.set("getl",7);
    hasht.set("rx7",2);
    hasht.set("ddl",1);
    hasht.set("stl",-14);
    
    hasht.print();
    
    std::cout << "table length \t" << hasht.length() << '\n';
    std::cout << "table size \t" << hasht.size() << '\n';
   
    std::cout << hasht.get("gx") << '\n';
    std::cout << hasht.get("name") << '\n';
    std::cout << hasht.get("avl") << '\n';
    std::cout << hasht.get("ddc") << '\n';
    std::cout << hasht.get("sara") << '\n';

   
    return 0;
}

