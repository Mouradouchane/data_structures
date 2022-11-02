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
	sort				O(n log n) --> O(n�)

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

		// array its self
		T* arr = nullptr;
		// map : to keep track which index is empty or not
		bool *map = nullptr;

	public :

		// constructor 1
		static_array( size_t array_size = 0 ) {

			// save array size
			this->_size = array_size;

			// allocated array and map at the heap
			this->arr = new T[sizeof(T) * array_size];
			this->map = new bool[sizeof(bool) * array_size];

			// o(n)
			// declare all places in array as empty places
			for (size_t i = 0; i < this->_size; i += 1) {
				this->map[i] = false;
			}
			

		}
		
		// constructor 2
		static_array( std::initializer_list<T> const& elements ) {
	
			this->_size = elements.size();
			this->arr = new T[sizeof(T) * this->_size];
			this->map = new bool[sizeof(bool) * this->_size];

			size_t i = 0;
			for (T element : elements) {

				*(this->arr + i) = element;
				this->map[i] = true;

				i += 1;
				this->len += 1;
			}

		}

		// constructor 3
		static_array(static_array<T>* new_array) {

			this->_size = new_array->_size;
			this->len   = new_array->len;
			this->arr   = new_array->arr;
			this->map   = new_array->map;

		}


		// destructor
		~static_array() {

			if (this->arr != nullptr) delete[] this->arr;
			if (this->map != nullptr) delete[] this->map;

		}


		/*

			public methods

		*/

		// o(n)
		// loop over all elements 
		void for_each( void (* const& call_back_function)(T& element) ) {

			for (unsigned int i = 0; i < this->_size; i += 1) {

				if(this->map[i] == true) call_back_function( *(this->arr + i) );

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
			T temp;
			bool tbool;

			// o(n/2)
			// loop from the beginning to the middel and preforme swap
			for (size_t i = 0, c = this->_size - 1; i < c ; i += 1, c -= 1) {

				temp = *(this->arr + i);
				bool tbool = *(this->map + i);


				*(this->arr + i) = *(this->arr + c);
				*(this->map + i) = *(this->map + c);
				*(this->arr + c) = temp;
				*(this->map + c) = tbool;

			}

		}

		// o(n)
		// loop over all and find the empty spot for that new_element
		bool insert( const T& new_element ) {
			
			for (size_t i = 0; i < this->_size; i += 1) {

				// if empty spot founded
				if ( this->map[i] == false ) {

					// insert 
					*(this->arr + i) = new_element;

					// update map & length
					this->map[i] = true;
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

				this->map[target_index] = true;
				this->len += 1;

				return true;
			}

		}

		// o(1)
		// remove element from array 
		// "NOTE" this function it's not affect the size of array 
		bool remove( const size_t& target_index ) {

			// if index out or range
			if ( target_index >= this->_size ) return false;

			// if already is empty
			if (this->map[target_index] == false) return false;

			// else
			this->map[target_index] = false;
			this->len -= 1;

			return true;
		}

		// o(1)
		// replacement for [] operator
		T* get(size_t const& index) {

			if (index >= this->_size) return (this->arr + this->_size);

			if (this->map[index] == false) return (this->arr + this->_size);
			
			else return (this->arr + index);
		}

		/*
		
			public operators

		*/

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


		/*/
			-------------- iterators --------------
		*/

		class iterator {
			private : 
				T* addr = nullptr;
			public:
				iterator() { }
				iterator(T* address) :addr{ address } { }
			
				// access and refer operators
				T operator *() {
					return *(this->addr);
				}
				T* operator &() {
					return this->addr;
				}

				// increment operators
				void operator ++() {
					this->addr = (this->addr + 1);
				}
				void operator +=( int const& increment_value ) {
					this->addr = (this->addr + increment_value);
				}

				// decrement operators
				void operator --() {
					this->addr = (this->addr - 1);
				}
				void operator -= ( int const& decrement_value ) {
					this->addr = (this->addr - decrement_value);
				}

				T* operator -> () {
					return this->addr;
				}

		}; // end of class iterator

		// O(1)
		T* begin() {
			return (this->arr + 0);
		}
		T* cbegin() {
			return (this->arr + this->_size - 1);
		}

		T* end() {
					// "size + 1" for "out of range" address
			return  (this->arr + this->_size);
		}
		T* cend() {
			return  (this->arr - 1);
		}


	}; // end of class static_array


	
} // end of namespace arrays