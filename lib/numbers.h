#ifndef _NUMBERS_H
#define _NUMBERS_H
#include <stdbool.h>
// gets the length of a integer
int int_getlen(int i);

// gets the length of a float
int float_getlen(float f);
// gets the length of a float
int float_getlen_adec(float f);

// gets the length of a double
int double_getlen(double d);
// gets the length of a double
int double_getlen_adec(double d);

// gets the length of a long double
int ldouble_getlen(long double ld);
// gets the length of a long double
int ldouble_getlen_adec(long double ld);
// compare long double ld with ld2
bool ldouble_eq(long double ld, long double ld2);
#endif
