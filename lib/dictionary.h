#ifndef _DICTIONARY_H
#define _DICTIONARY_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#define P_ALL 0
#define P_ONCE 1
#define DICT_MAX_RECURSION 256 // the maximum recursion amount that dict_print and list_print should do
extern int DICT_RECURSION;

typedef struct dict {
	int ktype, kint;
	char* kstring;
	long double kfloat;

	int type, integer;
	#ifdef _WIN32
		double floatt;
	#else
		long double floatt;
	#endif
	char* string;
	list_t* list;
	struct dict *left, *right, *tail;
} dict_t;

// creates and returns a pointer to a structure of type dict_t
dict_t* dict_create(int ktype, int type, ...);
void dict_move(dict_t** dict, int dir);

// inserts a key and a value at the front of the dictionary
void dict_insert(dict_t** dict, int ktype, int type, ...);

// inserts a key and a value at the end of the dictionary
void dict_append(dict_t** dict, int ktype, int type, ...);

// checks if a given key exists within the dictionary
bool dict_key_exists(dict_t* dict, int ktype, ...);

/* sets the value of a given key within the dictionary
   if the key doesn't exist it creates it assigning the value to key
*/
void dict_set_key(dict_t** dict, int ktype, int type, ...);

// gets the value of a given key within the dictionary
dict_t* dict_query(dict_t** result, dict_t* dict, int ktype, ...);

// does the same thing as dict_query
dict_t* dict_get(dict_t* dict, int ktype, ...);

// returns of a list of a list of keys within the dictionary
list_t* dict_keys(dict_t* dict);

// prints out the dictionary
void dict_print(dict_t* dict);

// prints out the dictionary allowing to specify the separator and the character that gets printed when printing the end of the dictionary
void dict_printf(dict_t* dict, const char* sep, char end);

// prints out the value of a given pointer to a dictionary
void dict_printq(dict_t* dict);

/* prints out the dictionary based on the given operation type
   P_ALL indicates print out everything within the dictionary
   P_ONCE indicates print out the first part of the dictionary leaving out the rest
*/
void dict_print_optype(dict_t* dict, int optype);

// frees the memory used by the dictionary
void dict_free(dict_t* dict);
#endif
