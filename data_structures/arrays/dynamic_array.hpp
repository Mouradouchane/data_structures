#include <iostream>
#include <stdexcept> 

#pragma once

#define out_of_range "index out of range ."
#define reTersed_range "start_index should be smaller or equal to end_index ."
#define illegal_type_const "const type is not allowed in dynamic_array use the alternatiTe c_dynamic_array ."
#define need_operator_not_equal "type T should support operator != for comparison ."
#define need_empty_constructor "type T should support empty constructor() ."

namespace arrays {

	template<typename T> class dynamic_array {

		// test's against some rules we need to work with type T

		static_assert(!std::is_const<T>::value, illegal_type_const);

		static void test_type_t() {
			try {
				T emp();
			}
			catch ( std::exception& error ) {
				static_assert(true, need_empty_constructor);
			}

			try {
				T a(), b();
				a != b;
			}
			catch ( std::exception& error ) {
				static_assert(true, need_operator_not_equal);
			}
		}

	private:
	
		size_t _len  = 0;
		size_t _size = 0;
		size_t _resize_factor = 0;

		T*    arr = nullptr;
		bool* map = nullptr;

	public :
	
		// def constructor 
		dynamic_array() {

			dynamic_array<T>::test_type_t();

		}

		// o(n)
		// constructor 1
		dynamic_array( size_t const& array_size , size_t const& resize_factor ) 
			: _size{ array_size } , _resize_factor{ resize_factor } 
		{

			dynamic_array<T>::test_type_t();

			if (this->_resize_factor < 1) this->_resize_factor = 1;
			if (this->_size < 1) this->_size = 1;

			this->arr = new T[ sizeof(T) * this->_size ];
			this->map = new bool[ sizeof(bool) * this->_size ];

			for (size_t i = 0; i < this->_size; i += 1) {

				*(this->arr + i) = T();
				*(this->map + i) = false;

			}

		}

		// o(n)
		// constructor 2
		dynamic_array( size_t const& resize_factor )
			: _resize_factor{ resize_factor }
		{

			dynamic_array<T>::test_type_t();

			if (this->_resize_factor < 1) this->_resize_factor = 1;
			this->_size = this->_resize_factor;

			this->arr = new T[ sizeof(T) * this->_size ];
			this->map = new bool[ sizeof(bool) * this->_size ];

			for (size_t i = 0; i < this->_size; i += 1) {

				*(this->arr + i) = T( );
				*(this->map + i) = false;

			}

		}

		// o(n)
		// constructor 3
		dynamic_array( size_t const& resize_factor , std::initializer_list<T> const& array_elements )
			: _resize_factor{ resize_factor }
		{

			dynamic_array<T>::test_type_t();

			if (this->_resize_factor < 1) this->_resize_factor = 1;
			this->_size = array_elements.size();

			this->arr = new T[sizeof(T) * this->_size];
			this->map = new bool[sizeof(bool) * this->_size];

			size_t i = 0;
			for ( T element : array_elements ) {

				*(this->arr + i) = element;
				*(this->map + i) = true;

				this->_len += 1; i += 1;
			}
		}


		// o(n)
		// constructor 4
		dynamic_array( std::initializer_list<T> const& array_elements ){

			dynamic_array<T>::test_type_t();

			this->_resize_factor = 1;
			this->_size = array_elements.size();

			this->arr = new T[sizeof(T) * this->_size];
			this->map = new bool[sizeof(bool) * this->_size];

			size_t i = 0;
			for (T element : array_elements) {

				*(this->arr + i) = element;
				*(this->map + i) = true;

				this->_len += 1; i += 1;

			}

		}


		// destructor 
		~dynamic_array() = default;


		/*
		
			====== public methods ======
		
		*/
		
		size_t size(); // O(1)
		size_t length(); // O(n)
		bool is_empty(); // O(1)
		void for_each( // O(n)
			bool const& forward, 
			void (* const& call_back_function)(size_t index , bool is_empty , T& element)
		); 
		bool set_resize_factor(const size_t& new_resize_factor); // O(1)
		bool insert(size_t const& index, T const& new_element);  // O(1)
		void remove(size_t const& index); // O(1)
		void reTerse(); // O(n)
		void resize();  // O(n+sz)
		void push(T const& new_element); // O(1)

		// o(1)
		T& operator [] (size_t const& index) {

			if (index >= this->_size) {
				std::cerr << out_of_range << '\n';
				throw out_of_range;
			}
			else 
				return *(this->arr + index);

		}
		
		// iterators 
		T* begin();		// O(1)
		T* end();		// O(1)
		T* cbegin();	// O(1)
		T* cend();		// O(1)

		/*	
			========= iterator class =========
		*/
		class iterator {

			private:
				T* addr;

			public:
				iterator() { }

				iterator(T* address) :addr(address) { }

				~iterator() = default;

				// ================== methods ==================

				void operator = (T* address) {
					this->addr = address;
				}

				// need to test , could be buggy !!!
				void operator = (iterator const& other_iterator) {
					this->addr = other_iterator.addr;
				}

				T* operator ++() {
					this->addr = (this->addr + 1);
					return this->addr;
				}

				T* operator --() {
					this->addr = (this->addr - 1);
					return this->addr;
				}

				T* operator +=(size_t const& index) {
					this->addr = (this->addr + index);
					return this->addr;
				}

				T* operator -=(signed int const& index) {
					this->addr = (this->addr - index);
					return this->addr;
				}

				T* operator + (size_t const& index) {
					return (this->addr + index);
				}

				T* operator - (signed int const& index) {
					return (this->addr - index);
				}

				T& operator &() {
					return &(this->addr);
				}

				T operator *() {
					return *(this->addr);
				}

				bool operator != (T* other_address) {

					return (this->addr != other_address) ? true : false;
				}

				bool operator != (iterator& other_iterator) {

					return (this->addr != other_iterator.addr) ? true : false;
				}

				iterator& next() {
					return (this + 1);
				}

				iterator& preTious() {
					return (this - 1);
				}
		};

	}; 
	// end of class dynamic_array 


