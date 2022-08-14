// c++ STD 
#include <iostream>
#include <vector>
#include <array> 
#include <algorithm>
#include <map>
#include <string>

#include "arrays/static_array.hpp"
#include "arrays/dynamic_array.hpp"

using namespace arrays;


int main() {

	static_array<int> arr( 4 );

	int x = 5;

	arr.insert_at(0,11);
	arr.insert_at(1,22);
	arr.insert_at(2,33);
	arr.insert_at(3,44);

	arr.remove(0);
	arr.remove(5);

	arr.for_each([](int a) {
		std::cout << a << '\n';
	});

	/*
	heap.insert(40);
	heap.insert(37);
	heap.insert(39);
	heap.insert(38);
	heap.insert(46);
	heap.insert(58);
	heap.insert(1);
	heap.insert(13);
	heap.insert(4);
	heap.insert(109);
	heap.insert(10);
	heap.insert(120);

	heap.insert(-1);
	heap.insert(-2);
	heap.insert(0);
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



	std::cout << "================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "IS_FULL : " << arr.is_full() << '\n';
	std::cout << "IS_EMPTY: " << arr.is_empty() << '\n';
	std::cout << "================================" << '\n';



	return 0;
}