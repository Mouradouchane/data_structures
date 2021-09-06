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

protected : 

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

		// check if table is full or not 
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
				if (this->table[index].key == key) return false;

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

}