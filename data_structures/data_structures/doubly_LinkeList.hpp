#include <vector>

#pragma once

// === doubly linke list ~ methods ===
/*
    length          => o(1)
    push_back       => o(1)
    push_front      => o(1)
    push_at         => o(1) ==> o(n)

    replace         => o(1) ==> o(n)
    has             => o(n)

    remove          => o(1) ==> o(n)
    remove_first    => o(1)
    remove_last     => o(1)

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

            // o(1) ==> o(n)
            // push in specific poition in linked list
            void push_at(t positionValue , t value) {


                // new node with new value
                d_node<t>* newNode = new d_node<t>(value);

                // o(1) : in case target position is the first
                if (first->value == positionValue) {
                    
                    newNode->next = first->next;
                    newNode->prev = first;
                    first->next->prev = newNode;
                    first->next = newNode;

                    // update linked list length
                    len += 1;

                    return;
                }

                d_node<t>* temp = first->next;
                while (temp != last) {
                    if (temp->value == positionValue) {
                        newNode->next = temp->next;
                        newNode->prev = temp;
                        temp->next->prev = newNode;
                        temp->next = newNode;
                        
                        // update linked list length
                        len += 1;

                        return;
                    }
                    temp = temp->next;
                }

                 push_back(value);
            }

            // o(n)
            void reverse() {
                // we start form the last to the first for making 'reverse'
                d_node<t>* oldNode = last;

                // clear first & last for new reversed linked list :)
                first = NULL;
                last  = NULL;
               
                // start form last
                while (oldNode != NULL) {
                    // using push_back it that task
                    // push values 
                    push_back(oldNode->value);
                    // go to previous one
                    oldNode = oldNode->prev;

                    // in case old not equal to null delete it :)
                    if(oldNode != NULL && oldNode->next != NULL) delete oldNode->next;
                }

            }

            // o(1) 
            // remove first node in linked list & make next node new 'first/head'
            // with bool as confirmation of that operation 
            bool remove_first() {

                // in case first equal to null that mean linked list empty
                if (first != NULL) {
                    // next one must be new "first/head" :)
                    d_node<t>* newFirst = first->next;
                    
                    // delete old
                    delete first;

                    // set new one 
                    first = newFirst;
                    first->prev = NULL;

                    // return must be true as confirmation of sucessed operation :)
                    return true;
                }
                
                // else return false that mean nothing happend in linked list 
                return false;
            }

            // o(1)
            // like remove first but here dealing with "last/tail"
            bool remove_last() {

                if (last != NULL) {
                    d_node<t>* newLast = last->prev;
                    delete last;

                    last = newLast;
                    last->next = NULL;

                    return true;
                }

                return false;
            }

            // o(n)
            // clear the hole linked list delete all nodes
            void clear() {
                // loop over all clean one by one 
                d_node<t>* temp = first->next;
                while (temp != NULL) {
                    delete temp->prev;
                    temp = temp->next;
                }

                // set head & tail to null because linked list empty right know :)
                first = NULL;
                last  = NULL;
            }

            bool replace(t oldValue , t NewValue) {
                // o(1) 
                // in case target is the first one
                if (first->value == oldValue) {
                    // put new value & return true as confirmation 
                    first->value = NewValue;
                    return true;
                }
                // o(1) 
                // in case target is the last one
                if (last->value == oldValue) {
                    // put new value & return true as confirmation 
                    last->value = NewValue;
                    return true;
                }

                // o(n)
                // else that mean target maybe in middle soo we loop over all
                d_node<t>* temp = first->next;
                
                while (temp != last) {
                    // in case target founded
                    if (temp->value == oldValue) {
                        temp->value = NewValue; // replace
                        return true; // confirmation
                    }
                    // else going to the next one ;)
                    temp = temp->next;
                }

                // in case target value not found that mean there's no replace operation happend 
                return false;
            }

            // o(1) ==> o(n)
            // remove node have target value in linked list  
            bool remove(t value) {
                
                // o(1)
                // in case target value in "first/head"
                if (first->value == value) {
                    return remove_first();
                }
                // o(1)
                // in case target value in "last/tail"
                if (last->value == value) {
                    return remove_last();
                }

                // else that mean we need to look in middle nodes of linked list
                // o(n)
                d_node<t>* temp = first;

                while (temp != NULL) {
                    // in case target found 
                    if (temp->value == value) {
                        temp->prev->next = temp->next;
                        delete temp;
                        return true;
                    }
                    // else keep going 
                    temp = temp->next;
                }

                // in case target not found 
                return false;
            }

            // o(1) ==> o(n)
            bool has(t value) {
                // o(1)
                // in case target value looking for in first or last
                if (first->value == value) return true;
                if (last->value  == value) return true;

                // else :o(n)
                d_node<t>* temp = first->next;

                while (temp != last) {
                    if (temp->value == value) return true;
                    else temp = temp->next;
                }

                // in case not found
                return false;
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