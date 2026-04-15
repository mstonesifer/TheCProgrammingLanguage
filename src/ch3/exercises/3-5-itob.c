#include <stdio.h>
#include <string.h>
#include <limits.h>

/* k&r exercise 3-5 */

/* macros */

/* prototypes */
void itob(int, char [], int);
void reverse(char []);

/*
 * Write the function `itob(n, s, b)` that converts the integer
 * n into a base b character representation in the string s.
 * In particular, `itob(n, s, 16)` formats n as a hexidecimal
 * integer in s.
 */
int main(int argc, char *argv[])
{
	int i = 19;
	char s[16];

	itob(i, s, 2);
	printf("i is %i\ns is %s\n", i, s);
	return 0;
}

/* itob: converts integer n into a base char representation
 * in the string s. */
void itob(int n, char s[], int b)
{
	int i, t;
	int sign = 1;			/* assume positive */

	if (n < 0)
		sign = -sign;		/* flip sign */

	i = 0;
	do {
		t = (n % b * sign);	/* get next digit */
		/*  use next digit to determine add '0' or 'a' */
		if (t >= 10)
			t += 'a' - 10;
		else
			t += '0';

		s[i++] = t;		/* save */
	} while (n /= b);		/* delete it */
	if (sign < 0)
		s[i++] = '-';
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

