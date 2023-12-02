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
		size_t len = 0;
		size_t _size = 0;
		t * stack = nullptr;
	public:
		static_stack(size_t const& stack_size) :_size(stack_size) , stack(new t[sizeof(t) * stack_size]) 
		{
		}

		static_stack(std::initializer_list<t> const& stack_elements) {

			this->_size  = stack_elements.size();
			this->len   = this->_size - 1;
			this->stack = new t[ sizeof(t) * this->_size ];

			size_t i = 0;
			for (t element : stack_elements) {
				this->stack[i] = element;
				i += 1;
			}

		}

		~static_stack(){

			try {

				if (this->stack != nullptr) {
					delete[] this->stack;
					this->stack = nullptr;
				}

			}
			catch (std::exception& error) {
				std::cerr << error.what() << '\n';
				throw error.what();
			}

		}

		// o(1)
		// push data to stack "make new top element :)"
		void push(t newValue) {
			if (this->len < this->_size) {
				this->stack[ this->len ] = newValue;
				this->len += 1;
			}
		}

		// o(1)
		// get data in top index & delete it "pop data"
		t pop() {
			if (this->len == 0) return NULL;

			t value = stack[ this->len - 1 ];
			this->stack[ this->len - 1 ] = NULL;

			this->len -= 1;
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
			return (len >= this->_size);
		}

		// o(1) 
		// stack length
		size_t length() {
			return this->len;
		}

		size_t size() {
			return this->_size;
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
				
			try {

				// clear process
				if (this->stack != nullptr) {

					delete[] this->stack;

					// reallocated stack
					this->stack = new t[ sizeof(t) * this->_size ];

					this->len = 0;
				}

			}
			catch (std::exception& error) {
				std::cerr << error.what() << '\n';
				throw error.what();
			}

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