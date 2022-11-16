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

		// NOTE : "T" should not be pointer type "T*"
		static_assert(!std::is_pointer_v<T>, "T* 'pointer type' not allowed in static_array use the alternative 'static_array_p' ");

	private:
		size_t _size = 0;
		int len = 0;

		// "pointer" to the array in the heap
		T* arr = nullptr;


	public :

		// default constructor 
		static_array( size_t array_size = 0 ) {

			// save array size
			this->_size = array_size;

			// allocated array at the heap
			this->arr = new T[sizeof(T) * array_size];

			// fill with empty values
			for (size_t i = 0; i < this->_size; i += 1) {
				*(this->arr + i) = T();
			}
			
		}
		
		// initializer_list constructor 
		static_array( std::initializer_list<T> const& elements ) {
	
			this->_size = elements.size();
			this->len = this->_size - 1;

			this->arr = new T[sizeof(T) * this->_size];

			size_t i = 0;
			for (T element : elements) {

				*(this->arr + i) = element;

				i += 1;
			}

		}

		// "copy constructor"
		static_array(static_array<T> & new_array) {

			this->arr = new T[sizeof(T) * new_array._size];

			this->_size  = new_array._size;
			this->len    = new_array.len;

			// copy process		
			for (size_t i = 0; i < this->_size; i += 1) {

				*(this->arr + i)  = *(new_array.arr + i);

			}

		}

		// default destructor	
		~static_array() { }

		/*
			===== methods =====
		*/

		void for_each(void (* const& call_back_function)(T& element)); // O(n)
		void for_each(
			size_t const& start_index , 
			size_t const& end_index ,
			void (* const& call_back_function)(T& element)
		); // O(n)
		size_t length();// O(1)
		size_t size();	// O(1)
		void reverse(); // O(n)
		void clear();	// O(n)
		void clear(size_t const& start_index, size_t const& end_index); // O(range)
		bool insert_at(size_t const& target_index, T const& new_element); // O(n)
		bool remove(size_t const& target_index); // O(n)
		bool remove(size_t const& start_index, size_t const& end_index); // O(range)

		/*
			===== methods for iterators =====
		*/
		T* begin(); // O(1)
		T* cbegin(); // O(1)
		T* end(); // O(1)
		T* cend(); // O(1)

		/*
			===== operators =====
		*/
		void operator = (std::initializer_list<T> const& elements); // O(1)
		T& operator[] (size_t const& index); // O(1)

		/*
			===== iterators =====
		*/
		class iterator;

	}; 
	/*

		end of class static_array

	*/



	/*
		-------------- static_array public methods --------------
	*/

	// loop over all elements
	template<typename T> void static_array<T>::for_each(void (* const& call_back_function)(T& element)) {

		for (size_t i = 0; i < this->_size; i += 1) {

			call_back_function( *(this->arr + i) );

		}

	}

	template<typename T> void static_array<T>::for_each(
		size_t const& start_index, 
		size_t const& end_index, 
		void (* const& call_back_function)(T& element)
	) {

		if (start_index >= this->_size) return;
		if (end_index >= this->_size) return;
		if (start_index > end_index) return;

		for (size_t i = start_index; i <= end_index; i += 1) {

			call_back_function( *(this->arr + i) );

		}
	}

	// size - 1
	template<typename T> size_t static_array<T>::length() {
		return (size_t)this->len;
	}

	// array size
	template<typename T> size_t static_array<T>::size() {
		return this->_size;
	}

	template<typename T> void static_array<T>::reverse() {

		T temp ; // for swaping elements

		// loop from the beginning to the middel and preforme swap
		for (size_t i = 0, c = this->_size - 1; i < c; i += 1, c -= 1) {

			temp = *(this->arr + i);

			*(this->arr + i) = *(this->arr + c);
			*(this->arr + c) = temp;

			temp = T();
	
		}

	}

	// try to replace all elements with empty value
	template<typename T> void static_array<T>::clear() {

		for (size_t i = 0; i < this->_size; i += 1) *(this->arr + i) = T();

	}

	template<typename T> void static_array<T>::clear(size_t const& start_index, size_t const& end_index) {

		if (start_index >= this->_size) return;
		if (end_index >= this->_size) return;

		if (start_index > end_index) return;

		for (size_t i = start_index; i <= end_index; i += 1) {

			*(this->arr + i) = T();

		}

	}

	template<typename T> bool static_array<T>::insert_at(size_t const& target_index, T const& new_element) {

		// if index out of array range
		if (target_index >= this->_size) return false;
		else {
			// otherwise insert

			*(this->arr + target_index) = new_element;

			this->len += 1;

			return true;
		}

	}

	// remove => repalce element with "T()" value
	template<typename T> bool static_array<T>::remove(size_t const& target_index) {

		// if index out or range
		if (target_index >= this->_size) return false;
		
		// else
		*(this->arr + target_index) = T();
		this->len -= 1;

		return true;
	}

	// replace a range of elements in array with "T()"
	template<typename T> bool static_array<T>::remove(size_t const& start_index, size_t const& end_index) {

		// if out of range
		if (start_index >= this->_size) return false;
		if (end_index >= this->_size) return false;

		// no reversed ranges :)
		if (end_index < start_index) return false;

		for (size_t i = start_index; i <= end_index; i += 1) {
			this->remove(i);
		}

		return true;
	}


	/*
		-------------- static_array public operators --------------
	*/
	template<typename T> void static_array<T>::operator = (std::initializer_list<T> const& elements) {

		this->_size = elements.size();
		this->len = this->_size - 1;
		this->arr = new T[sizeof(T) * this->_size];

		size_t i = 0;
		for (T element : elements) {

			*(this->arr + i) = element;

			i += 1;
		}

	}
	template<typename T> T& static_array<T>::operator[] (size_t const& index) {
		return *(this->arr + index);
	}


	/*
		-------------- static_array methods for iterators --------------
	*/
	template<typename T> T* static_array<T>::begin() {
		return (this->arr + 0);
	}
	template<typename T> T* static_array<T>::cbegin() {
		return (this->arr + this->_size - 1);
	}

	template<typename T> T* static_array<T>::end() {
		// "size + 1" for "out of range" address
		return  (this->arr + this->_size);
	}
	template<typename T> T* static_array<T>::cend() {
		// something like -1 index
		return  (this->arr - 1);
	}


	/*
		-------------- static_array iterator class --------------
	*/
	template<typename T> class static_array<T>::iterator {

		private:
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
			void operator +=(int const& increment_value) {
				this->addr = (this->addr + increment_value);
			}

			// decrement operators
			void operator --() {
				this->addr = (this->addr - 1);
			}
			void operator -= (int const& decrement_value) {
				this->addr = (this->addr - decrement_value);
			}

			T* operator -> () {
				return this->addr;
			}

			// =========== compare iterator to reference ===========
			bool operator != (T* address_of_other_element) {
				return (this->addr != address_of_other_element) ? true : false;
			}

			bool operator == (T* address_of_other_element) {
				return (this->addr == address_of_other_element) ? true : false;
			}


			// =========== compare iterator to iterator ===========
			bool operator != (static_array<T>::iterator& other_iterator) {
				return (this->addr != other_iterator.addr) ? true : false;
			}

			bool operator == (static_array<T>::iterator& other_iterator) {
				return (this->addr == other_iterator.addr) ? true : false;
			}

	}; 
	// end of class iterator


} // end of namespace arrays