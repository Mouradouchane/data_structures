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
*/

namespace singlyLinkedList {

    template<typename t> class node {
    public:
        node() {}
        t value;
        node* next = NULL;
    };

    template<typename t> class linkedList {
    private : 
        // len => length
        int len = 0; 
        node<t>* first = NULL; // head
        node<t>* last  = NULL; // tail
    public:
        linkedList() {}
        ~linkedList() {}

        // o(1)
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
        void  push_at(t position , t value) {
            len += 1;
        }

        void showAll() {
            node<t>* tempNode = first;

            while (tempNode != NULL) {
                std::cout << tempNode->value << std::endl;
                tempNode = tempNode->next;
            }

        }

        node<t> getFirstElement() {
            node<t> copy = *first;
            return copy;
        }

        t getFirstValue() {
            return first->value;
        }

        node<t> getLastElement() {
            node<t> copy = *last;
            return copy;
        }

        t getLastValue() {
            return last->value;
        }

        std::vector<t> toVector() {
            std::vector<t> vec;

            node<t>* tempNode = first;

            while (tempNode != NULL) {
                vec.push_back(tempNode->value);
                tempNode = tempNode->next;
            }

            return vec;
        }

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

        int length() {
            return len;
        }
    };

}