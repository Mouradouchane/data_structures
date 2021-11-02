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

	setChild		=> o(1)	--> o(log n)
	getChild		=> o(1)	--> o(log n)
	replaceChild	=> o(1) --> o(log n)
	sortChilds		=> o(n log n) --> o(n²)
	removeChild		=> o(1) --> o(log n)

	getParentName	=> o(1)
	go_to			=> o(1) --> o(n)
	move_to			=> o(1) --> o(n * height)

	search			=> o(log n) --> o(n)

	operator +=		=> shortcut of setChild
	operator -=		=> shortcut of removeChild
*/

template<typename t> class tree_node {

	protected:
		tree_node<t>* parent;
		std::vector<tree_node> childs;

	public:
		std::string name;
		t value;

		// default constructor
		tree_node() {}

		// second constructor
		tree_node(std::string node_name, t node_value , tree_node<t> *parent_node) 
			: name{ node_name } , 
			  value{ node_value } ,
			  parent{ parent_node }
		{ }

		// destructor 
		~tree_node() { }

		// ========================
		// === here all methods === 
		// ========================
		
		unsigned int length() {
			return childs.size();
		}

		bool isEmpty() {
			return (childs.size() > 0) ? false : true;
		}

		bool setChild(std::string child_name , t child_value) {
			
			//check if any child with that name is exist
			for (tree_node child : childs) {
				if (child.name == child_name) return false;
			}

			// add new child
			tree_node<t> new_child(child_name, child_value, this);
			childs.push_back(new_child);


			return true;

		}


		// give access to 'dynamic tree' for dealing with nodes :)
		template<typename v> friend class dynamic_tree;
};



// === dynamic tree ~ methods =====
/*
	-- NAME ------ BEST --> WORST

*/

template<typename v> class dynamic_tree {

	private:
		
		// main node in tree 
		tree_node<v> root;

	public:
		// current_position => node for making movement in tree
		tree_node<v> *current_position;

		// constructor 
		dynamic_tree(std::string root_name , v root_value) {
			root = tree_node<v>( root_name , root_value , NULL );
			current_position = &root;
		}

		// destructor 
		~dynamic_tree(){  }

		
};

}