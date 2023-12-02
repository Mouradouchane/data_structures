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

		/*
			-------------- vertex private methods --------------
		*/
		bool remove_edge(std::string const& edge_name);
		bool remove_edge(size_t const& edge_index);
		void remove_all_edges();


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
			-------------- vertex public methods --------------
		*/ 

		static void search_process(
			Vertex<T> const& vertex , std::string const& target_name , 
			int &catch_index , bool &catch_check , int l , int r
		);
		static void sort_process( Vertex<T> & vertex );
		std::string get_name() {
			return this->name;
		}
		size_t size() {
			return this->edges.size();
		}
		bool add_edge( std::string other_vertex );

		// Vertex<T>* go_to(size_t const& vertex_index);
		// Vertex<T>* go_to(std::string const& vertex_name);

		// testing function
		void print();

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

		// give access to graph_list;
		template<typename T> friend class graph_list;

}; 
// end of vertex class


	/*

		---------- Vertex functions implementation ----------

	*/

	template<typename T> void Vertex<T>::print() {
		std::cout << this->name << " : ";

		for (std::string& vptr : this->edges) {
			std::cout << vptr << ", ";
		}

		std::cout << " ;\n";
	}

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

	// remove edge's functions
	template<typename T> bool Vertex<T>::remove_edge(std::string const& edge_name) {

		int  catch_index = -1;
		bool catch_check = false;

		// search for edge index
		Vertex<T>::search_process(*this, edge_name, catch_index, catch_check, 0, this->edges.size() - 1);

		// if invalid
		if (catch_index == -1) return false;
		else {
			// earse and sort edges
			this->edges.erase(this->edges.begin() + catch_index);
			Vertex<T>::sort_process(*this);

			return true;
		}
	}

	template<typename T> bool Vertex<T>::remove_edge(size_t const& edge_index) {

		// if invalid index
		if (edge_index >= this->edges.size()) return false;
		else {

			this->edges.erase(this->edges.begin() + edge_index);
			Vertex<T>::sort_process(*this);

			return true;
		}

	}

	// remove all edges
	template<typename T> void Vertex<T>::remove_all_edges() {
		this->edges.clear();
	}




