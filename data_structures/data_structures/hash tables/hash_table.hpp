#include <iostream>
#pragma once

/*
	that module contain a simple & stupid hash_table with basics function like => get , set , clear ...
	we using that hash_table later in different good & better hash_tables like => open-addressing , chaining ...
*/

// === hash table ~ methods ===========
/*
   -- NAME ------------ BEST --> WORST

	clear			=> o(n)  --> o(n)
	clone			=> o(n)	 --> o(n)
	elements		=> o(n)	 --> o(n)

	set				=> o(1)
	get				=> o(1)

	remove			=> o(1)
	replace			=> o(1)
	replaceAll		=> o(n)	 --> o(n)

	isEmpty			=> o(1)
	isFull			=> o(1)

	values			=> o(n)	 --> o(n)

	print			=> o(n)	 --> o(n)
	length			=> o(1)
	size			=> o(1)
*/

namespace hash_tables {

// simple hash table => "" replacemenet hash table "" there's no keys only values
template<typename t> class hash_table {
	private:
		unsigned int table_size = 0;
		unsigned int len = 0;
		const unsigned int min_size = 3;
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
		hash_table(unsigned int hash_table_size = min_size){

			// check if table_size is bigger than min size allowed "3"
			table_size = (hash_table_size < min_size) ? min_size : hash_table_size;

			// chech if "table size" is prime  
			// if not we round it to be prime :)
			table_size = isPrimeNumber(table_size);

			// define hash table with valid size in construction time
			table = new t[table_size];

		}

		// set data by value to hash table
		void set(t data) {
			// hash & get index
			int index = hash(data);
			// put data in target index
			table[index] = data;
		}

		// get data by value from hash table
		t get(t data) {
			// hash & get index
			int index = hash(data);
			// get data in that index & return it 
			return table[index];
		}

		// deconstructor
		~hash_table() { }

		// table size must be prime number 
		unsigned int isPrimeNumber(unsigned int num) {
			// in case number prime return directlly 
			if (num % 2 != 0) return num;
			
			// else loop until we get prime number 
			for ( ; ; num += 1 ) {
				if (num % 2 != 0) return num;
			}

		}

		// simple function print values in console only work in that simple hash table
		void print() {
			std::cout << " HASH-TABLE :\t\t\n";
			std::cout << " ============\t\t\n";

			// loop over all
			for (int i = 0; i < table_size; i += 1) {
				// in case value NULL that mean EMPTY
				if (table[i] < 0) {
					std::cout << "| " << i << "\t\t <EMPTY> \n";
				}
				else std::cout << "| " << i << "\t\t   " << table[i] << "\n";
			}
			
			std::cout << " ============\t\t\n";

		}

		unsigned int size() {
			return table_size;
		}

		unsigned int length() {
			return len;
		}
};


}