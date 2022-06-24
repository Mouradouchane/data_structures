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
	
	binary_tree<int> nb( 9 , comp);
	nb.insert(5);
	nb.insert(3);
	nb.insert(8);
	nb.insert(9);
	nb.insert(2);
	nb.insert(1);
	/*
	nb.insert(10);
	nb.insert(15);
	nb.insert(3);
	nb.insert(13);
	nb.insert(6);
	nb.insert(9);
	nb.insert(4);
	nb.insert(1);
	*/

	unsigned int height = nb.height();

	nb.print();

	std::cout << "========== "  << height << '\n';

	return 0;
}