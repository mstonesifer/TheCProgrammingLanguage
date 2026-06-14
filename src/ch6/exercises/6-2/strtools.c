#include <stdio.h>
#include <ctype.h>
#include "varnames.h"

/* strcomp:  compare two strings, return 0 if equal */
int strcomp(char *s, char *t)
{
	if (*s != *t)
		return *s - *t;
	while (*(++s) == *(++t) && '\0' != *s)
		;
	if ('\0' == *s)
		return 0;
	return *s - *t;
}

int my_atoi(char *s)
{
	int n;
       	int sign = 1;

	/* skip whitespace */
	while (SPAC == *s || TABC == *s)
		s++;

	/* set sign */
	if ('-' == *s) {
		s++;
		sign = -1;
	}

	for (n = 0; isdigit(*s); s++)
	       n = (n * 10) + num_val(*s);

	return n;
}

void strcopy(char *s, char *t)
{
	while (NULC != (*s++ = *t++))
		;
}
