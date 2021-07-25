## about :
repository contain a collection of data structures using c++

## usage & implementation :
**note** : each data structure in 'unique file' all what you need to do is :
> 1 - copy 'data structure file' to your project folder .

> 2 - include 'data structure file' in your project .

> 3 - optional => use namespace of 'data structure' or you can use :: access .

> 4 - have a fun .

### usage example :
```c++
  // include doubly linked list header file  
  #include "linkedlists/doubly_LinkedList.hpp"
  
  // using linked list name space [optional !] 
  using namespace linkedlist;
   
  int main(){
    // create a doubly linked list [optional !] 
    doubly_LinkeList linked_ints<int>;  

    return 0;
  }

```
## linked lists : 

singly | [![status](https://img.shields.io/badge/status-stable-brightgreen?style=flat)](#) | [![status](https://img.shields.io/badge/manual%20testing-pass-ff69b4)](#)
-- | -- | -- 
doubly | [![status](https://img.shields.io/badge/status-stable-brightgreen?style=flat)](#) | [![status](https://img.shields.io/badge/manual%20testing-pass-ff69b4)](#)
singly circular | [![status](https://img.shields.io/badge/status-stable-brightgreen?style=flat)](#) | [![status](https://img.shields.io/badge/manual%20testing-pass-ff69b4)](#)


functions | singly | doubly  | singly circular
------------ | ------------- | ------------- | ------------- 
length          | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | | | 
push_back       | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | | | 
push_front      | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | | | 
push_at         | [![](https://img.shields.io/badge/O-(n)-success)](#) | | | 
replace         | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(n)-success)](#)  | | | 
has             | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)) to o(n)  | | | 
reverse         | o(n*3) | | | 
sort            | o(n²) | | | 
remove          | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(n)-success)](#) | | | 
remove_first    | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | | | 
remove_last     |[![](https://img.shields.io/badge/O-(n)-success)](#)| | | 
getFirstAsPointer | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | | | 
getLastAsPointer  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | | | 
getFistElement  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | | | 
getFistValue    | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | | | 
getLastElement  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | | | 
getLastValue    | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | | | 
toVector        | [![](https://img.shields.io/badge/O-(n)-success)](#) | | | 
toArray         | [![](https://img.shields.io/badge/O-(n)-success)](#) | | | 
clear           | [![](https://img.shields.io/badge/O-(n)-success)](#) | | | 
showAll         | [![](https://img.shields.io/badge/O-(n)-success)](#) | | | 
+=              | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(n)-success)](#) | | | 

