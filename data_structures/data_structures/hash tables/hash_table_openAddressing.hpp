#include <iostream>
#include "hash_table.hpp"
#pragma once

/*
	this file contain 3 "hash tables" all using "open addressing" technique in hash
	- Linear Probing
	- Quadratic Probing
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
template<typename k , typename v>class LP_hash_table : public hash_table<k,v> {


public : 
	// constructor 
	LP_hash_table(unsigned int hash_table_size = 3 , v emptyToken = NULL) : hash_table<k,v>(hash_table_size , emptyToken) {

	}
	// destructor
	~LP_hash_table() { }

	// o(h+1) --> o(h+n)
	// set data by "key , value" to hash table
	// return will be a boolean as confirmation of that  operation "set success or not" :)
	bool set(k key, v value) {

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
		if (this->table[index].value == this->emptyToken) {
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
				if (this->table[i].value == this->emptyToken) {
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
			this->table[index] = kv_node<k, v>(key, value);
			return success;
		}
		// otherwise false 
		else return false;
	}

	// o(h+1) --> o(h+n)
	// get value from hash table using key
	v get(k target_key) {

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
	std::pair<k, v> getPair(k target_key) {

		// in case table empty
		if (this->isEmpty()) return std::pair<k, v>();

		// hash & get index
		int index = this->hash(target_key);

		// check if "target" found
		if (this->table[index].key == target_key) {
			// return will be a <key , value> pair 
			return std::pair<k, v>(this->table[index].key, this->table[index].value);
		}
		// otherwise loop over all from index to the of table
		else{

			for (int i = index + 1; i < this->table_size; i += 1) {

				if (this->table[i].key == target_key) {
					// return will be a <key , value> pair 
					return std::pair<k, v>(this->table[i].key, this->table[i].value);
				}

			}

		}

		// in case target not found return will be an empty pair
		return std::pair<k, v>();
	}

	// o(h+1) --> o(h+n)
	// remove element from table
	bool remove(k target_key) {

		// check if table is  empty  
		if (this->isEmpty()) return false;

		// hash & get target index
		int index = this->hash(target_key);

		// check if target is still in table or not 
		if (this->table[index].key == target_key) {
			// just override old node by new one with emptyToken
			this->table[index] = kv_node<k, v>();
			this->table[index].value = this->emptyToken;

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
					this->table[i] = kv_node<k, v>();
					this->table[i].value = this->emptyToken;

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
	bool replace(k key, v value) {

		// check if table is empty  
		if (this->isEmpty()) return false;

		// hash key & get index
		int index = this->hash(key);

		// in case that key is found in first try
		if (this->table[index].key == key) {

			// replace old value by new one
			this->table[index].value = value;

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
					this->table[i].value = value;

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
		std::cout << "|| LP HASH-TABLE :                   ||\n";
		std::cout << " =====================================\n";

		// loop over all
		for (int i = 0; i < this->table_size; i += 1) {
			// in case value NULL that mean EMPTY
			if (this->table[i].value == this->emptyToken) {
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



	// QP = Quadratic Probing
	// inherit from Linear Probing 
	// but using different technique of hashing
template<typename k, typename v> class QP_hash_table : public LP_hash_table<k, v> {

protected : 

public : 	
	// constructor 
	QP_hash_table(unsigned int hash_table_size = 3, v emptyToken = NULL) : LP_hash_table<k, v>(hash_table_size, emptyToken) {

	}
	// destructor
	~QP_hash_table() { }


	// o(h+1) --> o(h+n)
	// set data by "key , value" to hash table "using quadratic hashing"
	// return will be a boolean as confirmation of that  operation "set success or not" :)
	bool set(k key, v value) {

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
		if (this->table[index].value == this->emptyToken) {
			success = true;
			this->len += 1;
		}
		// in case not empty !
		else {
			 

			// "quadratic probing" concept 
			// looking for empty place :)
			for (int i = index+1; i < this->table_size; i += 2) {

				// check if i is out of table size
				if (i > this->table_size) i = (i % this->table_size);

				// again inside loop check if that key is already in table or not , for avoiding problems
				if (this->table[i].key == key) return false;

				// in case empty place founded 
				if (this->table[i].value == this->emptyToken) {
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
			this->table[index] = kv_node<k, v>(key, value);
			return success;
		}
		// otherwise false 
		else return false;
	}

	// o(h+1) --> o(h+n)
	// get value from hash table using key
	v get(k target_key) {

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
	std::pair<k, v> getPair(k target_key) {

		// in case table empty
		if (this->isEmpty()) return std::pair<k, v>();

		// hash & get index
		int index = this->hash(target_key);

		// check if "target" found
		if (this->table[index].key == target_key) {
			// return will be a <key , value> pair 
			return std::pair<k, v>(this->table[index].key, this->table[index].value);
		}
		// otherwise loop over all from index to the of table
		else {

			for (int i = index + 1; i < this->table_size; i += 2) {

				if (this->table[i].key == target_key) {
					// return will be a <key , value> pair 
					return std::pair<k, v>(this->table[i].key, this->table[i].value);
				}

			}

		}

		// in case target not found return will be an empty pair
		return std::pair<k, v>();
	}

	// o(h+1) --> o(h+n)
	// remove element from table
	bool remove(k target_key) {

		// check if table is  empty  
		if (this->isEmpty()) return false;

		// hash & get target index
		int index = this->hash(target_key);

		// check if target is still in table or not 
		if (this->table[index].key == target_key) {
			// just override old node by new one with emptyToken
			this->table[index] = kv_node<k, v>();
			this->table[index].value = this->emptyToken;

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
					this->table[i] = kv_node<k, v>();
					this->table[i].value = this->emptyToken;

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

};



}