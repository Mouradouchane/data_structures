#include <vector>
#pragma once

// === singly linke list but key value pair system for hash tables ===
/*
 -- NAME ------------ BEST --> WORST

    length          => o(1)
    push_back       => o(1)
    push_front      => o(1)
    push_at         => o(n)

    replace         => o(1) ==> o(n)
    has             => o(1) ==> o(n)

    reverse         => o(n*3)
    sort            => o(n²)
    search          => o(n)

    remove          => o(1) ==> o(n)
    remove_first    => o(1)
    remove_last     => o(n)

    getFirstAsPointer => o(1)
    getLastAsPointer  => o(1)

    getFistElement  => o(1)
    getFistValue    => o(1)

    getLastElement  => o(1)
    getLastValue    => o(1)

    toVector        => o(n)
    toArray         => o(n)

    clear           => o(n)
    print         => o(n)

    +=              => o(1) ==> o(n)
*/

namespace key_value_linkedlist {

template<typename k , typename v> class kv_node {
    public:
        // only value & pointer for next one :)
        k key = NULL;
        v value = NULL;
        kv_node<k,v>* next = NULL;

        // empty constructor
        kv_node() { }
        // key value constructor
        kv_node(k Key, v Value) { 
            key = Key; 
            value = Value;
        }

        // destructor
        ~kv_node() { }

};


    // ========== singly linked list but key value pair ============
template<typename k , typename v> class key_value_LinkedList {

    private:
        int len = 0; // len => length
        kv_node<k, v>* first = NULL; // head
        kv_node<k, v>* last  = NULL; // tail

    public:
        key_value_LinkedList() {}
        ~key_value_LinkedList() {}

        // o(1)
        // return "first/head" as pointer
        kv_node<k,v>* getFirstAsPointer() {
            return first;
        }

        // o(1)
        // return "last/tail" as pointer
        kv_node<k,v>* getLastAsPointer() {
            return last;
        }


        // o(1)
        // push new value direct from the back of linked list (or you can say 'new tail')
        void push_back(k key , v value) {
            kv_node<k, v>* newNode = new kv_node<k, v>(key , value);

            len += 1;

            if (first == NULL && last == NULL) {
                first = newNode;
                last = newNode;
                return;
            }
            else {
                last->next = newNode;
                last = newNode;
            }
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
        // push new value in linked list with specific position 
        void push_at(k key_position, k key , v value) {
            len += 1; // just length of linked list :)

            // new node with value 
            kv_node<k,v>* newNode = new kv_node<k,v>(key , value);

            // temp for loop over all nodes & check one by one :) 
            kv_node<k,v>* temp = first;

            // loop over all nodes in linked list & check for position
            while (temp != NULL) {
                // in case we found position 
                if (temp->key == key_position) {
                    // getting next
                    kv_node<k,v>* next = temp->next;
                    // make next => newNode
                    temp->next = newNode;
                    // make newNode referring to next
                    newNode->next = next;
                    return; // stop as last step
                }
                // else keep going to next one 
                temp = temp->next;
            }

            // in case position value not found we add newNode as last one 
            last->next = newNode;
            last = newNode;
        }

        // o(1)
        // get first node in linked list
        kv_node<k,v> getFirstElement() {
            return (first != NULL) ? *first : NULL;
        }
        // o(1)
        // get first value in first node in linked list
        v getFirstValue() {
            return (first != NULL) ? first->value : NULL;
        }

        // o(1)
        // get last node in linked list
        kv_node<k,v> getLastElement() {
            return (last != NULL) ? *last : NULL;
        }
        // o(1)
        // get last value in last node in linked list
        v getLastValue() {
            return (last != NULL) ? last->value : NULL;
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
        // replace function take "target value" and replace it with "new value" 
        // if replace not found "target" don't do anything & return false 
        // else replace and return true as confirmation :)
        bool replace(k target_key, v new_value) {
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
        // searh for value if it in linked list or not
        bool has(k target_key) {
            kv_node<k,v>* temp = first;

            // loop over all and check
            while (temp != NULL) {
                // in case value found 
                if (temp->key == target_key) {
                    return true;
                }
                temp = temp->next;
            }

            // in case value not found 
            return false;
        }

        // o(1) ==> o(n)
        // remove take target if it found delete it and return true as confirmation 
        // else return false
        bool remove(k target_key) {

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
        // just method remove "first or head" & replace it with next one
        void remove_first() {
            // check if empty
            if (first == NULL) return;

            // check if one element in 
            if (first == last) {
                first = NULL;
                last = NULL;
                len = 0;
                return;
            }

            // in case linked list not empty
            len -= 1;
            // set head to next one & delete old one
            kv_node<k,v>* next = first->next;
            delete first;
            first = next;
        }

        // o(n)
        // remove "last one or tail"
        void remove_last() {
            // check if  empty
            if (first == NULL) return;

            kv_node<k,v>* prevtemp = first;

            kv_node<k,v>* temp = first->next;

            // check if one element in
            if (first->next == NULL) {
                first = NULL;
                last = NULL;
                len -= 1;
                return;
            }

            // loop over all until reach the last one
            while (temp != NULL) {
                if (temp->next == NULL) {
                    // then make previous => new last 
                    last = prevtemp;
                    //and next of that new one equal to null 
                    last->next = NULL;
                    // delete old last and return for stop function
                    delete temp;

                    len -= 1;

                    return;
                }
                // else going to next one in list
                prevtemp = temp;
                temp = temp->next;
            }

        }

        // o(n²)
        // sorting linked list using linear sort "worst one :)"
        void sort(bool from_greater_to_smaller = false) {
            kv_node<k,v>* temp = first;

            // in case you want sort from greatest to smallest
            if (from_greater_to_smaller) {

                // just linear sort o(n²)
                while (temp != NULL) {
                    kv_node<k,v>* comp = first;

                    while (comp != NULL) {
                        if (comp->value < temp->value) {
                            v tempValue = comp->value;
                            comp->value = temp->value;
                            temp->value = tempValue;
                        }
                        comp = comp->next;
                    }
                    temp = temp->next;
                }

            }
            // in case you want sort from smallest to greatest
            else {

                while (temp != NULL) {
                    kv_node<k,v>* comp = first;

                    while (comp != NULL) {
                        if (comp->value > temp->value) {
                            v tempValue = comp->value;
                            comp->value = temp->value;
                            temp->value = tempValue;
                        }
                        comp = comp->next;
                    }
                    temp = temp->next;
                }

            }

        }

        // o(n*3)
        void reverse() {
            std::vector<std::pair<k, v>> temp_vec;
            kv_node<k,v>* temp = first;

            // o(n) : take all linked list element & push them to vector
            while (temp != NULL) {
                temp_vec.insert(temp_vec.begin(), { temp->key , temp->value });
                temp = temp->next;
            }

            // o(n) : clear linked list 
            clear();

            // o(n) : push_back all reversed values to linked list 
            for (std::pair<k,v> kv : temp_vec) {
                push_back(kv->key , kv->value);
            }

        }

        // o(n)
        // search of target value 
        bool search(k target_key) {
            if (first == NULL) return false;
            kv_node<k,v>* temp = first;

            while (temp != NULL) {
                if (temp->key == target_key) return true;
                temp = temp->next;
            }

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
                std::cout << "| " << tempNode->key << " | " << tempNode->value << "|-->";
                tempNode = tempNode->next;
            }
            std::cout << "==================================================" << std::endl;
        }

};

}