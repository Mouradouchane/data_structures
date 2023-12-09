
#pragma once

#include <list>

#ifdef DEBUG_ON_CONSOLE
	#include <iostream>
#endif

/*
*/
#include "static_stack.hpp"


#ifndef STATIC_STACK_CLASS_CPP

	#define STATIC_STACK_CLASS_CPP


/*
			constructor's
*/

template<typename t> static_stack<t>::static_stack( size_t stack_size ) :
	_size(stack_size) , 
	memory(new t[ sizeof(t) * (stack_size + 1) ]) 
{

}

template<typename t> static_stack<t>::static_stack( std::initializer_list<t> const& stack_elements ) {

	this->_size  = stack_elements.size();
	this->len    = this->_size - 1;
	this->memory = new t[ sizeof(t) * (this->_size + 1) ];

	size_t i = 0;

	for (t const& element : stack_elements) {
		this->memory[i] = element;
		i += 1;
	}

}

/*
			destructor
*/

template<typename t> static_stack<t>::~static_stack() {

	try {

		if (this->memory != nullptr) {
			delete[] this->memory;
			this->memory = nullptr;
		}

	}
	catch (std::exception& error) {
		#ifdef DEBUG_ON_CONSOLE
			std::cerr << error.what() << '\n';
		#endif

		throw error.what();
	}

}


/*
			method's
*/


template<typename t> bool static_stack<t>::push(static_stack<t>&stack, t new_value) {
	
	// push data to the top of the stack 
	
	if ( (stack.len < stack._size) && stack.memory != nullptr ) {
		stack.memory[ stack.len ] = new_value;
		stack.len += 1;	
		
		return true;
	}

	return false;
}

template<typename t> t static_stack<t>::pop( static_stack<t>& stack ) {
	
	// get last element at the top of the stack then delete it 
	if (stack.len == 0 && stack.memory != nullptr) return NULL;

	t value = stack.memory[ stack.len - 1 ];

	stack.memory[ stack.len - 1 ] = NULL;
	stack.len -= 1;

	return value;
}

template<typename t> t static_stack<t>::peek(static_stack<t>& stack) {
	
	// get copy of the element who at top of the stack "without delete it"
	return (stack.len != 0 && stack.memory != nullptr) ? stack.memory[ stack.len - 1] : NULL ;
	
}

template<typename t> bool static_stack<t>::is_full(static_stack<t>& stack) noexcept {

	return (stack.len >= stack._size);

}

template<typename t> bool static_stack<t>::is_empty(static_stack<t>& stack) noexcept {

	return (stack.len == 0);

}

template<typename t> size_t static_stack<t>::size(static_stack<t>& stack) noexcept {

	return stack._size;

}

template<typename t> size_t static_stack<t>::length(static_stack<t>& stack) noexcept {

	return stack.len;

}

#ifdef DEBUG_ON_CONSOLE	

template<typename t> static void static_stack<t>::print( static_stack<t>& stack ) {
	
	if (stack.memory == nullptr) return;
	std::cout << "|   |" << '\n';
	
	for ( size_t i = len - 1; i > -1; i -= 1) {
		std::cout << "| " << stack.memory[i] << " |" << '\n';
	}

	std::cout << "|___|" << '\n';
	std::cout << "Length => " << stack.len << '\n';

}

#endif 

// wipe the hole stack
template<typename t> void static_stack<t>::clear( static_stack& stack ) {
				
	try {

		// clear process
		if (stack.memory != nullptr) {

			delete[] stack.memory;

			// reallocated stack
			stack.memory = new t[ sizeof(t) * stack._size ];
			stack.memory[stack._size - 1] = '\0';

			stack.len = 0;
		}

	}
	catch (std::exception& error) {
		#ifdef DEBUG_ON_CONSOLE
			std::cerr << error.what() << '\n';
		#endif

		throw error.what();
	}

}


template<typename t> bool static_stack<t>::search( static_stack<t>& stack , t const& target_value ) {

	if (stack.memory == nullptr) return false;
	
	for ( size_t i = 0; i < stack._size ; i += 1 ) {
	
		if (stack.memory[i] == target_value) return true;

	}

	return false;
};


/*
	NOTE : explicit instantiate is here !!!
	you have to instantiate the types your gonna use befor "build/link" .

	EXAMPLE : template class static_stack< float >;      // instantiate for float type 
*/ 



#endif
