#include <iostream>

// this queue build it on linked list for fast add & delete :)
#include "../linkedlists/singly_LinkedList.hpp"

#pragma once

/*
	=== queue ===
	add			=> o(1)
	remove		=> o(1)
	getFront	=> o(1)
	getRear		=> o(1)
	search		=> o(n)
	isEmpty		=> o(1)
	isFull		=> o(1)
	print		=> o(n)
*/


namespace queue {

// fixed size queue
template<typename t> class static_queue{
	private:
		unsigned int size = 0;

		linkedlist::singly_LinkedList<t> queue;

	public : 
		// static_queue fixed size need to defined size of queue in construction time :)
		static_queue(unsigned int queue_size):size(queue_size) {

		}
		~static_queue(){}


		// o(1)
		// add/push new elements to queue & "return true/false as confirmation of that operation"
		bool add(t new_value) {

			// in case queue is full no add & return false
			if (queue.length() >= size) return false;
			else {
				// else we can add new element
				queue.push_back(new_value);
				return true;
			}

		}

		// remove/delete first element from queue & "return true/false as confirmation of that operation"
		bool remove() {

			if (queue.length() <= 0) return false;
			else {
				queue.remove_first();
				return true;
			}

		}

		// o(1) 
		// delete/remove first element in queue 

		// o(n)
		// print all queue elements in console
		void print(){
			std::cout << "==================================================" << std::endl;
			std::cout << "                      QUEUE                       " << std::endl;
			queue.print();
		}

		// o(1)
		// length of queue 'element length' not queue length
		int length() {
			return queue.length();
		}
};


}