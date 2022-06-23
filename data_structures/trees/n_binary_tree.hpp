#pragma once

namespace trees {

	template<typename T> class b_node {
		
		private:

			b_node<T>* parent;
			b_node<T>* left;
			b_node<T>* right;

		public:
			// node value
			T value;

			// node constructor 1
			b_node(T node_value) :value{ node_value } { 
			}

			// node constructor 1
			b_node(T node_value, b_node<T>* node_parent = NULL) :value{ node_value }, parent{ node_parent } {
			}

			// node constructor 3
			b_node(){ }

			// node destructor
			~b_node() {

				if(this->left  != NULL) this->left->~b_node();
				if(this->right != NULL) this->right->~b_node();

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

			template<typename T> friend class n_binary_tree;
	}; // end of node class

	template<typename V> class n_binary_tree {

		private:
			b_node<V>* root;
			unsigned int len = 0;

			bool (*comp_function)(V const &node_a, V const &node_b);

		public:
			b_node<V>* current_node;

			// constructor 1
			n_binary_tree( V root_value  , bool(*comp)(V const &node_a, V const &node_b) )
				:comp_function{ comp }
			{
				root = new b_node<V>(root_value,NULL);
				current_node = root;
			}

			// constructor 2
			n_binary_tree(bool(*comp)(V const& node_a, V const& node_b))
				:comp_function{ comp }
			{
				root = new b_node<V>();
				current_node = root;
			}

			// destructor
			~n_binary_tree() {
				/*
				delete this->root;
				delete this->current_node;
				*/
			}

			// o( log n )
			bool insert(V const new_node_value) {

				b_node<V>* temp = this->root;

				while (temp != NULL) {

					if (temp->value == new_node_value) return false;

					if (temp->value == NULL) {

						temp->value = new_node_value;
						this->len += 1;
						return true;

					}
					else {
						if ( this->comp_function(new_node_value , temp->value) ) {
							
							if (temp->left == NULL) {

								temp->left = new b_node<V>(new_node_value , temp);
								this->len += 1;
								return true;

							}
							else temp = temp->left;
						}
						else {

							if (temp->right == NULL) {

								temp->right = new b_node<V>(new_node_value, temp);
								this->len += 1;
								return true;

							}
							else temp = temp->right;
						}
					}
				}

				return false;
			}

			// o( 1 )
			unsigned int length() {
				return this->len;
			}

			// o( log n )
			bool remove(V const &target_node_value) {
			
				b_node<V>* temp = root;

				while( temp != NULL ){

					if (temp->value == target_node_value) {

						temp->~b_node(); // delete this node & all it's children recursivly
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

				delete temp;

				return false;
			}

			bool search(V const &target_node_value) {
				
				return false;
			}

			bool travel_up() {
				
				return false;
			}

			bool travle_up() {

				return false;
			}

			bool travle_down() {

				return false;
			}



			// o( n ) 
			// print function just for testing 
			void print() {

				this->root->print();

			}

	}; // end of n_binary_tree class

} // end of namespace