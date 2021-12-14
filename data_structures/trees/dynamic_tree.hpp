#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#pragma once

namespace trees {

// === node ~ methods =====
/*
	-- NAME ---------- BEST --> WORST

	length			=> o(1)
	isEmpty			=> o(1)

	insert			=> o(1)	--> o(n) ==
	remove			=> o(1) --> o(log n)

	jump_to			=> o(1) --> o(n * highet)

	search			=> o(1) --> o(n) ==

	getChild		=> o(1)	--> o(log n)
	replaceChild		=> o(1) --> o(log n)
	sortChilds		=> o(n log n) --> o(n�)

	operator +=		=> shortcut of insert
	operator -=		=> shortcut of removeChild
	operator ==>		=> shortcut of move_to
*/

template<typename t> class tree_node {

	private:
		tree_node<t>* parent;
		std::vector<tree_node<t>> children;

	public:
		std::string name;
		t value;


		// default constructor
		tree_node() {}

		// second constructor
		tree_node(std::string node_name, t node_value , tree_node<t> *parent_node)
			: name  { node_name } ,
			  value  { node_value } ,
			  parent{ parent_node }
		{ }

		// destructor
		~tree_node() { }

		// ========================
		// === here all methods ===
		// ========================

		// o(1) --> o(n)
		// no duplicated allowed in dynamic tree
		bool insert(std::string new_node_name , t new_node_value) {

			// soo first we check if any node is already exist with that name
			for (tree_node child : children) {
				// in case we found duplicate , no insert will be & return will be false
				if (child.name == new_node_name) return false;
			}

			// in case no duplicated found
			//tree_node<t> new_node(new_node_name, new_node_value, this);
			children.push_back(tree_node<t>(new_node_name, new_node_value, this));

			// confirmation :)
			return true;
		}

		// o(1) --> o(n)
		// index_of_match : useful if you want to access that index in childer vector
		bool search(std::string target_name , unsigned int &index_of_match = NULL){

			unsigned int i = 0;
			for (tree_node<t> child : children) {
				// in case target founded
				if (child.name == target_name) {
					if (index_of_match != 0 ) index_of_match = i;
					return true;
				}

				i += 1;
			}

			// in case target not founded
			return false;

		}

		// give access to dynamic_tree for making movements in tree
		template<typename v> friend class dynamic_tree;
};


// === dynamic tree ~ methods =====
/*
	-- NAME ------	BEST --> WORST
	search_up		o(1)
	search_down		o(1) --> o(children)
	move_to			o(1) --> o(children) 
	jump_to			o(children * path)
*/

template<typename v> class dynamic_tree {

	private:

		// main node in tree
		tree_node<v> root;

		// o(1) : function take a "temp node" & make a simple check if that temp include a parent with specific name
		// return will be a parent pointer or NULL
		tree_node<v>* search_up(std::string node_name , tree_node<v>* temp) {
		    if(temp->parent != NULL && temp->parent->name == node_name) {
                    return temp->parent;
		    }
		    else return NULL;
		}

		// o(1) : like "search_up" function , but this one for looking down
		tree_node<v>* search_down(std::string node_name , tree_node<v>* temp) {
            for(int i = 0 ; i < temp->children.size() ; i += 1){
				if(temp->children[i].name == node_name) return &temp->children[i];
		    }

		    return NULL;
		}

	public:

		// current_position => node for making movement in tree
		tree_node<v> *current_position;

		// constructor
		dynamic_tree(std::string root_name , v root_value) {
			root = tree_node<v>( root_name , root_value , NULL ); // null for parent "no parent for root"
			current_position = &root;
		}

		// destructor
		~dynamic_tree(){  }


		// o(1) --> o(children)
		// node_name : mean node where you want to go could be 'child' or 'parent' or even 'root'
		bool move_to(std::string node_name , bool up = false) {

			// in case you want to move to the root directlly
			if (node_name == "root") {

				// if you already in root
				if (current_position == &root) return false;

				// otherwise => jumping to the root & return true
				current_position = &root;
				return true;
			}

			// in case you want to move up to the parent directlly
			if( up ){

				if (current_position->parent != NULL && node_name == current_position->parent->name){
					current_position = current_position->parent;
					return true;
				}
				// in case target 'not found !'
				else return false;

			}
			else {

				// in case your target child node
				for (unsigned int i = 0; i < current_position->children.size(); i += 1) {
					// if target found we move to it
					if (current_position->children[i].name == node_name) {
						current_position = &current_position->children[i];
						return true;
					}
				}

			}

			// in case target 'not found !'
			return false;
		}

		// o(childrens) --> o(childrens * path)
		// like move_to but this require a hole path of "nodes names"
		// return will be a boolean as a confirmation of that operation
		// note !! jump will be happend only if "the hole path" is valid , otherwise nope :)
		bool jump_to(std::vector<std::string> full_path , bool up = false){
			
			// temp only for check & testing if "the hole path" are valid or not
			// if it valid we make it current_position in the end :)
			tree_node<v>* temp = current_position;

			// boolean up it's mean that "hole path" in parents direction "up"
			if(up){

				// we starting looking up by using a private function "search_up"
				for(std::string path : full_path){
					temp = search_up(path , temp);
					// in case not found "that's mean invalid path"
					if(temp == NULL) return false;
				}

			}
			// "up == false" mean that "hole path" in childs direction "down"
			else{

				// we starting looking down by using a private function "search_down"
				for(std::string path : full_path){
					temp = search_down(path , temp);
					// in case not found "that's mean invalid path"
					if(temp == NULL) return false;
				}

			}

			// in case "the hole path" is valid we should make temp the new current_position 
			current_position = temp;
			// and return true as a confirmation of that operation
			return true;
		}

};

}
