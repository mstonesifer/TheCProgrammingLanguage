#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* k&r exercise 3-3 */

/* macros */
#define ARR_SZ 2048

/* prototypes */
void expand(char [], char []);
int fill(char [], int, int, int);

/*
 * Write a function `expand(s1, s2)` that expands shorthand
 * notations like a-z in the string s1 into the equivalent
 * complete list abc..xyz in s2. Allow for letters of either
 * case and digits, and be prepared to handle cases like
 * a-b-c and a-z0-9 and -a-z. Arrange that a leading or
 * trailing - is taken literally
 */
int main(int argc, char *argv[])
{
	char s1[] = "test1 a-z\n\ttest2 A-Z\n\ttest3 0-9\n\ttest4 a-l0-5\n\ttest5 -a-f";
	char s2[ARR_SZ];

	expand(s1, s2);
	printf("original:\n\t%s\n", s1);
	printf("expanded:\n\t%s\n", s2);
	return 0;
}

/* expand: expands shorthand notations in s1 into complete
 * list as it is copied into s2; example usage:
 * 	convert a-z into abc...xyz
 * note: currently char must immediately preceed or follow the hyphen
 */
void expand(char s1[], char s2[])
{
	int i, j;
	/* loop through s1 checking each char */
	for (i = j = 0; i < strlen(s1) - 1; ++i, ++j) {
		if (s1[i] == '-' && ( /* '-' found */
			(islower(s1[i-1]) && islower(s1[i+1])) || /* both lower */ 
			(isupper(s1[i-1]) && isupper(s1[i+1])) || /* both upper */
			(isdigit(s1[i-1]) && isdigit(s1[i+1]))	/* both digit */
		)) {
			/* copy chars into s2 between char before and after '-' */
			j = fill(s2, --j, s1[i-1], s1[i+1]);
		} else {
			s2[j] = s1[i];
		}
	}
	s2[j] = '\0';
}

/* fill: fills s from index si with contiguous ASCII characters between f and l
 * returns current index si completed on */
int fill(char s[], int si, int f, int l)
{
	int i;

	printf("\nf is %c = %i; l is %c = %i\n", f, f, l, l);

	if (f == l) {
		s[si++] = f;
		s[si++] = l;
	} else if (f < l) {
		for (i = f; i <= l; ++i)
			s[si++] = i;
	} else {
		for (i = f; i >= l; --i)
			s[si++] = i;
	}
	return si;
}
