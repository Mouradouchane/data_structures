#include<vector>
#pragma once

// "circly" singly like normal singly but with some simple changes

namespace linkedlist {

// ========== node ============
template<typename t> class c_node {
public:
    c_node() { }
    c_node(t Value) :value(Value) { }
    ~c_node() { }

    // only value & pointer for next one :)
    t value;
    c_node<t>* next = NULL;
};


// ========== singly linked list ============
template<typename t> class circly_singly_LinkedList {

private:
    int len = 0; // len => length
    c_node<t>* first = NULL; // head
    c_node<t>* last = NULL; // tail

public:
    circly_singly_LinkedList() {}
    ~circly_singly_LinkedList() {}

    // o(1)
    // return "first/head" as pointer
    c_node<t>* getFirstAsPointer() {
        return first;
    }

    // o(1)
    // return "last/tail" as pointer
    c_node<t>* getLastAsPointer() {
        return last;
    }

    // o(1)
    // push new value direct from the back of linked list (or you can say 'new tail')
    void push_back(t value) {
        c_node<t>* newNode = new c_node<t>(value);

        len += 1;

        if (first == NULL && last == NULL) {
            first = newNode;
            last = newNode;
            return;
        }
        else {
            last->next = newNode;
            last = newNode;

            // just referring from last for first in each operation :)
            last->next = first;
        }
    }

    // o(1)
    // push new value direct from the front of linked list (or you can say 'new head')
    void push_front(t value) {
        c_node<t>* newNode = new c_node<t>(value);

        len += 1;

        if (first == NULL && last == NULL) {
            first = newNode;
            last = newNode;
           
            return;
        }

        else {
            newNode->next = first;
            first = newNode;

            // just referring from last for first in each operation :)
            last->next = first;
        }
    }

    // o(n)
    // push new value in linked list with specific position 
    void push_at(t position, t value) {
        len += 1; // just length of linked list :)

        // new node with value 
        c_node<t>* newNode = new c_node<t>(value);

        // temp for loop over all nodes & check one by one :) 
        c_node<t>* temp = first;

        // loop over all nodes in linked list & check for position
        while (temp != last) {
            // in case we found position 
            if (temp->value == position) {
                // getting next
                c_node<t>* next = temp->next;
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

        // just referring from last for first in each operation :)
        last->next = first;
    }

    // o(1)
    // get first node in linked list
    c_node<t> getFirstElement() {
        return (first != NULL) ? *first : NULL;
    }
    // o(1)
    // get first value in first node in linked list
    t getFirstValue() {
        return (first != NULL) ? first->value : NULL;
    }

    // o(1)
    // get last node in linked list
    c_node<t> getLastElement() {
        return (last != NULL) ? *last : NULL;
    }
    // o(1)
    // get last value in last node in linked list
    t getLastValue() {
        return (last != NULL) ? last->value : NULL;
    }

    // o(n)
    // method return vector of all values in linked list
    std::vector<t> toVector() {
        std::vector<t> vec;

        c_node<t>* tempNode = first;

        // loop over all & push to the vector
        while (tempNode->next != first) {
            vec.push_back(tempNode->value);
            tempNode = tempNode->next;
        }

        // return vector of values
        return vec;
    }

    // o(n)
    // method return array as pointer
    t* toArray() {
        t* arr = new t[len];
        c_node<t>* tempNode = first;

        // loop over all & push to the array
        long long int i = 0;
        while (tempNode->next != first) {
            *(arr + i) = tempNode->value;
            tempNode = tempNode->next;
            i += 1;
        }
        // return array of values as pointer
        return arr;
    }

    // o(n)
    // method delete all nodes in linked list & make it clear 
    void clear() {
        c_node<t>* temp = first;

        do{
            c_node<t>* next_temp = temp->next;
            delete temp;
            temp = next_temp;
        } while (temp != first && temp != NULL);

        // start from 0
        first = NULL;
        last = NULL;
        len = 0;
    }

    // o(n)
    // replace function take "target value" and replace it with "new value" 
    // if replace not found "target" don't do anything & return false 
    // else replace it and return true as confirmation :)
    bool replace(t targetValue, t newValue) {
        // temp node for checking we start from "first or head"
        c_node<t>* temp = first;

        // loop over all
        while (temp->next != first) {
            // in case we found target value
            if (temp->value == targetValue) {
                // then replace it with new one
                temp->value = newValue;
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
    bool has(t wanted_value) {
        if (wanted_value == first->value || wanted_value == last->value)return true;

        c_node<t>* temp = first;

        // loop over all and check
        while (temp != last) {
            // in case value found 
            if (temp->value == wanted_value) {
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
    bool remove(t target_value) {
        // in case target value in first 
        if (first->value == target_value) {
            // make next equal to first and delete old first 
            c_node<t>* next = first->next;
            delete first;
            
            first = next;
            last->next = first;
            len -= 1;

            // return true as confirmation 
            return true;
        }

        // else we start loop over all & check 
        // we need "previous" for that "remove operation"
        c_node<t>* prev = first;
        c_node<t>* current = first->next;

        // check by using current or "next one"
        while (current != first) {
            // in case target value founded that mean we need to delete that "current"
            if (current->value == target_value) {
                // make previouse connected to next of current and delete current
                prev->next = current->next;
                delete current;

                // in case target is last , make sure to update last 
                if (prev->next == NULL) {
                    last = prev;

                    // just referring from last to first in each operation :)
                    last->next = first;
                }

                // update length
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
        len -= 1;
        // set head to next one & delete old one
        c_node<t>* next = first->next;
        delete first;

        first = next;
        last->next = first;
    }

    // o(n)
    // remove "last one or tail"
    void remove_last() {
        c_node<t>* prevtemp = first;
        c_node<t>* temp = first->next;

        // loop over all until reach the last one
        while (temp != first) {
            if (temp->next == first) {
                // then make previous => new last 
                last = prevtemp;

                // just referring from last to first in each operation : )
                last->next = first;

                // delete "old last" and return for stop functio
                delete temp;

                // update length
                len -= 1;

                // just for stop ;)
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
        c_node<t>* temp = first;


        // in case you want sort from greatest to smallest
        if (from_greater_to_smaller) {
            // just linear sort o(n²)
            do {
                c_node<t>* comp = first;

                do {
                    if (comp->value < temp->value) {
                        t tempValue = comp->value;
                        comp->value = temp->value;
                        temp->value = tempValue;
                    }

                    comp = comp->next;

                } while (comp != first);

                temp = temp->next;

            } while (temp != first);
        }
        // in case you want sort from smallest to greatest
        else {
            do {
                c_node<t>* comp = first;

                do {
                    if (comp->value > temp->value) {
                        t tempValue = comp->value;
                        comp->value = temp->value;
                        temp->value = tempValue;
                    }

                    comp = comp->next;

                } while (comp != first);

                temp = temp->next;

            } while (temp != first);
        }
  
    }

    // o(n*3)
    void reverse() {
        std::vector<t> temp_vec;
        c_node<t>* temp = first;

        // o(n) : take all linked list element & push them to vector
        do{
            temp_vec.insert(temp_vec.begin(), temp->value);
            temp = temp->next;
        } while (temp != first && temp != NULL);

        // o(n) : clear linked list 
        clear();

        // o(n) : push_back all reversed values to linked list 
        for (t value : temp_vec) {
            push_back(value);
        }

    }


    // o(1) ==> o(n)
    // += operator for concat external linked list with current linked list
    void operator +=(circly_singly_LinkedList<t> & c_s_linkedlist) {
        c_node<t>* cs_first = c_s_linkedlist.getFirstAsPointer();

        c_node<t>* stemp = c_s_linkedlist.getFirstAsPointer();
        
        do{
            if (stemp == NULL || cs_first == NULL) break;
            push_back(stemp->value);
            stemp = stemp->next;

        } while (stemp != cs_first);
    }

    // o(1) ==> o(n)
    // like first += operator but this one for vector of values :)
    void operator +=(std::vector<t> new_values) {

        for (t value : new_values) {
            push_back(value);
        }

    }

    // o(1)
    // return length of linked size :) 
    int length() {
        return len;
    }

    // o(n)
    // just "test function" who print all values in console
    void showAll() {
        if (first == NULL && last == NULL) {
            std::cout << "==================================================" << std::endl;
            std::cout << "==================================================" << std::endl;
            return;
        } 

        if(first == last) {
            std::cout << "==================================================" << std::endl;
            std::cout << first->value << std::endl;
            std::cout << "==================================================" << std::endl;
            return;
        }

        c_node<t>* tempNode = first->next;

        std::cout << "==================================================" << std::endl;
        std::cout << first->value << std::endl;

        while (tempNode != first) {
            std::cout << tempNode->value << std::endl;
            tempNode = tempNode->next;
        }
        std::cout << "==================================================" << std::endl;
    }
};


}