/*
    Dynamic Tree Node

	-- NAME ---------- BEST --> WORST

	length		    => o(1)

	insert			=> o(log n + 1)	--> o( (n log n) + (log n) + 1)

	search			=> o(1) --> o(log n)
	sort            => o(n log n) --> o(n²)

	getCopy        	=> o(1) --> o(log n)
	replace   		=> o(1) --> o(log n)

	remove			=> o(nodes * log n)
    removeChild     => o(log n) --> o(nodes * log n)

    operator <      => o(1) --> o(n)
    operator >      => o(1) --> o(n)

	operator +=		=> shortcut of insert
	operator -=		=> shortcut of removeChild
*/


/*
    Dynamic Tree 
    
    -- NAME ------	BEST --> WORST
    search_up		o(1)
    search_down		o(1) --> o(children)

    move_to			o(1) --> o(children) 
    travel_to	    o(path) --> o(children * path)

    remove          o(1) --> o(1 + children)
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#pragma once

#ifndef DYNAMIC_TREE_H
#define DYNAMIC_TREE_H

namespace cpstl {

    // Dynamic Tree Nodes class
    template<typename t> class DT_Node {

        private:
            // parent of this node 
            DT_Node<t>* parent;

        public:
            // children of this node 
            std::vector<DT_Node<t>> children;
            
            // name => for dealing with nodes "search , sort , ..."
            std::string name;

            // node value
            t value;

            // default constructor
            DT_Node() {}

            // second constructor
            DT_Node(std::string node_name, t node_value , DT_Node<t> *parent_node)
                : name    { node_name }  ,
                  value   { node_value } ,
                  parent  { parent_node }
            { }

            // destructor
            ~DT_Node() { }


            /* 
             =============================
             ===     Nodes methods     ===
             =============================
            */

            // o(log n + 1)	--> o( (n log n) + (log n) + 1)
            // duplicate names are not allowed here in dynamic tree
            bool insert(std::string new_node_name , t new_node_value) {

                // just int for required parameterin search function
                int fake_index = 0;

                // o(log n)
                // first we check if any node is already exist with the same name
                if( search(new_node_name , fake_index) ) return false;
                
                // then
                // insert new child
                children.push_back(DT_Node<t>(new_node_name, new_node_value, this));

                // o(n log n)
                // sort children
                this->sort();

                // confirmation
                return true;
            }

            // o(1) --> o(log n)
            // search => "bineay search" between children
            // target_index : useful if you want to get index of that target in case not found you get -1
            bool search(std::string target_name , int &target_index = NULL){

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

            // sort children
            // o(n log n) --> o(n²)
            void sort(bool reverse = false){

                if(reverse){
                    std::sort(this->children.begin() , this->children.end() , 
                        // comparison function
                        [](DT_Node<t> a , DT_Node<t> b){
                            return (a > b);
                        }
                    );
                }
                else{
                    std::sort(this->children.begin() , this->children.end() , 
                        // comparison function
                        [](DT_Node<t> a , DT_Node<t> b){
                            return (a < b);
                        }
                    );
                }

            }

            // o(1) --> o(n log n)
            // get a copy of specific child , this copy not connected to the original tree
            DT_Node<t> getCopy(int child_index){
                
                // temp copy
                DT_Node<t> copy_of_child;

                // set name & value & return it
                copy_of_child.name  = this->children[child_index].name;
                copy_of_child.value = this->children[child_index].value;

                return copy_of_child;
            }

            // o(log n) --> o(nodes * log n)
            // remove child with specific name 
            bool removeChild(std::string target_node_name){

                // search for target index
                int index = 0;
                search(target_node_name , index);

                // call recursive remove of this child nodes
                // make sure that all
                if(index != -1) children[index].remove();

            }


            // remove this node with all it's children
            void remove(){

                // recursive remove call
                for(DT_Node<t> &child : this->children){
                    child.remove();
                }

                // delete it's self in the end
                delete this;
            }

			// testing function
			void print(){
                std::cout << "==================================" << '\n'; 
				for(DT_Node<t> &child : this->children){
					std::cout << child.name << "=" << child.value << " "; 
				}
                std::cout << "\n==================================\n"; 
			}

            // get length of children in this node
            unsigned int length(){
                return this->children.size();
            }

            // < comparison operator between tow nodes
            bool operator < (DT_Node<t> &another_node){
                return ( this->name.compare(another_node.name) < 0 ) ? true : false;
            } 

            // > comparison operator between tow nodes
            bool operator > (DT_Node<t> &another_node){
                return ( this->name.compare(another_node.name) > 0 ) ? true : false;
            }

            // giving a access for making some processes like move_to , travel_to ... 
            template<typename v> friend class DynamicTree;
    };

 


    // DynamicTree class 
    template<typename v> class DynamicTree {

        private:

            // main node in DynamicTree
            DT_Node<v> root;

            /* 
                **** some private function **** 
                used in "travel_to" function
            */

            // o(1) : function take a "temp node" & make a simple check if that temp include a parent with specific name
            // return will be a parent pointer or NULL
            DT_Node<v>* search_up(std::string &node_name , DT_Node<v>* temp) {
                
                if(temp->parent != NULL && temp->parent->name == node_name) {
                        return temp->parent;
                }
                else return NULL;

            }

            // o(1) --> o(children) : like "search_up" function , but this one for looking down between children
            DT_Node<v>* search_down(std::string &node_name , DT_Node<v>* temp) {
                
                for(int i = 0 ; i < temp->children.size() ; i += 1){
                    if(temp->children[i].name == node_name) 
                            return &temp->children[i];
                }

                return NULL;

            }

        public:

            // current_node => it's a node represent you position in tree
            // "important !" for many operation like search , movement , ...
            DT_Node<v> *current_node;

            // constructor
            DynamicTree(std::string root_name , v root_value) {
                // parent of root must be null
                root = DT_Node<v>( root_name , root_value , NULL ); 
                current_node = &root;
            }

            // destructor
            ~DynamicTree(){  }

            // o(1) --> o(children)
            // node_name : mean node where you want to go could be 'child' or 'parent' depend on "boolean up" 
            // also you can jump to the 'root' directly if you want
            bool move_to(std::string &node_name , bool up = false) {

                // in case you want to jump to the root directly
                if (node_name == "root") {

                    // if you already in root
                    if (current_node == &root) return false;

                    // otherwise => jumping to the root & return true
                    current_node = &root;
                    return true;
                }

                // in case you want to move up to the parent
                if( up ){

                    if (current_node->parent != NULL && node_name == current_node->parent->name){
                        current_node = current_node->parent;
                        return true;
                    }
                    // in case target 'not found !'
                    else return false;

                }
                // in case you want to move down to child
                else {

                    // loop over all & check
                    for (unsigned int i = 0; i < current_node->children.size(); i += 1) {
                        // if target found we move to it
                        if (current_node->children[i].name == node_name) {
                            current_node = &current_node->children[i];
                            return true;
                        }
                    }

                }

                // in case target 'not found'
                return false;
            }

            // o(path) --> o(childrens * path)
            // like move_to but this require a hole path of "names"
            // return will be a true if travel_to succeed to travel between all that nodes
            // note !! travel will be happen only if "the whole path" is valid , otherwise nothing will be happen
            bool travel_to(std::vector<std::string> &full_path , bool up = false){
                
                // temp only for check & testing if "the hole path" are valid or not
                // if it valid we make it current_position in the end "as last step" 
                DT_Node<v>* temp = current_node;

                // boolean up it's mean that "the hole path" in parents direction "up"
                if(up){

                    // we start looking up by using a private function "search_up"
                    for(std::string path : full_path){
                        temp = search_up(path , temp);
                        // in case not found "that's mean invalid path"
                        if(temp == NULL) return false;
                    }

                }
                // "up == false" mean that "the hole path" in children direction "down"
                else{

                    // we start looking down by using a private function "search_down"
                    for(std::string path : full_path){
                        temp = search_down(path , temp);
                        // in case not found "that's mean invalid path"
                        if(temp == NULL) return false;
                    }

                }

                // in case "the hole path" is valid 
                // last step => travel from "current_position" to "the temp node"
                current_node = temp;
                // and confirmation 
                return true;
            }

    };


}

#endif