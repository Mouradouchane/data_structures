#include <set>
#include <list>
#include <iostream>

#pragma once 

namespace graphs {
	
	template<typename T> class graph_node{

		private : 
			T value; 
			std::list<graph_node*> edges; // represent the conncetion to other nodes

	public : 
		graph_node() {}

		graph_node( T node_value ) :value(node_value) { }

		~graph_node() {}
	};
	

	template<typename type> class graph_list {

		private :
			std::set<graph_node> nodes;

		public :

			graph_list() { }

			graph_list( std::initializer_list<type> const& values ) { 
			
				// copy process
				for (type value : values) {
					this->nodes.insert( graph_node<type>(value) );
				}

			}

			~graph_list(){}

	}; // end of class graph_lish


} // end of namespace graphs