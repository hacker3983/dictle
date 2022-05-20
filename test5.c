#include <stdio.h>
#include "lib/dictionary.h"

int main() {
	dict_t* user_accounts = NULL, *user_info = NULL;
	char* users_info[][5] = {
		{"catsanddogs", "Strongest password in the world 1234"},
		{"John Hammond", "Uncrackable 101*#()#(*$(*$#"},
		{"Imaginary friend 303", "IDK1234567890"},
		{"Nightwolf", "In the moonlight one two three ()#($#*$*#((#UOKDJLM<DJDFOIJDFIOU*(*#U**(#*(#*#**##**#(*#(*#(*(#"},
		{"null", "null, empty, nothing, none, nil, zero, i love zero, no one beats null, i'm void, i'm cool, always make me null"}
	};
	list_t* users = NULL;
	for(int i=0;i<sizeof(users_info)/sizeof(users_info[0]);i++) {
		user_info = dict_create(STRING, STRING, "Username", users_info[i][0]);
		dict_append(&user_info, STRING, STRING, "Password", users_info[i][1]);
		list_append(&users, DICT, user_info);
	}
	dict_append(&user_accounts, STRING, LIST, "User Accounts", users);
	dict_print(user_accounts);
	dict_free(user_accounts);
	return 0;
}
