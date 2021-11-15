#include <iostream>

#pragma once

//  === dynamic stack ===
/*
	push	=> o(1)
	pop		=> o(1)
	peek	=> o(1)

	isEmpty => o(1)
	isFull	=> o(1)
	search	=> o(1) ==> o(n)

	length	=> o(1)
	print	=> o(n)

	clear	=> o(1) ==> o(n)
*/

namespace stacks {

template<typename t> class static_stack {
	private:
		int len = 0; 
		int size = 0;
		t* stack = NULL;
	public:
		static_stack(unsigned int stack_size):size(stack_size),stack(new t[stack_size]) {
			/*
			stack = new t[stack_size];
			size = stack_size;
			*/
		}
		~static_stack(){}

		// o(1)
		// push data to stack "make new top element :)"
		void push(t newValue) {
			if (len < size) {
				stack[len] = newValue;
				len += 1;
			}
		}

		// o(1)
		// get data in top index & delete it "pop data"
		t pop() {
			if (len == 0) return NULL;

			t value = stack[len - 1];
			stack[len-1] = NULL;

			len -= 1;
			return value;
		}

		// o(1)
		// get copy of data at top index but not delete it 
		t peek() {
			// in case stack is empty return null else return value
			return (len != 0) ? stack[len - 1] : NULL;
		}

		// o(1)
		// check if stack is full or not
		bool isFull() {
			return (len == size) ? true : false;
		}

		// o(1) 
		// length => elements length not array/stack length
		int length() {
			return len;
		}

		// o(n)
		// print full stack in console
		void print() {
			std::cout << "|   |" << '\n';
			for (unsigned int i = len - 1; i != -1; i -= 1) {
				std::cout << "| " << stack[i] << " |" << '\n';
			}
			std::cout << "|___|" << '\n';
			std::cout << "Length => " << len << '\n';
		}

		// o(1)
		// check if stack is empty or not
		bool isEmpty() {
			return (len == 0) ? true : false;
		}

		//o(1) ==> o(n)
		// clear stack
		void clear() {

			// clear stack
			delete stack;

			// make new stack with same size
			stack = new t[size];
			len = 0;
		}

		// o(1) ==> o(n)
		// search if something is in stack or not
		bool search(t target_value) {

			// loop over all 
			for (int i = 0; i < len; i += 1) {
				// check 
				if (stack[i] == target_value) return true;
			}

			// in case not found 
			return false;
		}
};

}