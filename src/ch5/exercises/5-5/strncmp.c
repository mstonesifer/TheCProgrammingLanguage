#include <stdio.h>

/* k&r exercise 5-5 */

/* macros */


/* prototypes */
int strncmp_two(char *, char *, int);

/*
 * Exercise description:
 * Write versions of library functions which operate
 * on at most the first n characters of their argument
 * strings. Full descriptions are in Appendix B.
 */
int main(int argc, char *argv[])
{
	int out;
	char s[] = "Hello, World!";
	char t[] = "Hello, World!";
	char u[] = "Qoo!";

	if (out = strncmp_two(s,t,9)) {
		printf("out = %i\n", out);
		if (out > 0)
			puts("greater");
		else
			puts("less");
		puts("No match");
	} else
		puts("Match");

	if (out = strncmp_two(u,t,9)) {
		printf("out = %i\n", out);
		if (out > 0)
			puts("greater");
		else
			puts("less");
		puts("No match");
	} else
		puts("Match");
	return 0;
}

/* functions */
/* strncmp_two:  compare at most the first n characters of t to s */
int strncmp_two(char *s, char *t, int n)
{
	int i;

	for (i = 0; i < n && *s && *(s++) == *t++; i++)	
		printf("s = %c|t = %c\n", *(s-1), *(t-1));
	return *--s - *--t; 
}
