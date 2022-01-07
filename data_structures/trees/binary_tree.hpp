#include <vector>

#pragma once

namespace trees{
    
    // =======================================
    // ======= Binary tree Nodes Class =======
    // =======================================
    template<typename t> class BT_Node{
	  	
		private:
			t parent = NULL;	
			// children 
            t left;  	
           	t right;

        public:
            t value;

            // default constructor
            BT_Node(t node_value ,t lnode_value ,t rnode_value)
				:value(node_value),
				left(lnode_value),
				right(rnode_value)
			{ 
				
			}

			// destructor
			~BT_Node(){ }
 
    };


	template<typename t> class BinaryTree{
	
		private:
			unsigned int len = 0 , size = 0;
			bool fixed_size = false;

			// important number represent the index of current position in tree
			unsigned int current_index = 1;

			// comapre function for searching inserting ...
			bool(*comp_func)(t &a , t &b);

			// all nodes in should be here in this vector
			std::vector<t> nodes;
	
		public:
			/*
				=== constructors ===
			*/

			// for 'dynamic' size 
			BinaryTree( bool(*compare_function)(t &a , t &b) )
		
					:comp_func(compare_function)
			{
				std::cout << "init's successed ! \n";
			}

			// for 'static' size 
			BinaryTree(unsigned int const tree_size , bool(*compare_function)(t &a , t &b) )
				:fixed_size(true),
				 size(tree_size),
				 comp_func(compare_function)
			{
				std::cout << "init's successed ! \n";
			}

			// destructor
			~BinaryTree(){ }

			/*
				=== Binary Tree Methods ===
			*/

			// o(1)
			// how many nodes in that tree
			unsigned int length(){
				return this->len;
			}

			// o(1)
			// push new value to this binary tree , "index will be detected automaticlly"
			bool insert(t const &new_value){
				// calc index's of left/rigth child's of that parent 
				unsigned int left  = this->current_index * 2;
				unsigned int right = left + 1;

				
			}

			// o(1)
			// add new value to specific target in this binary tree
			bool insert_at(unsigned int const &target_index , t const new_value){

				// calc index's of left/rigth child's of that parent 
				unsigned int left  = target_index * 2;
				unsigned int right = left + 1;

				// NOTE : insert will happen only if "left or right" node empty 

				// in case bot left & right aren't empty
				if(this->nodes[left] != NULL && this->nodes[right] != NULL) return false;
				
				else{	// check which one is empty & insert 
					
					if(this->nodes[left] == NULL){
						this->nodes.insert(nodes.begin() + left , new_value);
						return true;
					} 

					if(this->nodes[right] == NULL){
						this->nodes.insert(nodes.begin() + right , new_value);
						return true;
					}

				}	

				return false;
			}

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
