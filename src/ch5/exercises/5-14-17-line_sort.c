#include <stdio.h>

#define ASC 1
#define DESC 0

#define F_NUMERIC 1		/* sort by numeric val */
#define F_REVERSE 1 << 1	/* sort in reverse order */
#define F_FOLD 1 << 2		/* ignore case */
#define F_DIR 1 << 3		/* only compare letters, nums, blanks */

#define NUL '\0'
#define NEWLINE '\n'
#define MAX_LINE_COUNT 1024
#define MAX_LINE 1024

#define CVAL(x) (x - '0')	/* numeric value of char x */
#define TEN_X_F(x) (x * 10.0)	/* multiply x by ten and convert to float */

int readargs(int, char **);
int xreadlines(char **s);
int xgetline(char *, int);
int xstrlen(char *);
void xstrcpy(char *, char *);
char *cache_alloc(int);
void xwritelines(char **s);
void xqsort(void **, int, int, int (*)(void *, void *));
double xatof(char *);
int xstrcmp(char *, char *);
int numcmp(char *, char *);
void xswap(void **, int, int);

/* line_sort:  sort input lines by various criteria */
int main(int argc, char *argv[])
{
	int lc;
	int flags = 0;			/* keep track of switches */
	char *lines[MAX_LINE_COUNT];	/* line collection */

	// read clargs
	flags = readargs(argc, argv);
	if (flags & F_NUMERIC)
		printf("numeric\n");
	if (flags & F_REVERSE)
		printf("reverse\n");

	// read in lines
	lc = xreadlines(lines);

	printf("%i lines read\n", lc);
	// sort by flags
	xqsort((void **) lines, 0, lc, 
			(int (*)(void *, void *))((flags & F_NUMERIC) ? numcmp : xstrcmp)); 

	// write sorted lines
	xwritelines(lines);

	return 0;
}

/* readargs:  returns flags based on command line arguments */
int readargs(int count, char **args)
{
	int c;
	int flags = 0;

	while (--count > 0 && *(++args)[0] == '-') {
		while (NUL != (c = *++args[0]))
			switch (c) {
				case 'n':
					flags |= F_NUMERIC;
					break;
				case 'r':
					flags |= F_REVERSE;
					break;
				default:
					printf("sort_lines: options usage -[nr}\n");
					break;
			}
	}

	if (count != 0)
		printf("sort_lines: unknown argument\n");

	return flags;
}

/* readlines:  read lines from input to memory cache */
int xreadlines(char *lines[])
{
	int i;
	int len;			/* current line length */
	char buf[MAX_LINE];		/* char buffer to read in text */

	for (i = 0; (len = xgetline(buf, MAX_LINE)) > 0; i++) {
		*lines = cache_alloc(len+1);
		xstrcpy(*lines, buf);
		lines++;
	}

	return i;
}

/* getline:  read next input line to s and return length */
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

/* cache_alloc:  allocates a block of cache space, if available;
 * returns pointer to starting index */
char *cache_alloc(int n)
{
	if (cache + CACHE_SIZE - cachep < n) {
		printf("cache size exceeded");
		return 0;
	}
	cachep += n;
	return cachep - n;
}

/* writelines:  writes all lines stored in memory cache */
void xwritelines(char **s)
{
	while (NULL != *s && xstrlen(*s) > 0)
		printf("%s", *s++);
}


/* qsort:  sort v using parameter comparator routine */
void xqsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
	putchar('-');
	int i, last;

	if (left >= right)	/* do nothing if array contains */
		return;		/* fewer than two elements */
	xswap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			xswap(v, ++last, i);
	xswap(v, left, last);
	xqsort(v, left, last-1, comp);
	xqsort(v, last+1, right, comp);
	printf("done!");
}

/* strcmp:  compare two strings, asciibetically */
int xstrcmp(char *s, char *t)
{
	while (*s == *t) {
		if (NUL == *s)
			return 0;
		s++, t++;
	}

	return *s - *t;
}

/* numcmp:  compare two strings, numerically */
int numcmp(char *s, char *t)
{
	double u, v;

	u = xatof(s);
	v = xatof(t);

	if (u > v)
		return 1;
	if (u < v)
		return -1;

	return 0;
}

/* swap:  switch the contents of an array at indecies i and j in place */
void xswap(void *v[], int i, int j)
{
	void *tmp;

	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

int xisdigit(char);
int xisspace(char);

/* atof:  converts a s to a floating point number */
double xatof(char *s)
{
	int c, sign;
	double n, pow;

	while (xisspace(c = *s++))	/* skip whitespace */
			;
	sign = ('-' == c) ? -1 : 1;

	/* check first char if not a minus */
	if (xisdigit(c))
		n = CVAL(c);

	/* read integer part */
	while (xisdigit(c = *s++))
		n = TEN_X_F(n) + CVAL(c);

	printf("n = %f\n", n);
	if ('.' != c)
		return n;

	/* read decimal part */
	pow = 1.0;
	while (xisdigit(c = *s++)) {
		n = TEN_X_F(n) + CVAL(c);
		pow = TEN_X_F(pow);
		printf("n = %f | pow = %f\n", n, pow);
	}

	return sign * n / pow;
}

int xisdigit(char c)
{
	return c >= '0' && c <= '9';
}

int xisspace(char c)
{
	return c == ' ';
}
