#pragma once

namespace trees{
    
    // =================================
    // ======= Binary tree Class =======
    // =================================
    template<typename v> class binary_node{
        public:
            binary_node * left; // left node
            binary_node * right; // right node
            v value; // node value

            // default constructor
            binary_node(){ }
            // second constructor
            binary_node(v value):value(value){ }

            // destructor
            ~binary_node(){ }

           
    };

};