#include "dictionary.h"

/* How the dictionary should look?
{"Person":{"Name":"John Doe", "Age": 10},
 "Nums":[10, 20, 30, 40],
 "Countries":["United States of America", "England", "China", "United Kingdom"],
 "Mixed_Types":["Discord is the best", 10, 'A', 99.9]
 "Days":{0:"Monday", 1:"Tuesday", 2:"Wednesday", 3:"Thursday", 4:"Friday", 5:"Saturday", 6:"Sunday"}
}
*/

dict_t* dict_create(int ktype, int type, void* key, ...) {
	va_list varg;
	va_start(varg, key);
	dict_t* dict = calloc(1, sizeof(dict_t));
	switch(ktype) {
		case INTEGER:
			dict->ktype = INTEGER;
			dict->kint = *(int*)key;
			break;
		case STRING:
			dict->ktype = STRING;
			if((char*)key != NULL) {
				size_t len = strlen((char*)key);
				if(len != 0) {
					dict->kstring = calloc(len, sizeof(char*));
					strcpy(dict->kstring, (char*)key);
				}
			}
			break;
		case CHARACTER:
			dict->ktype = CHARACTER;
			dict->kint = *(int*)key;
			break;
		case FLOAT:
			dict->ktype = FLOAT;
			#ifdef _WIN32
				dict->kfloat = *(double*)key;
			#else
				dict->kfloat = *(long double*)key;
			#endif
			break;

	}
	switch(type) {
		case INTEGER:
			dict->type = INTEGER;
			dict->integer = va_arg(varg, int);
			break;
		case STRING:
			dict->type = STRING;
			char* str = va_arg(varg, char*);
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
		/*case DICT:
			dict->type = DICT;
			dict->left = va_arg(varg, dict_t*);
			break;*/
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
void dict_insert(dict_t** dict, int ktype, int type, void* key, ...) {
	va_list varg;
	va_start(varg, key);
	dict_t* new_node = NULL, *temp = *dict;
	switch(type) {
		case INTEGER: new_node = dict_create(ktype, type, key, va_arg(varg, int)); break;
		case STRING: new_node = dict_create(ktype, type, key, va_arg(varg, char*)); break;
		case CHARACTER: new_node = dict_create(ktype, type, key, va_arg(varg, int)); break;
		case FLOAT:
			#ifdef _WIN32
				new_node = dict_create(ktype, type, key, va_arg(varg, double));
			#else
				new_node = dict_create(ktype, type, key, va_arg(varg, long double));
			#endif
			break;
		case LIST: new_node = dict_create(ktype, type, key, va_arg(varg, list_t*)); break;
		/*case DICT: new_node = dict_create(ktype, type, key, va_arg(varg, dict_t*)); break;*/
	}
	va_end(varg);
	if(*dict == NULL) {
		*dict = new_node;
		return;
	}
	// Create a new node
	// Assign values
	// add something to the left node
	new_node->right = temp;
	new_node->tail = new_node->right->tail;
	*dict = new_node;
}

void dict_append(dict_t** dict, int ktype, int type, void* key, ...) {
	va_list varg;
	va_start(varg, key);
	dict_t* new_node = NULL;
	switch(type) {
		case INTEGER: new_node = dict_create(ktype, type, key, va_arg(varg, int)); break;
		case STRING: new_node = dict_create(ktype, type, key, va_arg(varg, char*)); break;
		case CHARACTER: new_node = dict_create(ktype, type, key, va_arg(varg, int)); break;
		case FLOAT:
			#ifdef _WIN32
				new_node = dict_create(ktype, type, key, va_arg(varg, double));
			#else
				new_node = dict_create(ktype, type, key, va_arg(varg, long double));
			#endif
			break;
		case LIST: new_node = dict_create(ktype, type, key, va_arg(varg, list_t*)); break;
		/*case DICT: new_node = dict-create(ktype, type, key, va_arg(varg, dict_t*)); break;*/
	}
	va_end(varg);
	if(*dict == NULL) {
		*dict = new_node;
		return;
	}
	(*dict)->tail->right = new_node;
	(*dict)->tail = (*dict)->tail->right;
}

/*void dict_move(dict_t** dict, int dir) {
	
}*/

query_t dict_query(dict_t* dict, int ktype, void* key, ...) {
	query_t query = {0};
	while(dict != NULL) {
		switch(ktype) {
			case INTEGER: if(dict->kint == *(int*)key) { query.dict = dict; return query; } break;
			case STRING: if(strcmp(dict->kstring, (char*)key) == 0) { query.dict = dict; return query; } break;
			case CHARACTER: if(dict->kint == *(int*)key) { query.dict = dict; return query; } break;
			case FLOAT:
				#ifdef _WIN32
					if(dict->kfloat == *(double*)key) { query.dict = dict; return query; }
				#else
					if(dict->kfloat == *(long double*)key) { query.dict = dict; return query; }
				#endif
				break;
		}
		dict = dict->right;
	}
	return query;
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
			/*case DICT:
				break;*/
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

void dict_printq(query_t query) {
	dict_print_optype(query.dict, P_ONCE);
}
// TODO Fix dict_print
void dict_print(dict_t* dict) {
	dict_print_optype(dict, P_ALL);
}
// TODO fix dict_free
void dict_free(dict_t* dict) {
	dict_t *left = NULL, *right = NULL;
	while(dict != NULL) {
		if(dict->kstring != NULL) {
			free(dict->kstring);
		}
		if(dict->string != NULL) {
			free(dict->string);
		} else if(dict->list != NULL) {
			list_free(dict->list);
		} /*else if(dict->left != NULL) {
			left = dict->left->left, right = dict->left->right;
			if(dict->left->string != NULL) {
				free(dict->left->string);
                        }
			if(dict->left->list != NULL) {
				free(dict->left->list);
			}
			free(dict->left);
			dict->left = temp2;
		}*/
		free(dict);
		dict = dict->right;
	}
}
