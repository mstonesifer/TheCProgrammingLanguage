#include <stdio.h>
#include <string.h>

/* k&r exercise 3-5 */

/* macros */

/* prototypes */
void itoa(int, char [], int);
void reverse(char []);

/*
 * Write a version of `itoa` that accepts three arguments
 * instead of two. The third argument is a minimum field
 * width. The converted number must be padded with blanks
 * on the left if necessary to make it wide enough.
 */
int main(int argc, char *argv[])
{
	int i, n, w;
	
	n = -98754389;
	w = 30;
	char s[w+1];		/* make sure array big enough */
	
	/* lets us see w columns */
	printf("%i#s ", w);	
	for (i = 0; i < w; ++i)
		printf("#");
	printf("\n");

	itoa(n, s, w);
	printf("n is %i\ns is %s\n", n, s);
	return 0;
}

/* itoa: converts an integer n to a string representation
 * in s. w is the minimum width where left whitespace
 * padding will be used to fill the space if necessary. */
void itoa(int n, char s[], int w)
{
	int i = 0;
	int sign = 1;		/* assume positive */

	if (n < 0)
		sign = -sign;	/* flip sign */

	do {
		s[i++] = (n % 10 * sign) + '0';	/* get next digit */
	} while (n /= 10);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	for (i = i; i < w; i++)
		s[i] = ' ';
	s[i] = '\0';
	reverse(s);
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

