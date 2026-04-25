#include <stdio.h>
#include <string.h>

/* k&r exercise 4-13 */

/*
 * Write a recursive verion of the function `reverse(s)`
 * which reverses the string s in place.
 */

/* prototypes */
void reverse(char[]);

int main(void)
{
	char t[] = "flip it!";
	printf("The string '%s' backwards is ", t);
	reverse(t);
	printf("'%s'\n", t);
	reverse(t);
	printf("backwards again is '%s'\n", t);
	return 0;
}

/* reverse:  reverse a string in place, recursively */
void reverse(char s[])
{
	static int i = 0;
	int j = strlen(s) - i - 1;
	int t;

	t = s[i];
	s[i] = s[j];
	s[j] = t;

	if (i >= j) {
		return;
	} else {
		i++;
		reverse(s);
	}
	i = 0;
}
