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

using namespace linkedlist;
using namespace stacks;
using namespace queue;
using namespace hash_tables;
using namespace trees;

int main() {

    dynamic_tree<int> dt("rot", 1);
    dt.current_position->insert("aka", 2);
    dt.move_to("aka");
    dt.current_position->insert("rt", 3);
    dt.move_to("rt");
    dt.current_position->insert("gtt", 4);
    dt.move_to("gtt");
    dt.current_position->insert("dll", 5);

    dt.move_to("root");
    std::vector<std::string> path = {"aka","rt","gtt"};

    std::cout << "start... !" << '\n';

    std::cout << "jumping is ... !" << dt.jump_to( path ) << '\n';
    std::cout << dt.current_position->name << " " << dt.current_position->value << '\n';


    return 0;

}
