// c++ STD 
#include <iostream>
#include <vector>
#include <array> 
#include <algorithm>
#include <map>
#include <string>
// #include <functional>

#include "static_array.hpp"
#include "dynamic_array.hpp"

// objects for testing 
class tobj {
public:
	std::string data = "";
	tobj(std::string const& dt) {
		this->data = dt;
	}
	tobj() { }
	~tobj() { }

	tobj& operator = (tobj const& new_data) {
		this->data = new_data.data;
		return *this;
	}

	void operator = (std::string new_value) {
		this->data = new_value;
	}

	void operator = (int const& index) {
		this->data = "";
	}

	bool operator != (tobj const& other) {
		return (this->data != other.data) ? true : false;
	}

	bool operator == (tobj const& other) {
		return (this->data == other.data) ? true : false;
	}
};

bool cp(tobj const& a, tobj const& b) {
	return (a.data < b.data);
}


int main() {
	
	/*
	std::cout << "=============== OBJECT's TEST ===============\n";
	test1();
	std::cout << "=============== PRIMITIVE's TEST ===============\n";
	//p_test<int>(6);
	*/

	return 0;
}
