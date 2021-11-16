#ifndef _LIST_H
#define _LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
//#include "dictionary.h"
#define OP_INSERT 0
#define OP_APPEND 1
#define LIST_MAX_RECURSION 256
extern int LIST_RECURSION;

enum errors {
	FORMAT_ERROR = 1,
	TYPE_ERROR,
};

typedef struct linked_list {
	int type, integer;
	char* string, *error;
	#ifdef _WIN32
		double floatt;
	#else
		long double floatt;
	#endif
	size_t length, error_length;
	struct linked_list* list;
	struct linked_list* tail;
	struct linked_list* next;
} list_t;

extern list_t* next;
list_t* list_create(int type, ...);
void list_insert(list_t** list, int type, ...);
void list_append(list_t** list, int type, ...);
void list_insertf(list_t** list, int optype, char* format, ...);
void list_adderr(list_t** list, int type, const char* format, ...);
int list_raise_error(list_t* list);
void list_insert_optype(list_t** list, int optype, int type, ...);
void list_print(list_t* list);
void list_printf(list_t* list, const char* sep, char end);
bool list_streq(const char* s1, const char* s2);
list_t* __list_print_recursive(list_t* list, const char* sep, char end, int pb);
void* list_index(list_t* list, size_t index);
void list_free(list_t* list);
#endif
