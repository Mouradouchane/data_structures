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
		tree_node<t>* parent;
		std::vector<tree_node> childs;

	public:
		// default  constructor
		tree_node() {}

		// constructor
		tree_node(std::string node_name, t node_value , tree_node<t> *parent_node) 
			: name{ node_name } , 
			  value{ node_value } ,
			  parent{ parent_node }
		{ }

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

	addNode			=> o(nodes + 1)
	setName			=> o(1)

	getName			=> o(1)
	getParentName	=> o(1)

	getValue		=> o(1)
	getValueByRef	=> o(1)

	replace			=> o(1)
	replaceChild    => o(1) --> o(nodes)

	move_to			=> o(1) --> o(nodes)
	jump_to			=> o(1) --> o(nodes * height)
	search			=> o(h) --> o(h * log n) // h = tree height

	getChildName	=> o(1) --> o(nodes)
	getChildNames	=> o(nodes)

	getChildValue	=> o(1) --> o(nodes)
	getChildValueByRef	=> o(1) --> o(nodes)
	getChildValues	=> o(nodes)

	sortChilds		=> o(n log n) --> o(n²)
	child_length	=> o(1)
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
			root = tree_node<v>( root_name , root_value , NULL );
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

			// in case "no duplicate found" 

			// add new node
			tree_node<v> newnode(node_name, value, current_position);
			current_position->childs.push_back( newnode ) ;

			len += 1;
			// true as confirmation
			return true;
		}

		// o(1) --> o(nodes)
		// goto : make 'current_position' move between nodes
		// return bool as a confirmation of that operation if it happend or not :)
		bool move_to(std::string node_name) {

			// in case you want to 'GOTO' root
			if (current_position != &root) {
				if (node_name == "root" || node_name == root.name){

					// GOTO root direct
					current_position = &root;
					// true as confirmation 
					return true;

				}
			}

			// in case you want to 'GOTO' parent
			// you can if you are not in root
			if (current_position->parent != NULL) {
				if (node_name == "parent" || node_name == current_position->parent->name) {

					// GOTO parent direct
					current_position = current_position->parent;
					// true as confirmation 
					return true;

				}
			}

			// in case you want to 'GOTO' child
			unsigned int n = 0;
			for (; n < current_position->childs.size();  n += 1) {
				// in case we found it 
				// we move "current_position" to that node 
				if (current_position->childs[n].name == node_name) {
					current_position = &current_position->childs[n];
					return true;
				}
			}

			// in case what you want to move to is not found 
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
	
		// o(1)
		// get value of "current_position node" "by value"
		v getValueByValue() {
			return current_position->value;
		}

		// o(1)
		// get value of "current_position" 
		v* getValueByReference() {
			return &current_position->value;
		}

		// o(nodes)
		// get vector contain all childs names in that "current_position"
		std::vector<std::string> getChildNames() {

			std::vector<std::string> names;

			for (tree_node<v> node : current_position->childs) {
				names.push_back(node.name);
			}

			return names;
		}

		// o(nodes)
		// get vector contain all childs values depened on where is "current_position"
		std::vector<v> getChildByValues() {

			std::vector<v> values;

			for (tree_node<v> node : current_position->childs) {
				values.push_back(node.value);
			}

			return values;
		}

		// o(1)
		// some debug & testing functions
		std::string getParentName() {
			return (current_position->parent == NULL) ? "" : current_position->parent->name;
		}

		// o(1)
		std::string getName() {
			return current_position->name;
		}

		void print() {
			std::cout << current_position->name << " | " << current_position->value << '\n';
		}
};

}