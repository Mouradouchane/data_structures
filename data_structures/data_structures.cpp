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

bool lmb (int &x , int &y){
	return x < y;
};

int main() {
	unsigned int size = 20;

	BinaryTree<int> byt( lmb );
	BinaryTree<int> bbyt( 10, [](int &a , int &b){ return a < b; } );
	BinaryTree<float> fbt( size , [](float &a , float &b){return a < b;} );

	/*
	if(lmb(5,5)) std::cout << "true !!\n";
	else std::cout << "false !!\n";
	*/

	return 0;
}

