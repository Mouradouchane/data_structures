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

	BinaryTree<int> byt( 15 , comp );
	
	/*
	*/
	byt.insert(4);
	byt.insert(2);
	byt.insert(1);
	byt.insert(6);
	byt.insert(5);
	byt.insert(3);
	byt.insert(7);
	byt.insert(-1);
	byt.insert(10);

	byt.print();

	//byt.go_left();

	if(byt.go_left()) std::cout << "travel successed !\n" << byt.get() << " \n";
	else std::cout << "travel unsuccessed !!!!!\n";
	std::cout << byt.is_leaf_node() << '\n';

	return 0;
}


