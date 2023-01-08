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

using namespace graphs;

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

bool cp(pdf const& a, pdf const& b) {
	return (a.data < b.data);
}

void test1();
template<typename T> void p_test(size_t&& size);

int main() {
	
	std::cout << "=============== OBJECT's TEST ===============\n";
	test1();
	std::cout << "=============== PRIMITIVE's TEST ===============\n";
	//p_test<int>(6);

	return 0;
}

// test on objects
void test1() {

	Vertex<pdf> v1("v_1" , pdf("book 1"));
	Vertex<pdf> v2("v_2" , pdf("book 2"));
	Vertex<pdf> v3("v_3" , pdf("book 3"));
	Vertex<pdf> v4("v_4" , pdf("book 4"));
	Vertex <pdf> v11("v_11", pdf("book 11"));

	graph_list<pdf> gp( { v2 , v4 , v1, v3 , v1, v4} );


	gp.add_vertex( "v_9", pdf("book 9") , { "v_2" , "v_3", "v_1" , "v_4"});

	gp.add_vertex( "v_6", pdf("book 6") );
	gp.add_vertex( "v_7", pdf("book 7") );

	gp.add_edge( gp.search(v1) , gp.search(v11));

	gp.print();

	std::cout << "====================================\n";
	std::cout << gp.vertex->get_name()  << " : " << gp.vertex->value.data << "\n";


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

	//graphs::l_graph<type> g();

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
