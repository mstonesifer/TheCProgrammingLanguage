#include <stdio.h>
#define MAXLINE 1000	/* maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[]);
int count(char s[]);

/* print longest input line */
int main()
{
	int len;		/* current line length */
	char line[MAXLINE];	/* current input line */

	while ((len = get_line(line, MAXLINE)) > 0) {
		reverse(line);
		printf("%s", line);
	}
	putchar('\n');
	return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim-1 &&
	     (c = getchar()) != EOF &&
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

/* reverse: reverses s */
void reverse(char s[])
{
	int i, j, len;
	len = count(s);
	j = len - 1;
	char tmp[len];
	copy(tmp, s);
	for (i = 0; i < len; ++i) {
		s[i] = tmp[j];
		--j;
	}
	s[i+1] = '\0';
}

/* count: counts the number of contiguous chars */
int count(char s[])
{
	int i;
	i = 0;
	while (s[i] != '\0')
		++i;
	return i;
}
