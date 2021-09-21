#include "hash_table.hpp"

#pragma once

/*
	that module contain a hash_table with chaining concept
	C_hash_table based over basic hash_table in hash_table.hpp
*/


using namespace key_value_linkedlist;

namespace hash_tables {

template<typename v> class C_hash_table : public hash_table<v> {

	public : 

		C_hash_table(unsigned int hash_table_size = 3) : hash_table<v>(hash_table_size) {

		}

		~C_hash_table(){
		
		}

};


}
