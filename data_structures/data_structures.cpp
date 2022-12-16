// c++ STD 
#include <iostream>
#include <vector>
#include <array> 
#include <algorithm>
#include <map>
#include <string>
// #include <functional>

#include "graphs/graph_list.hpp"
#include "linkedlists/singly_LinkedList.hpp"


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
		return (this->data != other.data) ? true : false;
	}

	bool operator == (pdf const& other) {
		return (this->data == other.data) ? true : false;
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

	graphs::l_graph<pdf> g();
	/*
	{
		pdf("pdf0") ,  pdf("pdf1") ,  pdf("pdf2") ,  pdf("pdf3") , pdf("pdf4") , pdf("pdf5")
	}
	*/



	/*
	linkedlist::singly_LinkedList<pdf> arr = { pdf("a") , pdf("b") , pdf("c") };
	//for (linkedlist::iterator<pdf> a = arr.begin(); a != arr.end(); ++a) {
	for (linkedlist::node<pdf> const& a : arr ) {

		//a.value.data = "edit";
		std::cout << a.value.data << "\n";

	}

	for (linkedlist::iterator<pdf> a = arr.begin(); a != arr.end(); ++a) std::cout << (*a).data << '\n';
	*/

}


// test on primitives "int , float , ..."
template<typename type> void p_test( size_t && size ) {

	graphs::l_graph<type> g();

	/*
	std::srand(std::time(0));

	for (size_t i = 0; i < size; i += 1) {

		arr.insert( i, (V)std::rand());
		
	}
	*/


	/*
	std::cout << "===============================================" << '\n';
	std::cout << "SIZE    : " << arr.size() << '\n';
	std::cout << "LENGTH  : " << arr.length() << '\n';
	std::cout << "===============================================" << '\n';
	*/
}
