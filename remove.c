#include <stdio.h>
#include "lib/dictionary.h"

int main() {
	dict_t* dict = dict_create(STRING, STRING, "Name", "John Doe");
	dict_append(&dict, STRING, INTEGER, "Age", 21);
	dict_remove_key(&dict, STRING, "Age");
	dict_print(dict);
	dict_free(dict);
	return 0;
}
