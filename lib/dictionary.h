#ifndef _DICTIONARY_H
#define _DICTIONARY_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "string.h"
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
	char* string, *error;
	size_t length, error_length;
	
	struct dict *list, *dict, *right, *tail;
} dict_t, list_t;
/*
	LIST FUNCTIONS
*/
list_t* list_create(int type, ...);
void list_insert(list_t** list, int type, ...);
void list_append(list_t** list, int type, ...);
void list_insertf(list_t** list, int optype, char* format, ...);
void list_adderr(list_t** list, int type, const char* format, ...);
int list_raise_error(list_t* list);
void list_insert_optype(list_t** list, int optype, int type, ...);
string_t list_tostring(list_t* list);
void list_print(list_t* list);
void list_printf(list_t* list, const char* sep, char end);
bool list_streq(const char* s1, const char* s2);
/* TODO: IMPLEMENT __LIST_PRINT_RECURSIVE*/
list_t* __list_print_recursive(list_t* list, const char* sep, char end, int pb);
void* list_index(list_t* list, size_t index);
void list_safe_free(list_t** list);
void list_free(list_t* list);

/*
	DICTIONARY FUNCTIONS
*/

// creates and returns a pointer to a structure of type dict_t
dict_t* dict_create(int ktype, int type, ...);
dict_t* string_todict(const char* fmt, ...);
void string_todict_toks(strings_t tokens, size_t *index, dict_t** dict, const char* fmt, ...);
void parse_list(strings_t tokens, list_t** list, size_t* i);
void dict_move(dict_t** dict, int dir);

// inserts a key and a value at the front of the dictionary
void dict_insert(dict_t** dict, int ktype, int type, ...);

// inserts a key and a value at the end of the dictionary
void dict_append(dict_t** dict, int ktype, int type, ...);

// converts a given dictionary to a string
string_t dict_tostring(dict_t* dict);

// replaces a key of type ktype1 with a key of type ktype2
void dict_replace_key(dict_t** dict, int ktype1, int ktype2, ...);

// removes a key of a given type within a dictionargy
void dict_remove_key(dict_t** dict, int ktype, ...);

// checks if a given key exists within the dictionary
bool dict_key_exists(dict_t* dict, int ktype, ...);

// gets the value of a given key within the dictionary
dict_t* dict_query(dict_t** result, dict_t** dict, int ktype, ...);

// does the same thing as dict_query
dict_t* dict_get(dict_t** dict, int ktype, ...);

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

// safely fress the memory used by the dictionary
void dict_safe_free(dict_t** dict);

// frees the memory used by the dictionary
void dict_free(dict_t* dict);
#endif
