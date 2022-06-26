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
	
	binary_tree<int> nb( 16 , comp );
	nb.insert(5);
	nb.insert(3);
	nb.insert(8);
	nb.insert(9);
	nb.insert(2);
	nb.insert(1);
	nb.insert(7);
	nb.insert(10);
	nb.insert(3);
	nb.insert(13);
	/*
	nb.insert(6);
	nb.insert(9);
	nb.insert(-1);
	nb.insert(-4);
	*/

	unsigned int size = nb.size_at( nb.get_index_of(8) );

	binary_tree<int>* sub = nb.get_sub_tree( false , nb.get_index_of(5) );

	sub->print();

	std::cout << "==========" << '\n';

	nb.print();


	return 0;
}