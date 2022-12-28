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
		bool operator < ( std::string const& other_vertex_name ) {
			return (this->name < other_vertex_name);
		}

		bool operator > (Vertex<T> const& other) {
			return (this->name > other.name);
		}
		bool operator > (Vertex<T>* other_vertex) {
			return (this->name > other_vertex->name);
		}
		bool operator > (std::string const& other_vertex_name) {
			return (this->name > other_vertex_name);
		}

		bool operator == (Vertex<T> const& other) {
			return (this->name == other.name);
		}
		bool operator == (Vertex<T>* other_vertex) {
			return (this->name == other_vertex->name);
		}
		bool operator == (std::string const& other_vertex_name) {
			return (this->name == other_vertex_name);
		}

	}; 
	// end of vertex class




	template<typename t> class graph_list {

	private:
		std::vector< Vertex<t> > vertices;

		// privet methods
		
		void bin_search_process(

			std::string const& vertex_name , 
			bool & result, 
			int  & catch_target_index, 
			int  l, // left  index
			int  r // right index

		) {
			// calc mid index
			int mid = (l + r) / 2;

			// if target not found
			if (l > r) {
				result = false;
				catch_target_index = -1;
				return;
			}

			// if target found
			if ( this->vertices[mid].get_name() == vertex_name) {
				result = true;
				catch_target_index = mid;
				return;
			}

			// compare 
			if (this->vertices[mid] > vertex_name) {
				// go left
				this->bin_search_process(vertex_name, result, catch_target_index, l, mid - 1);
			}
			else {
				// go right
				this->bin_search_process(vertex_name, result, catch_target_index, mid + 1, r);
			}

		}

		void sort(); // quick sort

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

		int search(std::string const& vertex_name);
		int search(Vertex<t> const& target_verter);

		//bool is_connected( const vertex<t> &* vertex_a, const vertex<t> &* vertex_b);
		bool is_connected(size_t const& vertex_a_index, size_t const& vertex_b_index);

	}; 
	// end of graph_list class
	
	
	template<typename t> bool graph_list<t>::add_vertex( Vertex<t> new_vertex ) {

		int index = this->search( new_vertex.get_name() );
		
	
		if ( index < 0 ) return false;
		else {

			this->vertices.push_back(new_vertex);
			
			return true;
		}

	}

	template<typename t> int graph_list<t>::search(std::string const& vertex_name) {

		bool rslt = false;
		int index = -1;

		this->bin_search_process(vertex_name, rslt, index, 0, this->vertices.size() - 1);

		return index;
	}

} // end of namespace graphs 

