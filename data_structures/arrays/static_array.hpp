#include <iostream>
#include <stdexcept> 
#pragma once

/*
	static array methods

	-- NAME ----------- BEST --> WORST

	length				O(1)
	size				O(1)
	is_full				O(1)
	is_empty			O(1)

	insert				O(1) --> O(n)
	insert_at			O(1)

	get					O(1)
	remove				O(1)

	reverse				O(n)

	for_each			O(n)

	= {...}				O(n)
	= array				O(n)

*/

namespace arrays {


	template<typename T> class static_array {

		static_assert(!std::is_pointer_v<T>, "T* 'pointer type' not allowed in static_array use the alternative 'static_array_p' ");

	private:
		size_t _size = 0;
		int len = 0;

		// array its self
		T* arr = nullptr;
		// map : to keep track which index is empty or not
		bool *map = nullptr;

	public :

		// default constructor 
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
		
		// initializer_list constructor 
		static_array( std::initializer_list<T> const& elements ) {
	
			this->_size = elements.size();
			this->len = this->_size - 1;
			this->arr = new T[sizeof(T) * this->_size];
			this->map = new bool[sizeof(bool) * this->_size];

			size_t i = 0;
			for (T element : elements) {

				*(this->arr + i) = element;
				*(this->map + i) = true;

				i += 1;
			}

		}

		// "copy constructor"
		static_array(static_array<T> & new_array) {

			this->arr = new T[sizeof(T) * new_array._size];
			this->map = new bool[sizeof(bool) * new_array._size];

			// copy process
			
			this->_size  = new_array._size;
			this->len    = new_array.len;

			for (size_t i = 0; i < this->_size; i += 1) {

				*(this->arr + i)  = *(new_array.arr + i);
				*(this->map + i)  = *(new_array.map + i);

			}

		}


		// destructor	
		~static_array() { }

			
		// o(n)
		// loop over all elements 
		void for_each( void (* const& call_back_function)(T& element) ) {

			for (size_t i = 0; i < this->_size; i += 1) {

				if(this->map[i] == true) call_back_function( *(this->arr + i) );

			}

		}

		// o(1)
		// get the count of how many elements currently in this array
		int length() {
			return this->len;
		}

		// o(1)
		// get array size
		size_t size() {
			return this->_size;
		}

		// o(1)
		bool is_full() {
			if (this->_size == 0) return false;
			return (this->len < this->_size - 1) ? false : true;
		}

		// o(1)
		bool is_empty() {
			return (this->len > 0) ? false : true;
		}

		// o(n)
		void reverse() {

			// temp for swap each time
			T temp;

			// loop from the beginning to the middel and preforme swap
			for (size_t i = 0, c = this->_size - 1; i < c ; i += 1, c -= 1) {

				temp = *(this->arr + i);

				*(this->arr + i) = *(this->arr + c);
				*(this->arr + c) = temp;

				temp = T();
				/*
				try {
				}
				catch (std::exception err) {
					throw err;
					throw ("make sure that your \"data - type\" support assignment to \"NULL\" value .");
				}
				*/
			}

		}

		// o(n)
		// replace all elements empty values
		void clear() {

			for (size_t i = 0; i < this->_size; i += 1) *(this->arr + i) = T();

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
		// NOTE : this function it's not affect the size of array 
		// NOTE : remove "just as declare" the element will be there until overwrite or the hole array get deleted 
		bool remove( size_t const& target_index ) {

			// if index out or range
			if ( target_index >= this->_size ) return false;

			// if already empty
			if (this->map[target_index] == false) return false;

			// declare as removed
			this->map[target_index] = false;
			this->len -= 1;

			return true;
		}
		
		// o(range)
		// "virtual remove" range of elements in array
		bool remove(size_t const& start_index, size_t const& end_index) {

			if (start_index < 0 || start_index >= this->_size) return false;
			if (end_index   < 0 || end_index   >= this->_size) return false;
			if (end_index < start_index) return false;

			for (size_t i = start_index; i <= end_index; i += 1) {
				this->remove(i);
			}

			return true;
		}

		// o(1)
		// "get element by value"
		T get(size_t const& index) {

			if (index >= this->_size) return *(this->arr + this->_size);

			if (this->map[index] == false) return *(this->arr + this->_size);
			
			else return *(this->arr + index);
		}


		/*
		
			-------------- public operators --------------

		*/

		void operator = (std::initializer_list<T> const& elements) {

			this->_size = elements.size();
			this->len = this->_size - 1;
			this->arr = new T[sizeof(T) * this->_size];
			this->map = new bool[sizeof(bool) * this->_size];

			size_t i = 0;
			for (T element : elements) {

				*(this->arr + i) = element;
				*(this->map + i) = true;

				i += 1;
			}

		}

		T& operator[] (size_t const& index) {
			return *(this->arr + index);
		}


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


		/*

			-------------- iterators --------------

		*/

		class iterator {

			private : 
				T* addr = nullptr;
				int index = 0;

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

				// =========== compare iterator to reference ===========
				bool operator != ( T * address_of_other_element ) {
					return (this->addr != address_of_other_element) ? true : false;
				}

				bool operator == (T* address_of_other_element) {
					return (this->addr == address_of_other_element) ? true : false;
				}


				// =========== compare iterator to iterator ===========
				bool operator != (static_array<T>::iterator & other_iterator) {
					return (this->addr != other_iterator.addr) ? true : false;
				}

				bool operator == (static_array<T>::iterator& other_iterator) {
					return (this->addr == other_iterator.addr) ? true : false;
				}

		}; // end of class iterator


		/*
			-------------- methods for iterators --------------
		*/


	}; // end of class static_array


	
} // end of namespace arrays