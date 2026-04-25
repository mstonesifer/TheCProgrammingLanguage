#include <stdio.h>

/* k&r exercise 4-12 */

/*
 * Adapt the ideas of `printd` to write a recursive version
 * of itoa; that is, convert an integer into a string by
 * calling a recursive function
 */

/* prototypes */
void itoa(char[], int);

int main(void)
{
	int num = 123;
	char t[5];
	itoa(t, num);
	printf("The number %i as a string is %s\n", num, t);
	return 0;
}

/* itoa:  converts int n to string s */
void itoa(char s[], int n)
{
	static int i = 0;

	if (n < 0) {
		s[i++] = '-';
		n = -n;
	}
	if (n / 10)
		itoa(s, n / 10);
	s[i++] = n % 10 + '0';
	if (n % 10)
		s[i] = '\0';
}
