#include <vector>
#pragma once

// ==============================
// === binary tree nodes base ===
// ==============================

/*
	-- NAME ----------- BEST --> WORST

	length				O(1)
	min_height			O(n) --> O(log n)
	max_height			O(n) --> O(log n)

	insert				O(height) --> O(n)
	remove				O(height) --> O(n)
	search				O(height) --> O(n)

	get_sub_tree		O(nodes * 2) -->  O(n * 2) toor

	go_back				O(1)
	go_left				O(1)
	go_right			O(1)

	jump_to				O(1) --> O(log n)
	jump_to_root		O(1)
	travle_up			O(path)
	travle_down			O(log path)

	is_leaf_node		O(1)
*/


namespace trees {

	// binary tree nodes class
	template<typename T> class bt_node {
		
		private:

			bt_node<T>* parent = nullptr;
			bt_node<T>* left = nullptr;
			bt_node<T>* right = nullptr;
			// node value
			T value = NULL;

		public:

			// node constructor 1
			bt_node(T node_value) :value{ node_value } { 
			}

			// node constructor 1
			bt_node(T node_value, bt_node<T>* node_parent = NULL) :value{ node_value }, parent{ node_parent } {
			}

			// node constructor 3 "copy constructor"
			bt_node(bt_node<T>* other , bool const& cut) {

				if (cut) {
					// pass by value

					this->left = new bt_node<T>();
					this->right = new bt_node<T>();

					if(other->right != nullptr) *(this->right) = *(other->right) ;
					if(other->left  != nullptr) *(this->left)  = *(other->left) ;
					this->value = other->value; 
					other->value = NULL;

					if (other->parent != nullptr){
						if(other->parent->left == other) other->parent->left = nullptr;
						else other->parent->right = nullptr;
					}
					else {
						delete other;
					}
				}
				else {
					// pass by reference
					this->parent = other->parent;
					this->left   = other->left; 
					this->right  = other->right; 

					this->value  = other->value;
				}
				
			}

			// node constructor 4
			bt_node(){ }

			// node destructor
			~bt_node() {

				if(this->left  != nullptr) this->left->~bt_node();
				if(this->right != nullptr) this->right->~bt_node();

			}

			T get_value() {
				return this->value;
			}

			void print( unsigned int spaces = 1 ) {

				spaces += 1;

				if (this->right != nullptr) this->right->print(spaces);

				for (unsigned int i = 1; i <= spaces; i += 1) {
					std::cout << '\t';
				}
				std::cout << "[" << this->value << "]\n";
				

				if (this->left != nullptr) this->left->print(spaces);

			}

			// give binary_tree_nodes access
			template<typename T> friend class binary_tree_nodes;
	
	}; // end of node class


