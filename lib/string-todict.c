#include "dictionary.h"
#include <ctype.h>

#define tokchk_append() \
	if(tok.buff != NULL) { \
		strings_append(&tokens, tok.buff); \
		string_free(&tok); \
	}


int error_type = 0;
string_t get_string(size_t* i, const char* fmt) {
	size_t j = *i;
	string_t tok;
	string_init(&tok, NULL);
	j++;
	while(fmt[j] != '"') {
		if(fmt[j] == '\0') {
			string_free(&tok);
			error_type = EMQSTRING;
			*i = j;
			return tok;
		}
		string_push_char(&tok, fmt[j]);
		j++;
	}
	*i = j;
	return tok;
}

string_t get_char(size_t* i, const char* fmt) {
	size_t j = *i;
	string_t tok;
	string_init(&tok, NULL);
	j++;
	while(fmt[j] != '\'') {
		if(fmt[j] == '\0') {
			string_free(&tok);
			error_type = EMQCHAR;
			*i = j;
			return tok;
		}
		string_push_char(&tok, fmt[j]);
		j++;
	}
	*i = j;
	return tok;
}
string_t get_int(size_t* i, const char* fmt) {
	string_t tok;
	string_init(&tok, NULL);
	size_t j = *i;
	if(fmt[j] == '+') {
		while(fmt[j] == '+') { j++; }
		string_push_char(&tok, '+');
	} else if(fmt[j] == '-') {
		while(fmt[j] ==  '-') { j++; }
		string_push_char(&tok, '-');
	}
	if(fmt[j] == '\0' || fmt[j] == ' ') {
		error_type = EINVNUM;
		*i = j;
		string_free(&tok);
		return tok;
	}
	while(isdigit(fmt[j])) {
		string_push_char(&tok, fmt[j]);
		j++;
	}
	if(fmt[j] != ' ' && fmt[j] != ':' && fmt[j] != ','
			&& fmt[j] != '}' && fmt[j] != ']') {
		error_type = EINVNUM;
	}
	j--; *i = j;
	return tok;
}

strings_t string_tokenize(const char* string) {
	strings_t tokens = {0};
	strings_init(&tokens);
	string_t tok = {0};
	size_t i = 0;
	if(string[i] == '{') {
		strings_append(&tokens, "{");
		i++;
	}
	while(string[i]) {
		if(string[i] == '"') {
			tokchk_append();
			strings_append(&tokens, "\"");
			tok = get_string(&i, string);
			if(error_type != 0) {
				strings_free(&tokens);
				return tokens;
			}
			strings_append(&tokens, tok.buff);
			strings_append(&tokens, "\"");
		//	printf("str_tok: %ld, %c\n", i, string[i]);
		//	strings_print(tokens);
			string_free(&tok);
		}else if(string[i] == '+' || string[i] == '-' || isdigit(string[i])) {
			tokchk_append();
			tok = get_int(&i, string);
			if(error_type != 0) {
				strings_free(&tokens);
				return tokens;
			}
		//	printf("int: %s\n", tok.buff);
			strings_append(&tokens, tok.buff);
			string_free(&tok);
		} else if(string[i] == '\'') {
			tokchk_append();
			tok = get_char(&i, string);
			if(error_type != 0) {
				strings_free(&tokens);
				return tokens;
			}
			strings_append(&tokens, "'");
			strings_append(&tokens, tok.buff);
			strings_append(&tokens, "'");
			string_free(&tok);
		} else if(string[i] == ':') {
			tokchk_append();
			strings_append(&tokens, ":");
		} else if(string[i] == '{') {
			tokchk_append();
			strings_append(&tokens, "{");
		} else if(string[i] == '}') {
			tokchk_append();
			strings_append(&tokens, "}");
		} else if(string[i] == '[') {
			tokchk_append();
			strings_append(&tokens, "[");
		} else if(string[i] == ']') {
			tokchk_append();
			strings_append(&tokens, "]");
		} else if(string[i] == ',') {
			tokchk_append();
			i++;
			continue;
		} else if(isspace(string[i])) {
			i++;
			continue;
		} else {
			if(tok.buff == NULL) {
				string_init(&tok, NULL);
			}
			string_push_char(&tok, string[i]);
		}
		i++;
	}
	string_free(&tok);
	return tokens;
}

char* parse_string(strings_t tokens, size_t* i) {
	char* string = NULL;
	size_t j = *i;
	j++;
	if(tokens.array[j] != NULL) {
		string = tokens.array[j];
		j++;
	}
	if(j == tokens.size-1) {
		fprintf(stderr, "Expected `\"` after end of string\n");
		return NULL;
	}
	if(strcmp(tokens.array[j], "\"") != 0) {
		fprintf(stderr, "Expected `\"` after end of string\n");
		return NULL;
	}
	*i = j;
	return string;
}

