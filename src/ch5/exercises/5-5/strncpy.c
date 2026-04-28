#include <stdio.h>

/* k&r exercise 5-5 */

/* macros */


/* prototypes */
void strncpy_two(char *, char *, int);

/*
 * Exercise description:
 * Write versions of library functions which operate
 * on at most the first n characters of their argument
 * strings. Full descriptions are in Appendix B.
 */
int main(int argc, char *argv[])
{
	char s[32];
	char t[] = "Hello, World!";

	strncpy_two(s, t, 9);
	printf("s is now '%s'\n", s);
	return 0;
}

/* functions */
/* strncpy_two:  copy at most the first n characts of t to s */
void strncpy_two(char *s, char *t, int n)
{
	int i;

	for (i = 0; i < n; i++)
		*(s+i) = *t++;
	*(s+i) = '\0';
}	
