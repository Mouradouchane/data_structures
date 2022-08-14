#include <stdexcept> 
#pragma once

/*
	static array methods

	-- NAME ----------- BEST --> WORST

	length				O(1)
	size				O(1)

	insert				O(1) --> O(n)
	insert_at			O(1)
	remove				O(1)

	reverse				O(n/2)
	sort				O(n log n) --> O(n²)

	search				O(n)
	binary_search		O(log n) --> O(n)

	for_each			O(n)
	is_full				O(1)
	is_empty			O(1)
	
	[]					O(1)
	= {...}				O(n)
	= array				O(n)
	+=					O(n + new_n)
	+					O(arr_1 + arr_2)
*/

namespace arrays {

	template<typename T> class static_array {

	private:
		size_t _size = 0;
		int len = 0;

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

		// constructor 3
		static_array(static_array<T>* new_array) {

			this->_size = new_array->_size;
			this->len   = new_array->len;
			this->arr   = new_array->arr;


		}


		// destructor
		~static_array() {

			if (this->arr != nullptr) {

				delete[] this->arr;

			}

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
		int length() {
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

		// o(1)
		// check if array is empty or not
		bool is_empty() {
			return (this->len > 0) ? false : true;
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

		// o(n)
		// loop over all and find the empty spot for that new_element
		bool insert(const T& new_element ) {
			
			for (size_t i = 0; i < this->_size; i += 1) {
				// if empty spot found
				if ( *(this->arr + i) == NULL) {

					// insert at it & return
					*(this->arr + i) = new_element;

					this->len += 1;
					return true;
				}

			}
			
			return false;
		}

		// o(1)
		bool insert_at(size_t const& target_index , const T& new_element ) {

			// if index out of array range
			if (target_index >= this->_size) return false;
			else {
				// otherwise insert
				*(this->arr + target_index) = new_element;

				this->len += 1;
				return true;
			}

		}

		// o(1)
		// remove element from array 
		// "NOTE" this function it's not affect the size of array 
		bool remove( const size_t& target_index ) {

			// if index out or range
			if ( target_index > this->_size ) return false;

			// if spot is already empty
			if ( *(this->arr + target_index) == NULL ) return false;

			// otherwise
			*(this->arr + target_index) = NULL;
			this->len -= 1;

			return true;
		}

		/*
		
			public operators

		*/


		// o(1)
		// random access operator to access elements
		// but you can't assign values "READ-ONLY"
		T operator [] (size_t const& index) {

			// if index out of range
			if (index > this->_size) {

				throw std::invalid_argument("argument 'index' out of range").what();

			}
			// else get value at this index
			else return *(this->arr + index);

		}

		// o(n + new_arr)
		// add a hole static_array of elements to this current one
		void operator += (static_array<T>& new_elements) {

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

		// o(arr_1 + arr_2)
		static_array<T>& operator + ( static_array<T> &arr_2 ) {

			static_array<T>* new_array = new static_array<T>( this->size() + arr_2.size() );

			for (size_t i = 0 ; i < this->size() ; i += 1) {

				*(new_array->arr + i) = *(this->arr + i);
				new_array->len += 1;
			}

			for (size_t i = 0 , c = this->size() ; i < arr_2.size() ; i += 1 , c += 1) {

				*(new_array->arr + c) = *(arr_2.arr + i);
				new_array->len += 1;

			}

			return *new_array;
		}

		// o(n)
		// assign list of elements to this new array
		static_array<T>& operator = (std::initializer_list<T> &elements) {

			// construct new array and paste it over that current array
			return static_array<T>(elements);

		}

		// o(n)
		// assign a static_array to this one , it's like "copy constructor"
		void operator = ( static_array<T> &new_array ) {
			
			delete[] this->arr;
			this->arr = new T[sizeof(T) * new_array.size()];

	
			this->_size    = new_array._size;
			this->len      = new_array.len;
			
			for ( size_t i = 0; i < new_array.size(); i += 1 ) {

				*(this->arr + i) = *(new_array.arr + i);

			}

		}

	}; // end of class static_array


} // end of namespace arrays