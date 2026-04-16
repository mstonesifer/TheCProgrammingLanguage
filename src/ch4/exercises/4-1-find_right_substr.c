#include <stdio.h>

/* k&r exercise 4-1 */

/*
 * Write the function `strindex(s, t), which returns the position
 * of the rightmost occurance of t in s, or -1 if there is none.
 */

#define MAXLINE 1000	/* maximum input line length */

int get_line(char line[], int max);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";		/* pattern to search for */

/* find all lines matching pattern */
int main()
{
	char line[MAXLINE];
	int found = 0;

	printf("Searching for pattern \"%s\"...\n", pattern);
	while (get_line(line, MAXLINE) > 0)
		if (strrindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	return found;
}

/* get_line:  get line into s, return length */
int get_line(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* strindex:  return index of t in s, -1 if none */
int strrindex(char s[], char t[])
{
	int i, j, k, ri;

	ri = -1;
	for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			if(i > ri)
				ri = i;
	}

	printf("Rightmost index of \"%s\" is: %i", t, ri);
	
	return ri;
}

