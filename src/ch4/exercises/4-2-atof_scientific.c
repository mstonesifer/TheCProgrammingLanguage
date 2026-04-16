#include <ctype.h>
#include <stdio.h>

/* k&r exercise 4-2 */

/*
 * Extend atof to handle scientific notation of form
 * 	123.45e-6
 * where a floating point number may be followed by
 * e or E and an optionally signed exponent
 */

/* prototypes */
double atof(char []);
int pw(int, int);

int main()
{
	double result;
	char number[] = "123.45e-6";

	result = atof(number);
	printf("string \"%s\" expanded is %g\n", number, result);
	return 0;
}
/* atof:  convert string s to double */
double atof(char s[])
{
	double val, power, exp, mod;
	int i, sign;

	for (i = 0; isspace(s[i]); i++)	/* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E')
		i++;
	mod = (s[i] == '-') ? 0 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (exp = 1.0; isdigit(s[i]); i++)
	       exp *= pw(10, s[i] - '0');
	return (mod) ? (sign * (val / power) * exp) : (sign * (val / power) / exp);
}

int pw(int b, int p)
{
	int i;
	int base = b;
	for (i = 1; i < p; ++i)
		b *= base;
	return b;
}
