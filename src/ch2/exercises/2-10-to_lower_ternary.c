#include <stdio.h>

/* k&r exercise 2-10 */

/* prototypes */
int lower_ternary(int);

int main(void)
{
	char s[] = "HELLO, WORLD!";
	for (int i = 0; s[i] != '\0'; ++i)
		putchar(lower_ternary(s[i]));
	putchar('\n');
}

/* lower_ternary: convet c to lower case; ASCII only.
 * remark: uses a conditional operator */
int lower_ternary(int c)
{
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
