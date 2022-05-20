#include <stdio.h>
#include "lib/dictionary.h"

int main() {
	dict_t* dict = dict_create(STRING, STRING, "Name", "John"),
		*dict2 = dict_create(STRING, STRING, "Day", "Sunday");
	dict_append(&dict, INTEGER, DICT, 10, dict2);
//	string_t string = dict_tostring(dict);
//	string_print(string); // equivalent to dict_print
//	string_free(&string);
	printf("dict2 pointer: %p\n", dict2);
	printf("dict->right->dict pointer: %p\n", dict->right->dict);
	dict_safe_free(&dict->right->dict);
	dict_safe_free(&dict2);
	printf("%p\n", dict2);
	dict_print(dict2);
	dict_safe_free(&dict);
	return 0;
}
