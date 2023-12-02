#include <iostream>

// this queue build it on linked list for fast add & delete :)
#include "../linkedlists/singly_LinkedList.hpp"

#pragma once

/*
	=== queue =========
	push		=> o(1)
	pop			=> o(1)
	front		=> o(1)
	rear		=> o(1)
	search		=> o(n)
	isEmpty		=> o(1)
	print		=> o(n)
	length		=> o(1)
*/


namespace queue {

	// dynamic size queue
	template<typename t> class dynamic_queue {
	private:
	
		// queue as singly linked list
		linkedlist::singly_LinkedList<t> queue;

	public:
		// construction ;)
		dynamic_queue(){}
		~dynamic_queue() {}


		// o(1)
		// add/push new elements to queue without confirmation
		void push(t new_value) {

			// push directly
			queue.push_back(new_value);

		}

		// remove/pop first element from queue & "return true/false as confirmation of that operation"
		bool pop() {

			if (queue.length() <= 0) return false;
			else {
				queue.remove_first();
				return true;
			}

		}

		// o(1) 
		// get front 'first element in queue' with boolean as 'delete option'
		t front(bool remove_it = false) {
			t front_value = queue.getFirstValue();
			if (!remove_it) return front_value;
			else {
				queue.remove_first();
				return front_value;
			}
		}

		// o(1)
		// return a copy of 'last element in queue' 
		t rear() {
			return queue.getLastValue();
		}

		// o(1)
		// check if queue is empty
		bool isEmpty() {
			return (queue.length() > 0) ? false : true;
		}

		// o(n)
		// search of target value in queue
		bool search(t target_value) {
			return queue.search(target_value);
		}

		// o(n)
		// print all queue elements in console
		void print() {
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