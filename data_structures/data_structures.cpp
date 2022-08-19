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

	size_t size = 4;
	std::initializer_list<int> elements = { 4,8,9,10,3 };

	dynamic_array<int> arr  = { 1,2,3,4 };
	dynamic_array<int> arr2 = { 5,6,7,8 };

	dynamic_array<int> t = arr + arr2;


	t.for_each([](int a) {
		std::cout << a << '\n';
	});

	/*

	arr.insert(0, 111);
	arr.insert_at(0,11);
	arr.insert_at(1,22);
	arr.insert_at(2,33);
	arr.insert_at(3,44);

	arr.remove(0);
	arr.remove(5);

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
	std::cout << "SIZE    : " << t.size() << '\n';
	std::cout << "LENGTH  : " << t.length() << '\n';
	std::cout << "IS_EMPTY: " << t.is_empty() << '\n';
	std::cout << "================================" << '\n';

	return 0;
}