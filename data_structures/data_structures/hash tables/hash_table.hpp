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
template<typename k, typename v> class hash_table {
	private:
		unsigned int table_size = 0;
		unsigned int len = 0;
		const unsigned int min_size = 3;
		std::pair<k,v>* table = NULL;

		// simple hash function all what to do is => key % table_size
		int hash(k key) {

			// hash trick
			int key_size = 0;
			for (int i = 0; i < key.size(); i += 1) {
				key_size += (int)key[i];
			}

			// hashing key & getting index 
			int hash_index = key_size % table_size;

			// return hash_index
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
			table = new std::pair<k,v>[table_size];

			
			// fill hash table by null's
			for (unsigned int i = 0; i <= hash_table_size; i += 1) {
				table[i] = std::pair<k,v>();
			}
			
		}

		// set data by value to hash table
		void set(k key , v value) {

			// hash key & get index
			int index = hash(key);

			// check if that index empty or not , only for updating lenght
			if (table[index].second == NULL) {
				len += 1;
			}

			// otherwise in case is empty or not 
			// put data in target index "replacement concept " 
			table[index] = std::pair<k,v>(key,value);
		}

		// get data by value from hash table
		v get(k key) {
			// hash & get index
			int index = hash(key);

			// check if data is equal to parameter value
			if (table[index].first == key) return table[index].second;

			// get data in that index & return it 
			return NULL;
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
			std::cout << " ==================================\n";

			// loop over all
			for (int i = 0; i < table_size; i += 1) {
				// in case value NULL that mean EMPTY
				if (table[i].second == NULL) {
					std::cout << "| " << i << "\t\t <EMPTY> \n";
				}
				else std::cout << "| " << i << "\t\t [" << table[i].first << " | " << table[i].second << "] \n";
			}
			
			std::cout << " ==================================\n";

		}

		unsigned int size() {
			return table_size;
		}

		unsigned int length() {
			return len;
		}
};


}