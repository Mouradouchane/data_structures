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
	is_complete			o(n)

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
		static void PRINT(unsigned int const& size, int index , int tab , T* heap) {

			int left  = index * 2;
			int right = left  + 1;
			
			tab += 1;
			
			if (right <= size) binary_heap<T>::PRINT(size, right, tab, heap);

			for (unsigned int i = 0; i < tab ; i += 1) {
				std::cout << '\t';
			}
				
			std::cout << '[' << heap[index - 1] << ']' << "\n";

			if (left  <= size) binary_heap<T>::PRINT(size, left , tab, heap);
		}

	public: 

		// o(n)
		// normal constructor
		binary_heap( unsigned int const& heap_size  , bool (*comparison_function)(T const& a , T const& b) ) {

			// will be used to compare between heap values
			this->comp_function = comparison_function;

			// allocate array in heap with that heap_size
			this->heap = new T[heap_size];

			// set heap size & length
			this->heap_size = heap_size;
			this->len  = 0;

			// loop over all and set NULL values
			for (unsigned int i = 0; i < this->heap_size ; i += 1) {
				this->heap[i] = NULL;
			}

		}

		// o(n)
		// heapify constructor
		binary_heap( bool (*comparison_function)(T const& a , T const& b) , std::vector<T> const& heap_elements ) {

			// will be used to compare between heap values
			this->comp_function = comparison_function;

			// allocate array in heap with that heap_size
			this->heap = new T[heap_elements.size()];

			// set heap size & length
			this->heap_size = heap_elements.size();
			this->len  = 0;

			// o(n)
			// loop over all and insert values in heap
			for ( unsigned int i = 0; i < heap_elements.size(); i += 1 ) {
				
				// insert and update length
				this->heap[i] = heap_elements[i];
				this->len += 1;
				
			}

			// o(n)
			// then we have to preforme "heapify"
			this->heapify();
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

		// o(1) --> o(log n
		// get_root : if you want to take root value after it's get deleted
		bool remove( T *get_root = nullptr ) {

			if ( this->heap[0] == NULL || this->locked ) return false;

			if (get_root != nullptr) {
				*get_root = this->heap[0];
			}

			this->len -= 1; // update length
			this->heap[0] = this->heap[ this->len ]; // put last value in root 
			this->heap[this->len] = NULL; // remove last value from it's old position

			// index 1 => root
			this->adjust( 1 );

			return true;
		}

		// o(1) --> o(log n)
		bool remove_at( unsigned int const& index_of_target ) {
			return false;
		}

		// o(n)
		// search for index of target
		int index_of( T const& target ) {

			// loop over all & search
			for (unsigned int i = 0; i < this->heap_size ; i += 1) {

				// if target found return it's index in heap
				if (this->heap[i] == target) return i + 1;

			}

			// if target not found
			return -1;
		}

		// o(1)
		// adjust the process of compare current root with children and swap if needed
		// to keep the heap , a heap
		void adjust( unsigned int const& index ) {
				
			// if index is out heap stop
			if (index > this->heap_size) return;

			// calc left right index's
			int left_index  = index * 2;
			int right_index = left_index + 1;

			// we need it to store the index of each value is "the precedence one"
			int precedence = NULL;

			// if left & right index's out of heap stop
			if (left_index > this->heap_size && right_index > this->heap_size) return;

			// if left & right index's in the heap
			// then we have to compare bettween the left child & right child to get "the precedence one"
			if (left_index <= this->heap_size && right_index <= this->heap_size) {
				// compare left vs right 
				precedence = this->comp_function(this->heap[left_index - 1], this->heap[right_index - 1]) ? right_index : left_index;
			}

			// if left out of heap & right not
			if (left_index  > this->heap_size && right_index <= this->heap_size) precedence = right_index;

			// if right out of heap & left not
			if (right_index > this->heap_size && left_index  <= this->heap_size) precedence = left_index;

			// last step is to compare bettween "parent/index" & "the precedence" value
			if ( this->comp_function(this->heap[index - 1], this->heap[precedence - 1]) ) {

				/*
				if comparison is true that mean we need to prefome a swap 
				between target "parent/index" & "the precedence"
				*/ 
				T temp = this->heap[index - 1];
				this->heap[index - 1] = this->heap[precedence - 1];
				this->heap[precedence - 1] = temp;

				// if swap done that mean "the precedence" now it's "the old parent"
				// soo we need to adjust again 
				this->adjust(precedence);
			}

		}

		// o(n)
		// heapify the all elements in heap 
		void heapify() {

		}

		// o(1)
		// get copy of the "current root"
		T get_root() {
			return this->heap[0];
		}

		// o(1)
		// length or how many elements in the heap "currently"
		unsigned int length() {
			return this->len;
		}

		// o(1)
		// get the size of that heap
		unsigned int size() {
			return this->heap_size;
		}

		// o(1)
		// check if heap is full of values nor not yet
		bool is_full() {
			return ( this->len >= this->heap_size );
		}

		// o(n)
		// check if that heap is "complete binary tree"
		bool is_complete() {

			// loop over all & check for gaps
			for (unsigned int i = 1; i < this->heap_size; i += 1) {

				// if gaps found
				if (this->heap[i - 1] == NULL && this->heap[i] != NULL) return false;

			}

			// if no gaps found
			return true;
		}

		// o(1)
		// check if the heap is locked or not
		bool is_locked() {
			return this->locked;
		}

		// o(1)
		// if you want to lock the heap
		bool lock() {
			
			// if already locked then return false as confirmation
			if (this->locked) return false;
			// else mean we can lock that heap 
			else {
				// preforme lock & return true as confirmation
				this->locked = true;
				return true;
			}

		}

		// o(1)
		// this one like "lock function" above but it's for unlock the heap
		bool unlock() {

			if (!this->locked) return false;
			else {

				this->locked = false;
				return true;
			}

		}


		// o(n)
		// print function only for testing
		void print() {

			int index = 1 , tab = 0;

			// recursive print for binary heap visualisation
			binary_heap<T>::PRINT(this->heap_size, index , tab , this->heap);

			std::cout << "========================== \n";
		}

	}; // end of class "binary_heap"


} // end of namespace "trees"
