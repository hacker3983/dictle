#include <stdio.h>
#include "lib/string.h"

int main() {
	string_t string;
	string_init(&string, "Hello, World!\n");
	string_concat(&string, "%c, %f\n%d\n"
			"%H%E%Y%\n", 'a', (long double)10.1,
			97);
	string_concat(&string, "Anonymous");
	string_append(&string, "1234567890");
	string_print(string);
	string_free(&string);
	return 0;
}
