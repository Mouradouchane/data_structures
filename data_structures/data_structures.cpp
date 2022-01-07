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

bool comp (int const &x , int const &y){
	return x < y;
};

int main() {
	unsigned int size = 20;

	BinaryTree<int> byt( comp );

	std::vector<int> x;

	//if(x == 4) std::cout << "working !\n";

	/*
	byt.insert(4);
	byt.insert(2);
	byt.insert(1);
	byt.insert(4);
	byt.insert(6);

	if(lmb(5,5)) std::cout << "true !!\n";
	*/

	return 0;
}

