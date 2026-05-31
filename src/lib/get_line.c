#include <stdio.h>
#include "mylib.h"

/* get_line:  reads a line of input into s; returns length */
int get_line(char *s, int n)
{
	int c, i;

	for (i = 0; i < n-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';

	return (c == EOF) ? i : ++i;
}
