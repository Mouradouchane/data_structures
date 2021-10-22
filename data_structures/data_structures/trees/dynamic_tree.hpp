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
		std::string name;
		t value;
		tree_node* parent;
		std::vector<tree_node> childs;

	public:
		// default  constructor
		tree_node() {}

		// constructor
		tree_node(std::string node_name, t node_value) : name{ node_name }, value{ node_value } {
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

		// o(1) : get name of the parent node or null in case you are in 'root'
		std::string getParentName() {
			return parent->name;
		}

		// o(1) : length of childs 'how many childs in this node'
		unsigned int length() {
			return childs.size();
		}

		// give access to 'dynamic tree' for dealing with nodes :)
		template<typename v> friend class dynamic_tree;
};


// === dynamic tree ~ methods =====
/*
	-- NAME ------ BEST --> WORST

	length		=> o(1)

	addNode		=> o(nodes + 1)
	setName		=> o(1)
	getValue	=> o(1)
	move_to		=> o(1) --> o(nodes)
	search		=> o(h) --> o(h * log n) // h = tree height
*/

template<typename v> class dynamic_tree {

	private:
		// length of all nodes 'start with root as 1'
		unsigned int len = 1;
		
		tree_node<v> root;
		// current_position : current node where are you right know
		tree_node<v>* current_position;

	public:
		// constructor 
		dynamic_tree(std::string root_name , v root_value) {
			root = tree_node<v>(root_name, root_value);
			current_position = &root;
		}

		// destructor 
		~dynamic_tree(){  }

		// o(nodes + 1)
		// add "new node with value" as a "child" in this current "position"
		bool addNode(std::string node_name, v value) {

			// check if that node already exist
			unsigned int n = 0;
			for ( ; n < current_position->childs.size(); n += 1) {
				// return false mean that node is already exist 
				if (node_name == current_position->childs[n].name) return false;
			}

			// in case no duplicate found 

			// add new node
			current_position->childs.push_back( tree_node<v>(node_name,value) ) ;
			// update length
			len += 1;
			// true as confirmation
			return true;
		}

		// o(1) --> o(nodes)
		// goto : make 'current_position' move between nodes
		// return bool as a confirmation of that operation if it happend or not :)
		bool move_to(std::string node_name) {

			// in case you want to go to the root directlly you can
			if (node_name == "root" || node_name == root.name) {
				current_position = &root;
				// true as confirmation 
				return true;
			}

			unsigned int n = 0;
			for (; n < current_position->childs.size();  n += 1) {
				// in case we found it 
				// we move "current_position" to that node 
				if (current_position->childs[n].name == node_name) {
					current_position = &current_position->childs[n];
					return true;
				}
			}

			// in case that node who you want to move to it is not found 
			return false;
		}

		// o(1)
		// length of all childs nodes on that "current_position"
		unsigned int child_length() {
			return current_position->childs.size();
		}

		// o(1)
		// change node name
		void setName(std::string new_name) {
			current_position->name = new_name;
		}

		// o(1)
		// replace value of that current node "if exist" 
		void replace(v new_value) {
			current_position->value = new_value;
		}

		// o(nodes)
		// replace value of that child "if it exist" 
		bool replace(std::string new_node_name, v new_value) {

			for (tree_node<v> node : current_position->childs) {
				if (node->name == new_node_name) {
					
					// replace name & value
					node->name = new_node_name;
					node->value = new_value;
					
					// confirmation in that case "replace happend"
					return true;
				}
			}

			// in case replace not happend
			return false;
		}

		// o(1) --> o(nodes)
		// remove that child with all it's childs "if exist" 
		bool removeChild(std::string child_name) {

			for (tree_node<v> node : current_position->childs) {
				if (node->name == child_name) {

					// remove 
					current_position->childs.erase(node);

					// true as confirmation of that operation
					return true;
				}
			}

		}
	
		void print() {

			std::cout << current_position->name << " | " << current_position->value << '\n';
		}
};

}