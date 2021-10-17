#include <iostream>
#include <vector>
#include <string>

// === trees ~ methods =====
/*
	-- NAME ------ BEST --> WORST
	
	length		=> o(1)
	isEmpty		=> o(1)

	set			=> o(1)	--> o(n)
	get			=> o(1) --> o(log n)
*/

namespace trees {

template<typename t> class tree_node {

	private:
		std::string name = "def";
		t value;
		tree_node* parent = NULL;
		std::vector<tree_node> childs;
	public:
		// constructor 
		tree_node(std::string node_name, t node_value) {
		}
		// destructor 
		~tree_node() { }
};


template<typename t> class dynamic_tree {

	private:
		unsigned int len = 0;
		tree_node<t> root;

	public:
		// constructor 
		dynamic_tree(std::string root_name , t root_value) {

		}

		// destructor 
		~dynamic_tree(){ }
};

}