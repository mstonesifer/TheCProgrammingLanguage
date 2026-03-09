#include <stdio.h>
#define MAXLINE 100	/* maximum input line size */
#define OVERMAX 1	/* line is larger than MAXLINE */
#define UNDERMAX 0	/* line is shorter than MAXLINE */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
	int len;		/* current line length */
	int max;		/* maximum length seen so far */
	int fcount;		/* count times line is full */
	int part;		/* flag to track multipart lines */
	char line[MAXLINE];	/* current input line */
	char longest[MAXLINE];	/* longest line saved here */ 

	max = 0;
	part = UNDERMAX;
	// while there is another line
	while ((len = get_line(line, MAXLINE)) > 0) {
		if (part == UNDERMAX)
			fcount = 0;
		// if it's the max length and last char is not newline
		if (len == MAXLINE - 1 && line[MAXLINE-2] != '\n') {
			// save the first part of the line
			if (part == UNDERMAX)
				copy(longest, line);
			// increment full count 
			++fcount;
			part = OVERMAX;
			// and check next section
			continue;
		}
		len += (MAXLINE - 1) * fcount;
		// if it's longer than the previous longest
		if (len > max) {
			// save the length
			max = len;
			// save the line if not an overmax line
			if (part == UNDERMAX)
				copy(longest, line);
			part = UNDERMAX;
		}
	}
	if (max > 0)		/* there was a line */
		printf("len: %d; line:%s\n", max, longest);
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

