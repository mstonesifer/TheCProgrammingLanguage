#include <stdio.h>

/* k&r exercise 5-1 */

/* macros */
#define SIZE 100

/* prototypes */
int getint(int *);

/*
 * Exercise description:
 * As written, `getint` treats a + or - not followed by a digit
 * as a valid representation of zero. Fix it to push such a
 * character back on the input.
 * This was a terrible exercise because it lends itself to very
 * confusing outputs as pushing the character back onto the buffer
 * results in the same behavior as the example making it difficult
 * to determin if the program is behaving as expected.
 * The correct way to handle would not be to push back onto the
 * input rather early exit if a non-digit were entered. Thus,
 * treating a + or - followed by a non-digit would result in the
 * program terminating instead of pushing anything back and
 * carrying on as usual.
 */
int main(int argc, char *argv[])
{
	int n, array[SIZE];	

	for (n = 0; n < SIZE; n++)
		array[n] = 0;

	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		;

	for (n = 0; n < 10; n++)
		printf("array index %i holds value %i\n", n, array[n]);
	return 0;
}

/* functions */

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint:  get next integer from input into *pn */
int getint(int *pn)
{
	int c, t, sign;

	while (isspace(c = getch()))	/* skip white space */
		;
	printf("c is now %c\n", c);
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		printf("putting %c back on input\n", c);
		ungetch(c);		/* it's not a number  */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if ((c == '+' || c == '-')) {
		c = getch();
		if (!isdigit(c) && c != EOF) {
			printf("putting %c back on input\n", c);
			ungetch(c);
			return 0;
		}
	}
//	if (c == '+' || c == '-')
//		c = getchar();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	printf("returning %i when *pn is %i\n", c, *pn);
	return c;
}


#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int  bufp = 0;          /* next free position in buf */

/* get a (possibly pushed back) character */
int getch(void)
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
}
