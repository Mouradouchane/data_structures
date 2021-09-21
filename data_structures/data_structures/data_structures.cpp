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
   
    C_hash_table<int> chash(25);

    DP_hash_table<int> hasht(14);
    
    /*
    hasht.set("gx", 14);
    hasht.set("grey",16);
    hasht.set("rzae",8);
    hasht.set("tsqr",20);
    hasht.set("sara",4);
    hasht.set("name",10);
    hasht.set("gta",20);
    hasht.set("yty",30); //
    hasht.set("zxy",40);
    hasht.set("getl",7); 
    hasht.set("rx7",2);  
    hasht.set("ddl",1); 

    hasht.print();

    hasht.replace("gx" , 2021);
    hasht.replace("getl", 2021);
    hasht.replace("ddl", 2021);
    hasht.replace("rx7", 2021);
    hasht.replace("grey", 2021);
    hasht.replace("gta" , 2021);
    hasht.replace("yty" , 2021);
    hasht.replace("rzae" , 2021);
    hasht.replace("tsqr" , 2021);
    hasht.replace("zxy" , 2021);
    hasht.replace("sara" , 2021);
    hasht.replace("name" , 2021);
    hasht.print();

    */

    return 0;
}