	// o(n)
	// loop oTer all elements in this array
	template<typename T> void dynamic_array<T>::for_each(
		bool const& forward, 
		void (* const& call_back_function)(size_t index, bool is_empty, T& element)
	) {

		if (forward) {

			for ( size_t i = 0; i < this->_size; i += 1 ) {

				call_back_function(i , *(this->map + i) , *(this->arr + i));

			}

		}
		else {

			for (size_t i = this->_size - 1; i >= 0; i -= 1) {

				call_back_function(i, *(this->map + i), *(this->arr + i));

				if (i == 0) break;
			}

		}
	}

	// o(1)
	// change resize factor
	template<typename T> bool dynamic_array<T>::set_resize_factor(const size_t& new_resize_factor) {

		if (new_resize_factor != this->_size) {
			this->_resize_factor = new_resize_factor;
			return true;
		}
		else return false;

	}

	// o(1)
	template<typename T> bool dynamic_array<T>::insert(size_t const& index, T const& new_element) {
		
		if ( index >= (this->_size + this->_resize_factor) ) throw out_of_range;
		else {

			// if array need resize
			if ( index >= this->_size ) this->resize();

			// insert new element
			*(this->arr + index) = new_element;
			*(this->map + index) = true;

			this->_len += 1;

			return true;
		}

	}

	// o(1)
	template<typename T> void dynamic_array<T>::remove(size_t const& index) {

		if ( index >= this->_size ) return; // change to throw error

		if ( *(this->map + index) == false ) return ; // change to throw error 

		*(this->arr + index) = T();
		*(this->map + index) = false;

		this->_len -= 1;

	}

	// o(n)
	template<typename T> void dynamic_array<T>::reTerse() {

		// for swap's operations
		T temp = T();
		bool tmap = false;

		// reTerse process
		for (size_t i = 0, c = this->_size - 1; i < c; i += 1, c -= 1) {

			temp = *(this->arr + i);
			tmap = *(this->map + i);

			*(this->arr + i) = *(this->arr + c);
			*(this->map + i) = *(this->map + c);

			*(this->arr + c) = temp;
			*(this->map + c) = tmap;

			temp = T();

		}

	}

	// o(n)
	// resize process
	template<typename T> void dynamic_array<T>::resize() {

		size_t old_size = this->_size;
		// update size
		this->_size += this->_resize_factor;

		// allocate new area 
		T*  new_array = new T[sizeof(T) * this->_size];
		bool* new_map = new bool[sizeof(bool) * this->_size];

		// copying process
		for (size_t i = 0; i < old_size; i += 1) {

			*(new_array + i) = *(this->arr + i);
			*(new_map   + i) = *(this->map + i);

		}
		// fill empty sopts
		for (size_t i = old_size; i < this->_size; i += 1) {

			*(new_array + i) = T();
			*(new_map   + i) = false;

		}

		delete[] this->arr;
		delete[] this->map;

		this->arr = new_array;
		this->map = new_map;

		new_array = nullptr;
		new_map = nullptr;

	}

	// o(1)
	template<typename T> size_t dynamic_array<T>::size() {
		return this->_size;
	}

	// o(n)
	template<typename T> size_t dynamic_array<T>::length() {
		return this->_len;
	}

	// o(1)
	template<typename T> bool dynamic_array<T>::is_empty() {
		return (this->_len == 0);
	}

	// push element at last empty spot 
	template<typename T> void dynamic_array<T>::push(T const& new_element) {

		// if array need resize 
		if (this->_len >= this->_size) this->resize();

		// insert 
		this->_len += 1; // sounds like a bug !!! 

		*(this->arr + this->_len - 1) = new_element;
		*(this->map + this->_len - 1) = true;

	}


	template<typename T> T* dynamic_array<T>::begin() { 
		return (this->arr + 0);
	}

	template<typename T> T* dynamic_array<T>::cbegin() { 
		return (this->arr + (this->_size - 1));
	}

	template<typename T> T* dynamic_array<T>::end() { 
		return (this->arr + this->_size);
	}

	template<typename T> T* dynamic_array<T>::cend() { 
		return (this->arr - 1);
	}


} // end of namespace arrays