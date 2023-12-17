
#pragma once

#ifndef std_list
	#define std_list
	#include <list>
#endif

#ifdef DEBUG_ON_CONSOLE
	
	#ifndef std_iostream
		#define std_iostream	
		#include <iostream>
	#endif

#endif

#ifndef STATIC_STACK_CLASS_HPP
	#include "static_stack.hpp"
#endif

#ifndef STATIC_STACK_CLASS_CPP

	#define STATIC_STACK_CLASS_CPP

/*
			constructor's
*/

template<typename t> static_stack<t>::static_stack( size_t stack_size ) 
	: _size(stack_size + 1) , memory ( new t[sizeof(t) * (stack_size + 1)] ) 
{
	// this->memory[stack_size] = NULL;
}

template<typename t> static_stack<t>::static_stack( std::initializer_list<t> const& stack_elements ) {

	this->_size  = stack_elements.size();
	this->len    = this->_size - 1;
	this->memory = new t[ sizeof(t) * (this->_size + 1) ];

	size_t i = 0;

	for ( t const& element : stack_elements ) {
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
	catch (std::exception &error) {

		#ifdef DEBUG_ON_CONSOLE
			std::cerr << error.what() << '\n';
		#endif

	}

}


/*
			static method's
*/


// push data to the top of the stack 
template<typename t> bool static_stack<t>::push(static_stack<t>&stack, t new_value) {
		
	if ( (stack.len < stack._size ) && stack.memory != nullptr ) {
		stack.memory[ stack.len ] = new_value;
		stack.len += 1;	
		
		return true;
	}

	return false;
}

// get last element at the top of the stack then delete it 
template<typename t> t static_stack<t>::pop( static_stack<t>& stack ) {
	
	if ( (stack.len == 0) && (stack.memory != nullptr) ) return NULL;

	stack.len -= 1;

	t value = stack.memory[ stack.len ];
	stack.memory[ stack.len ] = NULL;

	return value;
}

// get copy of the current element at top of the stack "without delete it"
template<typename t> t static_stack<t>::peek(static_stack<t>& stack) noexcept {
	
	return ( (stack.len >= 0) && (stack.memory != nullptr) ) ? stack.memory[ stack.len - 1 ] : NULL ;
	
}

// get a copy of element in the stack by index
template<typename t> t static_stack<t>::get(static_stack<t>& stack, size_t const& index) {

	if (stack.memory == nullptr) return NULL;

	if (index >= stack._size) {
		throw std::exception("static_stack.get() : attempt to access out of range memory !");
	}

	return stack.memory[index];
}

template<typename t> bool static_stack<t>::is_full(static_stack<t>& stack) noexcept {

	return (stack.len >= stack._size);

}

template<typename t> bool static_stack<t>::is_empty(static_stack<t>& stack) noexcept {

	return (stack.len == 0);

}

template<typename t> size_t static_stack<t>::size(static_stack<t>& stack) noexcept {

	return (stack._size > 0) ? stack._size - 1 : 0;

}

template<typename t> size_t static_stack<t>::length(static_stack<t>& stack) noexcept {

	return (stack.len == 0) ? 0 : stack.len - 1;

}

#ifdef DEBUG_ON_CONSOLE	

template<typename t> static void static_stack<t>::print( static_stack<t>& stack ) {
	
	if (stack.memory == nullptr) return;

	std::cout << "stack :\n";

	for ( size_t i = stack._size ; i > 0 ; i -= 1 ) {
		std::cout << i << " : " << stack.memory[i - 1] << '\n';
	}

}

#endif 

// remove all the elements from the stack
template<typename t> void static_stack<t>::clear( static_stack& stack ) {
				
	// clear process
	if (stack.memory != nullptr) {

		for (size_t i = 0; i < stack._size; i += 1) {
			stack.memory[i] = NULL;
		}

		stack.len = 0;
	}

}

// search in stack for element if exist
template<typename t> bool static_stack<t>::search( static_stack<t>& stack , t const& target_value ) {

	if (stack.memory == nullptr) return false;
	
	for ( size_t i = 0; i < stack._size ; i += 1 ) {
	
		if (stack.memory[i] == target_value) return true;

	}

	return false;
}

/*
			none static method's
*/

// copy an existing stack to the current one
template<typename t> void static_stack<t>::operator = (static_stack<t>& stack_to_copy) {

	// copying process

	if(this->memory != nullptr) delete[] this->memory;
	this->memory = new t[sizeof(t) * stack_to_copy._size];
	
	this->len = stack_to_copy.len;
	this->_size = stack_to_copy._size;
	
	for (size_t i = 0; i < this->_size; i += 1) {

		this->memory[i] = stack_to_copy.memory[i];

	}

}

// this operator act like get function 
template<typename t> t static_stack<t>::operator [] (size_t const& index) {

	if (this->memory == nullptr) return NULL;

	if (index >= this->_size) {
		throw std::exception("static_stack operator [] : attempt to access out of range memory !");
	}

	return this->memory[index];

}



/*
	NOTE : explicit instantiate is required !
*/ 
#include "instantiate.hpp"


#endif
