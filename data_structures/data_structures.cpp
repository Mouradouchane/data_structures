	// c++ STD 
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include "trees/dynamic_tree.hpp"
#include "trees/binary_tree.hpp"

using namespace trees;

	/*
		===> just cpp file for testing 
	*/

int main() {

	BinaryTree<int> byt(1);
	std::cout << "tree size ! "<< byt.length() << "\n";
	

	return 0;
}

