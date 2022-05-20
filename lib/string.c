#include <stdio.h>
#include "string.h"

void string_init(string_t* string, char* buff) {
	if(buff == NULL) {
		string->size = 0;
		string->buff = calloc(1, sizeof(char*));
	} else {
		string->size = strlen(buff);
		string->buff = calloc(string->size, sizeof(char*));
	}
	if(buff != NULL) {
		strcpy(string->buff, buff);
	}
}

void string_reinit(string_t* string) {
	string_free(string);
	string_init(string, NULL);
}

void string_push_char(string_t* string, char c) {
	char* temp = string->buff;
	string->buff = calloc(string->size+1, sizeof(char*));
	strcpy(string->buff, temp);
	string->buff[string->size] = c;
	string->size++;
	free(temp);
}

void string_append(string_t* string, char* buff) {
	char* temp = string->buff;
	string->size += strlen(buff);
	string->buff = calloc(string->size, sizeof(char*));
	strcpy(string->buff, temp);
	strcat(string->buff, buff);
	free(temp);
}

void string_concat(string_t* string, char* format, ...) {
	va_list varg;
	va_start(varg, format);
	size_t i=0;
	while(format[i]) {
		if(format[i] == '%') {
			i++;
			/* Conversion specifiers / format characters
			 * % - modulo symbol just concatenates the '%' symbol in the string_t* string structure
			 * c - used for concatenating (formatting) a character in the string_t* string structure
			 * d - used for concatenating (formatting) a integer in the string_t* string structure
			 * s - used for concatenating (formatting) a string in the string_t* string structure
			 * f - used for concatenating (formatting) a float in the string_t* string structure
			 * S - used for concatenating (formatting) a string within a string_t structure
			 * if a format character is not valid then it is just concatinated within the string_t* string structure
			*/
			switch(format[i]) {
				case '%': string_push_char(string, '%'); break;
				case 'c': string_push_char(string, (char)va_arg(varg, int)); break;
				case 'd': {
					int i = va_arg(varg, int), j = int_getlen(i);
					char buff[j];
					memset(buff, 0, j);
					sprintf(buff, "%d", i);
					string_append(string, buff);
					break;
				}
				case 's': string_append(string, va_arg(varg, char*)); break;
				case 'f': {
					#ifdef _WIN32
					  	double d = va_arg(varg, double);
						int len = double_getlen(d), len_d = double_getlen_adec(d),
						    fmt_len = int_len(len_d)+4;
						char buff[len+1], fmt_str[fmt_len];
						memset(buff, 0, len+1);
						memset(fmt_str, 0, fmt_len);
						sprintf(fmt_str, "%%.%df", len_d);
						sprintf(buff, fmt_str, d);
						string_append(string, buff);
					#else
						long double ld = va_arg(varg, long double);
						int len = ldouble_getlen(ld), len_d = ldouble_getlen_adec(ld),
						    fmt_len = int_getlen(len_d)+4;
						char buff[len+1], fmt_str[fmt_len];
						memset(buff, 0, len+1);
						memset(fmt_str, 0, fmt_len);
						sprintf(fmt_str, "%%.%dLf", len_d);
						sprintf(buff, fmt_str, ld);
						string_append(string, buff);
					#endif
					break;
				}
				case 'S': {
					string_t temp = va_arg(varg, string_t);
					string_append(string, temp.buff);
					break;
				}
				case 'b': string_append(string, va_arg(varg, int) ? "true" : "false"); break;
				default: string_push_char(string, format[i]);
			}
			i++;
			continue;
		}
		string_push_char(string, format[i]);
		i++;
	}
	va_end(varg);
}

void string_print(string_t string) {
	printf("%s\n", string.buff);
}

void string_free(string_t* string) {
	free(string->buff); string->buff = NULL;
	string->size = 0;
}

// list of strings
void strings_init(strings_t* strings) {
	strings->array = calloc(1, sizeof(char*));
	strings->size = 0;
}

void strings_append(strings_t* strings, char* buff) {
	if(buff != NULL) {
		strings->array[strings->size] = calloc(strlen(buff), sizeof(char*));
		strcpy(strings->array[strings->size++], buff);
	} else {
		strings->array[strings->size] = calloc(1, sizeof(char*));
	}
	strings->array = realloc(strings->array, (strings->size+1) * sizeof(char*));
	strings->array[strings->size] = NULL;
}

void strings_print(strings_t strings) {
	printf("[");
	for(size_t i=0;i<strings.size;i++) {
		printf("\"%s\"", strings.array[i]);
		if(i != strings.size-1) {
			printf(", ");
		}
	}
	printf("]\n");
}

void strings_free(strings_t* strings) {
	for(size_t i=0;i<strings->size;i++) {
		free(strings->array[i]); strings->array[i] = NULL;
	}
	free(strings->array); strings->array = NULL;
	strings->size = 0;
}
