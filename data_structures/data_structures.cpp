// c++ STD 
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include "trees/dynamic_tree.hpp"
#include "trees/binary_tree_arr.hpp"
#include "trees/binary_tree_nodes.hpp"
#include "trees/avl_tree.hpp"

using namespace trees;


bool comp(int const& x, int const& y) {
	return x < y;
};

int main() {
	
	binary_tree_nodes<int> nb( comp );
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
	std::cout << nb.remove(5) << '\n';
	nb.print();

	/*
	std::cout << nb.search(7) << '\n';
	std::cout << nb.search(3) << '\n';
	std::cout << nb.search(11) << '\n';
	*/

	return 0;
}