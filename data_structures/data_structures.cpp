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

int main() {

    binary_node<int> root(1);
    root.left  = new binary_node<int>(2);
    root.right = new binary_node<int>(3);

    root.left->left->value = 44;

    std::cout << root.value <<" "<< root.left->value <<" "<<  root.right->value << '\n';
    std::cout << root.left->left->value << '\n';

    return 0;

}
