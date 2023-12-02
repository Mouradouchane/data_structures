#include <vector>
#pragma once

// === singly linke list ~ methods ===
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

namespace linkedlist {

// ============= node ===============
template<typename t> class node {

    public:

        // only value & pointer for next one :)
        t value;
        node<t>* next = nullptr;

        // constructors
        node() { }

        node(t const& Value) : value(Value) { }

        node(node<t> const& other_node): value(other_node.value) , next(other_node.next) { }

        // destructor
        ~node(){ 
        
            try {

                if (this->next != nullptr) {
                    this->next->~node();
                    this->next = nullptr;
                }

            }
            catch (std::exception& error) {
                std::cerr << error.what() << '\n';
                throw error.what();
            }

        }
    

        void operator = ( node<t>* & other_node ) {
            this->value = other_node->value;
            this->next = other_node->next;
        }

        void operator ++ () {
            this = this->next;
        }

        bool operator != (node<t>& other_node){
            return (this != &other_node) ? true : false ;
        }
        
        bool operator != ( t & other_value ){
            return (this->value != other_value);
        }

        bool operator == (node<t>& other_node) {
            return (this == other_node);
        }
        bool operator == ( t & other_value ) {
            return (this->value == other_value);
        }

};





/*

    ------------ iterator ------------

*/

template<typename t> class iterator {

private:

    node<t>* addr = nullptr;

public:

    // constructors
    iterator() {}
    iterator(node<t>* address) :addr(address) { }
    iterator(node<t> const& address) :addr(address) { }
    iterator(iterator const& other) :addr(other.addr) { }

    // destructor
    ~iterator() {}

    void next() {

        if (this->addr != nullptr) this->addr = this->addr->next;

    }

    t& operator * () {
        return this->addr->value;
    }

    void operator ++() {

        if (this->addr != nullptr) this->addr = this->addr->next;

    }

    void operator += (size_t const& move_value) {

        size_t counter = move_value;

        while (counter != 0) {

            if (this->addr == nullptr) break;
            else {
                this->addr = addr->next;
                counter -= 1;
            }

        }

    }


    node<t>& operator ->() {
        return *addr;
    }

    iterator& operator + (size_t const& move_value) {

        size_t counter = move_value;

        iterator temp(this->addr);

        while (counter != 0) {

            if (temp.addr == nullptr) break;
            else {
                temp.addr = temp.addr->next;
                counter -= 1;
            }

        }

        return temp;

    }

    bool operator != (iterator const& other) {
        return (this->addr != other.addr);
    }

    bool operator == (iterator const& other) {
        return (this->addr == other.addr);
    }

    void operator = (iterator const& other_itr) {
        if (&other_itr != nullptr) this->addr = other_itr.addr;
    }


    node<t>& get_node() {
        return *this->addr;
    }

};

/*

    ------------- end of class iterator -------------

*/



/*

    ------------- singly linked list--------------

*/ 

template<typename t> class singly_LinkedList {

private :

        int len = 0; 

        node<t>* first = nullptr; // head
        node<t>* last  = nullptr; // tail

public:
        // constructor
        singly_LinkedList() {}

        singly_LinkedList(std::initializer_list<t> const& list_elements) {
        
            this->first = new node<t>();

            node<t>* temp = this->first;
            size_t i = 1;

            for ( t element : list_elements ) {

                temp->value = element;

                if ( (list_elements.begin() + i) != list_elements.end()) {
                    temp->next = new node<t>();
                    temp = temp->next;
                }
                i += 1;
            }

            this->last = temp;

        }

        // destructor
        ~singly_LinkedList() {

            try {

                if (this->first != nullptr) {
                    this->first->~node();
                    this->first = nullptr;
                }

            }
            catch (std::exception& error) {
                std::cerr << error.what() << '\n';
                throw error.what();
            }

        }


        // o(1)
        // return "first/head" as pointer
        node<t>* getFirstAsPointer() {
            return first;
        }

        // o(1)
        // return "last/tail" as pointer
        node<t>* getLastAsPointer() {
            return last;
        }

        // o(1)
        // push new value direct from the back of linked list (or you can say 'new tail')
        void push_back(t const& value){
            node<t>* newNode = new node<t>(value);

            len += 1;

            if (first == NULL && last == NULL) {
                first = newNode;
                last =  newNode;
                return;
            }
            else {
                last->next = newNode;
                last = newNode;
            }
        }
    
        // o(1)
        // push new value direct from the front of linked list (or you can say 'new head')
        void push_front(t const& value) {
            node<t>* newNode = new node<t>(value);

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
        void push_at(t position , t value) {
            len += 1; // just length of linked list :)

            // new node with value 
            node<t>* newNode = new node<t>(value);
    
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
            return (first != NULL) ? *first : NULL;
        }
        // o(1)
        // get first value in first node in linked list
        t getFirstValue() {
            return (first != NULL) ? first->value : NULL;
        }

        // o(1)
        // get last node in linked list
        node<t> getLastElement() {
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
            long long int i = 0;
            while (tempNode != NULL) {
                *(arr+i) = tempNode->value;
                tempNode = tempNode->next;
                i+=1;
            }
            // return array of values as pointer
            return arr;
        }

        // o(n)
        // method delete all nodes in linked list & make it clear 
        void clear() {
            node<t>* temp = first;

            while (temp != NULL){
                node<t>* next_temp = temp->next;
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

                len -= 1;

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
                last  = NULL;
                len   = 0;
                return;
            }

            // in case linked list not empty
            len -= 1;
            // set head to next one & delete old one
            node<t>* next = first->next;
            delete first;
            first = next;
        }

        // o(n)
        // remove "last one or tail"
        void remove_last() {
            // check if  empty
            if (first == NULL) return;
            
            node<t>* prevtemp = first;

            node<t>* temp = first->next;

            // check if one element in
            if (first->next == NULL) {
                first = NULL;
                last  = NULL;
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
            node<t>* temp = first;

            // in case you want sort from greatest to smallest
            if (from_greater_to_smaller) {

                // just linear sort o(n²)
                while (temp != NULL) {
                    node<t>* comp = first;

                    while (comp != NULL) {
                        if (comp->value < temp->value) {
                            t tempValue = comp->value;
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
                    node<t>* comp = first;

                    while (comp != NULL) {
                        if (comp->value > temp->value) {
                            t tempValue = comp->value;
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
            std::vector<t> temp_vec;
            node<t>* temp = first;

            // o(n) : take all linked list element & push them to vector
            while (temp != NULL){
                temp_vec.insert(temp_vec.begin(),temp->value);
                temp = temp->next;
            }

            // o(n) : clear linked list 
            clear();

            // o(n) : push_back all reversed values to linked list 
            for (t value : temp_vec) {
                push_back(value);
            }

        }

        // o(n)
        // search of target value 
        bool search(t target_value) {
            if (first == NULL) return false;
            node<t>* temp = first;

            while ( temp != NULL){
                if (temp->value == target_value) return true;
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
        void foreach( void (* const& call_back_function)( size_t const& counter , t & node) ) {

            node<t>* temp = first;
            size_t ctr = 0;

            while (temp != nullptr) {

                call_back_function(ctr, temp->value);
                temp = temp->next;
                ctr += 1;

            }

        }

        // o(1) ==> o(n)
        // += operator for concat external linked list with current linked list
        void operator +=(singly_LinkedList<t> & slinkedlist) {
            
            node<t>* stemp = slinkedlist.getFirstAsPointer();

            while (stemp != NULL) {
                push_back(stemp->value);
                stemp = stemp->next;
            }
        }

        // o(1) ==> o(n)
        // like first += operator but this one for vector of values :)
        void operator +=(std::vector<t> new_values) {

            for (t value : new_values) {
                push_back(value);
            }

        }

        iterator<t> begin() {
            return iterator<t>( this->first );
        }

        iterator<t> end() {
            return iterator<t>( this->last->next );
        }

};


}