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
   
    C_hash_table<int> chash(24);

    //DP_hash_table<int> dhash(14);
    
    chash.set("gx", 14);
    chash.set("grey",16);
    chash.set("rzae",8);
    chash.set("tsqr",20);
    chash.set("sara",4);
    chash.set("name",10);
    chash.set("gta",20);
    chash.set("yty",30); 
    chash.set("zxy",40);
    chash.set("getl",7); 
    chash.set("rx7",2); 
    chash.set("gcc",1);
    /*
    hasht.print();
    */

    chash.replace("gx" , 2021);
    chash.replace("getl", 2021);
    chash.replace("ddlzddaz", 2021);
    chash.replace("rx7", 2021);
    chash.replace("grey", 2021);
    chash.replace("gta" , 2021);
    chash.replace("yty" , 2021);
    chash.replace("rzae" , 2021);
    chash.replace("tsqr" , 2021);
    chash.replace("zxy" , 2021);
    chash.replace("sara" , 2021);
    chash.replace("name" , 2021);


    chash.print();

    return 0;
}

