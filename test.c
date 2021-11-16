#include <stdio.h>
#include "lib/dictionary.h"
/*
{"Person":{"Name":"John Doe", "Age": 10},
 "Nums":[10, 20, 30, 40],
 "Countries":["United States of America", "England", "China", "United Kingdom"],
 "Mixed_Types":["Discord is the best", 10, 'A', 99.9],
 "Days_num":{0:"Sunday", 1:"Monday", 2:"Tuesday", 3:"Wednesday", 4:"Thursday", 5:"Friday", 6:"Saturday"}
}
*/
int main() {
	dict_t* dict = NULL, *person = dict_create(STRING, STRING, "Name", "John Doe"), *days_num = NULL;
	list_t* numbers = NULL, *countries = NULL, *mixed_typed_list = NULL;
	dict_append(&person, STRING, INTEGER, "Age", 20);
	for(int i=10;i<=40;i+=10) { list_append(&numbers, INTEGER, i); }
	char* week_days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	for(int i=0;i<=5;i++) { dict_append(&days_num, INTEGER, STRING, i, week_days[i]); }

	char* countries_list[] = {"United States of America", "England", "China", "United Kingdom"};
	for(int i=0;i<4;i++) { list_append(&countries, STRING, countries_list[i]); }
	list_insertf(&mixed_typed_list, OP_APPEND, "%s %d %c, %f", "Discord is the best", 10, 'A', (long double)99.9);

	dict_append(&dict, STRING, DICT, "Person", person);
	dict_append(&dict, STRING, LIST, "Nums", numbers);
	dict_append(&dict, STRING, LIST, "Countries", countries);
	dict_append(&dict, STRING, LIST, "Mixed_types", mixed_typed_list);
	dict_append(&dict, STRING, DICT, "Days_num", days_num);
	dict_print(dict);
	dict_free(dict);
	return 0;
}