	// binary tree class
	template<typename V> class binary_tree_nodes {

		private:
			bt_node<V>* root;
			unsigned int len = 0;

			bool (*comp_function)(V const &node_a, V const &node_b);

			// o( log n )
			bt_node<V>* SEARCH_FOR_NODE_REF(V const& target_node_value) {

				bt_node<V>* temp = this->root;

				while (temp != nullptr) {

					if (temp->value == target_node_value) {

						return temp;
					}
					else {

						if (this->comp_function(target_node_value, temp->value)) {
							temp = temp->left;
						}
						else temp = temp->right;

					}
				}

				return nullptr;
			}


		public:
			bt_node<V>* current_node;

			// constructor 1
			binary_tree_nodes( V root_value , bool(*comp)(V const &node_a, V const &node_b) )
				:comp_function{ comp }
			{
				root = new bt_node<V>(root_value,NULL);
				current_node = root;
			}

			// constructor 2
			binary_tree_nodes(bool(*comp)(V const& node_a, V const& node_b))
				:comp_function{ comp }
			{
				root = new bt_node<V>();
				current_node = root;
			}

			// constructor 3 "copy constructor"
			binary_tree_nodes(bt_node<V>* root_node , bool cut , bool(*comp)(V const& node_a, V const& node_b))
				:comp_function{ comp }
			{

				this->root = new bt_node<V>(root_node,cut);
				this->current_node = this->root;

			}

			// destructor
			~binary_tree_nodes() {
				/*
					delete this->current_node;
				*/
				 this->root->~bt_node();
			}

			// o( 1 )
			unsigned int length() {
				return this->len;
			}

			// o( log n )
			bool insert(V const new_node_value) {

				bt_node<V>* temp = this->root;

				// search for place to insert on it
				while (temp != nullptr) {

					// if target is already exist "no duplicates of values are allowed"
					if (temp->value == new_node_value) return false;

					// if empty node founded
					if (temp->value == NULL) {
						// insert it
						temp->value = new_node_value;
						this->len += 1;

						temp = nullptr;
						delete temp;

						return true;

					}
					else {

						// calc next direction
						if ( this->comp_function(new_node_value , temp->value) ) {
							
							// if there's no left child
							if (temp->left == nullptr) {
								// insert
								temp->left = new bt_node<V>(new_node_value , temp);
								this->len += 1;

								temp = nullptr;
								delete temp;

								return true;
							}
							// else go left
							else temp = temp->left;
						}
						else {

							// if there's no right child
							if (temp->right == nullptr) {
								// insert
								temp->right = new bt_node<V>(new_node_value, temp);
								this->len += 1;

								temp = nullptr;
								delete temp;

								return true;
							}
							// else go right
							else temp = temp->right;
						}
					}
				}

				// in case no insertion happend
				return false;
			}

			// o( log n )
			bool remove(V const &target_node_value) {
				
				bt_node<V>* temp = this->root;
				bool LorR = NULL;

				// search for target 
				while( temp != nullptr ){

					// if target found
					if (temp->value == target_node_value) {

						// call that node destructor
						temp->~bt_node(); 

						// delete it from it's parent
						if (!LorR) temp->parent->left = nullptr;
						else temp->parent->right = nullptr;

						delete temp;
						
						return true;

					}
					else {
						// calc direction to go "left" or "right" node 
						if (this->comp_function(target_node_value, temp->value)) {
							// if left 
							temp = temp->left;
							LorR = false;
						}
						else {
							// if right
							temp = temp->right;
							LorR = true;
						}
					}

				}

				temp = nullptr;
				delete temp;

				// in case target not found
				return false;
			}

			// o( log n )
			bool search(V const &target_node_value) {
				
				bt_node<V>* temp = this->root;

				while (temp != nullptr){

					if (temp->value == target_node_value) {
						
						temp = nullptr;
						delete temp;
						
						return true;
					}
					else {

						if (this->comp_function(target_node_value, temp->value)) {
							 temp = temp->left;
						}
						else temp = temp->right;

					}
				}

				temp = nullptr;
				delete temp;

				return false;
			}

			// o( path )
			// path : parent value as path to go on it 
			bool travel_up(std::vector<V> const &path) {
				
				// temp node for process
				bt_node<V>* temp = this->current_node;

				unsigned int i = 0;
				// to check if path is valid to travel on it or not
				bool gap = false; 


				while ( i < path.size() ) {
					// if no more parent 
					if (temp->parent == nullptr) {
						gap = true;
						break;
					}

					// if path still valid
					if (path[i] == temp->parent->value) {

						i += 1;
						temp = temp->parent;

					}
					// if there's gap on path
					else {
						gap = true;
						break;
					}
				}

				// travel through path should not happen , because path is invalid
				if (gap) return false;
				
				// else : mean path is valid
				this->current_node = temp;

				// make temp point to null-pointer & delete it 
				temp = nullptr;
				delete temp;

				// return confirmation of that travling around the path is successed 
				return true;
			}

			// o( log n )
			// path : path of childern values to go on it
			bool travel_down(std::vector<V> const &path) {

				bt_node<V>* temp = this->current_node;
				unsigned int i = 0;
				bool gap = false;

				while ( temp != nullptr && i < path.size() ) {

					if (this->comp_function(path[i], temp->value)) {

						if (temp->left != nullptr && temp->left->value == path[i]) {
							i += 1;
							temp = temp->left;
						}
						else{
							gap = true;
							break;
						}
					}
					else {

						if (temp->right != nullptr && temp->right->value == path[i]) {
							i += 1;
							temp = temp->right;
						}
						else {
							gap = true;
							break;
						}
					}

				}

				if (gap) return false;
				
				// else
				this->current_node = temp;

				temp = nullptr;
				delete temp;

				return false;
			}

			// o( 1 )
			bool go_left() {
				// if there's no left node to go in
				if (this->current_node->left == nullptr) return false;
				// else 
				this->current_node = this->current_node->left;
				return true;
			}

			// o( 1 )
			bool go_right() {
				// if there's no right node to go in
				if (this->current_node->right == nullptr) return false;
				// else
				this->current_node = this->current_node->right;
				return true;
			}

			// o( 1 )
			bool go_back() {
				// if there's no parent to go with
				if (this->current_node == nullptr || this->current_node->parent == nullptr) return false;
				
				// else
				this->current_node = this->current_node->parent;
				return true;
			}

			// o( 1 )
			// jump to root node
			void jump_to_root() {
				this->current_node = this->root;
			}

			// o( log n )
			// go/jump to target node if it's found
			bool jump_to(V const& target_node_value) {

				bt_node<V>* temp = this->root;

				while (temp != nullptr) {

					if (temp->value == target_node_value) {
						this->current_node = temp;

						temp = nullptr;
						delete temp;
						return true;
					}
					else {

						if ( this->comp_function(target_node_value, temp->value) ) {
							temp = temp->left;
						}
						else {
							temp = temp->right;
						}

					}

				}

				return false;
			}

			// o( 1 )
			// check if this current_node is a leaf node or not
			bool is_leaf_node() {

				return (this->current_node->left == nullptr && this->current_node->right == nullptr);
			}

			// o( log target_node )
			binary_tree_nodes<V>* get_sub_tree(bool const& cut , V const& target_node_value) {

				bt_node<V>* temp = this->SEARCH_FOR_NODE_REF(target_node_value);

				if (temp == nullptr) return nullptr;
				else {
					if (cut && temp == this->root) {
						this->root = new bt_node<V>();
						this->current_node = this->root;
					}
					this->jump_to_root();
					return new binary_tree_nodes<V>(temp,cut,this->comp_function);
				}
			}

			// o( n ) 
			// print function just for testing 
			void print() {

				if(this->root != nullptr) this->root->print();

			}

	}; // end of binary_tree_nodes class

} // end of namespace