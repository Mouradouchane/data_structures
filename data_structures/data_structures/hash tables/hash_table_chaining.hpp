#include <iostream>
#include <vector>
#include <string>
#include "key_value_linkedlist.hpp"

#pragma once

/*
	that module contain a hash_table with chaining concept
	C_hash_table not based on "basic hash_table in hash_table.hpp"
*/


// === hash table ~ methods ===========
/*
   -- NAME ----------- BEST  --> WORST

	hash			=> o(1)
	
	clear			=> o(n)
	elements		=> o(n)

	set				=> o(1)  --> o(n) 
	get				=> o(1)  --> o(n) 
	getPair			=> o(1)  --> o(n) 

	remove			=> o(1)  --> o(n) 
	replace			=> o(1)  --> o(n) 

	values			=> o(n)

	print			=> o(n) --> o(> n²)

	isEmpty			=> o(1)
	length			=> o(1)
	size			=> o(1)
*/

using namespace key_value_linkedlist;

namespace hash_tables {

template<typename v> class C_hash_table{
	
	protected :

		unsigned int min_size = 3;
		unsigned int table_size = min_size;
		unsigned int len = 0;

		// hash table of linked lists
		// key = strings , values = anything
		key_value_linked_list<std::string, v>* table = NULL;

		// o(1)
		// simple hasing trick
		int hash(std::string key) {
			int fint = key[0];
			int lint = key[key.size()-1];

			return ( (key.size() * fint * lint) % table_size );
		}

		// function check if table size is prime or not
		// in case not prime we ceil it to close one
		unsigned int isPrimeNumber(unsigned int num) {
			// in case number prime return directlly 
			if (num % 2 != 0) return num;

			// else loop until we get prime number 
			for (; ; num += 1) {
				if (num % 2 != 0) return num;
			}

		}

	public : 

		// constructor
		C_hash_table(unsigned int hash_table_size = 3){

			// check if table_size is bigger than min size allowed "3"
			table_size = (hash_table_size < min_size) ? min_size : hash_table_size;

			// chech if "table size" is prime  
			// if not we round it to be prime :)
			table_size = isPrimeNumber(table_size);

			// define hash table with valid size in construction time
			table = new key_value_linked_list<std::string, v>[table_size];

		}

		// destructor
		~C_hash_table(){}

		// o(1)	--> o(n)
		// set data by key , value to hash table
		// return bool as confirmation of that operation
		bool set(std::string key, v value) {

			// hash key & get index
			int index = hash(key);

			// push new node in that linked list 
			if (table[index].push_back(key, value)) {
				
				// in case push happend correctly update length
				len += 1;

				// confirm of that operation
				return true;
			}

			// in case value not added 'that mean it's already in that linked list
			return false;
		}


		// o(1) --> o(n)
		// get target value using key
		v get(std::string target_key) {

			// in case hash table empty
			if (isEmpty()) return NULL;

			// hashing key & get 'linked list' index
			int index = hash(target_key);

			// get value in that linked list is it exist 
			return table[index].get(target_key);
		}
		

		// o(1) --> o(n)
		// like get but pair with <key,value> :)
		std::pair<std::string, v> getPair(std::string target_key) {

			// in case hash table empty
			if (isEmpty()) return std::pair<std::string,v>();

			// hashing key & get 'linked list' index
			int index = hash(target_key);

			// get value in that linked list is it exist 
			return table[index].getPair(target_key);

		}

		// o(1) --> o(n) 
		// remove <key,value> from specific linked list in table
		bool remove(std::string target_key) {

			// hash & get index
			int index = hash(target_key);

			// remove target from linked list & return confirmation of that operation
			if (table[index].remove(target_key)) {
				len -= 1;
				return true;
			}
			else return false;
		}

		// o(1) --> o(n) 
		// replca <value> by 'new one' in specific linked list in table
		bool replace(std::string target_key , v new_value){

			// hash & get index
			int index = hash(target_key);

			// replace & return confirmation of that operation
			return table[index].replace(target_key , new_value);
		}

		// o(n) --> o(> n²)
		// print all linked lists with nodes
		void print() {
			std::cout << " =====================================\n";
			std::cout << "|| CHAINING HASH - TABLE :           ||\n";
			std::cout << " =====================================\n";

			for (int i = 0; i < table_size; i += 1) {
				if (table[i].isEmpty()) {
					std::cout << "| " << i << "\t\t [EMPTY] \n";
				}
				else {
					std::cout << "| " << i << "\t\t ";
					table[i].print();
				}
			}

			std::cout << "=====================================\n";
			std::cout << "table length \t" << length() << '\n';
			std::cout << "table size \t" << size() << '\n';
			std::cout << "is empty \t" << isEmpty() << '\n';
			std::cout << "=====================================\n";
		}

		// o(1)
		int length() {
			return len;
		}

		// o(1)
		int size() {
			return table_size;
		}

		// o(1)
		bool isEmpty() {
			return (len > 0) ? false : true;
		}

};


}
