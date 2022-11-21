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
template<typename T> void p_test(size_t&& size);

int main() {

	std::cout << "=============== OBJECTS TEST ===============\n";
	test1();
	std::cout << "=============== PRIMITIVE TEST ===============\n";
	p_test<int>(6);

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

	pdf& operator = (pdf const& new_data) {
		this->data = new_data.data;
		return *this;
	}
	
	void operator = (std::string new_value) {
		this->data = new_value;
	}

};

// test on objects
void test1() {

	arrays::dynamic_array<pdf> arr(5 ,{
		pdf("pdf0") ,  pdf("pdf1") ,  pdf("pdf2") ,  pdf("pdf3") , pdf("pdf4") , pdf("pdf5")
	});

	/*
	*/

	arr.remove(1);
	arr[1] = pdf("edit");

	std::cout << "const : " << arr[1].data << "\n";
	std::cout << "const : " << arr[2].data << "\n";


	arr.for_each(true, [](size_t i , bool emp , pdf& e) {
		if (emp) std::cout << i << " : " << e.data << '\n';
		else std::cout << i << " : EMPTY\n";
	});


	std::cout << "===============================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "===============================================" << '\n';

}

// test on primitives "int float ..."
template<typename T> void p_test( size_t && size ) {

	arrays::dynamic_array<T> arr( size , size );

	std::srand(std::time(0));

	for (size_t i = 0; i < size; i += 1) {

		arr.insert( i, (T)std::rand());
		
	}

	arr.remove(1);
	arr.remove(2);

	//arr.reverse();


	arr.for_each(
		true , [](size_t i , bool emp  , T& a) {
			if (emp) std::cout << i << " : " << a << '\n';
			else std::cout << i << " : EMPTY\n";
		}
	);

	std::cout << "===============================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "===============================================" << '\n';

}
