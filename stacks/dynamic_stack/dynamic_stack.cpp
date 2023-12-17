
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

template<typename t> dynamic_stack<t>::dynamic_stack(size_t stack_size)
	: _size( stack_size ) , 
	  memory( new std::vector<t>( sizeof(t) * (stack_size + 1) ) )
{

}

template<typename t> dynamic_stack<t>::dynamic_stack(std::initializer_list<t> const& stack_elements) {

	this->_size = stack_elements.size();
	this->len   = this->_size - 1;
	this->memory = new std::vector<t>( sizeof(t) * (this->_size + 1) );

	for ( t const& element : stack_elements ) {
		this->stack->push_back(element);
	}

}

/*
			destructor's
*/

template<typename t> dynamic_stack<t>::~dynamic_stack( ){

	try {

		if (this->memory != nullptr) {
			delete this->memory;
			this->memory = nullptr;
		}

	}
	catch (std::exception& error) {

		#ifdef DEBUG_ON_CONSOLE
				std::cerr << error.what() << '\n';
		#endif

	}

}

/*
			 method's
*/

// push data to stack "make new top element :)"
template<typename t> bool dynamic_stack<t>::push(dynamic_stack<t>& stack , t const& new_value) {
	
	if (stack.memory == nullptr) return false;

	stack.memory->push_back(new_value);
	stack.len += 1;

	return true;
}

// get last element at the top of the stack then delete it 
template<typename t> t dynamic_stack<t>::pop(dynamic_stack<t>& stack) {

	if (stack.len == 0 || stack.memory == nullptr ) return NULL;

	stack.len -= 1;

	t value = stack.memory[ stack.len ];
	stack.memory->pop_back();

	return value;

}

// get copy of the current element at top of the stack "without delete it"
template<typename t> t dynamic_stack<t>::peek(dynamic_stack<t>& stack) noexcept {

	return (stack.len >= 0 && stack.memory != nullptr) ? stack.memory[ stack.len ] : NULL ;

}

template<typename t> size_t dynamic_stack<t>::length(dynamic_stack<t>& stack) noexcept {
	return stack.len;
}

template<typename t> bool dynamic_stack<t>::is_empty(dynamic_stack<t>& stack) noexcept {
	return (stack.len == 0 || stack.memory == nullptr);
}

// remove all the elements from stack
template<typename t> void dynamic_stack<t>::clear(dynamic_stack<t>& stack) noexcept {

	if (stack.memory != nullptr) {

		stack.memory.clear();
		stack.len = 0;

	}

}

// search if something is in the stack 
template<typename t> bool dynamic_stack<t>::search(dynamic_stack<t>& stack , t const& target_value) noexcept {

	if (stack.memory == nullptr) return false;

	for ( t& value : stack.memory ) {
		if ( value == target_value ) return true;
	}

	return false;
}

#ifdef DEBUG_ON_CONSOLe
template<typename t> static void dynamic_stack<t>::print(dynamic_stack<t>& stack) noexcept {
	
	if (stack.memory == nullptr) return;

	std::cout << "stack :\n";

	for (size_t i = stack._size; i > 0; i -= 1) {
		std::cout << i << " : " << stack.memory[i - 1] << '\n';
	}

}
#endif

// copy an existing stack to the current one
template<typename t> void dynamic_stack<t>::operator = (dynamic_stack<t>& stack_to_copy) {

	if (this->memory != nullptr) delete this->memory;
	this->memory = new std::vector<t>( sizeof(t) * stack_to_copy.memory->size() );

	this->len = stack_to_copy.len;

	for (size_t i = 0; i < stack_to_copy.memory->size() ; i += 1) {

		this->memory[i] = stack_to_copy.memory[i];

	}

}

// this operator act like get function 
template<typename t> t dynamic_stack<t>::operator [ ] (size_t const& index) {

	if (this->memory == nullptr) return NULL;

	if (index >= this->_size) {
		throw std::exception("dynamic_stack operator [] : attempt to access out of range memory !");
	}

	return this->memory[index];

}

#endif