#include <vector>

#pragma once

namespace trees{
    
    // =======================================
    // ======= Binary tree Nodes Class =======
    // =======================================
    template<typename t> class BT_Node{
	  	
		private:
			// index's
			unsigned int parent = NULL;	
			// children 
            unsigned int left;  	
           	unsigned int right;

        public:
            t value;

            // default constructor
            BT_Node(t node_value):value(node_value){ 
				//value = node_value;
			}

			// destructor
			~BT_Node(){ }
 
    };


	template<typename t> class BinaryTree{
	
		private:
			unsigned int len = 0;
			unsigned int size = 0;
			bool fixed_size = false;

			// all nodes in should be here in this vector
			std::vector<t> nodes;
	
		public:
			/*
				=== constructors ===
			*/

			// for 'dynamic' size 
			BinaryTree(t root_value){
				// insert root & update length  
				nodes.push_back(root_value);
				len += 1;
			}

			// for 'static'  size 
			BinaryTree(t root_value , unsigned int tree_size):fixed_size(true),size(tree_size){
				// insert root & update length  
				nodes.push_back(root_value);
				len += 1;
			}

			// destructor
			~BinaryTree(){ }

			/*
				=== methods ===
			*/

			unsigned int length(){
				return this->len;
			}

			bool insert(t const &new_value){}

			bool search_up(t const &target){}
			bool search_down(t const &target){}

			bool remove(t const &target){}
			bool remove(unsigned int const index){}

			bool move_up(){}

			bool move_down(t const &target){}
			bool move_down(unsigned int const &index){}

			bool travle_up(std::vector<t> &full_path){}
			bool travle_down(std::vector<t> &full_path){}

			BinaryTree<t> get_sub_tree(unsigned int const &index){}

			bool is_perfect(){}

	};


}
