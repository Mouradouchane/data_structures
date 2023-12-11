
#include "../static_stack.hpp"

/*
		constructor / destructor testing
*/

bool test2() {

	static_stack<int>* stack1 = new static_stack<int>(8);

	try {
		stack1->~static_stack();
	}
	catch (std::exception error) {
		return false;
	}

	static_stack<int> stack2({ 1,2,3,4,5 });

	if ( !(static_stack<int>::push(stack2, 1)) ) return false;

	if (stack2[0] != 1) return false;
	if (stack2[1] != 2) return false;
	if (stack2[2] != 3) return false;
	if (stack2[3] != 4) return false;
	if (stack2[4] != 5) return false;

	
	return true;
}