int parse_int(strings_t tokens, size_t* i) {
	char* str = tokens.array[*i];
	size_t j = 0;
	int integer = 0, type = 0;
	if(str[j] == '+') {
		while(str[j] == '+') { j++; }
	} else if(str[j] == '-') {
		while(str[j] == '-') { j++; } type = 1;
	}
	if(!isdigit(str[j])) {
		fprintf(stderr, "invalid integer: %s\n", str);
		return 0;
	}
	while(isdigit(str[j])) {
		integer = integer * 10 + (str[j] - '0');
		j++;
	}
	if(type == 1) { integer *= -1; }
	return integer;
}

int parse_char(strings_t tokens, size_t* i) {
	size_t j = *i, k = 0;
	int character = 0;
	j++;
	if(tokens.array[j] != NULL) {
		char* str = tokens.array[j];
		character = str[0];
		while(str[k]) {
			k++;
			if(k > 1) {
				fprintf(stderr, "invalid character: %s\n", str);
				return -1;
			}
		}
		j++;
	}
	if(tokens.array[j] == NULL) {
		fprintf(stderr, "expected \"'\" at end of character\n");
		return -1;
	}
	if(strcmp(tokens.array[j], "'") != 0) {
		fprintf(stderr, "expected \"'\" at end of character\n");
		return -1;
	}
	*i = j;
	return character;
}

bool parse_bool(strings_t tokens, size_t* i) {
	return strcmp(tokens.array[*i], "true") == 0 ? 1 : 0;
}

void parse_list(strings_t tokens, list_t** list, size_t* i) {
	char* str = NULL, character = 0;
	int integer = 0;
	(*i)++;
	//printf("size is: %ld\n", tokens.size);
	while(*i < tokens.size-1) {
		str = tokens.array[*i];
		if(strcmp(str, "]") == 0) {
			//printf("%s, index = %ld\n", tokens.array[*i], *i);
			break;
		}
		if(strcmp(str, "[") == 0) {
			list_t* new_node = NULL;
			parse_list(tokens, &new_node, i);
			//list_print(new_node);
			//printf("Appending list\n");
			list_append(list, LIST, new_node);
		} else if(strcmp(str, "\"") == 0) {
			str = parse_string(tokens, i);
			//printf("%s\n", str);
			list_append(list, STRING, str);
		} else if(strcmp(str, "'") == 0) {
			character = parse_char(tokens, i);
			list_append(list, CHARACTER, character);
		} else if(str[0] == '+' || str[0] == '-' || isdigit(str[0])) {
			integer = parse_int(tokens, i);
			///printf("Integer: %d\n", integer);
			list_append(list, INTEGER, integer);
		} else if(strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
			integer = parse_bool(tokens, i);
			list_append(list, BOOL, integer);
		} else if(strcmp(str, "{") == 0) {
			dict_t* dict = NULL;
			//printf("{%ld, %s\n", (*i), tokens.array[*i]);
			string_todict_toks(tokens, i, &dict, NULL);
			list_append(list, DICT, dict);
		}
		(*i)++;
	}
}

dict_t* string_todict(const char* fmt, ...) {
	strings_t tokens = {0};
	dict_t* dict = NULL;
	string_todict_toks(tokens, NULL, &dict, fmt);
	return dict;
}

