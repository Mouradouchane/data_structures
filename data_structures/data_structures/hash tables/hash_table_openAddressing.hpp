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

	// LP = Linear Probing 
template<typename k , typename v>class LP_hash_table : public hash_table<k,v> {

private : 

public : 
	LP_hash_table(unsigned int hash_table_size = 3 , v emptyToken = NULL) : hash_table<k,v>(hash_table_size , emptyToken) {

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