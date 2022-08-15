#pragma once

/*
	dynamic array methods 

	-- NAME ----------- BEST --> WORST
	
	constructor			o(n)
	destructor			o(n)

	size				o(1)
	length				o(1)
	is_empty			o(1)

	insert				o(1)
	remove				o(1)

	search				o(n)
	binary_search		o(log n) --> o(n)

	sort				o(n log n)
	reverse				o(n/2)

	resize				o(n)
	set_resize_factor	o(1)

	for_each			o(n)

	=					o(n)
	[]					o(1)
	+=					o(arr_1 + arr_2)
	+					o(arr_1 + arr_2)
*/

namespace arrays {

	template<typename T> class dynamic_array {

	private:
		
		size_t _len  = 0;
		size_t _size = NULL;
		size_t _resize_factor = NULL;

		T* arr = nullptr;

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

				*(this->arr + i) = NULL;

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

				*(this->arr + i) = NULL;

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
		// destructor 
		~dynamic_array() {

			if (this->arr != nullptr) {

				delete[] this->arr;
			}

		}


		/*
		
			public methods
		
		*/


		// o(n)
		// loop over all elements in this array
		void for_each( void (*call_back_function)(T element) ) {

			for (size_t i = 0; i < this->_size; i += 1) {

				call_back_function( *(this->arr + i) );

			}

		}

		// o(1)
		// set resize factor for next resize operation
		bool set_resize_factor( const size_t& new_resize_factor ) {

			if (new_resize_factor > 0) {
				this->_resize_factor = new_resize_factor;
				return true;
			}
			else return false;

		}

		// o(1)
		// insert new element to the array
		bool insert( const size_t& index , const T& new_element ) {

			// if index out of range
			if (index >= this->_size) return false;

			// if the same element is already there
			if ( *(this->arr + index) == new_element ) return false;

			// update length if new element added
			if( *(this->arr + index) == NULL ) this->_len += 1;

			// insert new element
			*(this->arr + index) = new_element;

			// if array is full we need to "resize it"
			if (this->_len == this->_size) this->resize();

			return true;
		}

		// o(1)
		bool remove( const size_t& index ) {

			if (index >= this->_size) return false;

			if( *(this->arr + index) == NULL ) return false;

			*(this->arr + index) = NULL;
			this->_len -= 1;

			return true;
		}

		// o(n/2)
		void reverse() {

			// temp for swap's operations
			T temp = NULL;

			// loop over all & preforme swap's
			for (size_t i = 0, c = this->_size - 1; i < c; i += 1, c -= 1) {
				
				temp = *(this->arr + i);

				*(this->arr + i) = *(this->arr + c);

				*(this->arr + c) = temp;

				temp = NULL;

			}

		}

		// o(n)
		void resize() {

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

				*(new_array + i) = NULL;

			}

			delete[] this->arr;

			this->arr = new_array;

			new_array = nullptr;

		}

		// o(1)
		size_t size() {
			return this->_size;
		}

		// o(1)
		size_t length() {
			return this->_len;
		}

		// o(1)
		bool is_empty() {
			return (this->_len == 0);
		}


		/*
		
			operators
		
		*/


		// o(1)
		T operator [] ( const size_t& index ) {

			if (index >= this->_size) return NULL;
			else return *(this->arr + index);

		}

		dynamic_array<T>& operator = (  std::initializer_list<T> &elements ) {
			return dynamic_array<T>(1, elements);
		}

		void operator = ( dynamic_array<T>& new_array ) {

			this->_len  = new_array._len;
			this->_size = new_array._size;
			this->_resize_factor = new_array._resize_factor;

			this->arr = new T[ sizeof(T) * this->_size ];

			for (size_t i = 0; i < this->_size; i += 1) {

				*(this->arr + i) = *(this->new_array.arr + i);

			}

		}
		

	}; // end of dynamic_array class

} // end of namespace arrays