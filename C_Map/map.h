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
		#define MAX_SIZE_MAP 4294967296 // (2^(4*8) posibles values)
		
	/// DATA STRUCTUTES 
		
		/*
			Structure that stores the data and connects it in the dictionary  
		*/
		typedef struct map_node_struct {
			void* key; 							// Unique Key (Only support 32 bit types)
			void* data; 						// Pointer to the data to be store
			struct map_node_struct* next;		// Pointer to the next element
		} map_node_type;
		
		/* 
			Structure that reprsent the whole map
		*/
		typedef struct map_struct {
			int len; 			 // Stores the total amount of entries stored.
			map_node_type* next; // Pointer to head of the linked list.
		} map_type;
		
	/// FUNCTION PROTOTIPES
	
		// Removes all the elements from the map
		int clear(map_type* map);
		
		// Erase an entry of the map
		int delate(map_type* map, void* key);
		
		// Insert or update an entry of the map
		int insert(map_type* map, void* key, void* data);
		
		// Get data from the map given a key 
		void* get(map_type* map, void* key);
		
		// Check is a key exist
		int isKey(map_type* map, void* key);

		// Instantiate an empty map
		map_type new_map();
		
#endif /*__MAP_H*/