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

	arrays::dynamic_array<pdf> arr(5 ,{
		pdf("pdf0") ,  pdf("pdf1") ,  pdf("pdf2") ,  pdf("pdf3") , pdf("pdf4") , pdf("pdf5")
	});

	arr.insert(1, pdf("pdf1"));

	arr.for_each(false, [](pdf& e) {
		std::cout << e.data << '\n';
	});

	/*
	arrays::dynamic_array<pdf>::iterator s = arr.begin();
	arrays::dynamic_array<pdf>::iterator e = arr.end();
	for (; s != e; ++s) if (s != nullptr) std::cout << s->data << "\n";
	*/
	
	std::cout << "===============================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "===============================================" << '\n';

}

// test on primitives "int float ..."
void test2() {

	arrays::static_array<int> arr = { 1, 1, 3 , 6, 2, 9 };
	
	arr.for_each(
		true , [](int& a) {
			std::cout << "CB : " << &a << '\n';
		}
	);

	std::cout << "===============================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "===============================================" << '\n';

}
