#include <vector>


// === singly linke list ~ methods ===
/*
    length          => o(1)
    push_back       => o(1)
    push_front      => o(1)
    push_at         => o(n)

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

            while (tempNode != NULL) {
                vec.push_back(tempNode->value);
                tempNode = tempNode->next;
            }

            return vec;
        }

        // o(n)
        // method return array as pointer
        t* toArray() {
            t* arr = new t[len];
            node<t>* tempNode = first;

            int i = 0;
            while (tempNode != NULL) {
                *(arr+i) = tempNode->value;
                tempNode = tempNode->next;
                i+=1;
            }

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

        // o(1)
        // return length of linked size :) 
        int length() {
            return len;
        }
};

}