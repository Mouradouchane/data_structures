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
		std::vector< std::string > edges; // connection to other vertices
		std::string name = "";

	public:
		T value;

		// constructor 1
		Vertex() { }

		// constructor 2
		Vertex(
			std::string vertex_name , T vertex_value,
			std::vector< std::string > const& vertex_edges = {}
		) 
			:name(vertex_name), value(vertex_value) {

			// copy edges
			for ( std::string edge : vertex_edges ) {
				this->edges.push_back(edge);
			}

			Vertex<T>::sort_process(*this);

		}

		// destructor
		~Vertex() { }


		/*
			-------------- vertex public methods--------------
		*/ 

		static void search_process(
			Vertex<T> const& vertex , std::string const& target_name , 
			int &catch_index , bool &catch_check , int l , int r
		);
		static void sort_process( Vertex<T> & vertex );


		std::string get_name() {
			return this->name;
		}

		//Vertex<T>* go_to(size_t const& vertex_index);
		//Vertex<T>* go_to(std::string const& vertex_name);

		bool add_edge( std::string other_vertex );

		bool remove_edge( std::string const& other_vertex_name );

		size_t size() {
			return this->edges.size();
		}

		// testing function
		void print() {
			std::cout << this->name << " : ";

			for (std::string & vptr : this->edges) {
				std::cout << vptr << ", ";
			}

			std::cout << " ;\n";
		}

		/*
			-------------- operators -------------- 
		*/

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


	/*

		---------- Vertex functions implementation ----------

	*/

	// search for edge connection in edges of vertex
	template<typename T> void Vertex<T>::search_process(
		Vertex<T> const& vertex, std::string const& target_name,
		int& catch_index, bool& catch_check, int l, int r
	) {

		// calc mid index
		int mid = (l + r) / 2;

		// if target not found
		if (l > r) {
			catch_check = false;
			catch_index = -1;
			return;
		}

		std::string v_name = vertex.edges[mid];

		// if target found
		if (v_name == target_name) {
			catch_check = true;
			catch_index = mid;
			return;
		}

		// compare 
		if (v_name > target_name) {
			// go left
			Vertex<T>::search_process(vertex, target_name, catch_index, catch_check, l, mid - 1);
		}
		else {
			// go right
			Vertex<T>::search_process(vertex, target_name, catch_index, catch_check, mid + 1, r);
		}


	}

	// sort edges of vertex
	template<typename T> void Vertex<T>::sort_process(Vertex<T>& vertex) {

		std::sort(
			vertex.edges.begin(), vertex.edges.end(),
			[&](std::string & a, std::string & b) -> bool {
				return (a < b);
			}
		);

	}
	
	// add edge connection to vertex
	template<typename T> bool Vertex<T>::add_edge(std::string other_vertex) {

		bool check = false;
		int index = -1;

		Vertex<T>::search_process(*this, other_vertex, index, check, 0, this->edges.size() - 1);

		// if edge already exist
		if ( index != -1 ) return false;
		else {

			this->edges.push_back(other_vertex);

			Vertex<T>::sort_process(*this);

			return true;

		}

	}






	template<typename t> class graph_list {

	private:
		std::vector< Vertex<t> > vertices;

		// graph private methods
		
		void bin_search_process(

			std::string const& vertex_name , 
			bool & result, 
			int  & catch_target_index, 
			int  l, // left  index
			int  r  // right index

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

		// basically quick sort 
		void sort() {

			std::sort(this->vertices.begin(), this->vertices.end(),
				[&](Vertex<t>& a, Vertex<t>& b) -> bool {
					return (a < b);
				}
			);

		};

	public:

		Vertex<t>* vertex = nullptr; // current vertex you in

		// constructor 1
		graph_list() { }

		// constructor 2
		graph_list(std::initializer_list< Vertex<t> > const& graph_vertices) {

			int check = -1;

			// copy vertices to the graph , 'NOTE' we copying only name & value , "no edges"
			for (Vertex<t> vtx : graph_vertices) {

				// check to avoid duplicates
				check = this->search(vtx.get_name());

				if (check == -1) {
					this->vertices.push_back( Vertex<t>( vtx.get_name() , vtx.value ) );
					this->sort();
				}

				check = -1;
			}
			// keep track vertex
			this->vertex = &(this->vertices[0]);

		}

		// destructor 
		~graph_list(){ 
		
			this->vertex = nullptr;

		}

		/*
			graph public methods
		*/

		void print() {

			for (Vertex<t>& v : this->vertices) {
				v.print();
			}

		}

		bool add_vertex(
			std::string vertex_name , t vertex_value , std::initializer_list<size_t> const& edges_indexes
		);
		bool add_vertex(
			std::string vertex_name , t vertex_value , std::initializer_list<std::string> const& edges_names
		);
		bool add_vertex( std::string vertex_name, t vertex_value );

		bool add_edge(size_t const& vertex_a_index, size_t const& vertex_b_index);
		bool add_edge(std::string const& vertex_a_name, std::string const& vertex_b_name);

		bool remove_vertex(size_t const& vertex_index);
		bool remove_vertex(std::string const& vertex_name);

		bool remove_edge(size_t const& vertex_a_index, size_t const& vertex_b_index);
		bool remove_edge(std::string const& vertex_a_name, std::string const& vertex_b_name);

		int search(std::string const& vertex_name);
		int search(Vertex<t> & target_vertex);

		bool is_connected(size_t const& vertex_a_index, size_t const& vertex_b_index);
		bool is_connected(std::string const& vertex_a_name , std::string const& vertex_b_name);

	}; 
	// end of graph_list class
	


	/*

		---------- graph_list functions implementation ----------

	*/

	template<typename t> bool graph_list<t>::add_vertex( std::string vertex_name , t vertex_value ) {

		// check if there's a vertex with same name
		int index = this->search(vertex_name);
 
		if (index == -1) {

			/*
				we don't want to lose "vertex" where we are in , 
				so we get it's name to catch it later after "push_back" and "sort"
			*/ 
			std::string current_vertex_name = this->vertex->get_name();

			// push and sort
			this->vertices.push_back( Vertex<t>( vertex_name , vertex_value ) );
			this->sort();

			// catch "vertex" after sort
			index = this->search(current_vertex_name);
			this->vertex = &(this->vertices[index]);

			return true;
		}
		else return false;

	}

	template<typename t> bool graph_list<t>::add_vertex(
		std::string vertex_name , t vertex_value , std::initializer_list<size_t> const& edges_indexes
	) {

		// check if there's a vertex with same name
		int index = this->search(vertex_name);

		if (index == -1) {

			/*
				we don't want to lose "vertex" where we are in ,
				so we get it's name to catch it later after "push_back" and "sort"
			*/
			std::string current_vertex_name = this->vertex->get_name();

			// push and sort
			this->vertices.push_back(Vertex<t>(vertex_name, vertex_value));
			this->sort();


			// add edges process 
			int vertices_size = this->vertices.size();
			int added_vertex_index = this->search(vertex_name);

			for (size_t const& index : edges_indexes) {

				if (index >= vertices_size) continue;
				else {

					this->add_edge( index , added_vertex_index );

				}

			}

			// catch "vertex" after sort
			index = this->search(current_vertex_name);
			this->vertex = &(this->vertices[index]);

			return true;
		}
		else return false;

	}

	template<typename t> bool graph_list<t>::add_vertex(
		std::string vertex_name, t vertex_value, std::initializer_list<std::string> const& edges_names
	) {

		// check if there's a vertex with same name
		int index = this->search(vertex_name);

		if (index == -1) {

			/*
				we don't want to lose "vertex" where we are in ,
				so we get it's name to catch it later after "push_back" and "sort"
			*/
			std::string current_vertex_name = this->vertex->get_name();

			// push and sort
			this->vertices.push_back( Vertex<t>(vertex_name, vertex_value) );
			this->sort();

			// add edges process 
			for (std::string const& name : edges_names) {

				this->add_edge(name, vertex_name);

			}

			// catch "vertex" after sort
			index = this->search(current_vertex_name);
			this->vertex = &(this->vertices[index]);

			return true;
		}
		else return false;

	}

	// search functions
	template<typename t> int graph_list<t>::search(std::string const& vertex_name) {

		bool rslt = false;
		int index = -1;

		this->bin_search_process(vertex_name, rslt, index, 0, this->vertices.size() - 1);

		return index;
	}

	template<typename t> int graph_list<t>::search( Vertex<t> & target_vertex ) {

		bool rslt = false;
		int index = -1;

		this->bin_search_process( target_vertex.get_name(), rslt, index, 0, this->vertices.size() - 1);

		return index;
	}


	// add edge functions
	template<typename t> bool graph_list<t>::add_edge(size_t const& vertex_a_index, size_t const& vertex_b_index) {

		// if invalid index
		if (vertex_a_index == vertex_b_index) return false;
		if (vertex_a_index >= this->vertices.size() || vertex_b_index >= this->vertices.size()) {
			return false;
		}
		else {

			std::string vertex_a = (this->vertices[vertex_a_index].get_name());
			std::string vertex_b = (this->vertices[vertex_b_index].get_name());

			bool connect_a = this->vertices[vertex_a_index].add_edge( vertex_b );
			bool connect_b = this->vertices[vertex_b_index].add_edge( vertex_a );

			return (connect_a && connect_b);
		}

	}
	
	template<typename t> bool graph_list<t>::add_edge(
		std::string const& vertex_a_name, std::string const& vertex_b_name
	) {

		// if invalid index
		if (vertex_a_name == vertex_b_name) return false;
		else {
			
			// get index's of a & b
			int vertex_a_index = this->search(vertex_a_name);
			int vertex_b_index = this->search(vertex_b_name);

			// if a or b not found
			if (vertex_a_index == -1 || vertex_b_index == -1) return false;

			bool connect_a = this->vertices[vertex_a_index].add_edge(vertex_b_name);
			bool connect_b = this->vertices[vertex_b_index].add_edge(vertex_a_name);

			return (connect_a && connect_b);
		}

	}


	// is connected functions
	template<typename t> bool graph_list<t>::is_connected(size_t const& vertex_a_index, size_t const& vertex_b_index) {

		// if invalid args
		if (vertex_a_index == vertex_b_index) return false;
		if (vertex_a_index >= this->vertices.size() || vertex_b_index >= this->vertices.size()) return false;

		int  catch_index = -1;
		bool catch_check = false;

		// search on vertex_a for veretx_b
		Vertex<t>::search_process(
			this->vertices[vertex_a_index] , this->vertices[vertex_b_index].get_name() , 
			catch_index , catch_check , 0 , this->vertices[vertex_a_index].size() - 1
		);

		// if a not connected with b
		if ( !catch_check ) return false;
		else {

			catch_index = -1;
			catch_check = false;

			// search on vertex_b for veretx_a
			Vertex<t>::search_process(
				this->vertices[vertex_b_index], this->vertices[vertex_a_index].get_name(),
				catch_index, catch_check, 0, this->vertices[vertex_b_index].size() - 1
			);

			// if b not connected with a
			if (!catch_check) return false;
			else return true;

		}

	}

	template<typename t> bool graph_list<t>::is_connected(std::string const& vertex_a_name, std::string const& vertex_b_name) {

		int vertex_a_index = this->search(vertex_a_name);
		int vertex_b_index = this->search(vertex_b_name);

		// if invalid args
		if (vertex_a_index == vertex_b_index) return false;
		if (vertex_a_index >= this->vertices.size() || vertex_b_index >= this->vertices.size()) return false;

		int  catch_index = -1;
		bool catch_check = false;

		// search on vertex_a for veretx_b
		Vertex<t>::search_process(
			this->vertices[vertex_a_index], vertex_b_name ,
			catch_index, catch_check, 0, this->vertices[vertex_a_index].size() - 1
		);

		// if a not connected with b
		if (!catch_check) return false;
		else {

			catch_index = -1;
			catch_check = false;

			// search on vertex_b for veretx_a
			Vertex<t>::search_process(
				this->vertices[vertex_b_index], vertex_a_name ,
				catch_index, catch_check, 0, this->vertices[vertex_b_index].size() - 1
			);

			// if b not connected with a
			if (!catch_check) return false;
			else return true;

		}

	}

} // end of namespace graphs 

