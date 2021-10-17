#include <iostream>
#include <vector>
#include <string>

#pragma once


namespace trees {


// === node ~ methods =====
/*
	-- NAME ---------- BEST --> WORST

	len	=> o(1)
	isEmpty			=> o(1)

	getName			=> o(1)
	setName			=> o(1)

	getValue		=> o(1)
	setValue		=> o(1)
	
	setChild		=> o(1)	--> o(log n)
	search			=> o(log n) 

	removeChild		=> o(1) --> o(log n)
*/

template<typename t> class tree_node {

	protected:
		unsigned int child_length = 0;
		std::string name = "def";
		t value;
		tree_node* parent = NULL;
		std::vector<tree_node> childs;
	public:
		// default  constructor
		tree_node(){}

		// constructor
		tree_node(std::string node_name, t node_value) {
			name = node_name;
			value = node_value;
		}
		// destructor 
		~tree_node() { 
		}

		// o(1) : just change node name
		void setName(std::string node_name) {
			name = node_name;
		}

		// o(1) : just change node value
		void setValue(t node_value) {
			value = node_value;
		}

		// o(1) : get node name
		std::string getName() {
			return name;
		}

		// o(1) : get node value
		t getValue() {
			return value;
		}

		// o(1) : length of childs 'how many childs in this node'
		unsigned int length() {
			return child_length;
		}
};


// === dynamic tree ~ methods =====
/*
	-- NAME ------ BEST --> WORST

	length		=> o(1)
	isEmpty		=> o(1)

	setChild	=> o(1)	--> o(n)
	setName		=> o(1)
	get			=> o(1) --> o(log n)
	search		=> o(h) --> o(h * log n) // h = tree height
*/


template<typename t> class dynamic_tree {

	private:
		unsigned int len = 0;
		tree_node<t> root;

	public:
		// constructor 
		dynamic_tree(std::string root_name , t root_value) {
			root = tree_node<t>(root_name, root_value);
		}

		// destructor 
		~dynamic_tree(){  }

};

}