void string_todict_toks(strings_t tokens, size_t *index, dict_t** dict, const char* fmt, ...) {
	if(index == NULL) {
		tokens = string_tokenize(fmt);
	}
	if(tokens.size == 0 && error_type != 0) {
		switch(error_type) {
			case EFORMAT: fprintf(stderr, "invalid format specifier\n"); break;
			case ETYPE: fprintf(stderr, "invalid datatype\n"); break;
			case EINVNUM: fprintf(stderr, "invalid number\n"); break;
			case EINVCHAR: fprintf(stderr, "invalid character\n"); break;
			case EMQSTRING: fprintf(stderr, "Expected `\"` to indicate the end of a string\n"); break;
			case ESYNTAX: fprintf(stderr, "invalid syntax\n"); break;
			case EMQCHAR: fprintf(stderr, "Expected `'` to indicate the end of a string\n"); break;
		}
		return;
	}
	if(index == NULL) {
		if(strcmp(tokens.array[0], "{") != 0 && strcmp(tokens.array[tokens.size-1], "}") != 0) {
			fprintf(stderr, "Expected '{' and '}' to indicate the start of the dictionary\n");
			strings_print(tokens);
			return;
		}
	}
	char* kstr = NULL, *str = NULL;
	int kint = 0, integer = 0;
	size_t i = 0;
	for(i=(index == NULL) ? 1 : *index;i<tokens.size-1;i++) {
		dict_t* dict2 = NULL, *list = NULL;
		str = tokens.array[i];
		if(str[0] == '"') {
			//printf("loop: %ld\n", i);
			kstr = parse_string(tokens, &i);
			//printf("key: %s\n", kstr);
			i++;
			str = tokens.array[i];
			if(strcmp(str, ":") == 0) {
				i++;
				str = tokens.array[i];
				if(str[0] == '"') {
					str = parse_string(tokens, &i);
					dict_append(dict, STRING, STRING, kstr, str);
				} else if(str[0] == '+' || str[0] == '-' || isdigit(str[0])) {
					integer = parse_int(tokens, &i);
					dict_append(dict, STRING, INTEGER, kstr, integer);
				} else if(str[0] == '\'') {
					integer = parse_char(tokens, &i);
					if(integer == -1) {
						strings_free(&tokens);
						dict_safe_free(dict);
						return;
					}
					dict_append(dict, STRING, CHARACTER, kstr, integer);
				} else if(strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
					integer = parse_bool(tokens, &i);
					dict_append(dict, STRING, BOOL, kstr, integer);
				} else if(strcmp(str, "[") == 0) {
					parse_list(tokens, &list, &i);
					dict_append(dict, STRING, LIST, kstr, list);
				} else if(strcmp(str, "{") == 0) {
					string_todict_toks(tokens, &i, &dict2, NULL);
					dict_append(dict, STRING, DICT, kstr, dict2);
				}
			}
		} else if(str[0] == '+' || str[0] == '-' || isdigit(str[0])) {
			kint = parse_int(tokens, &i);
			i++;
			str = tokens.array[i];
			if(strcmp(str, ":") == 0) {
				i++;
				str = tokens.array[i];
				if(str[0] == '"') {
					str = parse_string(tokens, &i);
					dict_append(dict, INTEGER, STRING, kint, str);
					continue;
				} else if(str[0] == '+' || str[0] == '-' || isdigit(str[0])) {
					integer = parse_int(tokens, &i);
					dict_append(dict, INTEGER, INTEGER, kint, integer);
				} else if(str[0] == '\'') {
					integer = parse_char(tokens, &i);
					if(integer == -1) {
						strings_free(&tokens);
						dict_safe_free(dict);
						return;
					}
					dict_append(dict, INTEGER, CHARACTER, kint, integer);
				} else if(strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
					integer = parse_bool(tokens, &i);
					dict_append(dict, INTEGER, BOOL, kint, integer);
				} else if(strcmp(str, "[") == 0) {
					parse_list(tokens, &list, &i);
					dict_append(dict, INTEGER, LIST, kint, list);
				} else if(strcmp(str, "{") == 0) {
					string_todict_toks(tokens, &i, &dict2, NULL);
					dict_append(dict, INTEGER, DICT, kint, dict2);
				}
			}
		} else if(str[0] == '\'') {
			kint = parse_char(tokens, &i);
			if(kint == -1) {
				strings_free(&tokens);
				dict_safe_free(dict);
				return;
			}
			i++;
			str = tokens.array[i];	
			if(strcmp(str, ":") == 0) {
				i++;
				str = tokens.array[i];	
				if(str[0] == '"') {
					str = parse_string(tokens, &i);
					dict_append(dict, CHARACTER, STRING, kint, str);
				} else if(str[0] == '+' || str[0] == '-' || isdigit(str[0])) {
					integer = parse_int(tokens, &i);
					dict_append(dict, CHARACTER, INTEGER, kint, integer);
				} else if(str[0] == '\'') {
					integer = parse_char(tokens, &i);
					if(integer == -1) {
						strings_free(&tokens);
						dict_safe_free(dict);
						return;
					}
					dict_append(dict, CHARACTER, CHARACTER, kint, integer);
				} else if(strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
					integer = parse_bool(tokens, &i);
					dict_append(dict, CHARACTER, BOOL, kint, integer);
				} else if(strcmp(str, "[") == 0) {
					parse_list(tokens, &list, &i);
					dict_append(dict, CHARACTER, LIST, kint, list);
				} else if(strcmp(str, "{") == 0) {
					string_todict_toks(tokens, &i, &dict2, NULL);
					dict_append(dict, CHARACTER, DICT, kint, dict2);
				}
			}
		} else if(strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
			kint = parse_bool(tokens, &i);
			i++;
			str = tokens.array[i];
			if(strcmp(str, ":") == 0) {
				i++;
				str = tokens.array[i];
				if(str[0] == '"') {
					str = parse_string(tokens, &i);
					dict_append(dict, BOOL, STRING, kint, str);
				} else if(str[0] == '+' || str[0] == '-' || isdigit(str[0])) {
					integer = parse_int(tokens, &i);
					dict_append(dict, BOOL, INTEGER, kint, integer);
				} else if(str[0] == '\'') {
					integer = parse_char(tokens, &i);
					if(integer == -1) {
						strings_free(&tokens);
						dict_safe_free(dict);
						return;
					}
					dict_append(dict, BOOL, CHARACTER, kint, integer);
				} else if(strcmp(str, "true") == 0 || strcmp(str, "false") == 0) {
					integer = parse_bool(tokens, &i);
					dict_append(dict, BOOL, BOOL, kint, integer);
				} else if(strcmp(str, "[") == 0) {
					parse_list(tokens, &list, &i);
					dict_append(dict, BOOL, LIST, kint, list);
				} else if(strcmp(str, "{") == 0) {
					string_todict_toks(tokens, &i, &dict2, NULL);
					dict_append(dict, BOOL, DICT, kint, dict2);
				}

			}
		} else if(strcmp(str, ",") == 0) {
			continue;
		}
		if(index != NULL && strcmp(str, "}") == 0) {
			break;
		}

	}
	if(index != NULL) {
		*index = i;
	}
	if(index == NULL) {
		strings_free(&tokens);
	}
}
