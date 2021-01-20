# DSAA-Class-Homework
## About  
This repository is the homeworks code store of university class "Data Structures and Algorithm Analysis" for CalunVier.  
It's writen in C, and not prepared to be use in product. Just for exercise.  
The repository is hosted on Github: https://github.com/CalunVier/DSAA-Class-Homework

## How to build the 
The project use CMake to auto build. All necessary information to build has been writen in CMakeLists.txt. You just need to import the project in you IDE, and build it.  
Note: The main() is an empty function! Please call the _main() function in specific homework project. It's all in homeworks/ directory.

## Project structure
### homeworks/
This is the directory to store the homework file. The files contains _main() in this directory.  
It contains:
- supermarket.c
- array_supermarket.c
- migong.c
- migong_tao.c

#### Homework supermarket
The final edition is in the array_supermarket.c. The "array" means used the ArrayQueue instead of ListQueue witch is used in supermarket.c with low index performance.  
There are also some bugs in supermarket.c, as it was an old edition. PLEASE DON'T USE IT!

#### Homework migong(maze)
The final edition is in the migong.c. The code in migong_tao.c is old and unavailable.  
For the beauty of output and compatible to Windows environment, migong.c file was encoded in GBK, and contains Chinese word(Because Chinese characters are in positive direction). If you need to build in other environments, please make sure the file can be read correctly in GBK encoding by the environment.

### calunvier/
The directory only contains tools.c. There's some code of random number generation in it. It's just a little personal library.

### object/
The directory object/ was for an OOP(Object Oriented Programing) System of ANSI C. Obviously I don't have enough energy to complete it.    
Although it is now flooded with a lot of obsolete code. But it is still an important ADT and algorithm support library.
The list.c queue.c sorts.c is still work.  
I am not sure about the dependencies of the current code. But objects.c and char_search_tree.c has been has been removed from the main logic. You can safely delete object.c and char_search_tree.c with little or no modification.  
Note: 
- ArrayList is an automatic expansion List ADT based on array implementation. And it has not been finished. 
- ObjList is a List ADT of a singly linked list, it is available.
- Both ArrayQueue and ListQueue are available.
- Sort.c may rely on object.c to provide data types, which comes from the ancient OOP project. It can be reused with slight modifications, but can only be used for basic types. There is a quick sort function(ObjList_sort()) available in ObjList. It can be used instead of the sorting algorithm at this stage.  

The naming convention of this project:  
- Contains basic object-oriented ideas
- In general, the class name uses the camel case nomenclature with the first letter capitalized. OOP-based functions use camel case nomenclature with lowercase initials.
- The member functions of the class use an underscore(_) to connect the class name and the function name, with the class name first. In general, the first parameter is the self-directed use of the object.
- Variable names and function names based on functional programming use lowercase letters and use underscores (_) to connect two complete words.
