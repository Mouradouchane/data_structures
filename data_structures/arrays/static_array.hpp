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

		}

	
		// destructor
		~static_array() {

			delete[] this->arr;

		}


		/*

			public methods

		*/

		// o(n)
		// loop over all elements 
		void for_each( void (*call_back_function)(T element) ) {

			for (unsigned int i = 0; i < this->_size; i += 1) {

				call_back_function( *(this->arr + i) );

			}

		}

		// o(1)
		// get the count of how many elements currently in this array
		int lenght() {
			return this->len;
		}

		// o(1)
		// get size of this array
		size_t size() {
			return this->_size;
		}

		// o(1)
		// check if array is full of elements or not
		bool is_full() {

			return (this->len < this->_size) ? false : true;
		}

		// o(n/2)
		void reverse() {

			// temp for swap each time
			T temp = NULL;

			// o(n/2)
			// loop from the beginning to the middel and preforme swap
			for (size_t i = 0, c = this->_size - 1; i < c ; i += 1, c -= 1) {

				temp = *(this->arr + i);
				*(this->arr + i) = *(this->arr + c);
				*(this->arr + c) = temp;

				temp = NULL;
			}

		}

		/*
		
			public operators

		*/

		// random access operator to access elements
		T& operator[] (size_t const& index) {

			// if index out of range
			if (index > this->_size) {

				throw std::invalid_argument("argument 'index' out of range").what();

			}
			// else get value at this index
			else return *(this->arr + index);

		}

		// o(n + x)
		// add a hole static_array of elements to this current one
		void operator+= (static_array<T>& new_elements) {

			// allocated new array with new size that can fit all elements
			T* new_arr = new T[sizeof(T) * ( this->_size + new_elements._size)];

			// start copying from first array
			unsigned int i = 0;
			for (; i < this->_size; i += 1) {

				new_arr[i] = *(this->arr + i);

			}

			// delete old array from the heap
			delete[] this->arr;

			// start copying from second array
			for (int c = 0; c < new_elements._size; c += 1 , i += 1) {

				*(new_arr + i) = new_elements[c];
				this->len += 1;

			}

			// then save that new array
			this->_size += new_elements._size;
			this->arr = new_arr;
			
		}

		// o(n)
		// assigne list of elements to this new array
		static_array<T>& operator= (std::initializer_list<T> &elements) {

			// construct new array and paste it over that current array
			return static_array<T>(elements);

		}


	}; // end of class static_array


} // end of namespace arrays