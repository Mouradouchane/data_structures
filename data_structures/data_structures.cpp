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


int main() {

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

};

// test on objects
void test1() {

	arrays::static_array<pdf> arr1 = { pdf("pdf1") ,  pdf("pdf2") ,  pdf("pdf3") };
	arrays::static_array<pdf> arr = { pdf("pdf4") ,  pdf("pdf5") ,  pdf("pdf6") };
	/*
	arr.insert(pdf("PDF0"));
	arr.insert(pdf("PDF1"));
	arr.insert(pdf("PDF2"));
	arr.insert(pdf("PDF3"));
	arr.insert(pdf("PDF4"));
	arr.insert(pdf("PDF5"));
	*/
	
	arr = { pdf("pdf1") ,  pdf("pdf2") ,  pdf("pdf3") };
	
	arrays::static_array<pdf>::iterator it = arr.begin();

	pdf dt = arr.get(2);

	//it -= 1;
	//std::cout << it->data << " : 0x" << &it << '\n';
	std::cout << dt.data << " : 0x" << &dt << '\n';

	std::cout << "================================" << '\n';
	arr.for_each([](pdf& a) {
		std::cout << a.data << " : 0x" << &a << '\n';
	});


	std::cout << "================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "IS_EMPTY: " << arr.is_empty() << '\n';
	std::cout << "IS_FULL : " << arr.is_full() << '\n';
	std::cout << "================================" << '\n';

}

// test on int float ... primitives
void test2() {

	arrays::static_array<int> arr1 = { 1, 2, 3, 5, 4, 9, 8, 6, 2, 9, 9 };
	arrays::static_array<int> arr  = { 1, 2, 3, 5, 4, 9 };

	arr = { 1, 2, 3, 5, 4, 9, 8, 6, 2, 9, 9 };
	//for (int i = 0; i < 9; i += 1) arr.insert(std::rand());

	arr.for_each([](int& n) {
		std::cout << n << ": 0x" << &n << '\n';
	});

	std::cout << "================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "IS_EMPTY: " << arr.is_empty() << '\n';
	std::cout << "IS_FULL : " << arr.is_full() << '\n';
	std::cout << "================================" << '\n';

}

/*
size_t size = 4;
std::initializer_list<int> elements = { 4,8,9,10,3 };

std::vector<int> vt;
std::vector<int>::iterator vit = vt.begin();
*/
// { pdf("PDF1"),  pdf("PDF2") ,  pdf("PDF3") , pdf("PDF4") }
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


