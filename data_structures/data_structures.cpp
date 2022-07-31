// c++ STD 
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include "trees/dynamic_tree.hpp"
#include "trees/binary_tree_arr.hpp"
#include "trees/binary_tree_nodes.hpp"
#include "trees/binary_tree_avl.hpp"

using namespace trees;


bool comp(int const& x, int const& y) {
	return x < y;
};

int main() {
	
	binary_tree_avl<int> nb( comp );

	nb.insert(58);
	nb.insert(46);
	nb.insert(37);
	nb.insert(38);
	nb.insert(39);
	nb.insert(40);
	nb.insert(-1);
	nb.insert(-2);
	nb.insert(0);
	nb.insert(13);
	nb.insert(14);
	nb.insert(16);
	nb.insert(10);
	nb.insert(1);
	nb.insert(4);
	nb.insert(109);
	nb.insert(10);
	nb.insert(13);
	nb.insert(120);
	nb.insert(7);
	nb.insert(1);
	nb.insert(160);
	nb.insert(9);
	nb.insert(500);
	nb.insert(44);
	/*
	*/

	nb.print();

	std::cout << " ===========================\n";

	std::cout << " MAX HEIGTH : " << nb.max_height() << " \n";
	std::cout << " MIN HEIGTH : " << nb.min_height() << " \n";
	std::cout << " IS BALANED : " << (nb.is_balanced() ? "true" : "false") << " \n";

	std::cout << " ===========================\n";

	
	return 0;
}