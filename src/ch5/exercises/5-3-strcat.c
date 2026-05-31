#include <stdio.h>
#include <string.h>

/* k&r exercise 5-3 */

/* macros */
#define SIZE 32

/* prototypes */
void strcatp(char *, char *);

/*
 * Exercise description:
 * Write a pointer version of the function strcatp that
 * we showed in Chapter 2: `strcatp(s, t)` copies the
 * string t to the end of s.
 */
int main(int argc, char *argv[])
{
	int i;
	char s[SIZE] = "Hello,";
	char t[] = " World!";
	strcatp(s, t);
	printf("%s\n", s);
	return 0;
}

/* functions */
/* strcatp:  copies t to s; assumes s is large enough */
void strcatp(char *s, char *t)
{
	while (*s++)		/* find end of s */	
		;
	s--;			/* get back to end of string */
	while (*s++ = *t++)	/* load t into s */
		;
}
