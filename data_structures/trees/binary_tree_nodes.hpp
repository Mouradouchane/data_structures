#include <vector>
#pragma once

// ==============================
// === binary tree nodes base ===
// ==============================

/*
	-- NAME ----------- BEST --> WORST

	length				O(1)
	max_height			O(n) --> O(nodes)

	insert				O(height) --> O(n)
	remove				O(height) --> O(n)
	search				O(height) --> O(n)

	get_sub_tree		O(nodes * 2) -->  O(n * 2) toor

	go_back				O(1)
	go_left				O(1)
	go_right			O(1)

	travle_up			O(path)
	travle_down			O(path)

	is_leaf_node		O(1)
*/


namespace trees {

	// binary tree nodes class
	template<typename T> class bt_node {
		
		private:

			bt_node<T>* parent = nullptr;
			bt_node<T>* left = nullptr;
			bt_node<T>* right = nullptr;

		public:
			// node value
			T value = NULL;

			// node constructor 1
			bt_node(T node_value) :value{ node_value } { 
			}

			// node constructor 1
			bt_node(T node_value, bt_node<T>* node_parent = NULL) :value{ node_value }, parent{ node_parent } {
			}

			// node constructor 3
			bt_node(){ }

			// node destructor
			~bt_node() {

				if(this->left  != nullptr) this->left->~bt_node();
				if(this->right != nullptr) this->right->~bt_node();

			}

			void print( unsigned int spaces = 1 ) {

				spaces += 1;

				if (this->right != NULL) this->right->print(spaces);

				for (unsigned int i = 1; i <= spaces; i += 1) {
					std::cout << '\t';
				}
				std::cout << "[" <<this->value << "]\n";
				

				if (this->left != NULL) this->left->print(spaces);

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
			//
			bool travel_up(std::vector<V> const &path) {
				
				bt_node<V>* temp = this->current_node;
				unsigned int i = 0;
				bool gap = false;

				while ( i < path.size() ) {

					if (temp->parent == nullptr) break;
					if (path[i] == temp->parent->value) {

						i += 1;
						temp = temp->parent;

					}
					else {
						gap = true;
						break;
					}
				}

				if (gap) return false;

				this->current_node = temp;

				temp = nullptr;
				delete temp;

				return true;
			}

			bool travle_up() {

				return false;
			}

			bool travle_down() {

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
			void go_to_root() {
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

			// o( n ) 
			// print function just for testing 
			void print() {

				this->root->print();

			}

	}; // end of binary_tree_nodes class

} // end of namespace