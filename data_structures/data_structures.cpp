// c++ STD 
#include <iostream>
#include <vector>
#include <array> 
#include <algorithm>
#include <map>
#include <string>

#include "arrays/static_array.hpp"
#include "arrays/dynamic_array.hpp"


class pdf;
void test1();
void test2();

#define op ==

int main() {

	/*
	std::cout << "=============== OBJECTS TEST ===============\n";
	test1();
	*/
	std::cout << "=============== PRIMITIVE TEST ===============\n";
	test2();

	return 0;

}

// objects for testing 
class pdf {
public:
	std::string data = "";
	pdf(std::string const& dt) {
		this->data = dt;
	}
	pdf() {}
	~pdf() { }

	void operator = (pdf const& new_data) {
		this->data = new_data.data;
	}
	/*
	void operator = (int nl) {
		this->data = "";
	}
	*/
	
	void operator = (std::string new_value) {
		this->data = new_value;
	}
};

// test on objects
void test1() {

	arrays::static_array<pdf> arr = {
		pdf("pdf1") , pdf("pdf2") , pdf("pdf3")
	};

	for (pdf &p : arr) {
		std::cout << p.data << '\n';
	}

	/*
	for (arrays::static_array<pdf>::iterator i = &arr[0]; i != arr.end() ; i += 1 ) {
		std::cout << "itr : " << i->data << '\n';
	}
	*/


	std::cout << "================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "IS_EMPTY: " << arr.is_empty() << '\n';
	std::cout << "IS_FULL : " << arr.is_full() << '\n';
	std::cout << "================================" << '\n';

}

// test on primitives "int float ..."
void test2() {

	arrays::static_array<int> arr  = { 1, 1, 3 , 6, 2, 9 };

	arr[2] = 55;

	for (int& num : arr) {

		std::cout << num << '\n';

	}

	std::cout << "================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "IS_EMPTY: " << arr.is_empty() << '\n';
	std::cout << "IS_FULL : " << arr.is_full() << '\n';
	std::cout << "================================" << '\n';

}
