#include <stdio.h>
#include "lib/dictionary.h"

int main() {
	dict_t* dict = string_todict("{\"string\":20, 'A':\"Letter of the alphabet\", 1:2, 20:\"Hello\", \"Hello\":20, true: false, \"A\":true, " 
"\"B\":false, 'C':true, 10:false, 30:'A', true:\"Hello\", "
"false:\"booleans\", \"Hi\":[1, 2, 3, 4, [20, 30, 40,"
"\"We have strings too don't discriminate c. c is the best programming "
"language\"]], \"languages\":[\"python\", \"c\", \"c++\", \"perl\"],"
"\"credentials\":[{\"john doe\":\"password\"}], "
"\"dict-to-dict\":{\"A\":{'B':[\"Basic parsing\"]}}, "
"\"Sports\":{\"Soccer\":20, \"Basketball\":10000000,"
"\"Boxing\":20000000, \"Others\":1000000000}, "
"20:{20:30}, 'Z':{\"letter_of_the_alphabet\":true}, true:{\"Bools have dicts too\":true}, false:[\"Bools have lists\"]}"
"\"Characters\":['d', ['A', \"Chars\"]]");
	dict_print(dict);
	printf("search result:\n");
	dict_t* result = dict_get(&dict, STRING, "Sports");
	dict_printq(result);
	dict_free(dict);
	return 0;
}
