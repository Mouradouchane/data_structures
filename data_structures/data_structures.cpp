#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

class folder {

public:
    std::string fname = "";
    float fsize = 0;

    folder() {
    }
    folder(std::string foldername, float foldersize) : fname{ foldername }, fsize{ foldersize } {
    }

    ~folder() { }

    void print_data() {
        std::cout << "folder data\n";
        std::cout << "name : " << fname << '\n';
        std::cout << "size : " << fsize << '\n';
    }
};

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
using namespace cpstl;

void test(DT_Node<int> node , int index){
    if(index != -1){
    std::cout << "(" << node.children[index].name <<":"<< node.children[index].value << ")" <<  " " << index << '\n';
    }
    else {
        std::cout << "not found !\n";
    }
}

int main() {

    DynamicTree<int> dt("root",1);
    if(!dt.current_node->insert("a3",1)) std::cout << "insert error !!! \n";
    if(!dt.current_node->insert("a2",2)) std::cout << "insert error !!! \n";
    dt.go_to("a3");
    if(!dt.current_node->insert("g2",3)) std::cout << "insert error !!! \n";
    if(!dt.current_node->insert("g4",4)) std::cout << "insert error !!! \n";
    dt.go_to("g2");
    if(!dt.current_node->insert("ab4",4)) std::cout << "insert error !!! \n";
    if(!dt.current_node->insert("ab5",5)) std::cout << "insert error !!! \n";

    /*
    dt.go_to("ab4");
    DT_Node<int>* p = dt.current_node;
    dt.go_to("g2",true);
    */

    //dt.current_node->removeChildren();
 
    if(dt.go_to_root()) std::cout << "moved to root sucessed !\n";

    std::vector<std::string> path = {"a3","g4"};

    if(dt.go_to( "a3" )) std::cout << "travle sucessed !\n";
    else  std::cout << "travle unsucessed !\n";
    
    std::cout << dt.current_node->name << " " << dt.current_node->value << "\n";

    dt.current_node->removeChildren();

    if(dt.go_to_root()) std::cout << "moved to root sucessed !\n";

    if(dt.travel_to( path )) std::cout << "travle sucessed !\n";
    else  std::cout << "travle unsucessed !\n";
    
    std::cout << dt.current_node->name << " " << dt.current_node->value << "\n";

    return 0;
}
