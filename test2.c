#include <stdio.h>
#include "lib/dictionary.h"

int main() {
	dict_t* dict = dict_create(STRING, INTEGER, "Number", 50),
		*dict1 = dict_create(INTEGER, STRING, 1, "John Doe"),
		*dict2 = dict_create(CHARACTER, FLOAT, 'A',
			(long double)100),
		*dict3 = dict_create(FLOAT, CHARACTER,
			(long double)65.4, 'F');
	dict_append(&dict, STRING, DICT, "Dict 1", dict1);
	dict_append(&dict1, STRING, DICT, "Dict 2", dict2);
	dict_append(&dict2, STRING, DICT, "Dict 3", dict3);
	dict_append(&dict3, STRING, INTEGER, "Hello", 20);
	dict_append(&dict, STRING, INTEGER, "Hello", 30);
	dict_print(dict);
	dict_free(dict);
	return 0;
}
