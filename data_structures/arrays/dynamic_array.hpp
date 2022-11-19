#include <iostream>

#pragma once

#define out_of_range "index out of range !"
#define reversed_range "start_index should be smaller or equal to end_index ."
#define illegal_type_const "const type is not allowed in dynamic_array use the alternative c_dynamic_array ."

namespace arrays {

	template<typename T> class dynamic_array {

		static_assert(!std::is_const<T>::value, illegal_type_const);

	private:
		
		size_t _len  = 0;
		size_t _size = 0;
		size_t _resize_factor = 0;

		T* arr = nullptr;
		bool* map = nullptr;

	public :

		// def constructor 
		dynamic_array() {

		}

		// o(n)
		// constructor 1
		dynamic_array( const size_t& array_size , const size_t& resize_factor)
			: _size{ array_size } , _resize_factor{ resize_factor } 
		{

			if (this->_resize_factor < 1) this->_resize_factor = 1;
			if (this->_size < 1) this->_size = 1;

			this->arr = new T[ sizeof(T) * this->_size ];

			for (size_t i = 0; i < this->_size; i += 1) {

				*(this->arr + i) = T();

			}

		}

		// o(n)
		// constructor 2
		dynamic_array( const size_t& resize_factor )
			: _resize_factor{ resize_factor }
		{

			if (this->_resize_factor < 1) this->_resize_factor = 1;
			this->_size = this->_resize_factor;

			this->arr = new T[ sizeof(T) * this->_size ];

			for (size_t i = 0; i < this->_size; i += 1) {

				*(this->arr + i) = T( );

			}

		}

		// o(n)
		// constructor 3
		dynamic_array( size_t const& resize_factor , std::initializer_list<T> const& array_elements )
			: _resize_factor{ resize_factor }
		{

			if (this->_resize_factor < 1) this->_resize_factor = 1;
			this->_size = array_elements.size();

			this->arr = new T[sizeof(T) * this->_size];

			size_t i = 0;
			for ( T element : array_elements ) {

				*(this->arr + i) = element;
				this->_len += 1;
				i += 1;
			}
		}


		// o(n)
		// constructor 4
		dynamic_array( std::initializer_list<T> const& array_elements ){

			this->_resize_factor = 1;
			this->_size = array_elements.size();

			this->arr = new T[sizeof(T) * this->_size];

			size_t i = 0;
			for (T element : array_elements) {

				*(this->arr + i) = element;
				this->_len += 1;
				i += 1;
			}

		}


		// o(n)
		// destructor 
		~dynamic_array() = default;


		/*
		
			====== public methods ======
		
		*/
		
		size_t size(); // O(1)
		size_t length(); // O(1)
		bool is_empty(); // O(1)
		void for_each(bool forward, void (* const& call_back_function)(T& element)); // O(n)
		bool set_resize_factor(const size_t& new_resize_factor); // O(1)
		bool insert(size_t const& index, T const& new_element);  // O(1)
		bool remove(size_t const& index); // O(1)
		void reverse(); // O(n)
		void resize();  // O(n+sz)
		void push(T const& new_element); // O(1)


		/*	
			========= iterator class =========
		*/
		class iterator;

	}; 
	// end of class dynamic_array 


	// o(n)
	// loop over all elements in this array
	template<typename T> void for_each(bool forward, void (* const& call_back_function)(T& element)) {

		if (forward) {

			for (size_t i = 0; i < this->_size; i += 1) {

				call_back_function(*(this->arr + i));

			}

		}
		else {

			for (size_t i = this->_len; i >= 0; i -= 1) {

				call_back_function(*(this->arr + i));
				if (i == 0) break;

			}

		}
	}

	// o(1)
	// set resize factor for next resize operation
	template<typename T> bool dynamic_array<T>::set_resize_factor(const size_t& new_resize_factor) {

		if (new_resize_factor > 0) {
			this->_resize_factor = new_resize_factor;
			return true;
		}
		else return false;

	}

	// o(1)
	// insert new element to the array
	template<typename T> bool dynamic_array<T>::insert(size_t const& index, T const& new_element) {

		// if array need resize
		if (this->_len == this->_size) this->resize();

		// if out_of_range
		if (index >= this->_size) return false;

		if ((this->arr + index) != nullptr || new_element != T()) {

			// insert new element
			*(this->arr + index) = new_element;

			return true;

		}

	}

	// o(1)
	template<typename T> bool dynamic_array<T>::remove(size_t const& index) {

		if (index >= this->_size) return false;

		if (*(this->arr + index) == T()) return false;

		*(this->arr + index) = T();
		this->_len -= 1;

		return true;
	}

	// o(n)
	template<typename T> void dynamic_array<T>::reverse() {

		// temp for swap's operations
		T temp = T();

		// loop over all & preforme swap's
		for (size_t i = 0, c = this->_size - 1; i < c; i += 1, c -= 1) {

			temp = *(this->arr + i);

			*(this->arr + i) = *(this->arr + c);

			*(this->arr + c) = temp;

			temp = T();

		}

	}

	// o(n)
	template<typename T> void dynamic_array<T>::resize() {

		size_t old_size = this->_size;
		// update size
		this->_size += this->_resize_factor;

		// allocated a new array with new size
		T* new_array = new T[sizeof(T) * this->_size];

		// o(n)
		// loop over the old one & move elements to the new one
		for (size_t i = 0; i < old_size; i += 1) {

			*(new_array + i) = *(this->arr + i);

		}
		for (size_t i = old_size; i < this->_size; i += 1) {

			*(new_array + i) = T();

		}

		delete[] this->arr;

		this->arr = new_array;

		new_array = nullptr;

	}

	// o(1)
	template<typename T> size_t dynamic_array<T>::size() {
		return this->_size;
	}

	// o(1)
	template<typename T> size_t dynamic_array<T>::length() {
		return this->_len;
	}

	// o(1)
	template<typename T> bool dynamic_array<T>::is_empty() {
		return (this->_len == 0);
	}

	// o(1)
	template<typename T> void dynamic_array<T>::push(T const& new_element) {

		// o(n)
		// if array is full resize it then insert in last empty position
		if (this->_len >= this->_size) this->resize();

		// insert & update length
		this->_len += 1;
		*(this->arr + this->_len - 1) = new_element;

	}


	/*
		
		---------- iterator class ----------

	*/
	template<typename T> class dynamic_array<T>::iterator {
		private:
			T * addr;
		public :
			iterator() { }
			~iterator() = default;
	};

} // end of namespace arrays