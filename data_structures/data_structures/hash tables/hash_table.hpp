#include <iostream>
#pragma once

/*
	that module contain a simple hash_table with basics function like => clear , isEmpty , isFull .... 
	we using that class later in different hash tables like => open-addressing , chaining ...
*/

// === hash table ~ methods ===========
/*
   -- NAME ------------ BEST --> WORST

	clear			=> o(n)  --> o(n)
	clone			=> o(n)	 --> o(n)
	elements		=> o(n)	 --> o(n)

	get				=> o(1)
	put				=> o(1)

	search			=> o(1)	 --> o(n)
	remove			=> o(1)
	replace			=> o(1)
	replaceAll		=> o(n)	 --> o(n)

	isEmpty			=> o(1)
	isFull			=> o(1)

	keys			=> o(n)	 --> o(n)
	values			=> o(n)	 --> o(n)

	print			=> o(n)	 --> o(n)
	length			=> o(1)
*/

namespace hash_tables {

	// simple hash table => "" replacemenet hash table "" 
	template<typename t> class hash_table {
	private:
		unsigned int table_size = 0;
		unsigned int len = 0;
		t* table = NULL;

		// simple hash function all what to do is => value % table_size
		int hash(t value) {
			// hashing & getting index 
			int hash_index = value % table_size;

			// send value to that hashing index
			table[hash_index] = value;

			// return hash_index as a key
			return hash_index;
		}

	public:
		// constructor 
		hash_table(unsigned int hash_table_size = 2){
			// define size in construction time
			table_size = (hash_table_size < 2) ? 2 : hash_table_size;

			// define hash table in construction time
			table = new t[table_size];

		}
		// deconstructor
		~hash_table() { }



		// simple function print values in console only work in that simple hash table
		void print() {

			for (int i = 0; i < table_size; i += 1) {
				std::cout << (table[i] == NULL) ? " E " : table[i]  << " ";
			}

		}
};


}