#include <stdio.h>
#include <string.h>
#include <limits.h>
/* k&r exercise 3-4 */

/* macros */


/* prototypes */
void itoa(int, char []);
void reverse(char s[]);
/*
 * In a twos compliment number representation, our version of
 * `itoa` does not handle the largest negative number, that is,
 * the value of n equal to -(2^(wordsize-1)). Explain why not.
 * Modify it to print that value correctly, regardless of the
 * machine on which it is run.
 */

/* explanation: since we first check the sign and make n positive,
 * we limit the max possible value to 2^(wordsize-1)-1. Attempting 
 * to multiply by -1 is ineffective resulting in no change in the
 * sign bit. To resolve, we can make the whole operation slightly
 * less optimal by multiplying by sign when getting digits */
int main(int argc, char *argv[])
{
	int i = INT_MAX;
	char s[16];
	i++;
	itoa(i, s);	
	printf("i is %i\ns is %s\n", i, s);
	return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
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
