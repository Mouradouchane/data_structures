#include <iostream>
#include <stdexcept> 

#pragma once

#define out_of_range "index out of range !"
#define reversed_range "start_index should be smaller or equal to end_index ."
#define illegal_type_const "const type is not allowed in static_array use the alternative c_static_array ."

namespace arrays {


	template<typename T> class static_array {
		
		static_assert(!std::is_const<T>::value , illegal_type_const);

	private:
		size_t _size = 0;
		int len = 0;

		// would be heap allocation later
		T* arr = nullptr;

	public :

		// default constructor 
		static_array( size_t array_size = 0 ) {

			// array size
			this->_size = array_size;

			this->arr = new T[sizeof(T) * array_size];

			// fill with T()
			for (size_t i = 0; i < this->_size; i += 1) *(this->arr + i) = T();

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
		~static_array() { 

			try {

				if (this->arr != nullptr) {

					delete[] this->arr;
					this->arr = nullptr;

				}

			}
			catch (std::exception& error) {
				std::cerr << error.what() << '\n';
				throw error.what();
			}
				
		}

		/*
			===== methods =====
		*/

		void for_each(bool const& forward , void (* const& call_back_function)(T& element)); // O(n)
		void for_each(
			size_t const& start_index , 
			size_t const& end_index ,
			void (* const& call_back_function)(T& element)
		); // O(n)
		size_t length();// O(1)
		size_t size();	// O(1)
		void reverse(); // O(n)
		void clear();	// O(n)
		void remove(size_t const& index); // O(1) 
		void remove(size_t const& start_index, size_t const& end_index); // O(range)
		bool insert_at(size_t const& target_index, T const& new_element); // O(n)


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

		/*
			===== errors =====
		*/
		class error ;
	}; 
	/*

		end of class static_array

	*/



	/*
		-------------- static_array public methods --------------
	*/

	// loop over all elements
	template<typename T> void static_array<T>::for_each(bool const& forward , void (* const& call_back_function)(T& element)) {

		if (forward) {

			for (size_t i = 0; i < this->_size; i += 1) {

				call_back_function( *(this->arr + i) );

			}

		}
		else {

			for (size_t i = this->len; i >= 0; i -= 1) {

				call_back_function(*(this->arr + i));

				if (i == 0) break;
			}

		}
	}

	template<typename T> void static_array<T>::for_each(
		size_t const& start_index, 
		size_t const& end_index, 
		void (* const& call_back_function)(T& element)
	) {
		try {

			if (start_index >= this->_size) throw static_array<T>::error(out_of_range);
			if (end_index >= this->_size) throw static_array<T>::error(out_of_range);
			
			if (start_index < end_index) {

				for (size_t i = start_index; i <= end_index; i += 1) {
					call_back_function( *(this->arr + i) );
				}

			}
			else {

				for (size_t i = start_index; i >= end_index; i -= 1) {

					call_back_function(*(this->arr + i));

					if (i == 0) break;
				}

			}

		}
		catch (static_array<T>::error& err) {
			std::cerr << err.what() << '\n';
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

		this->len = 0;

		for (size_t i = 0; i < this->_size; i += 1) {

			*(this->arr + i) = T();
		}

	}
	
	template<typename T> void static_array<T>::remove(size_t const& start_index, size_t const& end_index) {
		try {

			if (start_index >= this->_size)	throw static_array<T>::error( out_of_range );
			if (end_index >= this->_size)	throw static_array<T>::error( out_of_range );

			if (start_index > end_index) throw static_array<T>::error( reversed_range );

			for (size_t i = start_index; i <= end_index; i += 1) {

				*(this->arr + i) = T();
				this->len -= 1;

			}

		}
		catch (static_array<T>::error & err) {
			std::cerr << err.what() << '\n';
		}
	}

	template<typename T> void static_array<T>::remove(size_t const& index) {
		try {

			if (index >= this->_size) throw static_array<T>::error(out_of_range);
			else {

				*(this->arr + index) = T();
				this->len -= 1;

			}
		}
		catch (static_array<T>::error& err) {
			std::cerr << err.what() << '\n';
		}
	}

	template<typename T> bool static_array<T>::insert_at(size_t const& target_index, T const& new_element) {

		// if index out of array range
		if (target_index >= this->_size) {
			throw static_array<T>::error(out_of_range);
			return false;
		}
		else {
			// otherwise insert

			*(this->arr + target_index) = new_element;

			this->len += 1;

			return true;
		}

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
		
		try {

			if (index >= this->_size) throw static_array<T>::error(out_of_range);
			else return *(this->arr + index);

		}
		catch (static_array<T>::error & err) {
			std::cerr << err.what() << '\n';
		}

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



	/*
		-------------- static_array error class --------------
	*/
	template<typename T> class static_array<T>::error : public std::runtime_error {
		
		private:
			const char* msg;

		public:

			error();

			error(const char* error_message) : std::runtime_error(error_message) {
				this->msg = error_message;
			}

			~error() = default;

			char const* what() const override {
				return this->msg;
			}

	};
	// end of class error


} // end of namespace arrays