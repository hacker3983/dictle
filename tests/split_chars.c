#include <stdio.h>
#include "../lib/list.h"

int main(int argc, char** argv) {
	if(argc < 2) {
		puts("Please specify a string to split into characters");
		return -1;
	}
	list_t* list = NULL;
	for(int i=0;i<strlen(argv[1]);i++) {
		list_append(&list, CHARACTER, argv[1][i]);
	}
	list_print(list);
	list_free(list);
	return 0;
}
