#include <stdio.h>
#include "lib/dictionary.h"

/*
{"Persons": [{"Tim": 11}, {"John": 20}, {"Oscar": 45}]}
*/

int main() {
	dict_t* dict = dict_create(STRING, INTEGER, "John", 20),
		*dict2 = NULL, *dict3 = NULL, *dict4 = NULL;
	dict_append(&dict2, STRING, INTEGER, "Oscar", 45);
	dict_insert(&dict3, STRING, INTEGER, "Tim", 11);
	list_t* list = list_create(DICT, dict);
	list_append(&list, DICT, dict2);
	list_insert(&list, DICT, dict3);
	dict4 = dict_create(STRING, LIST, "Persons", list);
	dict_print(dict4);
	dict_free(dict4);
	return 0;
}
