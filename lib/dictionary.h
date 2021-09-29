#ifndef _DICTIONARY_H
#define _DICTIONARY_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#define P_ALL 0
#define P_ONCE 1

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

typedef struct query {
	dict_t* dict;
} query_t;

dict_t* dict_create(int ktype, int type, void* key, ...);
void dict_move(dict_t** dict, int dir);
void dict_insert(dict_t** dict, int ktype, int type, void* key, ...);
void dict_append(dict_t** dict, int ktype, int type, void* key, ...);
query_t dict_query(dict_t* dict, int ktype, void* key, ...);
list_t* dict_keys(dict_t* dict, int ktype);
void dict_print(dict_t* dict);
void dict_printq(query_t query);
void dict_print_optype(dict_t* dict, int optype);
void dict_free(dict_t* dict);
#endif
