#include <vector>

#pragma once

// === doubly linke list ~ methods ===
/*
    length          => o(1)
    push_back       => o(1)
    push_front      => o(1)
    push_at         => o(n)

    replace         => o(n)
    has             => o(n)

    remove          => o(n)
    remove_first    => o(1)
    remove_last     => o(n)

    getFistElement  => o(1)
    getFistValue    => o(1)

    getLastElement  => o(1)
    getLastValue    => o(1)

    toVector        => o(n)
    toArray         => o(n)

    clear           => o(n)
    showAll         => o(n)
*/

namespace doubly_linkedlist {

    // special node for doubly linked list wich ca take previous and next
	template<typename t>class d_node {
	public :
            // like singly but have previous 
			d_node<t>* prev = NULL;
			t value;
			d_node<t>* next = NULL;

            d_node(){}
            d_node(t Value):value(Value) {}

            ~d_node(){}
	};



    // doubly linked list inherit from singly public functions for dealing with stuff
    template<typename t> class doubly_LinkeList {
        
        private:
            int len = 0; // len => length
            d_node<t>* first = NULL; // head
            d_node<t>* last  = NULL; // tail

        public : 

            // o(1)
            // push_back new value direct 
            void push_back(t value) {
                len += 1; // increment length of linked list

                // new doubly node with value
                d_node<t>* newNode = new d_node<t>(value);

                // in case linked list is empty
                if (first == NULL && last == NULL) {
                    // soo simple :) 
                    first = newNode;
                    last = newNode;
                    return;
                }
                else {
                    // else that mean linked list not empty 
                    newNode->prev = last;
                    last->next = newNode;
                    last = newNode;
                }
            };

            // o(1)
            // push new value direct from the front of linked list (or you can say 'new head')
            void push_front(t value) {
                len += 1; // increment length of linked list

                // new doubly node with value
                d_node<t>* newNode = new d_node<t>(value);

                // in case linked list is empty
                if (first == NULL && last == NULL) {
                    // soo simple :) 
                    first = newNode;
                    last  = newNode;
                    return;
                }
                else { 
                    // else that mean linked list not empty 
                    newNode->next = first;
                    first->prev = newNode;
                    first = newNode;
                }
            }

            void reverse() {

                d_node<t>* newF = new d_node<t>(last->value);
                d_node<t>* newL = new d_node<t>(first->value);

                d_node<t>* temp = last->prev;
                d_node<t>* newNode = NULL;

                while (temp != NULL) {
                    newNode = new d_node<t>(temp->value);
                    newF->next = newNode;
                    temp = temp->prev;
                }

                first = newF;
            }

            // o(1)
            // return length of linked size :) 
            int length() {
                return len;
            }

            // just "test function" who print all values in console
            void showAll() {
                d_node<t>* tempNode = first;

                std::cout << "==================================================" << std::endl;
                while (tempNode != NULL) {
                    std::cout << tempNode->value << std::endl;
                    tempNode = tempNode->next;
                }
                std::cout << "==================================================" << std::endl;
            }
    };

}