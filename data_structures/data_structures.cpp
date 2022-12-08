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

// objects for testing 
class pdf {
public:
	std::string data = "";
	pdf(std::string const& dt) {
		this->data = dt;
	}
	pdf() { }
	~pdf() { }

	pdf& operator = (pdf const& new_data) {
		this->data = new_data.data;
		return *this;
	}

	void operator = (std::string new_value) {
		this->data = new_value;
	}

	void operator = (int const& index) {
		this->data = "";
	}

	bool operator != (pdf const& other) {
		return (this->data == other.data);
	}
};

void test1();
template<typename T> void p_test(size_t&& size);

int main() {
	
	std::cout << "=============== OBJECTS TEST ===============\n";
	test1();
	std::cout << "=============== PRIMITIVE TEST ===============\n";
	p_test<int>(6);

	return 0;
}


// test on objects
void test1() {

	arrays::dynamic_array<pdf> arr(10 ,{
		pdf("pdf0") ,  pdf("pdf1") ,  pdf("pdf2") ,  pdf("pdf3") , pdf("pdf4") , pdf("pdf5")
	});
	

	for ( pdf & s : arr ) {
		std::cout << " iterator : " << s.data << '\n';
	};

	std::cout << "===============================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "===============================================" << '\n';

}


// test on primitives "int float ..."
template<typename V> void p_test( size_t && size ) {

	arrays::dynamic_array<V> arr( size , size );

	std::srand(std::time(0));

	for (size_t i = 0; i < size; i += 1) {

		arr.insert( i, (V)std::rand());
		
	}

	arr.remove(1);
	arr.remove(2);

	arr.for_each(
		true, [](size_t i, bool b, V& e) {
			std::cout << i << " " << e << '\n';
		}
	);
	
	arrays::dynamic_array<int>::iterator s = arr.begin();
	arrays::dynamic_array<int>::iterator e = arr.end();
	
	for (; s != e; ++s) {
		std::cout << " iterator : " << *s << '\n';
	};

	std::cout << "===============================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "===============================================" << '\n';

}
