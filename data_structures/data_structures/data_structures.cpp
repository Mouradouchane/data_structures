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

using namespace linkedlist;
using namespace stacks;
using namespace queue;

using namespace hash_tables;
using namespace key_value_linkedlist;

int main() {
   
    //hash_table<std::string,int> hasht(14,-1);
    LP_hash_table<std::string, int> lphasht(2, -1);
    
    lphasht.set("gx", 14);
    lphasht.set("grey",16);
    lphasht.set("rzae",8);
    lphasht.set("tsqdvr",20);
    lphasht.set("sara",4);
    lphasht.set("name",10);
    
    /*
    hasht.set("getl",7);
    hasht.set("rx7",2);
    hasht.set("ddl",1);
    hasht.set("gxx",-14);
    hasht.set("erze", -14);
    hasht.set("stazel", -14);
    hasht.set("fsdftl", -14);
    hasht.set("taazel", -14);
    */
    
    lphasht.print();

    lphasht.clear();

    lphasht.print();

    return 0;
}

