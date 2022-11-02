// c++ STD 
#include <iostream>
#include <vector>
#include <array> 
#include <algorithm>
#include <map>
#include <string>

#include "arrays/static_array.hpp"
#include "arrays/dynamic_array.hpp"

class pdf {
	public :
		std::string data = "";
		pdf( std::string const& dt) {
			this->data = dt;
		}
		pdf() {}
		~pdf() { }

		void operator = (pdf const& new_data) {
			this->data = new_data.data;
		}
};

int main() {
	/*
	size_t size = 4;
	std::initializer_list<int> elements = { 4,8,9,10,3 };

	std::vector<int> vt;
	std::vector<int>::iterator vit = vt.begin();
	*/
	// { pdf("PDF1"),  pdf("PDF2") ,  pdf("PDF3") , pdf("PDF4") }
	arrays::static_array<pdf> arr({ pdf("PDF1"),  pdf("PDF2") ,  pdf("PDF3") , pdf("PDF4") });
	/*
	arr[0] = pdf("PDF0");
	arr[1] = pdf("PDF1");
	arr[2] = pdf("PDF2");
	arr[3] = pdf("PDF3");
	arr.insert(pdf("PDF0"));
	arr.insert(pdf("PDF1"));
	arr.insert(pdf("PDF2"));
	arr.insert(pdf("PDF3"));
	*/

	arr.remove(2);
	arrays::static_array<pdf>::iterator it = arr.begin();

	//it -= 1;
	//std::cout << it->data << " : 0x" << &it << '\n';
	std::cout << arr.get(3)->data << " : 0x"  << arr.get(3) << '\n';

	std::cout << "================================" << '\n';
	arr.for_each([](pdf& a) {
		std::cout << a.data << " : 0x" << &a << '\n';
	});

	std::cout << "================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "IS_EMPTY: " << arr.is_empty() << '\n';
	std::cout << "================================" << '\n';

	return 0;
}

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


