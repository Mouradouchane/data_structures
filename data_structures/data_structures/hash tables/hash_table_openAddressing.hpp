#include <iostream>
#include <string>
#include "hash_table.hpp"
#pragma once

/*
	this file contain 3 "hash tables" all using "open addressing" technique in hash
	- Linear Probing
	- like Quadratic Probing
	- Double Hashing
*/

using namespace key_value_linkedlist;

namespace hash_tables {

// === Linear Probing ~ methods ===========
/*
	-- NAME ----------- BEST  --> WORST

	hash			=> o(h)

	clear			=> o(n)
	elements		=> o(n)

	set				=> o(h + 1) --> o(h + n) ( note !! o(h) for hash time + extra one step or few setps "n" )
	get				=> o(h + 1) --> o(h + n) ( note !! o(h) for hash time + extra one step or few setps "n" )
	getPair			=> o(h + 1) --> o(h + n) ( note !! o(h) for hash time + extra one step or few setps "n" )

	remove			=> o(h + 1) --> o(h + n) ( note !! o(h) for hash time + extra one step or few setps "n" )
	replace			=> o(h + 1) --> o(h + n) ( note !! o(h) for hash time + extra one step or few setps "n" )

	isEmpty			=> o(1)
	isFull			=> o(1)

	values			=> o(n)

	print			=> o(n)

	length			=> o(1)
	size			=> o(1)
*/

	// LP = Linear Probing 
	// inherit from base hash_table
template<typename v> class LP_hash_table : public hash_table<v> {

public : 
	// constructor 
	LP_hash_table(unsigned int hash_table_size = 3) : hash_table<v>(hash_table_size) {

	}
	// destructor
	~LP_hash_table() { }

	// o(h+1) --> o(h+n)
	// set data by "key , value" to hash table
	// return will be a boolean as confirmation of that  operation "set success or not" :)
	bool set(std::string key, v value) {

		// check if table is full or empty  
		if (this->isFull()) return false;

		// hash key & get index
		int index = this->hash(key);
		// confrimation
		bool success = false;

		// in case that key is already in table , return will be false directlly 
		// avoiding multi-keys problem 
		if (this->table[index].key == key) return false;

		// as first step , check if that hashed index empty or not 
		if (this->table[index].key == this->emptyToken) {
			success = true;
			this->len += 1;
		}
		// in case not empty !
		else {

			// "linear probing" concept 
			// looking for empty place :)
			for (int i = index+1; i < this->table_size; i += 1) {

				// again inside loop check if that key is already in table or not , for avoiding problems
				if (this->table[i].key == key) return false;

				// in case empty place founded 
				if (this->table[i].key == this->emptyToken) {
					success = true;
					this->len += 1;

					// set index to that new empty inedx "i"
					index = i;
					break;
				}

			}

		}

		// in case empty place found 
		if (success) {
			// operation will be successfully & return will be true 
			this->table[index] = kv_node<std::string , v>(key, value);
			return success;
		}
		// otherwise false 
		else return false;
	}

	// o(h+1) --> o(h+n)
	// get value from hash table using key
	v get(std::string target_key) {

		// hash & get index 
		int index = this->hash(target_key);

		// in case "target" in first place o(1)
		if (this->table[index].key == target_key) return this->table[index].value;
		// otherwise we need to loop unti the end of table
		else {

			for (int i = index+1; i < this->table_size; i += 1) {
				// in case target found 
				if (this->table[i].key == target_key) {
					return this->table[i].value;
				}
			}

		}
		// in case not found return must be null
		return NULL;
	}

	// o(h+1) --> o(h+n)
	// get a key value pair if it found 
	std::pair<std::string , v> getPair(std::string target_key) {

		// in case table empty
		if (this->isEmpty()) return std::pair<std::string, v>();

		// hash & get index
		int index = this->hash(target_key);

		// check if "target" found
		if (this->table[index].key == target_key) {
			// return will be a <key , value> pair 
			return std::pair<std::string, v>(this->table[index].key, this->table[index].value);
		}
		// otherwise loop over all from index to the of table
		else{

			for (int i = index + 1; i < this->table_size; i += 1) {

				if (this->table[i].key == target_key) {
					// return will be a <key , value> pair 
					return std::pair<std::string, v>(this->table[i].key, this->table[i].value);
				}

			}

		}

		// in case target not found return will be an empty pair
		return std::pair<std::string, v>();
	}

	// o(h+1) --> o(h+n)
	// remove element from table
	bool remove(std::string target_key) {

		// check if table is  empty  
		if (this->isEmpty()) return false;

		// hash & get target index
		int index = this->hash(target_key);

		// check if target is still in table or not 
		if (this->table[index].key == target_key) {
			// just override old node by new one with emptyToken
			this->table[index] = kv_node<std::string , v>();
			this->table[index].key = this->emptyToken;

			// update length
			this->len -= 1;

			// confirmation of remove operation
			return true;
		}
		// otherwise that mean we need to loop over all from index to the end of table
		else {

			for (int i = index + 1; i < this->table_size; i += 1) {
				// in case target found 
				if (this->table[i].key == target_key) {

					// just override old node by new one with emptyToken
					this->table[i] = kv_node<std::string , v>();
					this->table[i].key = this->emptyToken;

					// update length
					this->len -= 1;

					// confirmation of remove operation
					return true;
				}
			}

		}
			
		// in case not found 
		return false;
	}

	// o(h+1) --> o(h+n)
	// replace old value by new one it if found 
	bool replace(std::string key, v new_value) {

		// check if table is empty  
		if (this->isEmpty()) return false;

		// hash key & get index
		int index = this->hash(key);

		// in case that key is found in first try
		if (this->table[index].key == key) {

			// replace old value by new one
			this->table[index].value = new_value;

			// true as confrimation
			return true;
		}
		// in case not found !
		else {

			// loop over all form index to the end of table
			for (int i = index + 1; i < this->table_size; i += 1) {

				// in case key found
				if (this->table[i].key == key) {

					// replace old value by new one
					this->table[i].value = new_value;

					// true as confrimation
					return true;
				}

			}

		}

		// in case not found
		return false;
	}

	// o(n)
	void print() {
		std::cout << " =====================================\n";
		std::cout << "|| LP HASH-TABLE :                   ||\n";
		std::cout << " =====================================\n";

		// loop over all
		for (int i = 0; i < this->table_size; i += 1) {
			// in case value NULL that mean EMPTY
			if (this->table[i].key == this->emptyToken) {
				std::cout << "| " << i << "\t\t [EMPTY] \n";
			}
			else std::cout << "| " << i << "\t\t [" << this->table[i].key << " | " << this->table[i].value << "] \n";
		}

		std::cout << "======================================\n";
		std::cout << "table length \t" << this->length() << '\n';
		std::cout << "table size \t" << this->size() << '\n';
		std::cout << "is empty \t" << this->isEmpty() << '\n';
		std::cout << "is full \t" << this->isFull() << '\n';
		std::cout << "======================================\n";
	}
	
};



