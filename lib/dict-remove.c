#include "dictionary.h"

void dict_remove_key(dict_t** dict, int ktype, ...) {
	va_list varg;
	va_start(varg, ktype);
	dict_t* result = NULL, *temp = NULL;
	int key_int = 0;
	long double key_float = 0;
	char* key_string = NULL;
	if(*dict == NULL) {
		return;
	}
	switch(ktype) {
		case INTEGER:
			key_int = va_arg(varg, int);
			if((*dict)->ktype == ktype) {
				if((*dict)->kint == key_int) {
					temp = (*dict)->right;
					if((*dict)->string != NULL) {
						free((*dict)->string); (*dict)->string = NULL;
					}
					if((*dict)->list != NULL) {
						list_free((*dict)->list); (*dict)->list = NULL;
					}
					if((*dict)->dict != NULL) {
						dict_free((*dict)->dict); (*dict)->dict = NULL;
					}
					free(*dict); *dict = temp; return;
				}
			}
			break;
		case STRING:
			key_string = va_arg(varg, char*);
			if((*dict)->ktype == ktype) {
				if(list_streq((*dict)->kstring, key_string)) {
					temp = (*dict)->right;
					free((*dict)->kstring); (*dict)->kstring = NULL;
					if((*dict)->string != NULL) {
						free((*dict)->string); (*dict)->string = NULL;
					}
					if((*dict)->list != NULL) {
						list_free((*dict)->list); (*dict)->list = NULL;
					}
					if((*dict)->dict != NULL) {
						dict_free((*dict)->dict); (*dict)->dict = NULL;
					}
					free(*dict); *dict = temp; return;
				}
			}
			break;
		case CHARACTER:
			key_int = va_arg(varg, int);
			if((*dict)->ktype == ktype) {
				if((*dict)->kint == key_int) {
					temp = (*dict)->right;
					if((*dict)->string != NULL) {
						free((*dict)->string); (*dict)->string = NULL;
					}
					if((*dict)->list != NULL) {
						list_free((*dict)->list); (*dict)->list = NULL;
					}
					if((*dict)->dict != NULL) {
						dict_free((*dict)->dict); (*dict)->dict = NULL;
					}
					free(*dict); *dict = temp; return;
				}
			}
			break;
		case FLOAT:
			#if _WIN32
				key_float = va_arg(varg, double);
			#else
				key_float = va_arg(varg, long double);
			#endif
			if((*dict)->ktype == ktype) {
				if((*dict)->kfloat == key_float) {
					temp = (*dict)->right;
					if((*dict)->string != NULL) {
						free((*dict)->string); (*dict)->string = NULL;
					}
					if((*dict)->list != NULL) {
						list_free((*dict)->list); (*dict)->list = NULL;
					}
					if((*dict)->dict != NULL) {
						dict_free((*dict)->dict); (*dict)->dict = NULL;
					}
					free(*dict); *dict = temp; return;
				}
			}
			break;
		case BOOL:
			key_int = (bool)va_arg(varg, int);
			if((*dict)->ktype == ktype) {
				if((*dict)->kint == key_int) {
					temp = (*dict)->right;
					if((*dict)->string != NULL) {
						free((*dict)->string); (*dict)->string = NULL;
					}
					if((*dict)->list != NULL) {
						list_free((*dict)->list); (*dict)->list = NULL;
					}
					if((*dict)->dict != NULL) {
						dict_free((*dict)->dict); (*dict)->dict = NULL;
					}
					free(*dict); *dict = temp; return;
				}
			}
			break;
	}
	dict_t* ref = *dict;
	while(ref->right != NULL) {
		if(ref->right->ktype == ktype) {
			switch(ref->right->ktype) {
				case INTEGER:
					if(ref->right->kint == key_int) {
						printf("Memory Leak!\n\n");
						temp = ref->right->right;
						if(ref->right->string != NULL) {
							free(ref->right->string); ref->right->string = NULL;
						}
						if(ref->right->list != NULL) {
							list_free(ref->right->list); ref->right->list = NULL;
						}
						if(ref->right->dict != NULL) {
							dict_free(ref->right->dict); ref->right->dict = NULL;
						}
						free(ref->right); ref->right = temp; return;
					}
					break;
				case CHARACTER:
					if(ref->right->kint == key_int) {
						temp = ref->right->right;
						if(ref->right->string != NULL) {
							free(ref->right->string); ref->right->string = NULL;
						}
						if(ref->right->list != NULL) {
							list_free(ref->right->list); ref->right->list = NULL;
						}
						if(ref->right->dict != NULL) {
							dict_free(ref->right->dict); ref->right->dict = NULL;
						}
						dict_free(ref->right); ref->right = temp; return;
					}
					break;
				case STRING:
					if(list_streq(ref->right->kstring, key_string)) {
						temp = ref->right->right;
						free(ref->right->kstring); ref->right->kstring = NULL;
						if(ref->right->string != NULL) {
							free(ref->right->string); ref->right->string = NULL;
						}
						if(ref->right->list != NULL) {
							list_free(ref->right->list); ref->right->list = NULL;
						}
						if(ref->right->dict != NULL) {
							dict_free(ref->right->dict); ref->right->dict = NULL;
						}
						free(ref->right); ref->right = temp; return;
					}
					break;
				case FLOAT:
					if(ref->right->kfloat == key_float) {
						temp = ref->right->right;
						if(ref->right->string != NULL) {
							free(ref->right->string); ref->right->string = NULL;
						}
						if(ref->right->list != NULL) {
							list_free(ref->right->list); ref->right->list = NULL;
						}
						if(ref->right->dict != NULL) {
							dict_free(ref->right->dict); ref->right->dict = NULL;
						}
						free(ref->right); ref->right = temp; return;
					}
					break;
				case BOOL:
					if(ref->right->kint == key_int) {
						temp = ref->right->right;
						if(ref->right->string != NULL) {
							free(ref->right->string); ref->right->string = NULL;
						}
						if(ref->right->list != NULL) {
							list_free(ref->right->list); ref->right->list = NULL;
						}
						if(ref->right->dict != NULL) {
							dict_free(ref->right->dict); ref->right->dict = NULL;
						}
						free(ref->right); ref->right = temp; return;
					}
					break;
			}
		}
		ref = ref->right;
	}
	va_end(varg);
}
