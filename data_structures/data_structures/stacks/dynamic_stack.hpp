#include <iostream>
#include <vector>
#pragma once

//  === dynamic stack ===
/*
	push	=> o(1)
	pop		=> o(1)
	peek	=> o(1)

	isEmpty => o(1)
	search	=> o(1) ==> o(n)

	length	=> o(1)
	print	=> o(n)

	clear	=> o(1) ==> o(n)
*/

namespace stacks {

// dynamic stack respace automaticly 
template<typename t> class dynamic_stack {

	private :
		// len represent stack length & stack top index 
		unsigned int len = 0;

		// dynamic vector represent "stack"
		std::vector<t> stack;

	public : 
		dynamic_stack(){}
		~dynamic_stack(){}

		// o(1)
		// push data to stack "make new top element :)"
		void push(t newValue) {
			len += 1;
			stack.push_back(newValue);
		}

		// o(1)
		// get data in top index & delete it "pop data"
		t pop() {
			if (len == 0) return NULL;

			t value = stack[len-1];
			stack.pop_back();

			len -= 1;
			return value;
		}

		// o(1)
		// get copy of data at top index but not delete it 
		t peek() {
			// in case stack is empty return null else return value
			return (len != 0) ? stack[len-1] : NULL;
		}

		// o(1) length =>  elements length not vector length
		int length() {
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

		// o(1)
		// check if stack is empty or not
		bool isEmpty() {
			return (len == 0) ? true : false;
		}

		//o(1) ==> o(n)
		// clear stack
		void clear() {
			stack.clear();
			len = 0;
		}

		// o(1) ==> o(n)
		// search if something is in stack or not
		bool search(t target_value) {

			// loop over all 
			for (t value : stack) {
				// check 
				if (value == target_value) return true;
			}

			// in case not found 
			return false;
		}
};

}