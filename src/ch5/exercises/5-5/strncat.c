#include <stdio.h>

/* k&r exercise 5-5 */

/* macros */
#define SIZE 32

/* prototypes */
void my_strncat(char *, char *, int);

/*
 * Exercise description:
 * Write versions of library functions which operate
 * on at most the first n characters of their argument
 * strings. Full descriptions are in Appendix B.
 */
int main(int argc, char *argv[])
{
	char s[SIZE] = "Hello,";
	char t[] = " World!";
	my_strncat(s, t, 3);
	printf("%s\n", s);
	return 0;
}

/* functions */
void my_strncat(char *s, char *t, int n)
{
	int i;

	while (*s++)		/* find end of s */
		;
	s--;			/* get back to end of string */
	for (i = 0; i < n; i++)	/* load n of t into s */
	       *s++ = *t++;
}
