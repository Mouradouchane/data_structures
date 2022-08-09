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

	static_array<int> arr( { 10,22,31,14,25,63,7,80 } );

	static_array<int> x = { 1,5,6,88 };

	arr.reverse();

	arr.for_each([](int a) {
		std::cout << a << '\n';
	});


	/*
	arr.for_each([](int a) {
		std::cout << a << '\n';
	});

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


	return 0;
}