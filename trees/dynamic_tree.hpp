#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>

#pragma once

namespace trees{


    /* 
       ================================
       === Dynamic Tree Nodes class ===
       ================================
    */

    /*
        Dynamic Tree Node

        -- NAME ---------- BEST --> WORST

        length		    => o(1)

        insert			=> o( (n log n) + (log n) + 1 )

        search			 => o(1) --> o(log n)
        search_for_index

        sort            => o(n log n) --> o(n²)

        getCopy        	=> o(1) --> o(log n)

        removeChild     => o(log n) 
        removeChildren  => o(log n + children)

        operator <      => o(1) 
        operator >      => o(1)
    */

    template<typename T> class dt_node {

        private:
            // parent of this node 
            dt_node<T>* parent;

            bool binary_search(std::string const &target_name , int &target_index){
                int min = 0;
                int max = this->children.size() - 1;
                int mid = ( min + max ) / 2;

                while( min <= max ){

                    // in case target found
                    if(this->children[mid].name == target_name){
                        if(&target_index != NULL) {
                            target_index = mid;
                        }
                        return true;
                    }
                    
                    // going left
                    if(this->children[mid].name.compare(target_name) > 0){
                        max = (mid - 1);
                    }

                    // going right
                    if(this->children[mid].name.compare(target_name) < 0){
                        min = (mid + 1);
                    }

                    // update mid
                    mid = ( min + max ) / 2 ;
                }

                // in case not found
                if(&target_index != NULL) {
                    target_index = -1;
                }
                return false;
            }

        public:
            // children of this node 
            std::vector<dt_node<T>> children;
            
            // name => for dealing with nodes "search , sort , ..."
            std::string name;

            // node value
            T value;

            // default constructor
            dt_node() {}

            // second constructor
            dt_node(std::string node_name, T node_value , dt_node<T> * parent_node = NULL)
                : name    { node_name }  , 
                  value   { node_value } ,
                  parent  { parent_node }
            { 

            }

            // default destructor
            ~dt_node() {

                try {

                    for ( dt_node<T> & child : this->children ) {
                        child.~dt_node();
                    }

                    this->children.clear();

                }
                catch (std::exception& error) {
                    std::cerr << error.what() << '\n';
                    throw error;
                }

            }

            // o( (n log n) + (log n) + 1 )
            // duplicate names are not allowed here in dynamic tree
            bool insert(std::string new_node_name , T new_node_value) {

                // just int for required parameter in search function
                int fake_index = -1;

                // o(log n)
                // first we check if any node is already exist with the same name
                if( search_for_index(new_node_name , fake_index) ) return false;
                
                // then
                // insert new child
                children.push_back( dt_node<T>(new_node_name, new_node_value, this) );

                // o(n log n)
                // sort children
                this->sort();

                // confirmation
                return true;
            }

            // o(1) --> o(log n)
            // 2 search function "overloading"

            // target_index : useful if you want to get index of that target in case not found you get -1
            bool search_for_index(std::string const &target_name , int &target_index){

                return this->binary_search(target_name , target_index);
            }

            // same search but when no need to index
            bool search(std::string const &target_name_){
                
                int skip_index = -1;
               
                return this->binary_search(target_name_ , skip_index);
            }
            

            // sort children
            // o(n log n) --> o(n²)
            void sort(bool reverse = false){

                if(reverse){
                    std::sort(this->children.begin() , this->children.end() , 
                        // comparison function
                        [](dt_node<T> a , dt_node<T> b){
                            return (a > b);
                        }
                    );
                }
                else{
                    std::sort(this->children.begin() , this->children.end() , 
                        // comparison function
                        [](dt_node<T> a , dt_node<T> b){
                            return (a < b);
                        }
                    );
                }

            }

            // o(1) --> o(log n)
            // get a copy of specific child , this copy not connected to the original tree
            // in case target not found return will be a empty node
            dt_node<T> getCopy(std::string const &target_node_name){
                
                int index = -1;

                // search for target
                this->search_for_index(target_node_name,index);

                // temp copy
                dt_node<T> copy_of_child;

                // in case target found
                if(index != -1){
                    // set name & value using index
                    copy_of_child.name  = this->children[index].name;
                    copy_of_child.value = this->children[index].value;
                }

                return copy_of_child;
            }

            // get a copy of this node
            dt_node<T> getCopy(){
                return *this;
            }

            // o(log n) --> o(nodes * log n)
            // remove child with specific name with his all children
            bool removeChild(std::string const &target_node_name){

                // search for target index
                int index = -1;
                search_for_index(target_node_name , index);

                // call recursive remove of this child node
                if(index != -1){
                    children[index].removeChildren();
                    children.erase(children.begin() + index);
                    return true;
                } 

                return false;
            }

            // like removeChild function but this for all children 
            void removeChildren(){
                
                // nested recursive removeChildren => remove all children of children
                for(dt_node<T> &child : this->children){
                    child.removeChildren();
                }

                // last step remove children by setup a new empty vector 
                this->children = std::vector<dt_node<T>>();
            }


            // get length of children in this node
            std::size_t length(){
                return this->children.size();
            }

            // < comparison operator between tow nodes
            bool operator < (dt_node<T> &another_node){
                return ( this->name.compare(another_node.name) < 0 ) ? true : false;
            } 

            // > comparison operator between tow nodes
            bool operator > (dt_node<T> &another_node){
                return ( this->name.compare(another_node.name) > 0 ) ? true : false;
            }

            // giving a access for making some processes like go_to , travel_to ... 
            template<typename v> friend class DynamicTree;
    };

 

