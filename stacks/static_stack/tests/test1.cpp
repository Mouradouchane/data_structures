
#include "../static_stack.hpp"

/*
		push / pop  testing
*/

bool test1() {

	static_stack<int> stack(10);

	static_stack<int>::push(stack, 1);
	static_stack<int>::push(stack, 2);
	static_stack<int>::push(stack, 3);

	if (stack[0] != 1) return false;
	if (stack[1] != 2) return false;
	if (stack[2] != 3) return false;

	if (static_stack<int>::length(stack) != 2) return false;
	if (static_stack<int>::size(stack) != 10) return false;

	if( static_stack<int>::pop(stack) != 3 ) return false;
	if( static_stack<int>::pop(stack) != 2 ) return false;
	if( static_stack<int>::pop(stack) != 1 ) return false;

	if( static_stack<int>::pop(stack) != 0 ) return false;
	if( static_stack<int>::pop(stack) != 0 ) return false;


	return true;
}




