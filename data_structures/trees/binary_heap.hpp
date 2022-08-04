#include <vector> 
#pragma once

/*
	Binary Heap methods

	-- NAME ----------- BEST --> WORST

	size				o(1)
	lenght				o(1)

	insert				o(1) --> o(log n)
	remove				o(1) --> o(log n)
	remove_at			o(1) --> o(log n)

	adjust				o(1)
	heapify				o(n)

	get_root			o(1) --> o(log n)

	is_full				o(1)
	is_complete			o(1)

	lock				o(1)
	unlock				o(1)
	is_locked			o(1)

	index_of			o(n)
*/

namespace trees {


	template<typename T> class binary_heap {

	private :

		// full size of that heap
		unsigned int heap_size = NULL; 
		
		// how much values/nodes currently in heap
		// we can also using it to refer to last empty spot in heap
		unsigned int len  = NULL; 

		T* heap = nullptr; // heap as array

		// call_back function used to comapre nodes 
		bool (*comp_function)(T const& a, T const& b);

		// parameter for lock/unlock insert/remove... from heap
		bool locked = false;


		// ========= some static private functions for heap ============

		// print function only for testing
		static void PRINT(unsigned int const& size, T* heap) {

			for (unsigned int i = 0; i < size; i += 1) {
				std::cout << "[" << i << "]" << heap[i] << "\n";
			}

		}

	public: 

		// o(n)
		// def constructor
		binary_heap( unsigned int const& heap_size  , bool (*comparison_function)(T const& a , T const& b) ) {

			this->comp_function = comparison_function;

			// allocate array in heap with that heap_size
			this->heap = new T[heap_size];

			this->heap_size = heap_size;
			this->len  = 0;

			// loop over all elements in heap & set NULL value
			for (unsigned int i = 0; i < this->heap_size ; i += 1) {
				this->heap[i] = NULL;
			}

		}

		// o(n)
		// heapify constructor
		binary_heap( bool (*comparison_function)(T const& a , T const& b) , std::vector<T> const& heap_elements ) {

			this->comp_function = comparison_function;

			// allocate array in heap with that heap_size
			this->heap = new T[heap_elements.size()];

			this->heap_size = heap_elements.size();
			this->len  = 0;

			// o(n)
			// loop over all elements in heap & set NULL value
			for ( unsigned int i = 0; i < heap_elements.size(); i += 1 ) {
				
				// then insert element & update length
				this->heap[i] = heap_elements[i];
				this->len += 1;
				
			}

			// lock this heap because it's full
			this->locked = true;

			// o(n)
			// after that heapify

		}

		// o(1)
		// def destructor
		~binary_heap() {

			// delete/free heap array from "heap"
			delete this->heap;

		}

		// o(1) --> o(log n)
		bool insert( T const& new_value ) {

			int index = this->len + 1;

			// if heap is full or locked then no insert
			if (this->locked || index > this->heap_size) return false;

			// insert new value in last known empty spot
			this->heap[ index - 1 ] = new_value;

			// update length
			this->len += 1;

			// *** after insertion we have to preforme adjustment ***
			int parent_index = (int)( index / 2);

			while ( parent_index > 0  && parent_index < this->heap_size ){

				// if compare function tell us that parent must be switch with it's child "new_value"
				if (this->comp_function(this->heap[parent_index-1], this->heap[index-1])) {

					// preforme switch
					T temp = this->heap[parent_index-1];
					this->heap[parent_index-1] = this->heap[index-1];
					this->heap[index-1] = temp;

					index = parent_index;
					parent_index = (int)(index / 2);
				}
				else break;
			}

			// insert confirmation 
			return true;
		}

		// o(1) --> o(log n)
		bool remove() {
			return false;
		}

		// o(1) --> o(log n)
		bool remove_at( unsigned int const& index_of_target ) {
			return false;
		}

		// o(n)
		int index_of(T const& target ) {
			return -1;
		}

		// o(1)
		void adjust() {

		}

		// o(n)
		void heapify() {

		}

		// o(1)
		T get_root() {
			return this->heap[0];
		}

		// o(1)
		unsigned int length() {
			return this->len;
		}

		// o(1)
		unsigned int size() {
			return this->heap_size;
		}

		// o(1)
		bool is_full() {
			return ( this->len >= this->heap_size );
		}

		// o(1)
		bool is_complete() {
			return false;
		}

		// o(1)
		bool is_locked() {
			return this->locked;
		}

		// o(1)
		bool lock() {
			return false;
		}

		// o(1)
		bool unlock() {
			return false;
		}


		// o(n)
		// print function only for testing
		void print() {

			// recursive print for binary heap visualisation
			binary_heap<T>::PRINT(this->heap_size, this->heap);

		}

	}; // end of class "binary_heap"


} // end of namespace "trees"
