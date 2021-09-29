#include "list.h"

list_t* list_create(int type, ...) {
	list_t* new_node = calloc(1, sizeof(list_t));
	va_list varg;
	va_start(varg, type);
	char* str;
	switch(type) {
		case INTEGER:
			new_node->type = INTEGER;
			new_node->integer = va_arg(varg, int);
			break;
		case STRING:
			str = va_arg(varg, char*);
			new_node->type = STRING;
			if(str != NULL) {
				new_node->length = strlen(str);
				if(new_node->length != 0) {
					new_node->string = calloc(new_node->length, sizeof(char*));
					strcpy(new_node->string, str);
				}
			}
			break;
		case CHARACTER:
			new_node->type = CHARACTER;
			new_node->integer = va_arg(varg, int);
			break;
		case FLOAT:
			new_node->type = FLOAT;
			#ifdef _WIN32
				new_node->floatt = va_arg(varg, double);
			#else
				new_node->floatt = va_arg(varg, long double);
			#endif
			break;
		default: list_adderr(&new_node, TYPE_ERROR, "invalid type \033[1m'%c'\033[0m\n", type);
	}
	new_node->tail = new_node;
	va_end(varg);
	return new_node;
}

void list_insert(list_t** list, int type, ...) {
	va_list varg;
	va_start(varg, type);
	list_t* new_node = NULL;
	switch(type) {
		case INTEGER: new_node = list_create(type, va_arg(varg, int)); break;
		case STRING: new_node = list_create(type, va_arg(varg, char*)); break;
		case CHARACTER: new_node = list_create(type, va_arg(varg, int)); break;
		case FLOAT:
			#ifdef _WIN32
				new_node = list_create(type, va_arg(varg, double));
			#else
				new_node = list_create(type, va_arg(varg, long double));
			#endif
			break;
	//	default: list_adderr(list, TYPE_ERROR, "invalid type \033[1m'%d'\033[0m\n", type);
	}
	if(*list == NULL) {
		*list = new_node;
		return;
	}
	new_node->next = *list;
	new_node->tail = new_node->next->tail;
	*list = new_node;
	va_end(varg);
}

void list_append(list_t** list, int type, ...) {
	va_list varg;
	va_start(varg, type);
	list_t* new_node = NULL, *temp = *list;
	switch(type) {
		case INTEGER: new_node = list_create(type, va_arg(varg, int)); break;
		case STRING: new_node = list_create(type, va_arg(varg, char*)); break;
		case CHARACTER: new_node = list_create(type, va_arg(varg, int)); break;
		case FLOAT:
			#ifdef _WIN32
				new_node = list_create(type, va_arg(varg, double));
			#else
				new_node = list_create(type, va_arg(varg, long double));
			#endif
			break;
	//	default: list_adderr(list, TYPE_ERROR, "invalid type \033[1m'%d'\033[0m\n", type);
	}
	va_end(varg);
	if(*list == NULL) {
		*list = new_node;
		return;
	}
	temp->tail->next = new_node;
	temp->tail = new_node;
	va_end(varg);
}

void list_insert_optype(list_t** list, int optype, int type, ...) {
	va_list varg;
	va_start(varg, type);
	if(optype == OP_INSERT) {
		switch(type) {
			case INTEGER: list_insert(list, type, va_arg(varg, int)); break;
			case STRING: list_insert(list, type, va_arg(varg, char*)); break;
			case CHARACTER: list_insert(list, type, va_arg(varg, int)); break;
			case FLOAT:
				#ifdef _WIN32
					list_insert(list, type, va_arg(varg, double));
				#else
					list_insert(list, type, va_arg(varg, long double));
				#endif
				break;
			//default: list_adderr(list, TYPE_ERROR, "invalid type '%d'", type);
		}
		va_end(varg);
		return;
	}
	switch(type) {
		case INTEGER: list_append(list, type, va_arg(varg, int)); break;
		case STRING: list_append(list, type, va_arg(varg, char*)); break;
		case CHARACTER: list_append(list, type, va_arg(varg, int)); break;
		case FLOAT:
			#ifdef _WIN32
				list_append(list, type, va_arg(varg, double));
			#else
				list_append(list, type, va_arg(varg, long double));
			#endif
			break;
	//	default: list_adderr(list, TYPE_ERROR, "invalid type '%d'", type);
	}
	va_end(varg);
}

