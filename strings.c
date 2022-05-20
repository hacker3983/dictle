#include <stdio.h>
#include "lib/string.h"

int main() {
	strings_t strings;
	strings_init(&strings);
	strings_append(&strings, "This");
	strings_append(&strings, "Is");
	strings_append(&strings, "A");
	strings_append(&strings, "String");
	strings_print(strings);
	strings_free(&strings);
	return 0;
}
