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

void test(DynamicTree_Node<int> node , int index){
    if(index != -1){
    std::cout << "(" << node.children[index].name <<":"<< node.children[index].value << ")" <<  " " << index << '\n';
    }
    else {
        std::cout << "not found !\n";
    }
}

int main() {
    
    DynamicTree<int> dt("root",1);
    dt.current_node->insert("a3",1);
    dt.current_node->insert("a5",2);
    dt.current_node->insert("g2",3);
    dt.current_node->insert("b2",4);
    dt.current_node->insert("ab2",5);

    int idx1 = 0 , idx2 = 0 , idx3 = 0 , idx4 = 0;

    dt.current_node->print();

    dt.current_node->search("g2", idx1);
    dt.current_node->search("ab2", idx2);
    dt.current_node->search("b2", idx3);
    dt.current_node->search("a3", idx4);
    
    test(*dt.current_node,idx1);
    test(*dt.current_node,idx2);
    test(*dt.current_node,idx3);
    test(*dt.current_node,idx4);

    /*
    dt.current_node->print();
    dt.current_node->sort();
    dt.current_node->print();
    */

    return 0;
}
