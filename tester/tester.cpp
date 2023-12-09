 
#ifndef INCLUDE_LIBS
	#define INCLUDE_LIBS

	#include <iostream>
	#include <vector>
	#include <array> 
	#include <algorithm>
	#include <map>
	#include <string>

	#include "tobj.cpp"

#endif

#include "static_stack.hpp"

bool cp(tobj const& a, tobj const& b) {
	return (a.data < b.data);
}

int main() {
	
	static_stack<int> ss(10);

	return 0;
}
