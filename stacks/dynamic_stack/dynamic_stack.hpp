
#pragma once

#ifndef std_list
	#define std_list
	#include <list>
#endif

#ifndef std_vector
	#define std_vector
	#include <vector>
#endif



#ifndef DYNAMIC_STACK_CLASS_HPP

	#define DYNAMIC_STACK_CLASS_HPP

// dynamic stack respace automaticly 
template<typename t> class dynamic_stack {

private:

	size_t _size = 0;
	size_t  len  = 0;
	std::vector<t> memory;

public:
	
	// constructor's

	dynamic_stack(size_t stack_size);
	dynamic_stack(std::initializer_list<t> const& stack_elements);
	
	// destructor
	~dynamic_stack();

	// method's 
	
	static void   push(dynamic_stack<t>& stack , t new_value); // o(1)
	static t      pop(dynamic_stack<t>& stack ); // o(1)
	
	static t      peek(dynamic_stack<t>& stack) noexcept; // o(1)
	static t      get(dynamic_stack<t>& stack , size_t const& index); // o(1)
	
	static size_t length(dynamic_stack<t>& stack) noexcept; // o(1)
	static size_t size(dynamic_stack<t>& stack) noexcept; // o(1)
	static bool   is_empty(dynamic_stack<t>& stack) noexcept; // o(1)
	
	static bool   search(dynamic_stack<t>& stack , t const& target_value) noexcept; // o(n)
	static void   clear(dynamic_stack<t>& stack) noexcept; // o(n)

#ifdef DEBUG_ON_CONSOLE 
	static void point(dynamic_stack<t>& stack); // o(n)
#endif

	// operator's

	void operator  =  (dynamic_stack<t>& stack_to_copy); // o(n)
	t    operator [ ] (size_t const& index); // o(1)

}; 
// end of class "dynamic_stack"

#endif