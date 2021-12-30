#include <vector>

#pragma once

namespace trees{
    
    // =======================================
    // ======= Binary tree Nodes Class =======
    // =======================================
    template<typename type> class BT_Node{
	  private:
		unsigned int parent;  // parent     "index"
            unsigned int left  ;  // left node  "index"
           	unsigned int right ;  // right node "index"
        public:
            type value;              // node value

            // default constructor
            BT_Node(type node_value){ 
			value = node_value;
		}

            // destructor
            ~BT_Node(){ }
 
    };


	template<typename t> class BinaryTree{
	
		private:
			// all nodes in should be here in this vector
			std::vector<t> nodes;
	
		public:
			BinaryTree(t root_value){
				nodes[0] = root_value;

			}

			~BinaryTree(){ }
	};

};
