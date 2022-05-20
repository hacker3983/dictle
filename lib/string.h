#ifndef _STRING_LIB_H
#define _STRING_LIB_H
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "numbers.h"

typedef struct string {
	char* buff;
	size_t size;
} string_t;

typedef struct string_list {
	char** array;
	size_t size;
} strings_t;

void string_init(string_t* string, char* buff);
void string_reinit(string_t* string);
void string_push_char(string_t* string, char c);
void string_append(string_t* string, char* buff);
void string_concat(string_t* string, char* format, ...);
void string_print(string_t string);
void string_free(string_t* string);

void strings_init(strings_t* strings);
void strings_append(strings_t* strings, char* buff);
void strings_print(strings_t strings);
void strings_free(strings_t* strings);

string_t get_string(size_t* i, const char* fmt);
string_t get_char(size_t* i, const char* fmt);
string_t get_int(size_t* i, const char* fmt);
strings_t string_tokenize(const char* string);
char* parse_string(strings_t tokens, size_t* i);
int parse_int(strings_t tokens, size_t* i);
bool parse_bool(strings_t tokens, size_t* i);
int parse_char(strings_t tokens, size_t* i);
#endif
