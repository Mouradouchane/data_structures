
#pragma once

#ifndef STATIC_STACK_CLASS_HPP

	#define STATIC_STACK_CLASS_HPP

template<typename t> class static_stack {

		private:

			size_t len = 0;
			size_t _size = 0;

			t* memory = nullptr; // stack array
	
		public:

			// constructor's
			static_stack( size_t stack_size );
			static_stack( std::initializer_list<t> const& stack_elements );

			// destructor
			~static_stack();

			// method's

			static bool   push(static_stack<t>&stack, t new_value); // o(1)
			static t      pop( static_stack<t>& stack ); // o(1)
			static t      peek( static_stack<t>& stack ); // o(1)
			static bool   is_full( static_stack<t>& stack ) noexcept; // o(1)
			static bool   is_empty( static_stack<t>& stack ) noexcept; // o(1)
			static size_t length( static_stack<t>& stack ) noexcept; // o(1)
			static size_t size( static_stack<t>& stack ) noexcept; // o(1)

		#ifdef DEBUG_ON_CONSOLE	
			static print( static_stack<t>& stack ); // o(n)
		#endif	

			static void clear( static_stack<t>& stack ); // o(n)
			static bool search( static_stack<t>& stack , t const& target_value ); // o(n)

			// static_stack<t>& current_stack , 
			void operator = ( static_stack<t>& new_stack ); // o(n)

	}; // end of class "static_stack"



#endif
