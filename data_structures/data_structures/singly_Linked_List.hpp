
// == singly linke list ==
/*
    push_back  => o(1)
    push_front => o(1)
    
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
        node<t>* first = NULL;
        node<t>* last = NULL;
    public:
        linkedList() {}
        void push_back(t value) {
            node<t>* newNode = new node<t>;
                     newNode->value = value;

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

        void push_front(t value) {
            node<t>* newNode = new node<t>;
                     newNode->value = value;

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

        void showAll() {
            node<t>* tempNode = first;

            while (tempNode != NULL) {
                std::cout << tempNode->value << std::endl;
                tempNode = tempNode->next;
            }

        }
    };

}