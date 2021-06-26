#include <vector>


// === singly linke list ~ methods ===
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

namespace singlyLinkedList {

// ========== node ============
template<typename t> class node {
public:
    node() {}
    // only value & pointer for next one :)
    t value;
    node* next = NULL;
};


// ========== singly linked list ============
template<typename t> class singly_linkedList {

private : 
        int len = 0; // len => length
        node<t>* first = NULL; // head
        node<t>* last  = NULL; // tail

public:
        singly_linkedList() {}
        ~singly_linkedList() {}

        // o(1)
        // push new value direct from the back of linked list (or you can say 'new tail')
        void push_back(t value) {
            node<t>* newNode = new node<t>;
                     newNode->value = value;
            
            len += 1;

            if (first == NULL && last == NULL) {
                first = newNode;
                last  = newNode;
                return;
            }
            else {
                last->next = newNode;
                last = newNode;
            }
        }

        // o(1)
        // push new value direct from the front of linked list (or you can say 'new head')
        void push_front(t value) {
            node<t>* newNode = new node<t>;
                     newNode->value = value;

            len += 1;

            if (first == NULL && last == NULL) {
                first = newNode;
                last = newNode;
                first->next = last;
                return;
            }

            else {
                newNode->next = first;
                first = newNode;
            }
        }

        // o(n)
        // push new value in linked list with specific position 
        void  push_at(t position , t value) {
            len += 1; // just length of linked list :)

            // new node with value 
            node<t>* newNode = new node<t>;
                     newNode->value = value;
    
            // temp for loop over all nodes & check one by one :) 
            node<t>* temp = first;

            // loop over all nodes in linked list & check for position
            while (temp != NULL) {
                // in case we found position 
                if (temp->value == position) {
                    // getting next
                    node<t>* next = temp->next;
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
        node<t> getFirstElement() {
            node<t> copy = *first;
            return copy;
        }
        // o(1)
        // get first value in first node in linked list
        t getFirstValue() {
            return first->value;
        }

        // o(1)
        // get last node in linked list
        node<t> getLastElement() {
            node<t> copy = *last;
            return copy;
        }
        // o(1)
        // get last value in last node in linked list
        t getLastValue() {
            return last->value;
        }

        // o(n)
        // method return vector of all values in linked list
        std::vector<t> toVector() {
            std::vector<t> vec;

            node<t>* tempNode = first;

            // loop over all & push to the vector
            while (tempNode != NULL) {
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
            node<t>* tempNode = first;

            // loop over all & push to the array
            int i = 0;
            while (tempNode != NULL) {
                *(arr+i) = tempNode->value;
                tempNode = tempNode->next;
                i+=1;
            }
            // return array of values as pointer
            return arr;
        }

        // o(n)
        // method delete all nodes in linked list 
        void clear() {
            node<t>* temp = first;

            while (temp != NULL){
                node<t>* next_temp = temp->next;
                delete temp;
                temp = next_temp;
            }

            first = NULL;
            last = NULL;
        }

        // o(n)
        // replace function take "target value" and replace it with "new value" 
        // if replace not found "target" don't do anything & return false 
        // else replace and return true as confirmation :)
        bool replace(t targetValue , t newValue) {
            // temp node for checking we start from "first or head"
            node<t>* temp = first;
            
            // loop over all
            while (temp != NULL) {
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
            node<t>* temp = first;

            // loop over all and check
            while(temp != NULL){
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
                node<t>* next = first->next;
                delete first;
                first = next;
                // return true as confirmation 
                return true;
            }

            // else we start loop over all nodes & check 
            // we need "previous" and "next one" for this operation 
            node<t>* prev = first;
            node<t>* current = first->next;

            // check by using current or "next one"
            while (current != NULL) {
                // in case target value founded that mean we need to delete that "current"
                if (current->value == target_value) {
                    // make previouse connected to next of current and delete current
                    prev->next = current->next;
                    delete current;

                    // in case target is last , make sure to update last 
                    if (prev->next == NULL) last = prev;

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
            node<t>* next = first->next;
            delete first;
            first = next;
        }

        // o(n)
        // remove "last one or tail"
        void remove_last() {
            node<t>* prevtemp = first;
            node<t>* temp = first->next;

            // loop over all until reach the last one
            while (temp != NULL) {
                if (temp->next == NULL) {
                    // then make previous => new last 
                    last = prevtemp;
                    //and next of that new one equal to null 
                    last->next = NULL;
                    // delete old last and return for stop function
                    delete temp;
                    return;
                }
                // else going to next one in list
                prevtemp = temp;
                temp = temp->next;
            }

        }

        // o(1)
        // return length of linked size :) 
        int length() {
            return len;
        }

        // o(n)
        // just test function who print all values in console
        void showAll() {
            node<t>* tempNode = first;

            std::cout << "==================================================" << std::endl;
            while (tempNode != NULL) {
                std::cout << tempNode->value << std::endl;
                tempNode = tempNode->next;
            }
            std::cout << "==================================================" << std::endl;
        }
};

}