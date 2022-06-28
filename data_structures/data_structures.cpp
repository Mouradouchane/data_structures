// c++ STD 
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include "trees/dynamic_tree.hpp"
#include "trees/binary_tree.hpp"
#include "trees/n_binary_tree.hpp"
#include "trees/avl_tree.hpp"

using namespace trees;


bool comp(int const& x, int const& y) {
	return x < y;
};

int main() {
	
	binary_tree_arr<int> nb( 8 , comp );
	nb.insert(8);
	nb.insert(3);
	nb.insert(5);
	nb.insert(2);
	nb.insert(10);
	nb.insert(13);
	nb.insert(7);
	nb.insert(1);
	/*
	nb.insert(9);
	nb.insert(3);
	nb.insert(6);
	nb.insert(9);
	nb.insert(-1);
	nb.insert(-4);
	*/


	nb.print();

	std::cout << "is 1 leaf : " << nb.is_leaf_node(nb.get_index_of(1)) << '\n';
	std::cout << "is 5 leaf : " << nb.is_leaf_node( nb.get_index_of(10) ) << '\n';

	return 0;
}