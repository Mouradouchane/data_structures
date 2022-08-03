
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
		binary_heap( unsigned int heap_size , bool (*comparison_function)(T const& a , T const& b) ,T *heap_elements ) {

			this->comp_function = comparison_function;

			// allocate array in heap with that heap_size
			this->heap = new T[heap_size];

			this->heap_size = heap_size;
			this->len  = 0;

			// o(n)
			// loop over all elements in heap & set NULL value
			for (unsigned int i = 0; i < this->heap_size ; i += 1) {
				
				// if element not out of heap size
				if (i > this->heap_size) break;

				// then insert element & update length
				this->heap[i] = heap_elements[i];
				this->len += 1;
				
			}

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
		bool insert(T const& new_value) {
			return false;
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
			return false;
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

		// print function only for testing
		static void print( binary_heap<T> *heap ) {

			for (unsigned int i = 0; i < heap->heap_size; i += 1) {
				std::cout << "[" << i << "]" << heap->heap[i] << "\n";
			}
			 
		}

	}; // end of class "binary_heap"


} // end of namespace "trees"
