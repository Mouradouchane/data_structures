#include <vector>
#pragma once

// ==============================
// === binary tree avl ==========
// ==============================

/*
	-- NAME ----------- BEST --> WORST

	length				O(1)
	min_height			O(log n) --> O(n)
	max_height			O(log n) --> O(n)

	insert				O(height) --> O(n)
	remove				O(height) --> O(n)
	search				O(height) --> O(n)

	get_sub_tree		O(log n) -->  O(log n * 2)

	go_back				O(1)
	go_left				O(1)
	go_right			O(1)

	jump_to				O(1) --> O(log n)
	jump_to_root		O(1)
	travle_up			O(path)
	travle_down			O(log path)

	is_leaf_node		O(1)

	is_balanced			O(log n) --> O(n)
	ll_rotation			O(1)
	rr_rotation			O(1)
	lr_rotation			O(1)
	rl_rotation			O(1)
*/


namespace trees {

	// binary tree nodes class
	template<typename T> class avl_node {

	private:

		avl_node<T>* parent = nullptr;
		avl_node<T>* left   = nullptr;
		avl_node<T>* right  = nullptr;

		// this node value
		T value = NULL;


		unsigned int CALC_PATH(bool const& min = false) {

			unsigned int LEFT = NULL;
			unsigned int RIGHT = NULL;

			if (this->left != nullptr) {
				LEFT = this->left->CALC_PATH(min) + 1;
			}
			if (this->right != nullptr) {
				RIGHT = this->right->CALC_PATH(min) + 1;
			}

			if (min) {

				if (LEFT == NULL && RIGHT == NULL) return NULL;
				if (LEFT == NULL && RIGHT != NULL) return RIGHT;
				if (LEFT != NULL && RIGHT == NULL) return LEFT;

				return (LEFT < RIGHT) ? LEFT : RIGHT;
			}
			else  return (LEFT > RIGHT) ? LEFT : RIGHT;

		}

		// O( log n )
		// calc balance factor recursivly at some specific node
		static void CALC_BALANCE( avl_node<T>* target , int &left  , int &right ) {

			if (target == nullptr) return;

			if (target->left != nullptr) {
				avl_node<T>::CALC_BALANCE(target->left, left , right);
				left += 1;
			}
			if (target->right != nullptr) {
				avl_node<T>::CALC_BALANCE(target->right, left , right );
				right += 1;
			}

			int balance = left - right;
			
			if (balance < -1 || balance > 1) avl_node<T>::BALANCE( target, (right > left) );

		}

		// O(1)
		// balance unbalance target in tree
		static void BALANCE(avl_node<T>* target, bool right = false) {

			std::cout << "unbalance in node : " << target->value << '\n';

			// unbalance in left
			if (!right) {

			}
			// unbalance in right
			else {

			}

		}


	public:

		// node constructor 1
		avl_node(T node_value) :value{ node_value } {
		}

		// node constructor 2
		avl_node(T node_value, avl_node<T>* node_parent = NULL) :value{ node_value }, parent{ node_parent } {
		}

		// node constructor 3 "copy constructor"
		// cut boolean option to cut that node from it's origin or not
		avl_node(avl_node<T>* other, bool const& cut) {

			// cut node from it's origin
			if (cut) {

				// define new child's at the heap
				this->left  = new avl_node<T>();
				this->right = new avl_node<T>();


				// connect new child's with this node as parent
				this->left->parent  = this;
				this->right->parent = this;

				this->value = other->value;

				// cut values from origin
				if (other->right != nullptr) {

					this->right  = other->right;
					other->right = nullptr;

				}
				if (other->left != nullptr) {

					this->left  = other->left;
					other->left = nullptr;

				}

				if (other->parent != nullptr) {

					if (other->parent->left == other) other->parent->left = nullptr;
					else other->parent->right = nullptr;

				}

				delete other;
			}
			// copy node from it's origin
			else {

				// define new child's at the heap

				if (other->left != nullptr) {
					//*(this->left) = *(other->left);
					this->left = new avl_node<T>(other->left, cut);
					this->left->parent = this;
				}
				if (other->right != nullptr) {
					//*(this->right) = *(other->right);
					this->right = new avl_node<T>(other->right, cut);
					this->right->parent = this;
				}

				this->value = other->value;

			}

		}

		// def constructor
		avl_node() { }

		// node destructor
		~avl_node() {

			if (this->left != nullptr) {
				this->left->~avl_node();

				free((void*)(this->left));
				this->left = nullptr;
			}

			if (this->right != nullptr) {
				this->right->~avl_node();

				free((void*)(this->right));
				this->right = nullptr;
			}

			//free( (void*)(this->value) );
		}

		T get_value() {
			return this->value;
		}

		// testing function
		static void print(avl_node<T>* target , unsigned int spaces = 1) {

			spaces += 1;

			if (target->right != nullptr) avl_node<T>::print(target->right , spaces);

			for (unsigned int i = 1; i <= spaces; i += 1) {
				std::cout << '\t';
			}
			std::cout << "[" << target->value << "]\n";


			if (target->left  != nullptr) avl_node<T>::print(target->left, spaces);

		}

		// give binary_tree_avl access
		template<typename T> friend class binary_tree_avl;

	}; // end of node class


