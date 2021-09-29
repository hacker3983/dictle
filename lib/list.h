#ifndef _LIST_H
#define _LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#define OP_INSERT 0
#define OP_APPEND 1
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
	struct linked_list* tail;
	struct linked_list* next;
} list_t;

list_t* list_create(int type, ...);
void list_insert(list_t** list, int type, ...);
void list_append(list_t** list, int type, ...);
void list_insertf(list_t** list, int optype, char* format, ...);
void list_adderr(list_t** list, int type, const char* format, ...);
int list_raise_error(list_t* list);
void list_insert_optype(list_t** list, int optype, int type, ...);
void list_print(list_t* list);
void list_printf(list_t* list, const char* sep, char end);
void* list_index(list_t* list, size_t index);
void list_free(list_t* list);
#endif
