#include <stdio.h>
#define CHUNK 1024	/* maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
	int len;		/* current line length */
	int max;		/* maximum length seen so far */
	char line[CHUNK];	/* current input line */
	char longest[CHUNK];	/* longest line saved here */

	max = 0;
	while ((len = get_line(line)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0)		/* there was a line */
		printf("%s", longest);
	return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[])
{
	int c, i;

	for (i = 0; (c = getchar()) != EOF &&
	     c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy: copy 'from' into 'to'; assume to  is big enough */
void copy(char to[], char from[])
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

