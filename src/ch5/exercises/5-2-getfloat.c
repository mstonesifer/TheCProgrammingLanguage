#include <stdio.h>
#include "getch.h"

/* k&r exercise 5-2 */

/* macros */
#define SIZE 50

/* prototypes */
int getfloat(float *);

/*
 * Exercise description:
 * Write `getfloat` the floating point analog to `getfloat`.
 * What does `getfloat` return as its function return
 * value?
 * int because the return value is used to signal to the
 * caller if EOF, a number, or non-number character
 * was found.
 */
int main(int argc, char *argv[])
{
	int n;
	float array[SIZE];

	for (n = 0; n < SIZE; n++)
		array[n] = 0;

	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		;

	for (n = 0; n < 10; n++)
		printf("array index %i holds value %f\n", n, array[n]);
	return 0;
}

/* functions */

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getfloat:  get next float from input into *pn */
int getfloat(float *pn)
{
	int c, sign, power;

	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);		/* it's not a number  */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if ((c == '+' || c == '-') && !isdigit(c = getch())) {
		ungetch(c);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');
	power = 1.0;
	if (c == '.') {
		while ((c = getch()) != EOF && isdigit(c)) {
			*pn = 10.0 * *pn + (c - '0'); 
			power *= 10.0;
		}
	*pn = sign * *pn / power;
	if (c != EOF)
		ungetch(c);
	return c;
	}
}
