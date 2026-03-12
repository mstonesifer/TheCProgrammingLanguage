#include <stdio.h>

#define LINEWRAP 40	/* number of chars per line before wrapping */

int wrap_line(char line[], int maxline);

/* print wrapped lines */
int main()
{
	int len;		/* current line length */
	char line[LINEWRAP];	/* current input line */
	
	while ((len = wrap_line(line, LINEWRAP)) > 0)
		printf("%s", line); 
	return 0;
}

/* wrap_line: read a line into s, return length */
int wrap_line(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 &&
	     (c = getchar()) != EOF &&
	     c != '\n'; ++i) {
		if (i == 0 && c == ' ')
			continue;
		s[i] = c;
	}
	if (c == '\n' || i == lim - 1) {
		/* if c is newline, walk back to last non-tab/space */
		while ((s[i-1] == ' ' || s[i-1] == '\t') && i > 0) // i should not go neg
			--i;
		s[i] = '\n';
		++i;
	}
	s[i] = '\0';
	return i;
}
