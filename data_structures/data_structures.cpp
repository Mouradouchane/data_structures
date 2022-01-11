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

	BinaryTree<int> byt( 10 , comp );
	
	/*
	*/
	byt.insert(4);
	byt.insert(2);
	byt.insert(1);
	byt.insert(4);
	byt.insert(6);
	byt.insert(5);
	byt.insert(3);
	byt.insert(7);
	byt.insert(-1);

	byt.print();

	int x , y , z;
	if( byt.search_from(1,3,x) ) std::cout << "found at "<< x << "\n";
	if( byt.search_from(2,7,y) )  std::cout << "found at "<< y << "\n";
	if( byt.search_from(0,-1,z) )  std::cout << "found at "<< z << "\n";


	return 0;
}

