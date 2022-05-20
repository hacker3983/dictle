#include "dictionary.h"
// TODO: fix dict_replace_key by preventing the user from replacing a key with a already existing key
void dict_replace_key(dict_t** dict, int ktype1, int ktype2, ...) {
	va_list varg;
	va_start(varg, ktype2);
	char* key_string = NULL, *key_string2 = NULL;
	int key_int = 0, key_int2 = 0;
	long double key_float = 0, key_float2 = 0;
	switch(ktype1) {
		case INTEGER: key_int = va_arg(varg, int); break;
		case CHARACTER: key_int = va_arg(varg, int); break;
		case BOOL: key_int = (bool)va_arg(varg, int); break;
		case STRING: key_string = va_arg(varg, char*); break;
		case FLOAT:
			#ifdef _WIN32
				key_float = va_arg(varg, double);
			#else
				key_float = va_arg(varg, long double);
			#endif
			break;
	}
	switch(ktype2) {
		case INTEGER: key_int2 = va_arg(varg, int); break;
		case CHARACTER: key_int2 = va_arg(varg, int); break;
		case BOOL: key_int2 = (bool)va_arg(varg, int); break;
		case STRING: key_string2 = va_arg(varg, char*); break;
		case FLOAT:
			#ifdef _WIN32
				key_float2 = va_arg(varg, double);
			#else
				key_float2 = va_arg(varg, long double);
			#endif
			break;
	}
	if(ktype1 == ktype2) {
		switch(ktype1) {
			case INTEGER:
				if(key_int == key_int2) {
					return;
				}
				break;
			case CHARACTER:
				if(key_int == key_int2) {
					return;
				}
				break;
			case BOOL:
				if(key_int == key_int2) {
					return;
				}
				break;
			case STRING:
				if(list_streq(key_string, key_string2)) {
					return;
				}
				break;
			case FLOAT:
				if(key_float == key_float2) {
					printf("It works!\n");
					return;
				}
				break;
		}
	}
	switch(ktype2) {
		case INTEGER: dict_remove_key(dict, ktype2, key_int2); break;
		case CHARACTER: dict_remove_key(dict, ktype2, key_int2); break;
		case BOOL: dict_remove_key(dict, ktype2, key_int2); break;
		case STRING: dict_remove_key(dict, ktype2, key_string2); break;
		case FLOAT: dict_remove_key(dict, ktype2, key_float2); break;
	}
	dict_t* ref = *dict;
	int bk = 0;
	while(ref != NULL) {
		if(ref->ktype == ktype1) {
			switch(ref->ktype) {
				case INTEGER:
					if(ref->kint == key_int) {
						ref->ktype = ktype2; bk = 1;
					}
					break;
				case CHARACTER:
					if(ref->kint == key_int) {
						ref->ktype = ktype2; bk = 1;
					}
					break;
				case STRING:
					if(list_streq(ref->kstring, key_string)) {
						free(ref->kstring); ref->kstring = NULL;
						ref->ktype = ktype2; bk = 1;
					}
					break;
				case FLOAT:
					if(ref->kfloat == key_float) {
						ref->ktype = ktype2; bk = 1;
					}
					break;
				case BOOL:
					if(ref->kint == key_int) {
						ref->ktype = ktype2; bk = 1;
					}
					break;
			}
			if(bk) {
				break;
			}
		}
		ref = ref->right;
	}
	if(bk) {
		switch(ref->ktype) {
			case INTEGER: ref->kint = key_int2; break;
			case STRING:
				free(ref->kstring); ref->kstring = NULL;
				if(key_string2 != NULL) {
					size_t len = strlen(key_string2);
					if(len != 0) {
						ref->kstring = calloc(len, sizeof(char*));
						strcpy(ref->kstring, key_string2);
					}
				}
				break;
			case CHARACTER: ref->kint = key_int2; break;
			case FLOAT: ref->kfloat = key_float2; break;
			case BOOL: ref->kint = (bool)key_int2; break;
		}
	}
	va_end(varg);
}
