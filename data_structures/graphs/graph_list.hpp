#include <set>
#include <list>
#include <iostream>

#pragma once 

namespace graphs {
	
	namespace {

		template<typename T> class vertex {

			private:
				T value;
				std::set< vertex<T>* > edges; // represent the conncetion to other nodes

			public:
				vertex() {}

				vertex(T node_value) :value(node_value) { }

				~vertex() {}

		};
		// end of class node


	};
	// end of anonymouse namespace


	/*
		- graph based on list
		- undirected graph
		- dynamic graph
	*/
	template<typename type> class l_graph {

		private :
			std::set< vertex<type> > graph;

		public :

			// constructor's

			l_graph() { }

			l_graph( std::initializer_list<type> const& values ) {
			
				// copy process
				for (type value : values) {
					this->graph.insert( vertex<type>(value) );
				}

			}

			~l_graph(){}


			// graph method's

			void insert_vertex(type& new_vertex_value);
			void insert(type& new_vertex_value, std::initializer_list<vertex<type>*> const& new_vertex_edges);

			void delete_vertex(	type const& target_vertex);
			void delete_vertex(	size_t const& vertex_index);

			void insert_edge(type const& vertex_a, type const& vertex_b); // to connect to vertex's 

			void delete_edge(type const& vertex_a, type const& vertex_b); // to delete connection between vertex's

			void bfs(); // search algorithm !
			void dfs(); // search algorithm !




	}; // end of class l_graph


} // end of namespace graphs