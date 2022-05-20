#include "dictionary.h"
void dict_insert(dict_t** dict, int ktype, int type, ...) {
	va_list varg;
	va_start(varg, type);
	dict_t* new_node = NULL, *temp = *dict, *result = NULL;
	int key_int = 0;
	char* key_string = NULL, *str = NULL;
	long double key_float = 0;
	switch(ktype) {
		case INTEGER:
			key_int = va_arg(varg, int);
			dict_query(&result, dict, ktype, key_int);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_int, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case STRING:
			key_string = va_arg(varg, char*);
			dict_query(&result, dict, ktype, key_string);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_string, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_string, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
			}
			break;
		case CHARACTER:
			key_int = va_arg(varg, int);
			dict_query(&result, dict, ktype, key_int);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_int, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case FLOAT:
			#ifdef _WIN32
				key_float = va_arg(varg, double);
			#else
				key_float = va_arg(varg, long double);
			#endif
			dict_query(&result, dict, ktype, key_float);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_float, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_float, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
			}
			break;
		case BOOL:
			key_int = va_arg(varg, int);
			dict_query(&result, dict, ktype, key_int);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_int, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
	}
	va_end(varg);
	if(result != NULL) {
	return;
	}
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
	dict_t* new_node = NULL, *result = NULL;
	int key_int = 0;
	char* key_string = NULL, *str = NULL;
	long double key_float = 0;
	switch(ktype) {
		case INTEGER:
			key_int = va_arg(varg, int);
			dict_query(&result, dict, ktype, key_int);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list); result->list = NULL;
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_int, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_safe_free(&result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list); result->list = NULL;
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case STRING:
			key_string = va_arg(varg, char*);
			dict_query(&result, dict, ktype, key_string);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_string, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_string, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_string, va_arg(varg, int)); break;
			}
			break;
		case CHARACTER:
			key_int = va_arg(varg, int);
			dict_query(&result, dict, ktype, key_int);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_int, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
		case FLOAT:
			#ifdef _WIN32
				key_float = va_arg(varg, double);
			#else
				key_float = va_arg(varg, long double);
			#endif
			dict_query(&result, dict, ktype, key_float);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_float, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_float, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_float, va_arg(varg, int)); break;
			}
			break;
		case BOOL:
			key_int = va_arg(varg, int);
			dict_query(&result, dict, ktype, key_int);
			switch(type) {
				case INTEGER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int));
					break;
				case CHARACTER:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
				case FLOAT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						#ifdef _WIN32
							result->floatt = va_arg(varg, double);
						#else
							result->floatt = va_arg(varg, long double);
						#endif
						break;
					}
					#ifdef _WIN32
						new_node = dict_create(ktype, type, key_int, va_arg(varg, double));
					#else
						new_node = dict_create(ktype, type, key_int, va_arg(varg, long double));
					#endif
					break;
				case STRING:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						str = va_arg(varg, char*);
						if(str != NULL) {
							size_t len = strlen(str);
							if(len != 0) {
								result->string = calloc(len, sizeof(char*));
								strcpy(result->string, str);
							}
						}
						break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, char*)); break;
				case LIST:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->list = va_arg(varg, list_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, list_t*)); break;
				case DICT:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->dict = va_arg(varg, dict_t*); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, dict_t*)); break;
				case BOOL:
					if(result != NULL) {
						result->type = type;
						if(result->string != NULL) {
							free(result->string); result->string = NULL;
						}
						if(result->dict != NULL) {
							dict_free(result->dict); result->dict = NULL;
						}
						if(result->list != NULL) {
							list_safe_free(&result->list);
						}
						result->integer = va_arg(varg, int); break;
					}
					new_node = dict_create(ktype, type, key_int, va_arg(varg, int)); break;
			}
			break;
	}
	va_end(varg);
	if(result != NULL) {
		return;
	} 
	if(*dict == NULL) {
		*dict = new_node;
		return;
	}
	(*dict)->tail->right = new_node;
	(*dict)->tail = (*dict)->tail->right;
}
