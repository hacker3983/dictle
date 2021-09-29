#include <stdio.h>
#include "../lib/list.h"

int main() {
	list_t* list = list_create(INTEGER, 10);
	list_insertf(&list, OP_INSERT, "%s %f %c", "Hello", (long double)10.0, 'A');
	list_insert(&list, STRING, "World");
	list_append(&list, STRING, "Hi, There");
	list_insertf(&list, OP_APPEND, "%d %f %s %c", 70, (long double)89.7, "Hey", 'B');
	list_print(list);
	list_free(list);
	return 0;
}
