
#pragma once

#ifndef DYNAMIC_STACK_CLASS_HPP
	#include "dynamic_stack.hpp"
#endif

#ifdef DEBUG_ON_CONSOLE

	#ifndef std_iostream
		#define std_iostream	
		#include <iostream>
	#endif

#endif

#ifndef STATIC_STACK_CLASS_CPP

	#define STATIC_STACK_CLASS_CPP

/*
			constructor's
*/

template<typename t> dynamic_stack<t>::dynamic_stack(size_t stack_size) {

}

template<typename t> dynamic_stack<t>::dynamic_stack( std::initializer_list<t> const& stack_elements ) {
		
	for (t element : stack_elements) {
		this->stack.push_back(element);
	}

}

/*
			destructor's
*/

template<typename t> dynamic_stack<t>::~dynamic_stack(){
	this->stack.clear();
}

/*
			 method's
*/

// push data to stack "make new top element :)"
template<typename t> void dynamic_stack<t>::push(dynamic_stack<t>& stack , t new_value) {
	len += 1;
	this->stack.push_back(new_value);
}

// get data in top index & delete it "pop data"
template<typename t> t dynamic_stack<t>::pop(dynamic_stack<t>& stack) {
	if (this->len == 0) return NULL;

	t value = this->stack[len-1];
	this->stack.pop_back();

	this->len -= 1;
	return value;
}

// get copy of data at top index but not delete it 
template<typename t> t dynamic_stack<t>::peek(dynamic_stack<t>& stack) {
	// in case stack is empty return null else return value
	return (len != 0) ? this->stack[ this->len-1 ] : NULL;
}

// elements length not vector length
template<typename t> size_t dynamic_stack<t>::length(dynamic_stack<t>& stack) {
	return len;
}

// check if stack is empty or not
template<typename t> bool dynamic_stack<t>::is_empty(dynamic_stack<t>& stack) {
	return (len == 0);
}

// remove all the elements from stack
template<typename t> void dynamic_stack<t>::clear(dynamic_stack<t>& stack) {
	this->stack.clear();
	this->len = 0;
}

// search if something is in the stack 
template<typename t> bool dynamic_stack<t>::search(dynamic_stack<t>& stack , t const& target_value) {

	// check
	for (t & value : stack) {
		if (value == target_value) return true;
	}

	// in case not found 
	return false;
}

#endif