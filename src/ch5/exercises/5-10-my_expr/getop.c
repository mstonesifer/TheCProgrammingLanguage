#include <stdio.h>
#include <ctype.h>
#include "my_expr.h"

#define MINUS 1

static int isminus(char *);

/* getop:  get next operator or numeric operand */
int getop(char *s, char *o)
{
	if (isminus(o) || !isdigit(*o) && *o != '.' && *o != '-') {
		return *o;		/* not a number */
	}
	if (*o == '-')
		*s++ = *o++;
	if (isdigit(*o))	/* collect integer part */
		while (isdigit(*s++ = *o++) && *o != '\0')
			;
	if (*o == '.')			/* collect fraction part */
		while (isdigit(*s++ = *++o) && *o != '\0')
			;
	
	*s = '\0';
	return NUMBER;
}

static int isminus(char *o)
{
	if (*o != '-')
		return 0;			/* not a minus */
	
	return (isdigit( *(o+1) )) ? 0 : MINUS;	/* a digit means negative */
}

