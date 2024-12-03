/** 
 * @file: map.c -- Map data structure implemented using linked lists.
 * 
 * @author: Eduardo Palou de Comasema
 * 
 * This file conatins the implementation of a Map data structure based on
 * linked list.
 * 
 * @note This implementation is not pointer secure and it is not recommended for production.
 *   
 */

/*
 *  DATA STRUCTURE
 *  
 *		Sorted associative container that contains key-value pairs with unique keys.
 *		
 *  REFERENCES
 *	
 *	Yale University (Iterators in c)
 * 		https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Iterators.html
 * 	
 * 	C++ map implementation 
 * 		https://en.cppreference.com/w/cpp/container/map
 *
 *	Google Tech Dev Guide 
 * 		https://techdevguide.withgoogle.com/paths/data-structures-and-algorithms/#linear
 *
 *	Introduction to the Map Data Structure
 *		https://cloudnativejourney.wordpress.com/2023/05/04/introduction-to-the-map-data-structure/
 *
 * 	Gnu Error code
 * 		https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html
 *
 * 	Code Documentation (Deoxygen Format - For functions)
 * 
 * 		https://nus-cs1010.github.io/2223-s1/documentation.html
 * 
 * 	Hash key to 4 bytes
 * 		¿? 
 * 
 *  
 */
 
#include "map.h"
	
/**
 * Removes all the elements from the map and free the memory
 * 
 * @param[in,out] map Pointer to the map to be cleared.
 * 
 * @return Returns 0 if the map is cleared and 1 if not.
 *   
 */ 
int clear(map_type* map) {
	// REVIEW: Uncleared usage of the map.

	// Check if the arguments are valid 
	if (map != NULL) {
		map_node_type* pre_node = map->next; // Stores the previous map
		map_node_type* node = map->next; // Stores the node to be reviewed

		while(node->next != NULL) {
			pre_node = node;
			node = node->next;

			// Free memory
			free(pre_node->data);
			free(pre_node);			 
		}

		// Clean map
		map->next = NULL;

		// Free memory
		free(node->data);
		free(node);

		return 0; // THe operation is performed	
	} else {
		return 1; // Invalid argument map.
	}
};
		
/** 
 * Erase an entry of the map
 * 
 * @param[in,out] map Pointer to the map to be modified.
 * @param[in] key Pointer to the key to be removed.
 * 
 * @return Returns 0 if the operation is performed and 1 if not.
 *  
 */
int delate(map_type* map, void* key) {
	// REVIEW: THe function should be tested.

	// Check if the arguments are valid
	if (map != NULL || key != NULL) {
		map_node_type* pre_node = NULL; // Stores previous node.
		map_node_type* cur_node = map->next; // Stores the node to be reviewed.

		if ((int*)(cur_node->key) != (int*)key) {
			pre_node = cur_node;
			cur_node = cur_node->next;

			while(cur_node->next != NULL) {
				if( (int*)(cur_node->key) != (int*)key) {
					pre_node = cur_node;
					cur_node = cur_node->next;
				} else {
					pre_node->next = cur_node->next;
					
					map->len--; // Decrement counter of entries

					// Free memory
					free(cur_node->data);
					free(cur_node);

					return 0; // Entry deleted.
				} 
			}
				return 1; // Not entry for key is found.
		} else {
			map->next = cur_node->next;
			
			// Free memory
			free(cur_node->data);
			free(cur_node);

			map->len--; // Decrement counter of entries

			return 0; // Entry deleted. 
		}
	} else 
		return 1; // Invalid map or key values.
};
		
/** 
 * Insert or update an entry of the map
 * 
 * @param[in,out] map Pointer to the map to be modified.
 * @param[in] key Pointer to the key to be modified or insert.
 * @param[in] data Pointer to the data to be inserted with the key.
 * 
 * @return Returns 0 if the insertion operation is performed, 1 if the update
 *  	   operation is performed and 2 if no operation is performed.
 * 
 */
int insert(map_type* map, void* key, void* data) {
	// REVIEW: Needs to be validate with test. 

	// Check if the arguments are valid
	if (map != NULL || key != NULL || data != NULL) {
		// We travers through the linked list until we arrive at the end 
		// or find the key to update.
		map_node_type* node = map->next; // Stores the node to be reviewed

		while(node->next != NULL) {
			if( (int*)(node->key) != (int*)key) {
				node = node->next;
			} else {
				free(node->data);  // Free previous data
				node->data = data; // Update pointer to the data

				return 1; // Return update code
			} 
		}

		// Create new node
			map_node_type* new_node = (map_node_type*) malloc(sizeof(map_node_type));

			// Initialize new node
			new_node->key  = key;
			new_node->data = data;
			new_node->next = NULL;

		// Insert at the end of the linked list
		node->next = new_node;

		map->len++;		// Update counter of entries of map

		return 0; // Return insert code
	} else {
		return 2; // Return no opration code
	}
};
		
/**
 * Get data from the map given a key 
 * 
 * @param[in] map Pointer to the map to be reviewed.
 * @param[in] key Pointer to the key to be checked.
 * 
 * @return Returns pointer to the data associated with the key if exists and NULL if not.
 *  
 */
void* get(map_type* map, void* key) {
	// REVIEW: Needs to be validate with some tests.

	// Check if the arguments are valid
	if (map != NULL || key != NULL) {
		// Check if the key is in the map 
		if (isKey(map, key) != 1) {
			map_node_type* node = map->next; // Stores the node to be reviewed

			while(node->next != NULL) {
				if( (int*)(node->key) != (int*)key) {
					node = node->next;
				} else {
					return node->data; // Return pointer to the data
				} 
			}
		} else {
			return NULL; // There is not data linked to the key
		}
	} else {
		return NULL; // There is not data linked to the key 
	}
};

/**
 * 	Check if a key is present in the map
 *  
 *  @param[in] map Pointer to the map to be checked
 *  @param[in] key Pointer to the key to be checked
 * 		
 *  @return Returns 0 if the key is not found in the map, 1 if it is in the map 
 *  		and 2 if the search could not be performed
 * 
 */
int isKey(map_type* map, void* key) {
	// REVIEW: The void* pointers should be reviewed because can't be dereferanced
	
	if (map != NULL || key != NULL) { // Check if the arguments are valid
		if (map->len != 0) {
			map_node_type* node = map->next; // Stores the node to be reviewed

			while(node->next != NULL) {
				if( (int*)(node->key) != (int*)key) {
					node = node->next;
				} else {
					return 1; // Key is found in the map
				} 
			}

			return 0; // Key is not found in the map 			
		} else {
			return 0; // Key is not found in the map
		}
	} else {
		return 2; // Indicate that the operation could not be performed
	}
}
	
/**  
 * Instantiate an empty map
 * 
 * @pre The map should be free with the clear function
 * 
 * @return Returns an empty map_type variable.
 * 
 */
map_type new_map() {
	// REVIEW: This function should be tested.

	// Instantiate map variable
	map_type map; 

	// Initalize variable
	map.len  =  0; 	  // No entries at the start.
	map.next =  NULL; // Empty map.

	// Return variable
	return map;
};