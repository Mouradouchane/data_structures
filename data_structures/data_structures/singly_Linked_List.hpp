
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
            ;
            node<t>* newNode = new node<t>;
            newNode->value = value;

            if (first == NULL && last == NULL) {
                first = newNode;
                last = newNode;
                first->next = last;
                return;
            }
            else {
                last->next = newNode;
                last = newNode;
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