#include <iostream>
#include <set>
#include <list>
#include <string>
#include <functional>

#pragma once 


namespace graphs {

template<typename t> class vertex{

	private:
		std::set< vertex<t>* > edges;	
		std::string name = "";

	public :
		t value;

	vertex(){ }

	vertex(

		std::string vertex_name , 
		t vertex_value , 
		std::set<vertex<t>*> const& vertex_edges = {}

	)	:name(vertex_name), value(vertex_value) {

		// copy edges
		for( vertex<t>* edge : vertex_edges ) {
			this->edges.insert( edge );			
		}

	}


	~vertex(){ }

	// getters
	std::string get_name();

	vertex<t>* go_to( size_t const& vertex_index );
	vertex<t>* go_to( std::string const& vertex_name );

} // end of class vertex



template<typename t> class l_graph{

	private :
		std::set< vertex<t> > graph; // graph vertices

	public :

		vertex<t> * vertex = nullptr;

		l_graph(){ }

		l_graph(std::set< vertex<t> > const& vertices = {} ) {

			// copy vertices to the graph
			for( vertex<t> vertex : vertices ) {
				this->graph.insert( vertex );
			}

		}	

	bool add_vertex( 
		std::string vertex_name , 
		t vertex_value , 
		std::set<size_t> const& edges_indexes = {} 
	);

	bool add_vertex( 
		std::string vertex_name , 
		t vertex_value , 
		std::set< vertex<t>* > const& edges_pointers = {} 
	);

	bool add_edge( size_t const& vertex_a_index , size_t const& vertex_b_index );
	bool add_edge( std::string const& vertex_a_name , std::string const& vertex_b_name);

	bool remove_vertex( size_t const& vertex_index );
	bool remove_vertex( std::string const& vertex_name );

	bool remove_edge( size_t const& vertex_a_index , size_t const& vertex_b_index );
	bool remove_edge( std::string const& vertex_a_name , std::string const& vertex_b_name );

	int search_by_name( std::string const& vertex_name );

	bool is_connected( vertex<t>* const& vertex_a , vertex<t>* const& vertex_b );
	bool is_connected( size_t const& vertex_a_index , size_t const& vertex_b_index );


} // end of class l_graph 


} // end of namespace graphs 


