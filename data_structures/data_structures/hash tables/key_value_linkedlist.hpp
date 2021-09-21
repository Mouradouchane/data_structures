#include <iostream>
#pragma once

// === singly linke list but key value pair system for hash tables ===
/*
 -- NAME ------------ BEST --> WORST

    length          => o(1)

    push_back       => o(1)
    push_front      => o(1)

    get             => o(1) ==> o(n)
    getPair         => o(1) ==> o(n)

    replace         => o(1) ==> o(n)
    search          => o(n)

    remove          => o(1) ==> o(n)
    clear           => o(n)

    print         => o(n)
*/

namespace key_value_linkedlist {

template<typename k , typename v> class kv_node {
    public:
        // only value & pointer for next one :)
        k key;
        v value;
        kv_node<k,v>* next = NULL;

        // empty constructor
        kv_node() {  }

        // key value constructor
        kv_node(k Key, v Value) { 
            key = Key; 
            value = Value;
        }

        // destructor
        ~kv_node() { }

};


    // ========== singly linked list but key value pair only ============
template<typename k , typename v> class key_value_linked_list {

    private:
        int len = 0; // len => length
        kv_node<k, v>* first = NULL; // head
        kv_node<k, v>* last  = NULL; // tail

    public:
         key_value_linked_list() {}
        ~key_value_linked_list() {}

        // o(1) --> o(n)
        // push new value direct from the back of linked list (or you can say 'new tail')
        bool push_back(k key , v value) {
            kv_node<k, v>* newNode = new kv_node<k, v>(key , value);

            len += 1;

            // in case empty
            if (first == NULL && last == NULL) {
                first = newNode;
                last = newNode;
                return true;
            }
            else {
                // in case not empty , we need to check first if that <key,value> is already in linked list or not
                // o(n)
                if ( !search(key) ) {
                    last->next = newNode;
                    last = newNode;
                    return true;
                }
            }

            return false;
        }

        // o(1) ==> o(n)
        // get function return value if it found otherwise return null
        v get(k target_key){
            // in case linked list empty
            if (first == NULL) return NULL;

            // loop over all & search of target
            kv_node<k,v>* temp = first;
            while (temp != NULL) {
                // in case found return value
                if (temp->key == target_key) return temp->value;
                else temp = temp->next;
            }

            // in case not found return will be null
            return NULL;
        }

        // o(1) ==> o(n)
        // get a pair { key , value }
        std::pair<k,v> getPair(k target_key) {
            // in case linked list empty return will be a empty pair
            if (first == NULL) return std::pair<k, v>();

            // loop over all & search of target
            kv_node<k, v>* temp = first;
            while (temp != NULL) {
                // in case found return value
                if (temp->key == target_key) {
                    std::pair<k,v> tpair(temp->key, temp->value);
                    return tpair;
                }
                // going to next one 
                else temp = temp->next;
            }

            // in case not found return will be a empty pair
            return std::pair<k, v>();
        }

        // o(1)
        // push new value direct from the front of linked list (or you can say 'new head')
        void push_front(k key , v value) {
            kv_node<k, v>* newNode = new kv_node<k, v>(key , value);

            len += 1;

            if (first == NULL && last == NULL) {
                first = newNode;
                last = newNode;
                //first->next = last;
                return;
            }

            else {
                newNode->next = first;
                first = newNode;
            }
        }

        // o(n)
        // method delete all nodes in linked list & make it clear 
        void clear() {
            kv_node<k,v>* temp = first;

            while (temp != NULL) {
                kv_node<k,v>* next_temp = temp->next;
                delete temp;
                temp = next_temp;
            }

            // start from 0
            first = NULL;
            last = NULL;
            len = 0;
        }

        // o(n)
        // replace old value by new one using  "key" 
        // if it found replace else don't ==> and return will be "true or false" as confirmation :)
        bool replace(k target_key, v new_value) {

            // in case linked list is empty
            if (first == NULL) return false;

            // temp node for checking we start from "first or head"
            kv_node<k,v>* temp = first;

            // loop over all
            while (temp != NULL) {
                // in case we found target value
                if (temp->key == target_key) {
                    // then replace by new value
                    temp->value = new_value;
                    // and return true as confirmation 
                    return true;
                }
                // else keep going to next one
                temp = temp->next;
            }
            // in case target not found that mean replace not happen soo return must be false
            return false;
        }


        // o(n)
        // search for target using key
        bool search(k target_key) {
            if (first == NULL) return false;

            kv_node<k, v>* temp = first;
            while (temp != NULL) {
                if (temp->key == target_key) return true;
                temp = temp->next;
            }

            return false;
        }


        // o(1) ==> o(n)
        // remove take target if it found delete it and return true as confirmation 
        // else return false
        bool remove(k target_key) {

            // in case linked list empty
            if (first == NULL) return false;

            // in case target value in first 
            if (first->key == target_key) {
                // make next equal to first and delete old first 
                kv_node<k,v>* next = first->next;
                delete first;
                first = next;

                len -= 1;

                // return true as confirmation 
                return true;
            }

            // else we start loop over all nodes & check 
            // we need "previous" and "next one" for this operation 
            kv_node<k,v>* prev = first;
            kv_node<k,v>* current = first->next;

            // check by using current or "next one"
            while (current != NULL) {
                // in case target value founded that mean we need to delete that "current"
                if (current->key == target_key) {
                    // make previouse connected to next of current and delete current
                    prev->next = current->next;
                    delete current;

                    // in case target is last , make sure to update last 
                    if (prev->next == NULL) last = prev;

                    len -= 1;

                    // then return true as confirmation 
                    return true;
                }
                // else keep going and looking for next one
                prev = current;         // prev to current
                current = prev->next;   // current to next
            }

            // in case target not found 
            return false;
        }

      
        // o(1)
        // return length of linked size :) 
        int length() {
            return len;
        }


        // o(n)
        // just "test function" who print all values in console
        void print() {
            kv_node<k,v>* tempNode = first;

            while (tempNode != NULL) {
                std::cout << "[" << tempNode->key << "|" << tempNode->value << "]-->";
                tempNode = tempNode->next;
            }
            std::cout << '\n';
        }


        // o(1)
        bool isEmpty() {
            return (first == NULL) ? true : false;
        }
};

}