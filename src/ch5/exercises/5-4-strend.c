#include <stdio.h>
#include <string.h>

/* k&r exercise 5-4 */

/* macros */


/* prototypes */
int strend(char *, char *);

/*
 * Exercise description:
 * Write the function strend(s, t) which returns 1
 * if the string t occurs at the end of the string
 * s, and zero otherwise.
 */
int main(int argc, char *argv[])
{
	int result;
	char first[] = "Hello, world!";
	char test[] = "orld!";
	char test2[] = "Hello";

	result = strend(first, test);
	printf("first result: %i\n", result);
	result = strend(first, test2);
	printf("second result: %i\n", result);

	return 0;
}

/* functions */
int strend(char *s, char *t)
{

	int tlen = strlen(t);	

	while (*s++)	/* find end of s */
		;
	s -= tlen;	/* go back length of t */
	while (*t++)
		if (*s++ != *t) /* any from here don't match it's different */
			return 0;
	return 1;
}
