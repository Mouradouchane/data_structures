#include <vector>

#pragma once

/*
	Binary Tree
		
	-- NAME ---------- BEST --> WORST

	length

	insert				O(height)
	search				O(height)
	search_from			O(height)

	remove				O(height)

	get					O(1)
	get_index			O(1)

	go_back				O(1)
	go_left				O(1)
	go_right			O(1)
	jump_to				O(1)

	travle_up			O(height)
	travle_down			O(height)

	get_sub_tree		O(height)

	is_perfect			O(n)
	is_leaf_node		O(1)
*/

namespace trees{
    
    // =======================================
    // ======= Binary tree Nodes Class =======
    // =======================================

	template<typename t> class binary_tree{
	
		private:
			unsigned int len = 0 , max_size = 0;

			// comapre function for searching , inserting , ...
			bool(*comp_func)(t const &a , t const &b);

			// all nodes in should be here in this vector
			t * nodes;
			// by def in root

			// important number represent the index of current position in tree
			unsigned int current_node = 1;

			// o(height)
			// search for target in tree 
			bool SEARCH(t const &target , unsigned int &idx , unsigned int start_point = 1){

				// check if start point out of range
				if(start_point > 0 && start_point <= this->max_size){
					// search from root to the end of tree
					for(unsigned int i = (start_point-1) ; i < this->max_size ; ){
						
						// check
						if(this->nodes[i] == target){
							idx = i+1;
							return true;
						} 
						
						// where should go next
						if( this->comp_func( target , this->nodes[i]) ){
							 i = ((i+1) * 2) - 1;
						}
						else i = ((i+1) * 2);

					}
				}
				idx = -1;
				return false;
			}

			bool RECURSIVE_CLEAR(unsigned int const &index){
				
				if(index < this->max_size){

					// clear target & update lenght
					if (this->nodes[index] != NULL) {

						this->nodes[index] = NULL;
						this->len -= 1;
						
						// recursive clear in both direction !!

						// left
						RECURSIVE_CLEAR(((index + 1) * 2) - 1);
						// right
						RECURSIVE_CLEAR((index + 1) * 2);

						return true;
					}
					else return false;
				}

				return false;
			}

		public:

			// constructor 1
			binary_tree(unsigned int const tree_size , bool(*compare_function)( t const &a , t const &b) )
				:comp_func(compare_function)
			{
				// locate a new array at "heap"
				this->max_size = (tree_size < 2 ? 2 : tree_size);
				this->nodes = new t[this->max_size];

				for(unsigned int i = 0 ; i < this->max_size ; i += 1){
					this->nodes[i] = NULL;
				}

			}

			// constructor 2
			binary_tree(t nodes[] , unsigned int const tree_size, bool(*compare_function)(t const& a, t const& b))
				:comp_func(compare_function)
			{
				// locate a new array at "heap"
				this->max_size = (tree_size < 2 ? 2 : tree_size);
				this->nodes = new t[this->max_size];

				for (unsigned int i = 0; i < this->max_size; i += 1) {
					this->nodes[i] = NULL;
				}

			}

			//  === destructor ===
			~binary_tree(){ 
				// make sure that allocated array at the "heap" will be deleted
				delete[] this->nodes; 
			}


			/*
				=== binary tree methods ===
			*/

			// o(1)
			// how many nodes in that tree
			unsigned int length(){
				return this->len;
			}
			
			// O(height)
			// function for manual testing :)
			void print(){
				int ln = 1;
				for(unsigned int i = 0 ; i < this->max_size ; i += 1){
					std::cout <<'[' << this->nodes[i] << ']';
					if(i+1 == ln ){
						ln = ln * 2 + 1;
						std::cout << '\n';
					} 
				}
				std::cout << '\n';
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
							this->len += 1;
							return true;
						}

						// calc direction
						bool dir = this->comp_func( new_value , this->nodes[i] );

						// check left node if empty
						unsigned int left = ((i+1) * 2) - 1;

						if(this->nodes[left] == NULL && dir){
							this->nodes[left] = new_value;
							this->len += 1;
							return true;
						}

						// check right node if empty
						unsigned int right = left + 1;

						if(this->nodes[right] == NULL && !dir){
							this->nodes[right] = new_value;
							this->len += 1;
							return true;
						}

						i = ( dir ) ? left : right;
 					}
				}

				// else mean tree 'fixed size' & full of nodes , or that new value already exist  
				return false;
				
			}

			// o(height)
			// search function using SEARCH function 
			// 1
			bool search(t const &target){
				int fake_index = 0;
				return this->SEARCH(target , fake_index);
			}
			// 2
			bool search(t const &target , unsigned int &index){
				return this->SEARCH(target , index);
			}
			// 3 like search function but start from diffrent point in tree
			bool search_from(unsigned int const &start_point , t const &target){
				int fake_index = 0;
				return this->SEARCH(target , fake_index , start_point);
			}
			// 4
			bool search_from(unsigned int const &start_point , t const &target , unsigned int &index){
				return this->SEARCH(target , index , start_point);
			}

			// o(1)
			// get value of current node 
			t get(){
				if(this->current_node > 0 && this->current_node <= this->max_size){
					return this->nodes[this->current_node-1];
				}
				else return NULL;
			}
			// o(1)
			// get value of specific node
			t get(unsigned int const& target_node_index = 0) {
				
				// if index out of range
				if (target_node_index > max_size) return NULL;

				// else return node value
				return this->nodes[target_node_index];
			}

			// O(1)
			unsigned int get_index(){
				return this->current_node;
			}

			// o(1)
			bool go_left(){
				// going left only if not out of tree space
				if(this->current_node < this->max_size){
					this->current_node *= 2;  
					return true;  
				}
				return false;
			}

			// o(1)
			bool go_right(){
				// going right only if not out of tree space
				if(this->current_node < this->max_size){
					this->current_node *= 2;  
					this->current_node += 1;  
					return true;  
				}
				return false;
			}

			// o(1)
			bool go_back(){
				// going right only if not out of tree space
				if(this->current_node > 1){
					this->current_node /= 2;  
					return true;  
				}
				return false;
			}

			// O(1)
			// go/jump to position in tree
			bool jump_to(unsigned int const &index = 1){

				// check if index out of tree
				if(index > 0 && index <= this->max_size){
					// go
					this->current_node = index;
					return true;
				}
				return false;
			}

			
			// O(n)
			// check if tree contain gaps or not
			bool is_perfect(){
				for(unsigned int i = 0 ; i < (this->max_size - 1); i += 1){
					if(this->nodes[i] == NULL && this->nodes[i+1] != NULL) return false;
				}
				return true;
			}

			// O(current_node -> height)
			// delete/clear target node and all it's children
			bool remove(unsigned int const &target_node_index = NULL){

				// if target_node_index not NULL and in range 
				if (target_node_index != NULL && target_node_index <= this->max_size) {
					// clear from that target_node_index
					return this->RECURSIVE_CLEAR(target_node_index - 1);
				}

				// else clear using current_node index
				return this->RECURSIVE_CLEAR(this->current_node - 1);
				
			}


			// O(height)
			// travel from current node to x node
			// note ! : travel only will happen if  
			bool travel_down(std::vector<t> const &full_path){
			
				// you can't travle from current node to it's self
				if(full_path[0] != this->nodes[this->current_node-1]){

					int index = this->current_node - 1;

					for(unsigned int i = 0; i < full_path.size(); i += 1){
						
						if( this->comp_func( full_path[i] , this->nodes[index]) ){
							index = ((index+1) * 2) - 1;
						}
						else index = ((index+1) * 2);

						// check
						if(this->nodes[index] != full_path[i] || this->nodes[index] == NULL) return false;

					}

					this->current_node = index + 1;
					return true;
				}
				return false;
			}

			// O(height)
			bool travel_up(std::vector<t> const &full_path){

				// you can't travle from current node to it's self
				if(full_path[0] != this->nodes[this->current_node-1]){

					int index = (this->current_node / 2) - 1;

					for(unsigned int i = 0; i < full_path.size(); i += 1 , index = (index / 2) - 1){

						if(this->nodes[index] != full_path[i] || this->nodes[index] == NULL) return false;
 						
					}

					this->current_node = index + 1;
					return true;
				}
				return false;
			
			}	
			
			bool is_leaf_node(){
				// calc left & right nodes
				unsigned int left  = (this->current_node * 2) - 1;
				unsigned int right = (this->current_node * 2);
				// if left & right NULL that's mean this current node is a leaf node
				return	(this->nodes[left] == NULL && this->nodes[right] == NULL || left >= this->max_size && right >= this->max_size) ? true : false;
			}
	
			// o( node -> height )
			// cut = mean you want to cut that target and all it's nodes
			binary_tree<t> get_sub_tree(unsigned int const &target_node_index , bool const &cut = false){
			
			
			}
	
	};


}
