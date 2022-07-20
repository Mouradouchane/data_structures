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
	template<typename V> class binary_tree_avl;

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
		// and return biggest balance_factor
		static int CALC_BALANCE(binary_tree_avl<T>* tree = nullptr , avl_node<T>* target = nullptr ,bool &skip_recursive = false ) {

			int left_factor  = NULL;
			int right_factor = NULL;

			if ( target == nullptr || skip_recursive ) return NULL;


			if ( target->left  != nullptr && !skip_recursive ) {
				left_factor  = avl_node<T>::CALC_BALANCE( nullptr , target->left  , skip_recursive ) + 1;
			}
			if ( target->right != nullptr && !skip_recursive ) {
				right_factor = avl_node<T>::CALC_BALANCE( nullptr , target->right , skip_recursive ) + 1;
			}

			if ( skip_recursive ) return NULL;

			// calc balance factor
			int balance_factor = left_factor - right_factor;
			
			// if tree unbalanced then we should perform balancing 
			if (balance_factor < -1 || balance_factor > 1) {

				avl_node<T>::BALANCE(tree, target, (right_factor > left_factor));
			
				skip_recursive = true;

			}

			// return biggest factor "important for recursive check"
			return (left_factor >= right_factor) ? left_factor : right_factor;
		}

		// O(1)
		// balance unbalance target in tree
		// unbalance_direction : mean where side are unbalanced at target node , left or right !
		static void BALANCE( binary_tree_avl<T>* tree = nullptr , avl_node<T>* target = nullptr, bool right_unbalance = false ) {


			// unbalance in left side
			if (!right_unbalance) {

				// LR unbalance
				if (target->left != nullptr && target->left->right != nullptr) {
					std::cout << "left right unbalance at node : " << target->value << '\n';

					// preforme LEFT RIGHT balance
					avl_node<T>::LR_BALANCE(tree, target);
					return;
				}

				// LL unbalance
				if (target->left != nullptr && target->left->left != nullptr) {
					std::cout << "left left unbalance at node : " << target->value << '\n';
					
					// preforme LEFT LEFT balance
					avl_node<T>::LL_BALANCE(tree , target);
					return;
				}

			}

			// unbalance in right side
			else {

				// RL unbalance
				if (target->right != nullptr && target->right->left != nullptr) {
					std::cout << "right left unbalance at node : " << target->value << '\n';

					// preforme RIGHT LEFT balance
					avl_node<T>::RL_BALANCE(tree , target);
					return;
				}


				// RR unbalance
				if (target->right != nullptr && target->right->right != nullptr) {
					std::cout << "right right unbalance at node : " << target->value << '\n';

					// preforme RIGHT RIGHT balance
					avl_node<T>::RR_BALANCE(tree , target);
					return;
				}

			}

		}

		// =========== rotation functions ===============

		// O(1)
		static void LL_BALANCE( binary_tree_avl<T>* tree , avl_node<T>* target ) {

			// target -> left node
			avl_node<T>* l_node = target->left;
			// target -> left node -> right node
			avl_node<T>* lr_node = l_node->right;

			// set target parent to left node parent
			l_node->parent = target->parent;

			// set left node to the parent as child
			if (target->parent != nullptr) {

				if (target->parent->left == target) {
					l_node->parent->left = l_node;
				}
				else {
					l_node->parent->right = l_node;
				}

			}

			if (tree != nullptr && tree->is_the_root(target)) {
				tree->root = l_node;
				tree->current_node = tree->root;
			}

			// set target as left child to right node
			target->parent = l_node;
			l_node->right = target;

			if (lr_node != nullptr) {
				target->left = lr_node;
				lr_node->parent = target;
			}
			else target->left = nullptr;

			l_node = nullptr;
			lr_node = nullptr;

			delete l_node;
			delete lr_node;
		}
		
		// O(1)
		static void LR_BALANCE( binary_tree_avl<T>* tree , avl_node<T>* target) {

			// target -> left node -> right node
			avl_node<T>* lr_node = target->left->right;
			// left & right child of rl_node
			avl_node<T>* l_node = lr_node->left;
			avl_node<T>* r_node = lr_node->right;

			lr_node->parent = target->parent;

			if (target->parent != nullptr) {

				if (target->parent->left == target) {
					target->parent->left  = lr_node;
				}
				else {
					target->parent->right = lr_node;
				}

			}

			if (tree != nullptr && tree->is_the_root(target)) {
				tree->root = lr_node;
				tree->current_node = tree->root;
			}

			lr_node->right = target;
			target->parent = lr_node;

			lr_node->left = target->left;
			lr_node->left->parent = lr_node;
			lr_node->left->right = nullptr;

			target->left = nullptr;

			if (l_node != nullptr) {

				lr_node->left->right = l_node;
				l_node->parent = lr_node->left;
			}

			if (r_node != nullptr) {

				lr_node->right->left = r_node;
				r_node->parent = lr_node->right;
			}

			lr_node = nullptr;
			l_node = nullptr;
			r_node = nullptr;

			delete lr_node;
			delete l_node;
			delete r_node;

		}

		// O(1)
		static void RL_BALANCE( binary_tree_avl<T>* tree , avl_node<T>* target) {

			// target -> right node -> left node
			avl_node<T>* rl_node = target->right->left;
			// left & right child of rl_node
			avl_node<T>* l_node = rl_node->left;
			avl_node<T>* r_node = rl_node->right;

			rl_node->parent = target->parent;

			if (target->parent != nullptr) {

				if (target->parent->left == target) {
					target->parent->left = rl_node;
				}
				else {
					target->parent->right = rl_node;
				}

			}

			if (tree != nullptr && tree->is_the_root(target)) {
				tree->root = rl_node;
				tree->current_node = tree->root;
			}

			rl_node->left  = target;
			target->parent = rl_node;

			rl_node->right = target->right;
			rl_node->right->parent = rl_node;
			rl_node->right->left = nullptr;

			target->right = nullptr;

			if (l_node != nullptr) {

				rl_node->left->right = l_node;
				l_node->parent = rl_node->left;
			}

			if (r_node != nullptr) {

				rl_node->right->left = r_node;
				r_node->parent = rl_node->right;
			}

			rl_node = nullptr;
			l_node = nullptr;
			r_node = nullptr;

			delete rl_node;
			delete l_node;
			delete r_node;

		}

		// O(1)
		static void RR_BALANCE( binary_tree_avl<T>* tree , avl_node<T>* target ) {

			// target -> right node
			avl_node<T>* r_node = target->right;
			// target -> right node -> left node
			avl_node<T>* rl_node = r_node->left;

			// set target parent to right node parent
			r_node->parent = target->parent;
			
			// set right node to the parent as child
			if (target->parent != nullptr) {

				if (target->parent->left == target) {
					r_node->parent->left = r_node;
				}
				else {
					r_node->parent->right = r_node;
				}

			}

			if (tree != nullptr && tree->is_the_root(target)) {
				tree->root = r_node;
				tree->current_node = tree->root;
			}

			// set target as left child to right node
			target->parent = r_node;
			r_node->left = target;

			if (rl_node != nullptr) {
				target->right = rl_node;
				rl_node->parent = target;
			}
			else target->right = nullptr;

			r_node  = nullptr;
			rl_node = nullptr;

			delete r_node;
			delete rl_node;
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

							// check if tree is still balanced or not
			if (get_insert) {
				bool skip_recursive = false;
				avl_node<V>::CALC_BALANCE(this , this->root , skip_recursive);
			}
			// confirmation
			return get_insert;
		}

		// o( log n )
		bool remove(V const& target_node_value) {

			avl_node<V>* temp = this->root;
			bool LorR = NULL;
			bool target_found = false;

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


			if (target_found) {
				// check if tree is still balanced or not
				bool skip_recursive = false;
				avl_node<V>::CALC_BALANCE(this , this->root , skip_recursive);
			}

			// confirmation
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

		// o( path )
		// travel from the current_node to the root
		void travle_to_root() {

			avl_node<V>* temp = this->current_node;

			while ( temp->parent != nullptr ){

				temp = temp->parent;

			}

			this->root = temp;
			this->current_node = this->root;

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

		void balance() {

			avl_node<V>::CALC_BALANCE(this , this->root , false);

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


		// o( 1 )
		// function check if a specific node is the same root of this tree
		bool is_the_root(avl_node<V>* target) {

			return (this->root == target);

		}

		template<typename T> friend class avl_node;

	}; // end of binary_tree_avl class

} // end of namespace