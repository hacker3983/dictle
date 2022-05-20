#include <stdio.h>
#include <stdlib.h>
#include "../lib/list.h"

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("please specify a integer to split\n");
		return -1;
	}
	list_t* list = NULL;
	int a = atoi(argv[1]);
	while(a != 0) {
		list_insert(&list, INTEGER, a % 10);
		a /= 10;
	}
	list_print(list);
	list_free(list);
	return 0;
}