	// binary tree class
	template<typename V> class binary_tree_avl {

	private:
		avl_node<V>* root;
		unsigned int len = 0;

		bool (*comp_function)(V const& node_a, V const& node_b);

		// o( log n )
		avl_node<V>* SEARCH_FOR_NODE_REF(V const& target_node_value) {

			avl_node<V>* temp = this->root;

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
		avl_node<V>* current_node;

		// constructor 1
		binary_tree_avl(V root_value, bool(*comp)(V const& node_a, V const& node_b))
			:comp_function{ comp }
		{
			root = new avl_node<V>(root_value, NULL);
			current_node = root;
		}

		// constructor 2
		binary_tree_avl(bool(*comp)(V const& node_a, V const& node_b))
			:comp_function{ comp }
		{
			root = new avl_node<V>();
			current_node = root;
		}

		// constructor 3 "copy/cut constructor"
		// root_node reference to that copied or cuted "sub tree"
		binary_tree_avl(avl_node<V>* root_node, bool cut, bool(*comp)(V const& node_a, V const& node_b))
			:comp_function{ comp }
		{
			// call "copy/cut node constructor"
			this->root = new avl_node<V>(root_node, cut);
			this->current_node = this->root;

		}

		// destructor
		~binary_tree_avl() {

			// destruct tree from the root recursivly 
			if (this->root != nullptr) {
				this->root->~avl_node();

				this->root = nullptr;
				this->current_node = this->root;
			}

		}

		// o( 1 )
		unsigned int length() {
			return this->len;
		}

		// o( log n )
		bool insert(V const new_node_value) {

			bool get_insert = false;
			avl_node<V>* temp = this->root;
			
			// for balance calaculations
			int left = NULL, right = NULL;

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

					get_insert = true;
					break;

				}
				else {

					// calc next direction
					if (this->comp_function(new_node_value, temp->value)) {

						// if there's no left child
						if (temp->left == nullptr) {
							
							// insert
							temp->left = new avl_node<V>(new_node_value, temp);
							this->len += 1;

							temp = nullptr;
							delete temp;

							get_insert = true;
							break;

						}
						// else go left
						else temp = temp->left;
					}
					else {

						// if there's no right child
						if (temp->right == nullptr) {
							
							// insert
							temp->right = new avl_node<V>(new_node_value, temp);
							this->len += 1;

							temp = nullptr;
							delete temp;

							get_insert = true;
							break;

						}
						// else go right
						else temp = temp->right;
					}
				}
			}

			// check if tree became unbalanced or not
			if(get_insert) avl_node<V>::CALC_BALANCE(this->root , left , right);

			// in case no insertion happend
			return get_insert;
		}

		// o( log n )
		bool remove(V const& target_node_value) {

			avl_node<V>* temp = this->root;
			bool LorR = NULL;
			bool target_found = false;

			// for balance calculating
			int left = NULL, right = NULL;

			// search for target 
			while (temp != nullptr) {

				// if target found
				if (temp->value == target_node_value) {

					// call that node destructor
					temp->~avl_node();

					// delete it from it's parent
					if (!LorR) temp->parent->left = nullptr;
					else temp->parent->right = nullptr;

					delete temp;

					target_found = true;
					break;

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

			//
			if (target_found) {
				avl_node<V>::CALC_BALANCE(this->root , left , right);
			}

			// in case target not found
			return target_found;
		}

		// o( log n )
		bool search(V const& target_node_value) {

			avl_node<V>* temp = this->root;

			while (temp != nullptr) {

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
		bool travel_up(std::vector<V> const& path) {

			// temp node for process
			avl_node<V>* temp = this->current_node;

			unsigned int i = 0;
			// to check if path is valid to travel on it or not
			bool gap = false;


			while (i < path.size()) {
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
		bool travel_down(std::vector<V> const& path) {

			avl_node<V>* temp = this->current_node;
			unsigned int i = 0;
			bool gap = false;

			while (temp != nullptr && i < path.size()) {

				if (this->comp_function(path[i], temp->value)) {

					if (temp->left != nullptr && temp->left->value == path[i]) {
						i += 1;
						temp = temp->left;
					}
					else {
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

			avl_node<V>* temp = this->root;

			while (temp != nullptr) {

				if (temp->value == target_node_value) {
					this->current_node = temp;

					temp = nullptr;
					delete temp;
					return true;
				}
				else {

					if (this->comp_function(target_node_value, temp->value)) {
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
		// copy or cut a part from this tree 
		binary_tree_avl<V>* get_sub_tree(bool const& cut, V const& target_node_value) {

			// search for target node "reference"
			avl_node<V>* temp = this->SEARCH_FOR_NODE_REF(target_node_value);

			// if target not found
			if (temp == nullptr) return nullptr;
			else {

				// if you want to cut from root 
				if (cut && temp == this->root) {

					// set root to another object at the heap
					this->root = new avl_node<V>();

				}

				// jump to root , to avoid refering to deleted node in tree
				this->jump_to_root();

				// return new sub tree
				return new binary_tree_avl<V>(temp, cut, this->comp_function);
			}
		}

		// o( n ) 
		// print function just for testing 
		void print() {

			if (this->root != nullptr) avl_node<V>::print(this->root);

		}

		// o( log n ) --> o( n )
		unsigned int max_height() {

			return this->root->CALC_PATH(false);

		}

		// o( log n ) --> o( n )
		unsigned int min_height() {

			return this->root->CALC_PATH(true);

		}

	}; // end of binary_tree_avl class

} // end of namespace