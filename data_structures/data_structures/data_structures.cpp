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
    QP_hash_table<std::string, int> lphasht(14, -1);
    
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

    lphasht.remove("gfsfdx");
    lphasht.remove("grey");
    lphasht.remove("rqsfqsfzae");
    lphasht.remove("tsqr");
    lphasht.remove("safqsfra");
    lphasht.remove("nsdfdfsdfame");
    lphasht.remove("gsdfsdfta");
    lphasht.remove("yty");
    lphasht.remove("zxy");
    lphasht.remove("getl");
    lphasht.remove("rx7");
    lphasht.remove("dfqsfqsdl");

    lphasht.print();

    return 0;
}

