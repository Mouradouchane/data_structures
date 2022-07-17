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
	nb.insert(8);
	nb.insert(12);
	nb.insert(10);
	//nb.insert(1);
	//nb.insert(4);
	//nb.insert(109);
	//nb.insert(10);
	//nb.insert(13);
	//nb.insert(120);
	//nb.insert(7);
	//nb.insert(1);
	//nb.insert(160);
	/*
	nb.insert(9);
	nb.insert(-1);
	nb.insert(-4);
	*/

	nb.print();
	std::cout << " ===========================\n";
	std::cout << " MAX HEIGTH : " << nb.max_height() << " \n";
	std::cout << " MIN HEIGTH : " << nb.min_height() << " \n";
	std::cout << " ===========================\n";


	return 0;
}