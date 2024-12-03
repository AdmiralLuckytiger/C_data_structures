/// Implementation of a map in c based on a linked list.
/// Notation convetion
///
/// 1. Types in snake case (snake_case)
/// 2. Functions in camel case (camleCase)
///

#ifndef _MAP_H
	
	/// INCLUDE GUARDS
	#define _MAP_H	1
	
	#ifndef __SSP__STDIO_H
		#include <stdio.h>
	#endif /* __SSP__STDIO_H */
	
	#ifndef __STDLIB_H
		#include <stdlib.h>
	#endif /* __STDLIB_H */
	
	#include <errno.h> // Error handling with systems code 
	
	/// MACROS
	
		/*
			Indicate the max number of keys in present in the map.
		*/
		#define MAX_SIZE_MAP 100
		
	/// DATA STRUCTUTES 
		
		/*
			Structure that stores the data and connects it in the dictionary  
		*/
		typedef struct map_node_struct {
			void* key; 			// Unique Key
			void* data; 		// 
			map_node* next;		// Pointer to the next element
		} map_node_type;
		
		/* 
			Strcuture that reprsent the whole map
		*/
		typedef struct map_struct {
			map_node* next; // Pointer to head of the linked list
		} map_type;
		
	/// FUNCTION PROTOTIPES
	
		// Removes all the elements from the map
		int clear(map* map);
		
		// Erase an entry of the map
		int delate(map* map, void* key);
		
		// Insert or update an entry of the map
		int insert(map* map, void* key, void* data);
		
		// Get data from the map given a key 
		int get(map* map, void* key);
		
		// Instantiate an empty map
		map_type new_map();
		
#endif /* __MAP_H */