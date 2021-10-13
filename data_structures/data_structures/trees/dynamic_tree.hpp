#include <iostream>
#include <string>


namespace trees {

template<typename t> class tree_node{

private :
	std::string name = "def";
	t value;
	tree_node* parent = NULL;
	tree_node* childs = NULL;
public:
	// constructor 
	tree_node() {
	}
	// destructor 
	~tree_node() { }
}

template<typename t> class dynamic_tree {

public:
	// constructor 
	dynamic_tree() {

	}

	// destructor 
	~dynamic_tree(){ }
};

}