void list_insertf(list_t** list, int optype, char* format, ...) {
	va_list varg;
	size_t i=0;
	va_start(varg, format);
	while(format[i]) {
		if(format[i] == '%') {
			i++;
			if(format[i] != '\0' ) {
				switch(format[i]) {
					case 'd': list_insert_optype(list, optype, INTEGER, va_arg(varg, int)); break;
					case 's': list_insert_optype(list, optype, STRING, va_arg(varg, char*)); break;
					case 'c': list_insert_optype(list, optype, CHARACTER, va_arg(varg, int)); break;
					case 'f':
						#ifdef _WIN32
							list_insert_optype(list, optype, FLOAT, va_arg(varg, double));
						#else
							list_insert_optype(list, optype, FLOAT, va_arg(varg, long double));
						#endif
						break;
				//	default: list_adderr(list, FORMAT_ERROR, "invalid conversion specifier \033[1m'%c'\033[0m\n",
				//			format[i]);
				}
				continue;
			}
		//	list_adderr(list, FORMAT_ERROR, "Expected conversion specifier after \033[1m'%%' but found nothing\n");
			i--;
		}
		i++;
	}
	va_end(varg);
}

// TODO FIX list_adderr
void list_adderr(list_t** list, int error_type, const char* format, ...) {
	va_list varg;
	va_start(varg, format);
	size_t i=0, size = 0;
	if(*list == NULL) {
		return;
	}
	char* err_msg = calloc(1, sizeof(char*)), *str_errtype = NULL;
	switch(error_type) {
		case FORMAT_ERROR:
			str_errtype = "\033[1m\033[31mFormatError\033[37m:";
			size += strlen(str_errtype);
			err_msg = calloc(size, sizeof(char*));
			strcpy(err_msg, str_errtype);
			break;
		case TYPE_ERROR:
			str_errtype = "\033[1m\033[31mTypeError\033[37m:";
			size += strlen(str_errtype);
			err_msg = calloc(size, sizeof(char*));
			strcpy(err_msg, str_errtype);
			break;
	}
	char* temp = (*list)->error;
	(*list)->error_length += size;
	(*list)->error = calloc((*list)->error_length, sizeof(char*));
	strcpy((*list)->error, temp);
	strcat((*list)->error, err_msg);

	free(temp);
	free(err_msg);
	va_end(varg);
}

void list_print(list_t* list) {
	printf("[");
	while(list != NULL) {
		switch(list->type) {
			case INTEGER: printf("%d", list->integer); break;
			case STRING: (list->string != NULL) ? printf("\"%s\"", list->string) : printf("\"\""); break;
			case CHARACTER: printf("'%c'", list->integer); break;
			case FLOAT: printf("%Lf", list->floatt); break;
		}
		if(list->next != NULL) {
			printf(", ");
		}
		list = list->next;
	}
	printf("]\n");
}

void list_printf(list_t* list, const char* sep, char end) {
	printf("[");
	while(list != NULL) {
		switch(list->type) {
			case INTEGER: printf("%d", list->integer); break;
			case STRING: (list->string != NULL) ? printf("\"%s\"", list->string) : printf("\"\""); break;
			case CHARACTER: printf("'%c'", list->integer); break;
			case FLOAT: printf("%Lf", list->floatt); break;
		}
		if(list->next != NULL) {
			printf("%s", sep);
		}
		list = list->next;
	}
	printf("]%c", end);
}

void* list_index(list_t* list, size_t index) {
	size_t i=0;
	while(list != NULL) {
		if(i == index) {
			switch(list->type) {
				case INTEGER: return (int*)&list->integer;
				case STRING: return (char*)list->string;
				case CHARACTER: return (char*)&list->integer;
				case FLOAT:
					#ifdef _WIN32
						return (double*)&list->floatt;
					#endif
					return &list->floatt;
			}
		}
		i++;
		list = list->next;
	}
	return NULL;
}

int list_geterror(list_t* list) {
	if(list->error != NULL) {
		fprintf(stderr, ">>>>\tAn Error has occured!\t<<<<\n%s\n"
				">>>>\tAn Error has occured!\t<<<<\n", list->error);
		return 1;
	}
	return 0;
}

void list_free(list_t* list) {
	while(list != NULL) {
		list_t* temp = list->next;
		if(list->type == STRING && list->string != NULL) { free(list->string); }
		if(list->error != NULL) { free(list->error); }
		free(list);
		list = temp;
	}
}