	// QP = like Quadratic Probing
	// inherit from Linear Probing 
	// but using different technique of hashing
template<typename v> class QP_hash_table : public LP_hash_table<v> {

public : 	
	// constructor 
	QP_hash_table(unsigned int hash_table_size = 3) : LP_hash_table<v>(hash_table_size) {

	}
	// destructor
	~QP_hash_table() { }


	// o(h+1) --> o(h+n)
	// set data by "key , value" to hash table "using like quadratic hashing"
	// return will be a boolean as confirmation of that  operation "set success or not" :)
	bool set(std::string key, v value) {

		// check if table is full or empty  
		if (this->isFull()) return false;

		// hash key & get index
		int index = this->hash(key);
		// confrimation
		bool success = false;

		// in case that key is already in table , return will be false directlly 
		// avoiding multi-keys problem 
		if (this->table[index].key == key) return false;

		// as first step , check if that hashed index empty or not 
		if (this->table[index].key == this->emptyToken) {
			success = true;
			this->len += 1;
		}
		// in case not empty !
		else {
			 
			// "like quadratic probing" concept but only going by +=2 in each step
			// looking for empty place :)
			for (int i = index+1; i < this->table_size; i += 2) {

				// check if i is out of table size
				if (i > this->table_size) i = (i % this->table_size);

				// again inside loop check if that key is already in table or not , for avoiding problems
				if (this->table[i].key == key) return false;

				// in case empty place founded 
				if (this->table[i].key == this->emptyToken) {
					success = true;
					this->len += 1;

					// set index to that new empty inedx "i"
					index = i;
					break;
				}

			}

		}

		// in case empty place found 
		if (success) {
			// operation will be successfully & return will be true 
			this->table[index] = kv_node<std::string , v>(key, value);
			return success;
		}
		// otherwise false 
		else return false;
	}

	// o(h+1) --> o(h+n)
	// get value from hash table using key
	v get(std::string  target_key) {

		// hash & get index 
		int index = this->hash(target_key);

		// in case "target" in first place o(1)
		if (this->table[index].key == target_key) return this->table[index].value;
		// otherwise we need to loop unti the end of table
		else {

			for (int i = index + 1; i < this->table_size; i += 2) {
				// in case target found 
				if (this->table[i].key == target_key) {
					return this->table[i].value;
				}
			}

		}
		// in case not found return must be null
		return NULL;
	}

	// o(h+1) --> o(h+n)
	// get a key value pair if it found 
	std::pair<std::string , v> getPair(std::string target_key) {

		// in case table empty
		if (this->isEmpty()) return std::pair<std::string , v>();

		// hash & get index
		int index = this->hash(target_key);

		// check if "target" found
		if (this->table[index].key == target_key) {
			// return will be a <key , value> pair 
			return std::pair<std::string , v>(this->table[index].key, this->table[index].value);
		}
		// otherwise loop over all from index to the of table
		else {

			for (int i = index + 1; i < this->table_size; i += 2) {

				if (this->table[i].key == target_key){
					// return will be a <key , value> pair 
					return std::pair<std::string , v>(this->table[i].key, this->table[i].value);
				}

			}

		}

		// in case target not found return will be an empty pair
		return std::pair<std::string , v>();
	}

	// o(h+1) --> o(h+n)
	// remove element from table
	bool remove(std::string target_key) {

		// check if table is  empty  
		if (this->isEmpty()) return false;

		// hash & get target index
		int index = this->hash(target_key);

		// check if target is still in table or not 
		if (this->table[index].key == target_key) {
			// just override old node by new one with emptyToken
			this->table[index] = kv_node<std::string , v>();
			this->table[index].key = this->emptyToken;

			// update length
			this->len -= 1;

			// confirmation of remove operation
			return true;
		}
		// otherwise that mean we need to loop over all from index to the end of table
		else {

			for (int i = index + 1; i < this->table_size; i += 2) {
				// in case target found 
				if (this->table[i].key == target_key) {

					// just override old node by new one with emptyToken
					this->table[i] = kv_node<std::string , v>();
					this->table[i].key = this->emptyToken;

					// update length
					this->len -= 1;

					// confirmation of remove operation
					return true;
				}
			}

		}

		// in case not found 
		return false;
	}


	// o(h+1) --> o(h+n)
	// replace old value by new one it if found 
	bool replace(std::string key, v new_value) {

		// check if table is empty  
		if (this->isEmpty()) return false;

		// hash key & get index
		int index = this->hash(key);

		// in case that key is found in first try
		if (this->table[index].key == key) {

			// replace old value by new one
			this->table[index].value = new_value;

			// true as confrimation
			return true;
		}
		// in case not found !
		else {

			// loop over all form index to the end of table
			for (int i = index + 1; i < this->table_size; i += 2) {

				// in case key found
				if (this->table[i].key == key) {

					// replace old value by new one
					this->table[i].value = new_value;

					// true as confrimation
					return true;
				}

			}

		}

		// in case not found
		return false;
	}

	// o(n)
	// simple function print values in console only work in that simple hash table
	void print() {
		std::cout << " =====================================\n";
		std::cout << "|| QP HASH-TABLE :                   ||\n";
		std::cout << " =====================================\n";

		// loop over all
		for (int i = 0; i < this->table_size; i += 1) {
			// in case value NULL that mean EMPTY
			if (this->table[i].key == this->emptyToken) {
				std::cout << "| " << i << "\t\t [EMPTY] \n";
			}
			else std::cout << "| " << i << "\t\t [" << this->table[i].key << " | " << this->table[i].value << "] \n";
		}

		std::cout << "======================================\n";
		std::cout << "table length \t" << this->length() << '\n';
		std::cout << "table size \t" << this->size() << '\n';
		std::cout << "is empty \t" << this->isEmpty() << '\n';
		std::cout << "is full \t" << this->isFull() << '\n';
		std::cout << "======================================\n";
	}
	
};


