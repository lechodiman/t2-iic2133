/*
 * Generic hashmap manipulation functions
 *
 * Originally by Elliot C Back - http://elliottback.com/wp/hashmap-implementation-in-c/
 *
 * Modified by Pete Warden to fix a serious performance problem, support strings as keys
 * and removed thread synchronization - http://petewarden.typepad.com
 * Modified by Luis Chodiman to store strings as values specifically
*/

#pragma once
#include <stdbool.h>

#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	/* OK */

typedef struct hashmap_node{
    char key[17];
    int in_use;
    char data[17];
} HashmapNode;

typedef struct hashmap_map{
    int table_size;
    int size;
    /* Pointer to array of hashmap nodes*/
    HashmapNode* data;
} HashMap;

HashMap* hashmap_init();
int hashmap_put(HashMap* m, char* key, char* value);
int hashmap_get(HashMap* m, char* key, char* arg);
bool hashmap_in_map(HashMap* m, char* key);
void hashmap_free(HashMap* m);
