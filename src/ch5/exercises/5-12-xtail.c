#include <stdio.h>
#include <ctype.h>

#define NUL '\0'
#define INT_WIDTH 10
#define DEFAULT_LINE_COUNT 10
#define MAX_LEN 1000

int xatoi(char *);
int get_last_lines(char (*)[MAX_LEN], int);
int xgetline(char *, int);
void xstrcpy(char *, char *);

int main(int argc, char *argv[])
{
	int c, i, n, start;
	char sn[INT_WIDTH + 1];

	/* get arguments */
	while (--argc > 0 && **(++argv) == '-')
		for (i = 0; i < INT_WIDTH && NUL != (c = *++(*argv)) ; i++)
			sn[i] = c;
	sn[i] = NUL;

	/* parse number or set default */
	n = (NUL != *sn) ? xatoi(sn) : DEFAULT_LINE_COUNT;
	if (n < 0)
		n = DEFAULT_LINE_COUNT;

	/* build result container and fill */
	char lines[n][MAX_LEN];
	start = get_last_lines(lines, n);

	/* print result */
	for (i = start; i < n; i++)
		printf("%s", lines[i]);
	for (i = 0; i < start; i++)
		printf("%s", lines[i]);

	return 0;
}

/* xatoi:  converts a string representation of a number to an integer */ 
int xatoi(char *s)
{
	int c, i, sign, result;

	/* skip whitespace */
	while (' ' == (c = *s++) || '\t' == c)
		;
	
	/* get sign from first char */
	sign = ('-' == c) ? -1 : 1;
	if (isdigit(c))
		s--;

	/* parse string to int */
	for (i = 0, result = 0; (c=*s++)!=EOF && NUL!=c && isdigit(c); i++)
		result = (i * 10 * result) + (c - '0');

	return result * sign;
}

/* get_last_lines:  gets the last n lines of an input; returns index of first string */
int get_last_lines(char (*s)[MAX_LEN], int n)
{
	int i, l;
	char line[MAX_LEN];

	for (i = 0; (l = xgetline(line, MAX_LEN)) > 0; i++) {
		if (i == n)
			i = 0;
		xstrcpy(*(s+i), line);
	}
	return i;
}

/* xgetline:  gets a line from input and stores into s */
int xgetline(char *s, int n)
{
	int c;
	int l = 0;

	while (EOF != (c = getchar()) && l++ < n && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = NUL;

	return l;
}

/* xstrcpy:  copy t into s; assumes s has space */
void xstrcpy(char *s, char *t)
{
	while ((*s++ = *t++) != NUL)
		;
}
