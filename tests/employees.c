#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/dictionary.h"

struct Employee {
	char* name;
	int age, salary;
};

int main(int argc, char** argv) {
	if(argc < 2) {
		fprintf(stderr, "Please specify an employee's name to search for in our database\n");
		return 1;
	}
	dict_t* dict = NULL;
	struct Employee employees[] = {
		{"John Doe", 20, 500}, {"Johnny Test", 25, 1000},
		{"Peter Parker", 31, 50}, {"Katie Walker", 18, 9000},
		{"Random Shit", 60, 0}, {"Nothing", 25, 18},
		{"IFLKDJFKLJDKLj", 50, 40}, {"KKKJK", 25, 188}
	};
	size_t size = sizeof(employees)/sizeof(employees[0]);
	list_t* list[size];
	memset(list, 0, sizeof(list));
	for(size_t i=0;i<size;i++) {
		list_insertf(&list[i], OP_APPEND, "%d %d", employees[i].age, employees[i].salary);
		dict_append(&dict, STRING, LIST, employees[i].name, list[i]);
	}
	printf("Database:\n"); dict_print(dict);
	printf("\nSearching for \"%s\"\n", argv[1]);
	query_t query = dict_query(dict, STRING, argv[1]);
	if(query.dict == NULL) {
		printf("No such employee named %s\n", argv[1]);
	} else {
		list_t* temp = query.dict->list;
		int age = *(int*)list_index(temp, 0), salary = *(int*)list_index(temp, 1);
		printf("Sucessfully Found %s!\n", argv[1]);
		printf("%s is %d years old and has a salary of %d dollars a monthly\n", argv[1], age, salary);
	}
	dict_free(dict);
	return 0;
}
