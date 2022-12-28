#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <algorithm>

#pragma once 

namespace graphs {

	template<typename T> class Vertex {

	private:
		std::vector< Vertex<T>* > edges;
		std::string name = "";

	public:
		T value;

		Vertex() { }

		Vertex(
			std::string vertex_name , T vertex_value,
			std::vector< Vertex<T>* > const& vertex_edges = {}
		) 
			:name(vertex_name), value(vertex_value) {

			// copy edges
			for (Vertex<T>* edge : vertex_edges) {
				this->edges.push_back(edge);
			}

		}


		~Vertex() { }

		void print() {
			std::cout << this->name << " : ";

			for (Vertex<T>*& vptr : this->edges) {
				std::cout << vptr->name << ", ";
			}

			std::cout << " ;\n";
		}

		// getters
		std::string get_name() {
			return this->name;
		}

		// vertex public methods 
		Vertex<T>* go_to(size_t const& vertex_index);
		Vertex<T>* go_to(std::string const& vertex_name);

		// operators
		bool operator < ( Vertex<T> const& other ) {
			return (this->name < other.name);
		}
		bool operator < ( Vertex<T>* other_vertex ) {
			return ( this->name < other_vertex->name );
		}

		bool operator > (Vertex<T> const& other) {
			return (this->name > other.name);
		}
		bool operator > (Vertex<T>* other_vertex) {
			return (this->name > other_vertex->name);
		}

		bool operator == (Vertex<T> const& other) {
			return (this->name == other.name);
		}
		bool operator == (Vertex<T>* other_vertex) {
			return (this->name == other_vertex->name);
		}

	}; 
	// end of vertex class

	template<typename t> class graph_list {

	private:
		std::vector< Vertex<t> > vertices;

	public:

		Vertex<t>* vertex = nullptr; // current vertex you in

		graph_list() { }


		graph_list(std::initializer_list< Vertex<t> > const& graph_vertices) {

			// copy vertices to the graph
			for (Vertex<t> vtx : graph_vertices) {
				this->vertices.push_back(vtx);
			}

			std::sort(
				this->vertices.begin(), this->vertices.end(), 
				[&]( Vertex<t> a , Vertex<t> b) -> bool {
					return (a.get_name() < b.get_name()) ? true : false ;
				}
			);

		}

		void print() {

			for (Vertex<t>& v : this->vertices) {
				v.print();	
			}

		}
		/*
			graph public methods
		*/

		bool add_vertex(
			std::string vertex_name,
			t vertex_value,
			std::initializer_list<size_t> const& edges_indexes = {}
		);

		bool add_vertex(
			std::string vertex_name,
			t vertex_value,
			std::initializer_list< Vertex<t>* > const& edges_pointers = {}
		);

		bool add_vertex( Vertex<t> new_vertex );

		bool add_edge(size_t const& vertex_a_index, size_t const& vertex_b_index);
		bool add_edge(std::string const& vertex_a_name, std::string const& vertex_b_name);

		bool remove_vertex(size_t const& vertex_index);
		bool remove_vertex(std::string const& vertex_name);

		bool remove_edge(size_t const& vertex_a_index, size_t const& vertex_b_index);
		bool remove_edge(std::string const& vertex_a_name, std::string const& vertex_b_name);

		int search_by_name(std::string const& vertex_name);

		//bool is_connected( const vertex<t> &* vertex_a, const vertex<t> &* vertex_b);
		bool is_connected(size_t const& vertex_a_index, size_t const& vertex_b_index);

	}; 
	// end of graph_list class
	
	
	template<typename t> bool graph_list<t>::add_vertex( Vertex<t> new_vertex ) {

		bool check = std::binary_search(this->vertices.begin(), this->vertices.end(),
			new_vertex
			/*
			,
			[&](Vertex<t> target_vertex) -> bool {
				return (target_vertex.get_name() == new_vertex.get_name());
			}
			*/
		);
	
		if ( !check ) return false;
		else {

			this->vertices.push_back(new_vertex);

			std::sort(
				this->vertices.begin(), this->vertices.end(),
				[&](Vertex<t> a, Vertex<t> b) -> bool {
					return (a.get_name() < b.get_name());
				}
			);

			return true;
		}

	}

} // end of namespace graphs 

