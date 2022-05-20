#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "numbers.h"

int int_getlen(int i) {
	int len = 0, divisor = 10;
	if(i == 0) {
		return 1;
	}
	// if integer i is negative then make divisor -10
	if(i < 0) {
		divisor = -10;
	}

	while(i != 0) {
		len++; i++;
		i /= divisor;
		if(divisor == -10) {
			divisor *= -1;
		}
	}
	return len;
}

int float_getlen(float f) {
	float f2 = 0;
	int len = 1;
	while(1) {
		char buff[len];
		memset(buff, 0, len);
		snprintf(buff, len+1, "%f", f);
		f2 = strtof(buff, NULL);
		len++;
		if(f == f2) {
			len = strlen(buff);
			break;
		}
	}
	return len;
}

int float_getlen_adec(float f) {
	int len = float_getlen(f), i = 0;
	char buff[len], *ptr = NULL;
	snprintf(buff, len+1, "%f", f);
	int found = 0;
	while(buff[i]) {
		if(buff[i] == '.') {
			// skip the decimal point if found so we can count the amount of digits after the decimal point
			i++;
			found = 1;
			break;
		}
		i++;
	}
	len = 0;
	while(buff[i]) { len++; i++; }
	if(!found) {
		len = 1;
	}
	return len;
}

int double_getlen(double d) {
	double d2 = 0;
	int len = 1;
	while(1) {
		char buff[len];
		memset(buff, 0, len);
		snprintf(buff, len+1, "%f", d);
		d2 = strtod(buff, NULL);
		len++;
		if(d == d2) {
			len = strlen(buff);
			break;
		}
	}
	return len;
}

int double_getlen_adec(double d) {
	int len = double_getlen(d), i = 0;
	char buff[len], *ptr = NULL;
	snprintf(buff, len+1, "%f", d);
	int found = 0;
	while(buff[i]) {
		if(buff[i] == '.') {
			// skip the decimal point if found so we can count the amount of digits after the decimal point
			i++;
			found = 1;
			break;
		}
		i++;
	}
	len = 0;
	while(buff[i]) { len++; i++; }
	if(!found) {
		len = 1;
	}
	return len;
}

int ldouble_getlen(long double ld) {
	int len = 50000, len2 = 1;
	char buff[len];
	memset(buff, 0, len);
	sprintf(buff, "%Lf", ld);
	len = strlen(buff)-1;
	while(buff[len] == '0') {
		len--;
	}
	len++;
	return len;
}

int ldouble_getlen_adec(long double ld) {
	int len = ldouble_getlen(ld), i = 0;
	char buff[len], *ptr = NULL;
	snprintf(buff, len+1, "%Lf", ld);
	int found = 0;
	while(buff[i]) {
		if(buff[i] == '.') {
			// skip the decimal point if found so we can count the amount of digits after the decimal point
			i++;
			found = 1;
			break;
		}
		i++;
	}
	len = 0;
	while(buff[i]) { len++; i++; }
	if(!found) {
		len = 1;
	}
	return len;
}

bool ldouble_eq(long double ld, long double ld2) {
	int len = ldouble_getlen(ld), len2 = ldouble_getlen(ld2);
	char buff[len], buff2[len2];
	snprintf(buff, len+1, "%Lf", ld);
	snprintf(buff2, len2+1, "%Lf", ld2);
	if(strcmp(buff, buff2) == 0) {
		return true;
	}
	return false;
}
