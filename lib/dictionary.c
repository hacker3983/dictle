#include "dictionary.h"

/* How the dictionary should look?
{"Person":{"Name":"John Doe", "Age": 10},
 "Nums":[10, 20, 30, 40],
 "Countries":["United States of America", "England", "China", "United Kingdom"],
 "Mixed_Types":["Discord is the best", 10, 'A', 99.9],
 "Days":{0:"Monday", 1:"Tuesday", 2:"Wednesday", 3:"Thursday", 4:"Friday", 5:"Saturday", 6:"Sunday"}
}
*/

dict_t* dict_create(int ktype, int type, ...) {
	va_list varg;
	va_start(varg, type);
	dict_t* dict = calloc(1, sizeof(dict_t));
	char* str = NULL;
	switch(ktype) {
		case INTEGER:
			dict->ktype = INTEGER;
			dict->kint = va_arg(varg, int);
			break;
		case STRING:
			dict->ktype = STRING;
			str = va_arg(varg, char*);
			if(str != NULL) {
				size_t len = strlen(str);
				if(len != 0) {
					dict->kstring = calloc(len, sizeof(char*));
					strcpy(dict->kstring, str);
				}
			}
			break;
		case CHARACTER:
			dict->ktype = CHARACTER;
			dict->kint = va_arg(varg, int);
			break;
		case FLOAT:
			dict->ktype = FLOAT;
			#ifdef _WIN32
				dict->kfloat = va_arg(varg, double);
			#else
				dict->kfloat = va_arg(varg, long double);
			#endif
			break;
		case BOOL:
			dict->ktype = BOOL;
			dict->kint = va_arg(varg, int);
			break;
	}
	switch(type) {
		case INTEGER:
			dict->type = INTEGER;
			dict->integer = va_arg(varg, int);
			break;
		case STRING:
			dict->type = STRING;
			str = va_arg(varg, char*);
			if(str != NULL) {
				size_t len = strlen(str);
				if(len != 0) {
					dict->string = calloc(len, sizeof(char*));
					strcpy(dict->string, str);
				}
			}
			break;
		case CHARACTER:
			dict->type = CHARACTER;
			dict->integer = va_arg(varg, int);
			break;
		case FLOAT:
			dict->type = FLOAT;
			#ifdef _WIN32
				dict->floatt = va_arg(varg, double);
			#else
				dict->floatt = va_arg(varg, long double);
			#endif
			break;
		case LIST:
			dict->type = LIST;
			dict->list = va_arg(varg, list_t*);
			break;
		case DICT:
			dict->type = DICT;
			dict->left = va_arg(varg, dict_t*);
			break;
		case BOOL:
			dict->type = BOOL;
			dict->integer = va_arg(varg, int);
			break;
	}
	dict->tail = dict;
	va_end(varg);
	return dict;
}
/* TODO:
   Implement three functions called dict_insert, dict_append and dict_insertf
   dict_insert - inserts a key and a value at the front of the dictionary
   dict_append - appends a key and a value at the end of the dictionary a node to the left or the right of the dictionary.
   dict_insertf - inserts a key and a value using format strings and
   The function dict_insertf should use Conversion specifiers and Description specifiers describes what we want to do.
   Conversion specifiers - Tells the type we want to convert into a string
   Description specifiers - Describes the type of operation we want to do
   Conversion specifiers are:
   %s - Used for formatting Strings
   %d - Used for formatting Numbers
   %f - Used for formatting Integers
   %l - Used for formatting Lists
   %k - Used for formatting Dictionaries
   Description specifiers:
   >> - Tells dict_insertf we want to append or insert a node in the left node
   << - Tells dict_insertf or dict_append we want to append or insert a node in the right node
*/
void dict_insert(dict_t** dict, int ktype, int type, ...) {
	va_list varg;
	va_start(varg, type);
	dict_t* new_node = NULL, *temp = *dict;
	int key_int;
	char* key_string;
	long double key_float;
	switch(ktype) {
		case INTEGER:
			key_int = va_arg(varg, int);
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_string, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_string, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case STRING:
			key_string = va_arg(varg, char*);
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_string, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_string, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_string, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_string, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_string, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
			}
			break;
		case CHARACTER:
			key_int = va_arg(varg, int);
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_int, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case FLOAT:
			#ifdef _WIN32
				key_float = va_arg(varg, double);
			#else
				key_float = va_arg(varg, long double);
			#endif
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_float, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_float, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_float, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_float, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_float, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
			}
			break;
		case BOOL:
			key_int = va_arg(varg, int);
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_float, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_float, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
	}
	va_end(varg);
	if(*dict == NULL) {
		*dict = new_node;
		return;
	}
	new_node->right = temp;
	new_node->tail = new_node->right->tail;
	*dict = new_node;
}

