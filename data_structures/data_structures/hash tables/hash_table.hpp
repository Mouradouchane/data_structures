#include <iostream>
#include <vector>
#include "key_value_linkedlist.hpp"
#pragma once

/*
	that module contain a simple & stupid hash_table with basics function like => get , set , clear ...
	we using that hash_table later in different good & better hash_tables like => open-addressing , chaining ...
*/

// === hash table ~ methods ===========
/*
   -- NAME ----------- BEST  --> WORST
	
	hash			=> o(n)

	clear			=> o(n)  
	elements		=> o(n)	 

	set				=> o(n) // note !! o(n) for hash function
	get				=> o(n) // note !! o(n) for hash function
	getPair			=> o(n) // note !! o(n) for hash function

	remove			=> o(n) // note !! o(n) for hash function
	replace			=> o(n) // note !! o(n) for hash function

	isEmpty			=> o(1)
	isFull			=> o(1)

	values			=> o(n)	 

	print			=> o(n)

	length			=> o(1)
	size			=> o(1)
*/

using namespace key_value_linkedlist;

namespace hash_tables {

// simple hash table => "" replacemenet hash table "" there's no keys only values
template<typename k, typename v> class hash_table {
	protected :
		unsigned int table_size = 0;
		unsigned int len = 0;
		const unsigned int min_size = 3;

		v emptyToken = NULL;

		// hash table or array key value nodes
		kv_node<k,v>* table = NULL;

		// o(n)
		// simple hash function all what to do is => key_size % table_size
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

		// table size must be prime number 
		unsigned int isPrimeNumber(unsigned int num) {
			// in case number prime return directlly 
			if (num % 2 != 0) return num;

			// else loop until we get prime number 
			for (; ; num += 1) {
				if (num % 2 != 0) return num;
			}

		}


	public:
		// constructor 
		hash_table(unsigned int hash_table_size = min_size , v empty_token = NULL){

			// check if table_size is bigger than min size allowed "3"
			table_size = (hash_table_size < min_size) ? min_size : hash_table_size;

			// chech if "table size" is prime  
			// if not we round it to be prime :)
			table_size = isPrimeNumber(table_size);

			// define hash table with valid size in construction time
			table = new kv_node<k,v>[table_size];

			// set empty_token
			emptyToken = empty_token;

			// loop over all empty nodes & fill it by "empty token"
			for (unsigned int i = 0; i <= hash_table_size; i += 1) {
				table[i].value = emptyToken;
			}
			
		}

		// deconstructor
		~hash_table() { }

		// set data by value to hash table
		void set(k key , v value) {

			// hash key & get index
			int index = hash(key);

			// check if that index empty or not , only for updating lenght
			if (table[index].value == emptyToken) {
				len += 1;
			}

			// otherwise in case is empty or not 
			// put data in target index "replacement concept " 
			table[index] = kv_node<k,v>(key,value);
		}

		// o(n)
		// replace old value with new one & return bool as confirmation
		bool replace(k target_key, v new_value) {
			// hash & get index
			int index = hash(target_key);

			// check if same target or not
			if (table[index].key == target_key) {
				// in case right do replacement
				table[index].value = new_value;

				// and return true as confirmation
				return true;
			}
			// in case target not found or "replaced | deleted"
			else return false;
		}

		// get data by value from hash table
		v get(k target_key) {
			// hash & get index
			int index = hash(target_key);

			// check if "target key" is still in table or "deleted | replaced"
			if (table[index].key == target_key) return table[index].value;

			// in case key != key that mean target "deleted | replaced"
			return NULL;
		}

		// o(n)
		// get a key value pair if it found 
		std::pair<k,v> getPair(k target_key){
			// hash & get index
			int index = hash(target_key);

			// check if "target key" is still in table or "deleted | replaced"
			if (table[index].key == target_key) {
				// in case still in table return will be a <key , value> pair 
				return std::pair<k, v>(table[index].key, table[index].value);
			}
			// else return will be a empty pair
			else return std::pair<k, v>();
		}

		// o(n)
		// remove element from table
		bool remove(k target_key) {

			// hash & get target index
			int index = hash(target_key);

			// check if target is still in table or not 
			if (table[index].key == target_key) {
				// just override old node by new one with emptyToken
				table[index] = kv_node<k, v>();
				table[index].value = emptyToken;

				// update length
				len -= 1;

				// confirmation of remove operation
				return true;
			}
			// otherwise that mean target not found
			else return false;
			
		}
	
		// o(n)
		// simple function print values in console only work in that simple hash table
		void print() {
			std::cout << " ==================================\n";
			std::cout << "|| HASH-TABLE :                   ||\n";
			std::cout << " ==================================\n";

			// loop over all
			for (int i = 0; i < table_size; i += 1) {
				// in case value NULL that mean EMPTY
				if (table[i].value == emptyToken) {
					std::cout << "| " << i << "\t\t [EMPTY] \n";
				}
				else std::cout << "| " << i << "\t\t [" << table[i].key << " | " << table[i].value << "] \n";
			}
			
			std::cout << "====================================\n";
			std::cout << "table length \t" << length() << '\n';
			std::cout << "table size \t" << size() << '\n';
			std::cout << "is empty \t" << isEmpty() << '\n';
			std::cout << "is full \t" << isFull() << '\n';
			std::cout << "====================================\n";

		}

		// o(1)
		// check if table is empty
		bool isEmpty() {
			return (len <= 0) ? true : false;
		}

		// o(1)
		// check if table is full
		bool isFull() {
			return (len >= table_size) ? true : false;
		}

		// o(n)
		// delete all elements in hash table
		void clear() {

			delete[] table;

			// make new one
			table = new kv_node<k, v>[table_size];

			// loop over all empty nodes & fill it by "empty token"
			for (unsigned int i = 0; i <= table_size; i += 1) {
				table[i].value = emptyToken;
			}

			// reset lenght 
			len = 0;

		}


		// o(n)
		// return vector of values 
		std::vector<v> values() {

			// new vector
			std::vector<v> vals;

			// fill vector
			for (int i = 0; i < table_size; i += 1) {
				if (table[i].value != emptyToken) vals.push_back(table[i].value);	
			}

			// return vector
			return vals;
		}


		// o(n)
		// looks like values but this return vector with nodes <key,value> pair
		std::vector<kv_node<k, v>> elements() {

			std::vector<kv_node<k, v>> nodes;

			for (int i = 0; i < table_size; i += 1) {
				if (table[i].value != emptyToken) nodes.push_back(table[i]);
			}

			return nodes;
		}

		// o(1)
		// get size of that hash table
		unsigned int size() {
			return table_size;
		}

		// o(1)
		// get length of elements in that hash table
		unsigned int length() {
			return len;
		}
};


}