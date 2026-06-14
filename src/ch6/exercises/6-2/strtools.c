#include <stdio.h>
#include <stdlib.h>
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


/* my_atoi:  convert s to integer */
int my_atoi(char *s)
{
	int n;
       	int sign = 1;

	/* skip whitespace */
	while (SPAC == *s || TABC == *s)
		s++;

	/* set sign */
	if (HYPC == *s) {
		s++;
		sign = -1;
	}

	for (n = 0; isdigit(*s); s++)
	       n = (n * 10) + num_val(*s);

	return n;
}

/* strcopy:  copy t into s, assumes s is large enough */
void strcopy(char *s, char *t)
{
	while (NULC != (*s++ = *t++))
		;
}

/* strdupe:  make a duplicate of s */
char *strdupe(char *s)
{
	char *p;

	p = (char *) malloc(strlength(s)+1);	/* +1 for '\0' */
	if (p != NULL)
		strcopy(p, s);
	return p;
}

/* strlength:  get length of s */
int strlength(char *s)
{
	int i;
	while (i++ < MAXWORDLEN && NULC != *s++)
		;
}