void dict_append(dict_t** dict, int ktype, int type, ...) {
       	va_list varg;
	va_start(varg, type);
	dict_t* new_node = NULL;
	int key_int;
	char* key_string;
	long double key_float;
	dict_t* query = NULL;
	switch(ktype) {
		case INTEGER:
			key_int = va_arg(varg, int);
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_int, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case STRING:
			key_string = va_arg(varg, char*);
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_string, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_string, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_string, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_string, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_string, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
			}
			break;
		case CHARACTER:
			key_int = va_arg(varg, int);
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_int, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case FLOAT:
			#ifdef _WIN32
				key_float = va_arg(varg, double);
			#else
				key_float = va_arg(varg, long double);
			#endif
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_float, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_float, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_float, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_float, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_float, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
			}
			break;
		case BOOL:
			key_int = va_arg(varg, int);
			switch(type) {
				case INTEGER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case CHARACTER: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_float, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_float, va_arg(varg, long double));
					#endif
					break;
				case STRING: new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST: new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT: new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL: new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
	}
	va_end(varg);
	if(*dict == NULL) {
		*dict = new_node;
		return;
	}
	(*dict)->tail->right = new_node;
	(*dict)->tail = (*dict)->tail->right;
}
void dict_set_key(dict_t** dict, int ktype, int type, ...) {
	va_list varg;
	va_start(varg, type);
	dict_t* result = NULL;
	int key_int;
	char* key_string;
	long double key_float;
	switch(ktype) {
		case INTEGER:
			key_int = va_arg(varg, int);
			switch(type) {
				case INTEGER: dict_append(dict, ktype, type, key_int, va_arg(varg, int)); break;
				case STRING: dict_append(dict, ktype, type, key_int, va_arg(varg, char*)); break;
				case CHARACTER: dict_append(dict, ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						dict_append(dict, ktype, type, key_int, va_arg(varg, double));
					#else
						dict_append(dict, ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case BOOL: dict_append(dict, ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case CHARACTER:
			key_int = va_arg(varg, int);
			switch(type) {
				case INTEGER: dict_append(dict, ktype, type, key_int, va_arg(varg, int)); break;
				case STRING: dict_append(dict, ktype, type, key_int, va_arg(varg, char*)); break;
				case CHARACTER: dict_append(dict, ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						dict_append(dict, ktype, type, key_int, va_arg(varg, double));
					#else
						dict_append(dict, ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case BOOL: dict_append(dict, ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case STRING:
			key_string = va_arg(varg, char*);
			switch(type) {
				case INTEGER: dict_append(dict, ktype, type, key_string, va_arg(varg, int)); break;
				case STRING: dict_append(dict, ktype, type, key_string, va_arg(varg, char*)); break;
				case CHARACTER: dict_append(dict, ktype, type, key_string, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						dict_append(dict, ktype, type, key_string, va_arg(varg, double));
					#else
						dict_append(dict, ktype, type, key_string, va_arg(varg, long double));
					#endif
					break;
				case BOOL: dict_append(dict, ktype, type, key_string, va_arg(varg, int)); break;
			}
			break;
		case FLOAT:
			#ifdef _WIN32
				key_float = va_arg(varg, double);
			#else
				key_float = va_arg(varg, long double);
			#endif
			switch(type) {
				case INTEGER: dict_append(dict, ktype, type, key_float, va_arg(varg, int)); break;
				case STRING: dict_append(dict, ktype, type, key_float, va_arg(varg, char*)); break;
				case CHARACTER: dict_append(dict, ktype, type, key_float, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						dict_append(dict, ktype, type, key_float, va_arg(varg, double));
					#else
						dict_append(dict, ktype, type, key_float, va_arg(varg, long double));
					#endif
					break;
				case BOOL: dict_append(dict, ktype, type, key_float, va_arg(varg, int)); break;
			}
			break;
		case BOOL:
			key_int = va_arg(varg, int);
			switch(type) {
				case INTEGER: dict_append(dict, ktype, type, key_int, va_arg(varg, int)); break;
				case STRING: dict_append(dict, ktype, type, key_int, va_arg(varg, char*)); break;
				case CHARACTER: dict_append(dict, ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					#ifdef _WIN32
						dict_append(dict, ktype, type, key_int, va_arg(varg, double));
					#else
						dict_append(dict, ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case BOOL: dict_append(dict, ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
	}
	va_end(varg);
}
/*void dict_move(dict_t** dict, int dir) {
	
}*/
// TODO fix dict_query TODO remove this comment
dict_t* dict_query(dict_t** result, dict_t* dict, int ktype, ...) {
	va_list varg;
	va_start(varg, ktype);
	int key_int = 0;
	long double key_float = 0;
	char* key_string = NULL;
	switch(ktype) {
		case INTEGER: key_int = va_arg(varg, int); break;
		case STRING: key_string = va_arg(varg, char*); break;
		case CHARACTER: key_int = va_arg(varg, int); break;
		case FLOAT:
			#if _WIN32
				key_float = va_arg(varg, double);
			#else
				key_float = va_arg(varg, long double);
			#endif
			break;
		case BOOL: key_int = va_arg(varg, int); break;
	}
	while(dict != NULL) {
		if(dict->ktype == ktype) {
			switch(dict->ktype) {
				case INTEGER:
					if(dict->kint == key_int) {
						printf("Found integer key: %d\n", dict->kint);
						*result = dict;
						if(dict->type == DICT) {
							*result = dict->left;
						}
						va_end(varg);
						return *result;
					}
					break;
				case STRING:
					if(list_streq(dict->kstring, key_string)) {
						*result = dict;
						if(dict->type == DICT) {
							*result = dict->left;
						}
						va_end(varg);
						return *result;
					}
					break;
				case CHARACTER:
					if(dict->kint == key_int) {
						*result = dict;
						if(dict->type == DICT) {
							*result = dict->left;
						}
						va_end(varg);
						return *result;
					}
					break;
				case FLOAT:
					if(dict->kfloat == key_float) {
						*result = dict;
						if(dict->type == DICT) {
							*result = dict->left;
						}
						va_end(varg);
						return *result;
					}
					break;
				case BOOL:
					if(dict->kint == key_int) {
						*result = dict;
						if(dict->type == DICT) {
							*result = dict->left;
						}
						va_end(varg);
						return *result;
					}
					break;
			}
		}
		dict = dict->right;
	}
	va_end(varg);
	return *result;
}

dict_t* dict_get(dict_t* dict, int ktype, ...) {
	va_list varg;
	va_start(varg, ktype);
	dict_t* result = NULL;
	switch(ktype) {
		case INTEGER: dict_query(&result, dict, ktype, va_arg(varg, int)); break;
		case STRING: dict_query(&result, dict, ktype, va_arg(varg, char*)); break;
		case CHARACTER: dict_query(&result, dict, ktype, va_arg(varg, int)); break;
		case FLOAT:
			dict_query(&result, dict, ktype, va_arg(varg, double));
			#if _WIN32
				dict_query(&result, dict, ktype, va_arg(varg, double));
			#else
				dict_query(&result, dict, ktype, va_arg(varg, long double));
			#endif
			break;
		case BOOL: dict_query(&result, dict, ktype, va_arg(varg, int)); break;
	}
	va_end(varg);
	return result;
}

list_t* dict_keys(dict_t* dict) {
	list_t* keys = NULL;
	while(dict != NULL) {
		switch(dict->ktype) {
			case INTEGER: list_append(&keys, dict->ktype, dict->kint); break;
			case STRING: list_append(&keys, dict->ktype, dict->kstring); break;
			case CHARACTER: list_append(&keys, dict->ktype, dict->kint); break;
			case FLOAT: list_append(&keys, dict->ktype, dict->kfloat); break;
			case BOOL: list_append(&keys, dict->ktype, dict->kint); break;
		}
		dict = dict->right;
	}
	return keys;
}

bool dict_has_key(dict_t* dict, int ktype, ...) {
	va_list varg;
	va_start(varg, ktype);
	dict_t* query = NULL;
	switch(ktype) {
		case INTEGER: query = dict_get(dict, ktype, va_arg(varg, int)); break;
		case STRING: query = dict_get(dict, ktype, va_arg(varg, char*)); break;
		case CHARACTER: query = dict_get(dict, ktype, va_arg(varg, int)); break;
		case FLOAT:
			#if _WIN32
				query = dict_get(dict, ktype, va_arg(varg, double));
			#else
				query = dict_get(dict, ktype, va_arg(varg, long double));
			#endif
			break;
		case BOOL: query = dict_get(dict, ktype, va_arg(varg, int)); break;
	}
	va_end(varg);
	if(query != NULL) { return true; }
	return false;
}

void dict_printf(dict_t* dict, const char* sep, char end) {
	printf("{");
	while(dict != NULL) {
		switch(dict->ktype) {
			case INTEGER: printf("%d: ", dict->kint); break;
			case STRING: printf("\"%s\": ", dict->kstring); break;
			case CHARACTER: printf("'%c': ", dict->kint); break;
			case FLOAT: printf("%Lf: ", dict->kfloat); break;
		}
		switch(dict->type) {
			case INTEGER: printf("%d", dict->integer); break;
			case STRING: printf("\"%s\"", dict->string); break;
			case CHARACTER: printf("'%c'", dict->integer); break;
			case FLOAT: printf("%Lf", dict->floatt); break;
			case LIST: list_printf(dict->list, sep, end); break;
			case DICT: dict_printf(dict->left, sep, end); break;
		}
		if(dict->right != NULL) {
			printf("%s", sep);
		}
		dict = dict->right;
	}
	printf("}%c", end);
}

void dict_print_optype(dict_t* dict, int optype) {
	printf("{");
	while(dict != NULL) {
		switch(dict->ktype) {
			case INTEGER: printf("%d: ", dict->kint); break;
			case STRING: printf("\"%s\": ", dict->kstring); break;
			case CHARACTER: printf("'%c': ", dict->kint); break;
			case FLOAT: printf("%Lf: ", dict->kfloat); break;
		}
		switch(dict->type) {
			case INTEGER: printf("%d", dict->integer); break;
			case STRING: printf("\"%s\"", dict->string); break;
			case CHARACTER: printf("'%c'", dict->integer); break;
			case FLOAT: printf("%Lf", dict->floatt); break;
			case LIST: list_printf(dict->list, ", ", '\0'); break;
			case DICT: dict_printf(dict->left, ", ", '\0'); break;
		}
		if(optype == 1) {
			break;
		}
		if(dict->right != NULL) {
			printf(", ");
		}
		dict = dict->right;
	}
	printf("}\n");
}

void dict_printq(dict_t* dict) {
	if(dict == NULL) { return; }
	if(dict->type == INTEGER || dict->type == BOOL) {
		printf("%d\n", dict->integer);
	} else if(dict->type == CHARACTER) {
		printf("'%c'\n", dict->integer);
	} else if(dict->type == STRING) {
		printf("\"%s\"\n", dict->string);
	} else if(dict->type == FLOAT) {
		printf("%Lf\n", dict->floatt);
	} else if(dict->type == LIST) {
		list_print(dict->list);
	} else if(dict->type == DICT) {
		dict_print(dict->left);
	}
}
// TODO Fix dict_print
void dict_print(dict_t* dict) {
	dict_print_optype(dict, P_ALL);
}

// TODO fix dict_free
void dict_free(dict_t* dict) {
	while(dict != NULL) {
		if(dict->kstring != NULL) {
			free(dict->kstring);
			dict->kstring = NULL;
		}
		if(dict->string != NULL) {
			free(dict->string);
			dict->string = NULL;
		}
		if(dict->list != NULL) {
			list_free(dict->list);
			dict->list = NULL;
		}
		if(dict->left != NULL) {
			dict_free(dict->left);
			dict->left = NULL;
		}
		dict_t* temp = dict->right;
		free(dict);
		dict = temp;
	}
}
