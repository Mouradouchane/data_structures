## about :
repository contain a collection of data structures using c++

## usage & implementation :
**note** : each data structure in **'unique file'** all what you need to do is :
> 1 - copy **'data structure file'** to your project folder .

> 2 - include **'data structure file'** in your project .

> 3 - optional => use namespace of **'data structure'** or you can use :: access .

> 4 - have a fun :sweat_smile: .

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
### Wiki/Docs : [![](https://img.shields.io/badge/Wiki%2FDocs-Beta-blue)](#)
- you can use [doc](https://github.com/Mouradouchane/data_structures/wiki) to understand how **'thing's'** work with examples .

## linked lists : 

singly | [![status](https://img.shields.io/badge/status-stable-brightgreen?style=flat)](#) | [![status](https://img.shields.io/badge/manual%20testing-pass-ff69b4)](#)
-- | -- | -- 
doubly | [![status](https://img.shields.io/badge/status-stable-brightgreen?style=flat)](#) | [![status](https://img.shields.io/badge/manual%20testing-pass-ff69b4)](#)
singly circular | [![status](https://img.shields.io/badge/status-stable-brightgreen?style=flat)](#) | [![status](https://img.shields.io/badge/manual%20testing-pass-ff69b4)](#)


#### linked listes time complexity of all functions :
functions | singly | doubly  | singly circular
------------ | ------------- | ------------- | ------------- 
length          | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)| 
push_back       | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)| 
push_front      | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)| 
push_at         | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#)| 
replace         | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#)| 
has             | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#)|[![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | 
reverse         | [![](https://img.shields.io/badge/O-(N*3)-orange)](#) | [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(N*3)-orange)](#) | 
sort            | [![](https://img.shields.io/badge/O-(N%C2%B2)-red)](#)| [![](https://img.shields.io/badge/O-(N%C2%B2)-red)](#) | [![](https://img.shields.io/badge/O-(N%C2%B2)-red)](#) | 
remove          | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | 
remove_first    | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) |  [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)| 
remove_last     | [![](https://img.shields.io/badge/O-(N)-success)](#)| [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(N)-success)](#) | 
getFirstAsPointer | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | 
getLastAsPointer  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) |  [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | 
getFirstElement  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) |  [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | 
getFirstValue    | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | 
getLastElement  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) |  [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) | 
getLastValue    | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) |  [![](https://img.shields.io/badge/O-(1)-blueviolet)](#)  | 
toVector        | [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(N)-success)](#) | 
toArray         | [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(N)-success)](#) | 
clear           | [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(N)-success)](#) |  [![](https://img.shields.io/badge/O-(N)-success)](#) | 
print        | [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(N)-success)](#) |  [![](https://img.shields.io/badge/O-(N)-success)](#) | 
operator +=     | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | [![](https://img.shields.io/badge/O-(1)-blueviolet)](#) to [![](https://img.shields.io/badge/O-(N)-success)](#) | 

### contribution :
if want to contribute/reporte , your welcome 😙 
please before you make anything , discuss stuff with me or open [issue](https://github.com/Mouradouchane/data_structures/issues) 😄