    // ==========================
    // === dynamic tree class ===
    // ==========================

        
    /*
        dynamic tree 
        
        -- NAME ------	BEST --> WORST
        search_up		o(1)
        search_down		o(1) --> o(log n)

        go_to			o(1) --> o(log n) 
        go_back         o(1)
        go_to_root      o(1)

        travel_up	    o(log n) --> o(log n * path)
        travel_down	    o(log n) --> o(log n * path)

    */

    template<typename V> class dynamic_tree {

        private:

            // main node in DynamicTree
            dt_node<V> root;

            /* 
                **** some private function **** 
                used in "travel_to" function
            */

            // o(1) 
            // function take a "temp node" & make a simple check if that temp include a parent with specific name
            // return will be a "parent pointer" or NULL
            dt_node<V>* search_up(std::string &parent_name , dt_node<V> *temp) {
                
                if(temp->parent != NULL && temp->parent->name == parent_name) {
                        return temp->parent;
                }
                else return NULL;

            }

            // o(1) --> o(log n) 
            // like "search_up" function , but this one for looking "down" between children
            dt_node<V>* search_down(std::string &node_name , dt_node<V> *temp) {
                
                // o(log n)
                // search for target 
                int index = -1;
                temp->search_for_index(node_name , index);
                
                if(index != -1){
                    return &temp->children[index];
                }

                return NULL;
            }

            // o(path) --> o(log n * path)
            /* 
                like go_to but this require a hole path of "names" in one direction
                note !! travel will happend only if "the whole path of names" is valid 
                otherwise nothing will be happen & return will be false
            */
            bool travel(const std::vector<std::string> &path_of_names , bool up = false){
                
                // temp only for "check & test" if "path_of_names" are valid or not
                // if "path_of_names" is valid we make it the new current_position "as last step" 
                // else nothing will be happen
                dt_node<V> *temp = current_node;

                // up true => mean that "path_of_names" in parents direction "up"
                if(up){

                    // o(path)
                    // we start looking up by using a private function "search_up"
                    for(std::string path : path_of_names){

                        // o(log n)
                        temp = search_up(path , temp);

                        // in case not found "that's mean invalid path"
                        if(temp == NULL) return false;
                    }

                }
                // "up == false" mean that "path_of_names" in children direction "down"
                else{

                    // o(path)
                    // we start looking down by using a private function "search_down"
                    for(std::string path : path_of_names){

                        // o(log n)
                        temp = search_down(path , temp);

                        // in case not found "that's mean invalid path"
                        if(temp == NULL) return false;
                    }

                }

                // in case "path_of_names" is valid 
                // last step => travel/jump from "current_position" to "temp node"
                current_node = temp;

                // and confirmation 
                return true;
            }

        public:

            // current_node => it's a node represent you position in tree
            // "important !" for many operation like search , movement , ...
            dt_node<V> *current_node;

            // constructor
            dynamic_tree(std::string root_name , V root_value) {
                // parent of root must be null
                root = dt_node<V>( root_name , root_value , NULL ); 
                current_node = &root;
            }

            // destructor
            ~dynamic_tree(){  }

            // o(1) --> o(log n)
            // target_child_name => mean node where you want to go
            bool go_to(std::string const &target_child_name) {

                // search for target index
                int index = -1;
                this->current_node->search_for_index(target_child_name,index);

                // in case target found
                if(index != -1){
                    this->current_node = &(this->current_node->children[index]);

                    return true;
                }

                // in case target 'not found'
                return false;
            }

            // o(1)
            // go from this current_node to parent node
            bool go_back(){

                // if parent not NULL
                if(this->current_node->parent != NULL){
                    // move to parent
                    this->current_node = this->current_node->parent;

                    return true;
                }
                // else 
                return false;
            }

            // o(1)
            // go to the root directly 
            bool go_to_root(){
                
                // if parent of current node is NULL that mean current node already in root
                if(this->current_node->parent == NULL) return false;
                
                // else
                this->current_node = &this->root;
                return true;
            }

            // travel in parent's direction   "up"
            bool travel_up(const std::vector<std::string> &path_of_names){
                return this->travel(path_of_names , true);
            }

            // travel in child's direction    "down"
            bool travel_down(const std::vector<std::string> &path_of_names){
                return this->travel(path_of_names , false);
            }


    }; // end of Dynamic Tree Class


} // end of namespace


