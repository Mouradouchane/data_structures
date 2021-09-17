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
   
    //hash_table<int> lphasht(14);
    QP_hash_table<int> lphasht(14);
    
    lphasht.set("gx", 14);
    lphasht.set("grey",16);
    lphasht.set("rzae",8);
    lphasht.set("tsqr",20);
    lphasht.set("sara",4);
    lphasht.set("name",10);
    lphasht.set("gta",20);
    lphasht.set("yty",30); //
    lphasht.set("zxy",40);
    lphasht.set("getl",7); 
    lphasht.set("rx7",2);  
    lphasht.set("ddl",1); 

    lphasht.print();

    lphasht.replace("gx", 2021);
    lphasht.replace("grey",  2021);
    lphasht.replace("rzae", 2021);
    lphasht.replace("tsqr",  2021);
    lphasht.replace("sara", 2021);
    lphasht.replace("name",  2021);
    lphasht.replace("gta", 2021);
    lphasht.replace("yty", 2021); //
    lphasht.replace("zxy", 2021);
    lphasht.replace("getl", 2021);
    lphasht.replace("rx7", 2021);
    lphasht.replace("ddl", 2021);

    lphasht.print();

    return 0;
}

