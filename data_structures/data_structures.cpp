// c++ STD 
#include <iostream>
#include <vector>
#include <array> 
#include <algorithm>
#include <map>
#include <string>
// #include <functional>

#include "arrays/static_array.hpp"
#include "arrays/dynamic_array.hpp"

#define op ==

class pdf;
void test1();
void test2();

int main() {

	/*
	*/
	std::cout << "=============== OBJECTS TEST ===============\n";
	test1();
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
		pdf("pdf1") , pdf("pdf2") , pdf("pdf3") , pdf("pdf4")
	};

	for (pdf &p : arr) {
		std::cout << p.data << '\n';
	}

	std::cout << "===============================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "===============================================" << '\n';

}

// test on primitives "int float ..."
void test2() {

	arrays::static_array<int> arr = { 1, 1, 3 , 6, 2, 9 };

	for (int& num : arr) {

		std::cout << num << '\n';

	}

	std::cout << "===============================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "===============================================" << '\n';

}
