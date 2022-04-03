// c++ STD 
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include "trees/dynamic_tree.hpp"
#include "trees/binary_tree.hpp"
#include "trees/n_binary_tree.hpp"

using namespace trees;

/*
	===> just cpp file for testing
*/

bool comp(int const& x, int const& y) {
	return x < y;
};

int main() {
	
	n_binary_tree<int> nb(111, comp);

	nb.insert(5);
	nb.insert(2);
	nb.insert(7);
	nb.insert(2);
	nb.insert(8);
	nb.insert(10);
	nb.insert(5);
	nb.insert(3);
	
	nb.print();

	std::cout << "print passed !\n";

	return 0;
}