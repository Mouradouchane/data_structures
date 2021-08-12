#include <iostream>
#pragma once

/*
	that module contain a simple hash_table with basics function like => clear , isEmpty , isFull .... 
	we using that class later in different hash tables like => open-addressing , chaining ...
*/

// === hash table ~ methods ===
/*
   -- NAME ------------ BEST --> WORST

	clear			=> o(n)  --> ....
	clone			=> o(n)	 --> ....
	elements		=> o(n)	 --> ....

	get				=> o(1)	 --> o(n)
	set				=> o(1)	 --> o(n)
	put				=> o(1)	 --> o(n)

	remove			=> o(1)	 --> ....
	replace			=> o(1)	 --> ....
	replaceAll		=> o(1)	 --> ....

	isEmpty			=> o(1)
	isFull			=> o(1)

	keys			=> o(1)	 --> ....
	values			=> o(1)	 --> ....

	print			=> o(1)	 --> ....
	length			=> o(1)
*/

namespace hash_tables {




}