	// DP = Double Hashing 
	// inherit from Linear Probing 
template<typename v> class DP_hash_table : public LP_hash_table<v> {

	protected :
		// o(1)
		// 2nd hash function
		int hash2(std::string key) {
			return this->table_size - (key.size() % this->table_size);
		}

	public :
		// constructor
		DP_hash_table(unsigned int hash_table_size = 3) : LP_hash_table<v>(hash_table_size) {}

		// destructor
		~DP_hash_table() {}


		// o(h1+2) --> o(h1+1+n)
		// set data by "key , value" to hash table
		// return will be a boolean as confirmation of that  operation "set success or not" :)
		bool set(std::string key, v value) {

			// check if table is full or empty  
			if (this->isFull()) return false;

			// 1st hash function & get 1st index
			int index = this->hash(key);

			// dhi = double hashing index
			// where result of 1st & 2nd hasing functions store
			int dhi = index;

			// confrimation
			bool success = false;

			// in case that key is already in table , return will be false directlly 
			// avoiding multi-keys problem 
			if (this->table[dhi].key == key) return false;

			// as first step , check if that hashed index empty or not 
			if (this->table[dhi].key == this->emptyToken) {
				success = true;
				this->len += 1;
			}
			// in case not empty !
			else {

				// "double hasing" concept 
				 
				// 2nd hash function & get 2nd index
				// o(1)
				int index_2 = hash2(key);

				// looking for empty place :)
				for (int i = 1; i < this->table_size; i += 1) {

					// double hashing trick
					dhi = (index + i * index_2) % this->table_size;

					// again inside loop check if that key is already in table or not , for avoiding problems
					if (this->table[dhi].key == key) return false;

					// in case empty place founded 
					if (this->table[dhi].key == this->emptyToken) {
						success = true;
						this->len += 1;

						// set index to that new empty inedx "i"
						break;
					}

				}

			}

			// in case empty place found 
			if (success) {
				// operation will be successfully & return will be true 
				this->table[dhi] = kv_node<std::string, v>(key, value);
				return success;
			}
			// otherwise false 
			else return false;
		}

		// o(h1+2) --> o(h+1+n)
		// get value from hash table using key
		v get(std::string target_key) {

			// 1st hash function & get 1st index
			int index = this->hash(target_key);

			// in case "target" in first place o(1)
			if (this->table[index].key == target_key) return this->table[index].value;
			// otherwise 
			else {

				// "double hasing" concept 

				// 2nd hash function & get 2nd index
				// o(1)
				int index_2 = hash2(target_key);

				//  dhi = double hashing index
				int dhi = 0;

				for (int i = 1; i < this->table_size; i += 1) {
					
					dhi = (index + i * index_2) % this->table_size;
					
					// in case target found 
					if (this->table[dhi].key == target_key) {
						return this->table[dhi].value;
					}
				}

			}
			// in case not found return must be null
			return NULL;
		}


		// o(h1+2) --> o(h+1+n)
		// get value from hash table using key
		std::pair<std::string,v> getPair(std::string target_key) {

			// 1st hash function & get 1st index
			int index = this->hash(target_key);

			// in case "target" in first place o(1)
			if (this->table[index].key == target_key) {
				return std::pair<std::string, v>(this->table[index].key , this->table[index].value);
			}
			// otherwise 
			else {

				// "double hasing" concept 

				// 2nd hash function & get 2nd index
				// o(1)
				int index_2 = hash2(target_key);

				//  dhi = double hashing index
				int dhi = 0;

				for (int i = 1; i < this->table_size; i += 1) {

					dhi = (index + i * index_2) % this->table_size;

					// in case target found 
					if (this->table[dhi].key == target_key) {
						return std::pair<std::string, v>(this->table[dhi].key, this->table[dhi].value);
					}
				}

			}
			// in case not found return must be null
			return std::pair<std::string,v>();
		}


		// o(n)
		void print() {
			std::cout << " =====================================\n";
			std::cout << "|| DP HASH-TABLE :                   ||\n";
			std::cout << " =====================================\n";

			// loop over all
			for (int i = 0; i < this->table_size; i += 1) {
				// in case value NULL that mean EMPTY
				if (this->table[i].key == this->emptyToken) {
					std::cout << "| " << i << "\t\t [EMPTY] \n";
				}
				else std::cout << "| " << i << "\t\t [" << this->table[i].key << " | " << this->table[i].value << "] \n";
			}

			std::cout << "======================================\n";
			std::cout << "table length \t" << this->length() << '\n';
			std::cout << "table size \t" << this->size() << '\n';
			std::cout << "is empty \t" << this->isEmpty() << '\n';
			std::cout << "is full \t" << this->isFull() << '\n';
			std::cout << "======================================\n";
		}

};


}