#include <stdexcept> 
#pragma once

/*
	static array methods

	-- NAME ----------- BEST --> WORST

*/

namespace arrays {

	template<typename T> class static_array {

	private:
		size_t _size = 0;
		int len = -1;

		bool full = false;

		T* arr = nullptr;

	public :

		// constructor 1
		static_array( size_t array_size = 0 ) {

			// save array size
			this->_size = array_size;

			// allocated array at the heap
			this->arr = new T[sizeof(T) * array_size];

			// o(n)
			// loop over all & insert NULL , just clearing process
			for (unsigned int i = 0; i < this->_size; i += 1) {
				*(this->arr + i) = NULL;
			}

		}
		
		// constructor 2
		static_array( std::initializer_list<T> const& elements ) {
	
			this->_size = elements.size();
			this->arr = new T[sizeof(T) * this->_size];

			unsigned int i = 0;
			for (T element : elements) {

				*(this->arr + i) = element;

				i += 1;
				this->len += 1;
			}

			this->full = true;
		}

	
		// destructor
		~static_array() {

			delete[] this->arr;

		}


		// o(n)
		// loop over all elements 
		void for_each( void (*call_back_function)(T element) ) {

			for (unsigned int i = 0; i < this->_size; i += 1) {

				call_back_function( *(this->arr + i) );

			}

		}

		/*
		
			some public operators

		*/

		T operator[] (size_t const& index) {
			
			if (index > this->_size) {

				throw std::invalid_argument("argument 'index' out of range").what();

			}
			else return *(this->arr + index);

		}

		static_array<T>& operator= (std::initializer_list<T> &elements) {
			return static_array<T>(elements);
		}

	}; // end of class static_array


} // end of namespace arrays