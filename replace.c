#include <stdio.h>
#include "lib/dictionary.h"

void main() {
	dict_t* dict = dict_create(INTEGER, STRING, 10, "Hello");
	dict_append(&dict, STRING, INTEGER, "Number", 21);
	dict_append(&dict, CHARACTER, BOOL, 'K', true);
	dict_append(&dict, FLOAT, STRING, (long double)95.9, "Score");
	dict_append(&dict, BOOL, STRING, true, "Highscore");
	dict_append(&dict, INTEGER, INTEGER, 20, 30);
	puts("Before replace:");
	dict_print(dict);
	puts("After replace:");
	dict_replace_key(&dict, INTEGER, STRING, 20, "Twenty");
	dict_replace_key(&dict, STRING, STRING, "Number", "Integer");
	dict_replace_key(&dict, FLOAT, INTEGER, (long double)95.9, 10);
	dict_replace_key(&dict, CHARACTER, CHARACTER, 'K', 'A');
	dict_replace_key(&dict, BOOL, INTEGER, true, 1);
	dict_replace_key(&dict, BOOL, BOOL, true, true);
	dict_print(dict);
	dict_free(dict);
}
