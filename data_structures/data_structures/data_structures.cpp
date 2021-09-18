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
   
    DP_hash_table<int> hasht(14);
    
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

    std::pair<std::string,int> gpr = hasht.getPair("rsssd");

    /*
    */
    std::pair<std::string, int> arr[12] = {
            hasht.getPair("gx") ,
            hasht.getPair("getl") ,
            hasht.getPair("rx7")  ,
            hasht.getPair("ddl")  ,
            hasht.getPair("grey") ,
            hasht.getPair("gta")  ,
            hasht.getPair("yty")  ,
            hasht.getPair("rzae") ,
            hasht.getPair("tsqr") ,
            hasht.getPair("zxy")  ,
            hasht.getPair("sara") ,
            hasht.getPair("name")
    };

    for (std::pair<std::string, int> pr : arr) {
        std::cout << pr.first << " : " << pr.second << '\n';
    }

    return 0;
}