template<typename t> class graph_list {

	private:
		std::vector< Vertex<t> > vertices;

		// graph private methods
		void sort_process();
		void search_process( std::string const& vertex_name, bool& result, int& catch_target_index, int l, int r);

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
				check = this->index_of(vtx.get_name());

				if (check == -1) {
					this->vertices.push_back( Vertex<t>( vtx.get_name() , vtx.value ) );
					this->sort_process();
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
		bool remove_all_edges(size_t const& vertex_index);
		bool remove_all_edges(std::string const& vertex_name);

		int index_of(std::string const& vertex_name);
		int index_of(Vertex<t> & target_vertex);

		bool is_connected(size_t const& vertex_a_index, size_t const& vertex_b_index);
		bool is_connected(std::string const& vertex_a_name , std::string const& vertex_b_name);

}; 
// end of graph_list class
	


	/*

		---------- graph_list functions implementation ----------

	*/
	
	// binary search
	template<typename t> void graph_list<t>::search_process(
		std::string const& vertex_name, 
		bool& result, int& catch_target_index,
		int l, int r // left and right index's
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
		if (this->vertices[mid].get_name() == vertex_name) {
			result = true;
			catch_target_index = mid;
			return;
		}

		// compare 
		if (this->vertices[mid] > vertex_name) {
			// go left
			this->search_process(vertex_name, result, catch_target_index, l, mid - 1);
		}
		else {
			// go right
			this->search_process(vertex_name, result, catch_target_index, mid + 1, r);
		}

	}

	// quick sort 
	template<typename t> void graph_list<t>::sort_process() {

		std::sort(this->vertices.begin(), this->vertices.end(),
			[&](Vertex<t>& a, Vertex<t>& b) -> bool {
				return (a < b);
			}
		);

	};

	// add vertex functions
	template<typename t> bool graph_list<t>::add_vertex( std::string vertex_name , t vertex_value ) {

		// check if there's a vertex with same name
		int index = this->index_of(vertex_name);
 
		if (index == -1) {

			/*
				we don't want to lose "vertex" where we are in , 
				so we get it's name to catch it later after "push_back" and "sort"
			*/ 
			std::string current_vertex_name = this->vertex->get_name();

			// push and sort
			this->vertices.push_back( Vertex<t>( vertex_name , vertex_value ) );
			this->sort_process();

			// catch "vertex" after sort
			index = this->index_of(current_vertex_name);
			this->vertex = &(this->vertices[index]);

			return true;
		}
		else return false;

	}

	template<typename t> bool graph_list<t>::add_vertex(
		std::string vertex_name , t vertex_value , std::initializer_list<size_t> const& edges_indexes
	) {

		// check if there's a vertex with same name
		int index = this->index_of(vertex_name);

		if (index == -1) {

			/*
				we don't want to lose "vertex" where we are in ,
				so we get it's name to catch it later after "push_back" and "sort"
			*/
			std::string current_vertex_name = this->vertex->get_name();

			// push and sort
			this->vertices.push_back(Vertex<t>(vertex_name, vertex_value));
			this->sort_process();


			// add edges process 
			int vertices_size = this->vertices.size();
			int added_vertex_index = this->index_of(vertex_name);

			for (size_t const& index : edges_indexes) {

				if (index >= vertices_size) continue;
				else {

					this->add_edge( index , added_vertex_index );

				}

			}

			// catch "vertex" after sort
			index = this->index_of(current_vertex_name);
			this->vertex = &(this->vertices[index]);

			return true;
		}
		else return false;

	}

	template<typename t> bool graph_list<t>::add_vertex(
		std::string vertex_name, t vertex_value, std::initializer_list<std::string> const& edges_names
	) {

		// check if there's a vertex with same name
		int index = this->index_of(vertex_name);

		if (index == -1) {

			/*
				we don't want to lose "vertex" where we are in ,
				so we get it's name to catch it later after "push_back" and "sort"
			*/
			std::string current_vertex_name = this->vertex->get_name();

			// push and sort
			this->vertices.push_back( Vertex<t>(vertex_name, vertex_value) );
			this->sort_process();

			// add edges process 
			for (std::string const& name : edges_names) {

				this->add_edge(name, vertex_name);

			}

			// catch "vertex" after sort
			index = this->index_of(current_vertex_name);
			this->vertex = &(this->vertices[index]);

			return true;
		}
		else return false;

	}


	// remove vertex functions
	template<typename t> bool graph_list<t>::remove_vertex(size_t const& vertex_index) {
		
		if ( vertex_index >= this->vertices.size() ) return false;
		else {

			// to keep track current vertex after sort
			std::string current_vertex_name = this->vertex->get_name();

			// remove process

			this->remove_all_edges( vertex_index );
			this->vertices.erase(this->vertices.begin() + vertex_index);
		
			this->sort_process();

			// get current vertex new position
			int current_vertex_index = this->index_of(current_vertex_name);
			this->vertex = &(this->vertices[ (current_vertex_index == -1) ? 0 : current_vertex_index ]);

			return true;
		}

	}

	template<typename t> bool graph_list<t>::remove_vertex(std::string const& vertex_name) {
		
		int vertex_index = this->index_of(vertex_name);

		if (vertex_index == -1 || vertex_index >= this->vertices.size()) return false;
		else {

			// to keep track current vertex after sort
			std::string current_vertex_name = this->vertex->get_name();

			// remove process

			this->remove_all_edges(vertex_index);
			this->vertices.erase(this->vertices.begin() + vertex_index);

			this->sort_process();

			// get current vertex new position
			int current_vertex_index = this->index_of(current_vertex_name);
			this->vertex = &(this->vertices[(current_vertex_index == -1) ? 0 : current_vertex_index]);

			return true;
		}

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
			int vertex_a_index = this->index_of(vertex_a_name);
			int vertex_b_index = this->index_of(vertex_b_name);

			// if a or b not found
			if (vertex_a_index == -1 || vertex_b_index == -1) return false;

			bool connect_a = this->vertices[vertex_a_index].add_edge(vertex_b_name);
			bool connect_b = this->vertices[vertex_b_index].add_edge(vertex_a_name);

			return (connect_a && connect_b);
		}

	}



	// remove edge functions
	template<typename t> bool graph_list<t>::remove_edge(
		size_t const& vertex_a_index , size_t const& vertex_b_index
	) {
		
		// check if index invalid
		if (vertex_a_index == vertex_b_index) return false;
		if (vertex_a_index >= this->vertices.size() || vertex_b_index >= this->vertices.size()) return false;
		else {

			// remove edges process
			bool check_remove_1 = this->vertices[vertex_a_index].remove_edge( this->vertices[vertex_b_index].get_name() );
			bool check_remove_2 = this->vertices[vertex_b_index].remove_edge( this->vertices[vertex_a_index].get_name() );

			return (check_remove_1 && check_remove_2);
		}
		
	}

	template<typename t> bool graph_list<t>::remove_edge(
		std::string const& vertex_a_name , std::string const& vertex_b_name
	) {

		if (vertex_a_name == vertex_b_name) return false;

		// search and check for vertex "a" and "b"
		int index_a = this->index_of(vertex_a_name);
		if (index_a == -1) return false;

		int index_b = this->index_of(vertex_b_name);
		if (index_b == -1) return false;

		if (index_a >= this->vertices.size() || index_b >= this->vertices.size()) return false;
		else {

			// remove edge process
			bool check_remove_1 = this->vertices[index_a].remove_edge(vertex_b_name);
			bool check_remove_2 = this->vertices[index_b].remove_edge(vertex_a_name);

			return (check_remove_1 && check_remove_2);
		}

	}

	template<typename t> bool graph_list<t>::remove_all_edges(size_t const& vertex_index) {
		
		// check index
		if ( vertex_index == -1 || vertex_index >= this->vertices.size() ) return false;
		else {

			// remove edges from other vertices
			int edge_index = -1;
			for (std::string& edge_name : this->vertices[vertex_index].edges) {

				edge_index = this->index_of(edge_name);
				this->vertices[edge_index].remove_edge( this->vertices[vertex_index].get_name() );

			}

			this->vertices[vertex_index].remove_all_edges();

			return true;
		}

	}

	template<typename t> bool graph_list<t>::remove_all_edges(std::string const& vertex_name) {
		
		// search of vertex
		int vertex_index = this->index_of(vertex_name);

		if (vertex_index == -1) return false;
		else {

			// remove edges from other vertices
			int edge_index = -1;
			for ( std::string & edge_name : this->vertices[vertex_index].edges ) {

				edge_index = this->index_of(edge_name);
				this->vertices[edge_index].remove_edge(vertex_name);

			}

			this->vertices[vertex_index].remove_all_edges();

			return true;
		}

	}

	// search functions
	template<typename t> int graph_list<t>::index_of(std::string const& vertex_name) {

		bool rslt = false;
		int index = -1;

		this->search_process(vertex_name, rslt, index, 0, this->vertices.size() - 1);

		return index;
	}

	template<typename t> int graph_list<t>::index_of(Vertex<t>& target_vertex) {

		bool rslt = false;
		int index = -1;

		this->search_process(target_vertex.get_name(), rslt, index, 0, this->vertices.size() - 1);

		return index;
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

		int vertex_a_index = this->index_of(vertex_a_name);
		int vertex_b_index = this->index_of(vertex_b_name);

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

