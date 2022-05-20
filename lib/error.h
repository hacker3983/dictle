#ifndef _ERRORS_H
#define _ERRORS_H
extern int error_type;
enum errors {
	EFORMAT = 1, // invalid format
	ETYPE, // invalid type
	EINVNUM, // invalid number
	EMQSTRING, // string missing quote termination
	ESYNTAX, // invalid syntax
	EINVCHAR, // invalid character
	EMQCHAR // character missing quote termination
};
#endif
