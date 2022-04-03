#pragma once

namespace trees {

	template<typename T> class node {
		
		private:

			node<T>* parent;
			node<T>* left;
			node<T>* right;

		public:
			// node value
			T value;

			// node constructor 1
			node(T node_value) :value{ node_value } { 
			}

			// node constructor 1
			node(T node_value, node<T>* node_parent = NULL) :value{ node_value }, parent{ node_parent } {
			}

			// node constructor 3
			node(){ }

			// node destructor
			~node() {

				this->left->~node();
				this->right->~node();

				delete this->left;
				delete this->right;
			}

			void print() {

				std::cout << "--> " << this->value;

				if (this->left  != NULL) this->left->print();
				if (this->right != NULL) this->right->print();
				
				std::cout << std::endl;
			}

			template<typename T> friend class n_binary_tree;
	}; // end of node class

	template<typename V> class n_binary_tree {

		private:
			node<V>* root;

			bool (*comp_function)(V const &node_a, V const &node_b);

		public:
			node<V>* current_node;

			// constructor 1
			n_binary_tree( V root_value  , bool(*comp)(V const &node_a, V const &node_b) )
				:comp_function{ comp }
			{
				root = new node<V>(root_value,NULL);
				current_node = root;
			}

			// constructor 2
			n_binary_tree(bool(*comp)(V const& node_a, V const& node_b))
				:comp_function{ comp }
			{
				root = new node<V>();
				current_node = root;
			}

			// destructor
			~n_binary_tree() {
				
			}

			// o( log n )
			bool insert(V new_node_value) {

				node<V>* temp = this->root;

				while (temp != NULL) {

					if (temp->value == new_node_value) return false;

					if (temp->value == NULL) {
						temp->value = new_node_value;
						return true;
					}
					else {
						if ( this->comp_function(new_node_value , temp->value) ) {
							
							if (temp->left == NULL) {

								temp->left = new node<V>(new_node_value , temp);
								return true;

							}
							else temp = temp->left;
						}
						else {

							if (temp->right == NULL) {

								temp->right = new node<V>(new_node_value, temp);
								return true;

							}
							else temp = temp->right;
						}
					}
				}

				return false;
			}

			void print() {

				this->root->print();

			}

	}; // end of n_binary_tree class

} // end of namespace