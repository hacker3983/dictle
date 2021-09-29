#include <stdio.h>
#include "../lib/list.h"

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("Please specify a integer to reverse\n");
		return -1;
	}
	list_t* list = NULL;
	int x = atoi(argv[1]);
	while(x != 0) {
		list_append(&list, INTEGER, x % 10);
		x /= 10;
	}
	list_print(list);
	list_free(list);
	return 0;
}
