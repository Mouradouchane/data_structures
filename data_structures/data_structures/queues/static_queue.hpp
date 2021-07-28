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
	isFull		=> o(1)
	print		=> o(n)
	length		=> o(1)
*/


namespace queue {

// fixed size queue
template<typename t> class static_queue{
	private:
		// queue size 
		unsigned int size = 0;

		// queue as singly linked list
		linkedlist::singly_LinkedList<t> queue;

	public : 
		// construction with fixed size ;)
		static_queue(unsigned int queue_size):size(queue_size) {

		}
		~static_queue(){}


		// o(1)
		// add/push new elements to queue & "return true/false as confirmation of that operation"
		bool push(t new_value) {

			// in case queue is full no add & return false
			if (queue.length() >= size) return false;
			else {
				// else we can add new element
				queue.push_back(new_value);
				return true;
			}

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
		t front(bool remove_it = false){
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

		// o(1)
		// check if queue is full
		bool isFull() {
			return (queue.length() >= size) ? true : false;
		}

		// o(n)
		// search of target value in queue
		bool search(t target_value) {
			return queue.search(target_value);
		}

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