#include <array>

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
			unsigned int len = 0 , max_size = 0;

			// important number represent the index of current position in tree
			unsigned int current_index = 1;

			// comapre function for searching , inserting , ...
			bool(*comp_func)(t const &a , t const &b);

			// all nodes in should be here in this vector
			t * nodes;
	
		public:
			/*
				=== constructor ===
			*/
			BinaryTree(unsigned int const tree_size , bool(*compare_function)(t const &a , t const &b) )
				:comp_func(compare_function)
			{
				// locate a new array at "heap"
				this->max_size = (tree_size < 1 ? 1 : tree_size);
				this->nodes = new t[this->max_size]; 

				for(unsigned int i = 0 ; i < this->max_size ; i += 1){
					this->nodes[i] = NULL;
				}

			}

			//  === destructor ===
			~BinaryTree(){ 
				// make sure that allocated array at the "heap" will be deleted
				delete[] this->nodes; 
			}


			/*
				=== Binary Tree Methods ===
			*/

			// o(1)
			// how many nodes in that tree
			unsigned int length(){
				return this->len;
			}

			// function for manual testing :)
			void print(){
				for(unsigned int i = 0 ; i < this->max_size ; i += 1){
					std::cout <<'[' << this->nodes[i] << ']';
					std::cout << '\n';
				}
			}

			// o(height)
			// add new value to this binary tree , "index will be detected automaticlly"
			bool insert(t const &new_value){
				
				// "no insert !"
				// in case : current size of this tree is full or out of space
				if(this->len < this->max_size ){
					
					// index's for searching where to insert that new value
					unsigned int i = 0;

					for(;;){

						// "no insert !"
						// in case : value already in tree 'no duplicated allowed'
						// in case : index out of reserved space
						if( this->nodes[i] == new_value || i > this->max_size ) return false;

						// insert => if this node empty
						if( this->nodes[i] == NULL ){
							this->nodes[i] = new_value;
							return true;
						}

						// calc direction
						bool dir = this->comp_func( new_value , this->nodes[i] );

						// check left node if empty
						unsigned int left = ((i+1) * 2) - 1;

						if(this->nodes[left] == NULL && dir){
							this->nodes[left] = new_value;
							return true;
						}

						// check right node if empty
						unsigned int right = left + 1;

						if(this->nodes[right] == NULL && !dir){
							this->nodes[right] = new_value;
							return true;
						}

						i = ( dir ) ? left : right;
 					}
				}

				// else mean tree 'fixed size' & full of nodes , or that new value already exist  
				return false;
				
			}

			// o(1)
			// add new value to specific target in this binary tree
			bool insert_at(unsigned int const &target_index , t const new_value){

				return false;
			}
	/*
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
	*/
	};


}
