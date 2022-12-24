#include <iostream>
#include <set>
#include <list>
#include <string>
#include <functional>

#pragma once 

namespace graphs {
	
	// template<typename type> class l_graph;

	template<typename T> class vertex {

		private:
			std::set< vertex<T>& > edges; // this vertex connection

		public:
			std::string name;
			T value;

			// def constructor
			vertex() {}

			// constructor 1
			vertex(std::string vertex_name, T vertex_value)
				: name(vertex_name) , value(vertex_value)
			{

			}

			// constructor 2
			vertex(T vertex_value) : value(vertex_value) { }

			// constructor 3
			vertex(T vertex_value , std::initializer_list< vertex<T>& > const& vertex_edges ) 
				: value(vertex_value) 
			{ 

				for (vertex<T> & other : vertex_edges) {
					this->edges.insert(other);
					other.edges.insert(*this);
				}

			}

			// constructor 4
			vertex(std::string vertex_name, T vertex_value, std::initializer_list< vertex<T>& > const& vertex_edges)
				: name(vertex_name) , value(vertex_value)
			{

				for (vertex<T>& other : vertex_edges) {
					this->edges.insert(other);
					other.edges.insert(*this);
				}

			}

			// destructor 
			~vertex() { }

			template<typename T> friend class l_graph;
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

			//bool (* compare_function)(type const& vertex_a_value, type const& vertex_b_value);
			std::function< bool(type const& a, type const& b) > cp;

		public :

			// constructor's

			l_graph( 
				//bool (* comparison_function)(type const& vertex_a_value, type const& vertex_b_value) 
				std::function< bool(type const& a, type const& b) > comparison_function
			)
				//:compare_function(comparison_function)
			{ 
				this->cp = comparison_function;
			}

			l_graph( std::initializer_list<type> const& values ) {
			
				// copy process
				for (type value : values) {
					this->graph.insert( vertex<type>(value) );
				}

			}

			~l_graph(){}


			// graph method's

			void add_vertex(type vertex_value);
			void add_vertex(std::string vertex_name , type vertex_value);
			void add_vertex(vertex<type> const& vertex_value);
			void add_vertex(type& vertex_value, std::initializer_list< vertex<type>& > const& vertex_edges);
			void add_edge(type const& vertex_a, type const& vertex_b); // to connect to vertex's 

			void delete_vertex(	type const& target_vertex);
			void delete_vertex(	size_t const& vertex_index);
			void delete_edge(type const& vertex_a, type const& vertex_b); // to delete connection between vertex's

			void bfs(); // search algorithm !
			void dfs(); // search algorithm !

			// for testing 
			void print();

	}; // end of class l_graph

	 template<typename type> void l_graph<type>::add_vertex(type vertex_value) {
		
		this->graph.insert( vertex<type>(vertex_value) );

	}

	template<typename type> void l_graph<type>::print() {

		for (vertex<type> & vertex : this->graph) {
			std::cout << vertex.name << " : " << vertex.value  << ":: [";
			/*
			for ( vertex<T>& edge : vertex.edges)  {
				std::cout << edge.value << " , ";
			}
			*/

			std::cout << "]\n";
		}

	}

} // end of namespace graphs