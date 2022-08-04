// c++ STD 
#include <iostream>
#include <vector>
#include <array> 
#include <algorithm>
#include <map>
#include <string>

#include "trees/dynamic_tree.hpp"
#include "trees/binary_tree_arr.hpp"
#include "trees/binary_tree_nodes.hpp"
#include "trees/binary_tree_avl.hpp"
#include "trees/binary_heap.hpp"

using namespace trees;


bool comp(int const& x, int const& y) {

	return x < y;
};

int main() {

	std::vector<int> arr = { 11 , 2 , 30 , 4 , 50 , 6 };
	
	binary_heap<int> heap( 12 , comp );

	heap.insert(37);
	heap.insert(46);
	heap.insert(58);
	/*
	heap.insert(38);
	heap.insert(39);
	heap.insert(40);
	heap.insert(-1);
	heap.insert(-2);
	heap.insert(0);
	heap.insert(13);
	heap.insert(14);
	heap.insert(16);
	heap.insert(10);
	heap.insert(1);
	heap.insert(4);
	heap.insert(109);
	heap.insert(10);
	heap.insert(13);
	heap.insert(120);
	heap.insert(7);
	heap.insert(1);
	heap.insert(160);
	heap.insert(9);
	heap.insert(500);
	heap.insert(44);
	*/

	heap.print();


	std::cout << " ===========================\n";

	std::cout << "ROOT    : " << heap.get_root() << " \n";
	std::cout << "LENGTH  : " << heap.length() << " \n";
	std::cout << "SIZE    : " << heap.size() << " \n";
	std::cout << "IS_FULL : " << heap.is_full() << " \n";
	std::cout << "LOCKED  : " << heap.is_locked() << " \n";

	std::cout << " ===========================\n";

	
	return 0;
}