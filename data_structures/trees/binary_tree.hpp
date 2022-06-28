#include <vector>
//#include <stdexcept>

#pragma once

/*
	Based Array Binary Tree
		
	-- NAME ----------- BEST --> WORST

	length				O(1)
	size				O(1)
	size_at				O(n) --> O(nodes)
	max_height			O(n) --> O(nodes)

	insert				O(height) --> O(n)
	remove				O(height) --> O(n)

	search				O(height) --> O(n)
	search_from			O(height) --> O(n)

	get					O(1)
	get_index			O(1)
	get_left_index		O(1)
	get_right_index		O(1)
	get_sub_tree		O(nodes * 2) -->  O(n * 2) toor


	go_back				O(1)
	go_left				O(1)
	go_right			O(1)
	jump_to				O(1)

	travle_up			O(path)
	travle_down			O(path)

	is_perfect			O(n)
	is_full				O(1)
	is_leaf_node		O(1)
*/

namespace trees{
    
    // ===================================
    // ======== Binary tree Class ========
    // ===================================

	template<typename t> class binary_tree_arr{
	
		private:

			unsigned int len = 0 , max_size = 0;

			// comapre function for searching , inserting , ...
			bool(*comp_func)(t const &a , t const &b);

			// all nodes gonna be here in this array
			t * nodes;

			// important : number represent the index of current position in tree
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

			// O(n)
			// calc the maximum height at some position , by default starting will be at the root
			unsigned int CALC_MAX_HEIGHT(unsigned int node_index = 1) {

				// left & right child's index's
				unsigned int left = 0;
				unsigned int right = 0;

				if (node_index <= this->max_size && node_index != NULL && this->nodes[node_index - 1] != NULL) {

					left  = this->nodes[this->get_left_index(node_index)  - 1] == NULL ? 0 : this->CALC_MAX_HEIGHT(this->get_left_index(node_index));
					right = this->nodes[this->get_right_index(node_index) - 1] == NULL ? 0 : this->CALC_MAX_HEIGHT(this->get_right_index(node_index));

					return (left > right ? left : right) + 1;
				}
				else return 0;
			}


			void CALC_SIZE_OF_NODES( unsigned int const &target_node_index = 1 , unsigned int &size = 0) {
		
				if (target_node_index != NULL && target_node_index <= this->max_size && this->nodes[ target_node_index - 1] != NULL) {

					size += 1;
					
					unsigned int left  = this->get_left_index(target_node_index);
					unsigned int right = this->get_right_index(target_node_index);

					if( this->nodes[left  - 1] != NULL ) this->CALC_SIZE_OF_NODES(left , size);
					if( this->nodes[right - 1] != NULL ) this->CALC_SIZE_OF_NODES(right , size);

				}

			}


			void GET_SUB_TREE(bool const &cut , t* sub_tree , unsigned int const target_node_index = 1 , unsigned int i = 1) {

				if (target_node_index >= 1 && target_node_index <= this->max_size && this->nodes[target_node_index - 1] != NULL) {
					
					sub_tree[i - 1] = this->nodes[target_node_index - 1];

					if (cut) this->nodes[target_node_index - 1] = NULL;

					unsigned int left  = this->get_left_index(target_node_index);
					unsigned int right = this->get_right_index(target_node_index);

					this->GET_SUB_TREE(cut , sub_tree, left, i * 2);
					this->GET_SUB_TREE(cut , sub_tree, right, (i * 2) + 1);

				}

			}



		public:

			// constructor 1
			binary_tree_arr(unsigned int const tree_size , bool(*compare_function)( t const &a , t const &b) )
				:comp_func(compare_function)
			{
				// locate a new array at "heap"
				this->max_size = (tree_size < 3 ? 3 : tree_size);
				this->nodes = new t[this->max_size];

				for(unsigned int i = 0 ; i < this->max_size ; i += 1){
					this->nodes[i] = NULL;
				}

			}

			// constructor 2
			// in second constructor you can pass array of nodes
			binary_tree_arr(t nodes[] , unsigned int const tree_size, bool(*compare_function)(t const& a, t const& b))
				:comp_func(compare_function)
			{
				this->max_size = (tree_size < 3 ? 3 : tree_size);
				this->nodes = nodes;

			}

			// default constructor
			binary_tree_arr() { }

			// destructor 
			~binary_tree_arr(){ 
				// delete dynamic allocated array of nodes from "heap"
				delete[] this->nodes; 
			}


			/*
				==== binary tree : public methods ====
			*/

			// o(1)
			// how many nodes in that tree
			unsigned int length(){
				return this->len;
			}
			
			// o(1)
			// size of this tree
			unsigned int size() {
				return this->max_size;
			}

			// O(1)
			// check if this tree is full of nodes or not
			bool is_full() {

				// count of nodes must be equal to tree size to consider this tree as full tree
				return (this->len < this->max_size) ? false : true;
			}

			// O(nodes)
			// calc the maximum height recursivly using CALC_MAX_HEIGHT function
			unsigned int max_height(unsigned int const node_index = 1 ){
			
				// height must be total nodes in path - 1
				return this->CALC_MAX_HEIGHT(node_index) - 1;
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
			// get index of current node 
			unsigned int get_index(){
				return this->current_node;
			}

			// o(1)
			// get index of specific node
			unsigned int get_index_of(t const& target) {

				unsigned int index = NULL;
				this->SEARCH(target, index);

				if (index < 1 || index > this->max_size) return 0;

				return index;
			}

			// o(1)
			// go to the left child of current node
			bool go_left(){
				// go left only if not out of tree space
				if(this->current_node * 2 <= this->max_size){
					this->current_node *= 2;  
					return true;  
				}
				return false;
			}

			// o(1)
			// go to the right child of curent node
			bool go_right(){

				// going right only if not out of tree space
				if( (this->current_node * 2) + 1 <= this->max_size){
					this->current_node = (this->current_node * 2) + 1;  
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

			// o(1)
			// get right node index of current node or another specific node
			unsigned int get_right_index( unsigned int const &target_node_index = NULL ) {

				// calc right index at current_node 
				unsigned int index = target_node_index == NULL ? (this->current_node * 2) + 1 : (target_node_index * 2) + 1;

				// check if index is out of tree
				return (index > max_size) ? NULL : index;
			}

			// o(1)
			// get left node index of current node or another specific node
			unsigned int get_left_index( unsigned int const& target_node_index = NULL ) {

				// calc right index at current_node 
				unsigned int index = target_node_index == NULL ?  this->current_node * 2 : target_node_index * 2;

				// check if index is out of tree
				return (index > max_size) ? NULL : index;
			}

			// O(1)
			// go or jump to specific node in tree
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
			// check if this tree contain gaps or not
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
			
			// check if current node is leaf node at end or not 
			bool is_leaf_node( unsigned int const &target_node_index = NULL ){
				
				if (this->nodes[target_node_index - 1] == NULL) return false;

				unsigned int left , right;

				// if specifide target valid 
				if (target_node_index >= 1 && target_node_index <= this->max_size) {
					// calc left & right nodes
					left = (target_node_index * 2);
					right = (target_node_index * 2) + 1;
				}
				else { // else using current_node as default
					left  = (this->current_node * 2) - 1;
					right = (this->current_node * 2);
				}

				// if left & right child index out of range that mean it's a leaf node
				if (left > this->max_size && right > this->max_size) return true;

				// if left & right is NULL values => mean it's a leaf node
				if(this->nodes[left - 1] == NULL && this->nodes[right - 1] == NULL ) return true ;

				return false;
			}
	
			// O( nodes )
			// calc nodes count at specific node
			unsigned int size_at(unsigned int const &target_node_index = 1) {
				
				unsigned int size = 0;
				this->CALC_SIZE_OF_NODES(target_node_index , size);

				return size < 3 ? 3 : size;

			}

			// o( nodes * 2 )
			// function allow you to take a node with all it's children in new binary tree
			// cut = if you want to cut that target node and all it's childern nodes from this tree
			binary_tree_arr<t>* get_sub_tree(bool const &cut = false , unsigned int const &target_node_index = 1 ){
				
				if (target_node_index >= 1 && target_node_index <= this->max_size) {

					// calc nodes size + allocated array for nodes
					unsigned int nodes_size = this->size_at(target_node_index);
					t *sub_tree_nodes = new t[nodes_size];

					// get nodes in sub_tree_nodes
					this->GET_SUB_TREE(cut , sub_tree_nodes, target_node_index);

					binary_tree_arr<t>* sub_tree = new binary_tree_arr<t>(sub_tree_nodes , nodes_size, this->comp_func );

					sub_tree_nodes = nullptr;
					delete sub_tree_nodes;

					return sub_tree;
				}
				else {
					//binary_tree<t> *empty();
					return nullptr;
				}
			}
	
	};


}
