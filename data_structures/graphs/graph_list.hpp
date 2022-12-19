#include <set>
#include <list>
#include <iostream>

#pragma once 

namespace graphs {
	
	template<typename T> class vertex {

		private:
			std::set< vertex<T>* > edges; // this vertex connection

		public:
			T value;

			vertex() {}

			vertex(T vertex_value) :value(vertex_value) { }

			vertex(T vertex_value , std::initializer_list< vertex<T>* > const& vertex_edges ) 
				:value(vertex_value) 
			{ 

				for (vertex<T> *& vertex : vertex_edges) {
					vertex->add_edge(this);
					this->edges
				}

			}

			~vertex() { }

			void add_edge(vertex<T> *& other_vertex);
			void delete_edge(vertex<T> *& other_vertex);

	};
	// end of class vertex


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

			void insert_vertex(type vertex_value);
			void insert_vertex(vertex<type> const& vertex_value);
			void insert_vertex(type& vertex_value, std::initializer_list< vertex<type>& > const& vertex_edges);
			void insert_edge(type const& vertex_a, type const& vertex_b); // to connect to vertex's 

			void delete_vertex(	type const& target_vertex);
			void delete_vertex(	size_t const& vertex_index);
			void delete_edge(type const& vertex_a, type const& vertex_b); // to delete connection between vertex's

			void bfs(); // search algorithm !
			void dfs(); // search algorithm !


			// for testing 
			void print();

	}; // end of class l_graph

	template<typename type> void l_graph<type>::insert_vertex(type vertex_value) {
		
		this->graph.insert(vertex<type>(vertex_value));

	}

	template<typename type> void l_graph<type>::print() {

		for (vertex<type> *& vertex : this->graph) {
			std::cout << vertex.value << "\n";
		}

	}

} // end of namespace graphs