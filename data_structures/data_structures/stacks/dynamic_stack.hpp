#include <iostream>
#include <vector>
#pragma once

//  === stack ===
/*
	push	=> o(1)
	pop		=> o(1)
	peek	=> o(1)

	isEmpty => o(1)
	isFull	=> o(n)
	find	=> o(1) ==> o(n)

	length	=> o(1)
	print	=> o(n)

	clear	=> o(1) ==> o(n)
*/

namespace stacks {

// dynamic stack respace automaticly 
template<typename t> class dynamic_stack {

private :
	// stack length
	unsigned int len = 0;

	// dynamic vector represent "stack"
	std::vector<t> stack;

public : 
	dynamic_stack(){}
	~dynamic_stack(){}

	void push(t newValue) {
		len += 1;
		stack.push_back(newValue);
	}

	t pop() {
		if (len == 0) return NULL;

		t value = stack[len-1];
		stack.pop_back();

		len -= 1;
		return value;
	}

	t peek() {
		return (len != 0) ? stack[len] : NULL;
	}

	// o(1) length =>  elements length not vector length
	void length() {
		return len;
	}

	// o(n)
	// print full stack in console
	void print() {
			std::cout << "|   |" << '\n';
		for (unsigned int i = len-1 ; i != -1 ; i -= 1) {
			std::cout << "| " << stack[i] << " |" << '\n';
		}
			std::cout << "|___|" << '\n';
			std::cout << "Length => "<< len << '\n';
	}
};

}