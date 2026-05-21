#include <stdio.h>

#define NUL '\0'
#define NEWLINE '\n'
#define MAX_LINE_COUNT 1024
#define MAX_LINE 1024

void store_lines(char *s[]);
int xgetline(char *, int);
int xstrlen(char *);
void xstrcpy(char *, char *);
char *cache_alloc(int);


int main(int argc, char *argv[])
{
	int flags = 0;			/* keep track of switches */
	char *lines[MAX_LINE_COUNT];	/* line collection */

	store_lines(lines);

	putchar(NEWLINE);
	return 0;
}

void store_lines(char *lines[])
{
	int len;			/* current line length */
	char buf[MAX_LINE];		/* char buffer to read in text */

	while ((len = xgetline(buf, MAX_LINE)) > 0) {
		*lines = cache_alloc(len+1);
		xstrcpy(*lines, buf);
		lines++;
	}
}

/* get_line:  read next input line to s and return length */
int xgetline(char *s, int n)
{
	int c, i;

	for (i = 0; i < n-1 && (c=getchar()) != EOF && c != NEWLINE; i++)
		*s++ = c;

	if (NEWLINE == c) {
		*s++ = c;
		i++;
	}
	*s = NUL;

	return i;
}

/* xstrlen:  get string length */
int xstrlen(char *s)
{
	int i;
	for (i = 0; NUL != *(s + i); i++)
		;
	return i;
}

/* xstrcpy:  copy string t into s; assumes s is large enough */
void xstrcpy(char *s, char *t)
{
	while (NUL != (*s++ = *t++))
		;
}

#define CACHE_SIZE 1048576

static char cache[CACHE_SIZE];
static char *cachep = cache;

char *cache_alloc(int n)
{
	if (cache + CACHE_SIZE - cachep < n) {
		printf("cache size exceeded");
		return 0;
	}
	cachep += n;
	return cachep - n;
}
