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

	adjust				o(1) --> o(log n)
	heapify				o(n) 

	heap_sort			o(n log n)

	get_root			o(1) --> o(log n)

	is_full				o(1)
	is_complete			o(n)

	index_of			o(n)
	value_of			o(n)
*/

namespace trees {

	/*
	
		index's in binary_heap start from "1"

	*/

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


		/*
		
			========= some static private functions for heap ============

		*/ 

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

		// o(1) --> o(log n)
		// recursive heapify until the element get in it's place
		static void HEAPIFY(binary_heap<T>* BINARY_HEAP, unsigned int target_index) {

			/*
				the same process like adjust function but from down to top
			*/

			// get index's
			unsigned int left_index  = target_index * 2;
			unsigned int right_index = left_index   + 1;

			unsigned int precedence = NULL;

			// check the all possible cases

			// all is out of heap
			if (left_index > BINARY_HEAP->heap_size && right_index > BINARY_HEAP->heap_size) return;
			// all is inside heap
			if (left_index <= BINARY_HEAP->heap_size && right_index <= BINARY_HEAP->heap_size) {
				// compare to get the precedence
				precedence = BINARY_HEAP->comp_function(BINARY_HEAP->heap[left_index - 1], BINARY_HEAP->heap[right_index - 1]) ? right_index : left_index;

			}
			else { // otherwise one of them out of heap

				if (left_index <= BINARY_HEAP->heap_size && right_index > BINARY_HEAP->heap_size) precedence = left_index;
				
				if (left_index > BINARY_HEAP->heap_size && right_index <= BINARY_HEAP->heap_size) precedence = right_index;
			
			}
			
			// compare the precedence with target 
			if ( BINARY_HEAP->comp_function(BINARY_HEAP->heap[target_index - 1], BINARY_HEAP->heap[precedence - 1]) ) {

				// if we need to preforme a swap
				T temp = BINARY_HEAP->heap[target_index - 1];
				BINARY_HEAP->heap[target_index - 1] = BINARY_HEAP->heap[precedence - 1];
				BINARY_HEAP->heap[precedence - 1] = temp;

				// after swap check the down value recursivly 
				binary_heap<T>::HEAPIFY(BINARY_HEAP, precedence);
			}

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

			// o(n)
			// loop over all and set NULL values
			for (unsigned int i = 0; i < this->heap_size ; i += 1) {
				this->heap[i] = NULL;
			}

		}

		// o(n*2)
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

			try {

				if (this->heap != nullptr) {

					delete[] this->heap;
					this->heap = nullptr;

				}

			}
			catch (std::exception& error) {
				std::cerr << error.what() << '\n';
				throw error.what();
			}

		}

		// o(1) --> o(log n)
		bool insert( T const& new_value ) {

			unsigned int index = this->len + 1;

			// if heap is full then no insert
			if (index > this->heap_size) return false;

			// insert new value in last known empty spot
			this->heap[ index - 1 ] = new_value;

			// update length
			this->len += 1;

			// *** after insertion we have to preforme adjustment ***
			int parent_index = (int)( index / 2 );

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
		// remove root only
		// get_root : if you want to take root value after it's get deleted
		bool remove( T* get_root = nullptr ) {

			if ( this->heap[0] == NULL ) return false;

			if ( get_root != nullptr ) {
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
		// remove any value you want
		// index from 1 to ....
		bool remove_at( unsigned int const& index_of_target ) {

			if (index_of_target < 1 || index_of_target > this->heap_size) return false;
			else {
				// update length
				this->len -= 1;

				// move last element in heap to that target place
				this->heap[index_of_target-1] = this->heap[ this->len ];
				this->heap[ this->len ] = NULL;

				// then preforme adjust to keep heap valid
				this->adjust(index_of_target);

				return true;
			}

		}

		// o(n)
		// search for index of target in heap
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
		// get value of specific index at the heap
		T value_of_index(unsigned int const& index_of_target) {

			// if index ouf of heap
			if (index_of_target < 1 || index_of_target > this->heap_size) return NULL;
			else return this->heap[index_of_target-1];

		}

		// o(1) --> o(log n)
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

			// loop over all values & preforme heapify 
			for (unsigned int i = this->heap_size ; i > 0; i -= 1) {

				binary_heap<T>::HEAPIFY(this , i);

			}

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


		/*
			======= public static functions =========
		*/ 

		// o(n log n)
		// take all the elements sorted from target_heap
		static std::vector<T> heap_sort( binary_heap<T>& target_heap ) {

			T* temp = new T();
			std::vector<T> elements;

			for (unsigned int i = 1; i <= target_heap.heap_size; i += 1) {

				if ( target_heap.remove(temp) ) {
					elements.push_back( *temp );
				}

			}

			delete temp;

			
			return elements;
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
