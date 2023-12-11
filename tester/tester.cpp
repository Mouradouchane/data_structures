 
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
#include "../stacks/static_stack/tests/test1.cpp"
#include "../stacks/static_stack/tests/test2.cpp"

void run_test( bool (*test_fn)() , const char * fn_name ) {

	if ( test_fn() ) {
		std::cout << "PASS :: static_stack " <<  fn_name << " .\n";
	}
	else std::cout << "FAILED :: static_stack" << fn_name << " !\n";

}

int main() {
	
	run_test(test1, "test1");
	run_test(test2, "test2");

	return 0;
}
