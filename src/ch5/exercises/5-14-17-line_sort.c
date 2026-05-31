#include <stdio.h>

#define ASC 1
#define DESC 0

#define F_DEBUG 1		/* debug mode */
#define F_NUMERIC 1 << 1	/* sort by numeric val */
#define F_REVERSE 1 << 2	/* sort in reverse order */
#define F_FOLD 1 << 3		/* ignore case */
#define F_DIR 1 << 4		/* only compare letters, nums, blanks */

#define NUL '\0'
#define NEWLINE '\n'
#define MAX_LINE_COUNT 1024
#define MAX_LINE 1024

#define CVAL(x) (x - '0')	/* numeric value of char x */
#define TEN_X_F(x) (x * 10.0)	/* multiply x by ten and convert to float */

static int flags = 0;		/* set to 1 for debug mode */

int readargs(int, char **);

int readlines(char **);
int xgetline(char *, int);

int xstrlen(char *);
void xstrcpy(char *, char *);
void dircpy(char *, char *);

char *cache_alloc(int);

void printresult(char **s);

void qsort(void **, int, int, int, int (*)(void *, void *));

double xatof(char *);

int xstrcmp(char *, char *);
int strcmpci(char *, char *);
int numcmp(char *, char *);
int dircmp(char *, char *);
int dircmpci(char *, char *);
void xswap(void **, int, int);

int chartolower(char);
void strtolower(char *);

int isdirchar(char);
int xisdigit(char);
int xisspace(char);

/* line_sort:  sort input lines by various criteria */
int main(int argc, char *argv[])
{
	int lc;				/* total lines counted */
	char *lines[MAX_LINE_COUNT];	/* line collection */
	int (*comp)(void*, void*);	/* comparitor function */

	// read clargs
	flags = readargs(argc, argv);
	
	// read in lines
	lc = readlines(lines);

	if (flags & F_NUMERIC)
		comp = (int (*)(void*, void*))(numcmp);
	else if (flags & F_DIR)
		comp = (int (*)(void*, void*))(dircmp);
	else if ((flags & F_DIR) && (flags & F_FOLD))
		comp = (int (*)(void*, void*))(dircmpci);
	else if (flags & F_FOLD)
		comp = (int (*)(void*, void*))(strcmpci);
	else
		comp = (int (*)(void*, void*))(xstrcmp);

	printf("line_sort: sorting %i lines...", lc);
	// sort using flags
	qsort((void**) lines, 0, lc-1, (flags & F_REVERSE), comp); 
	printf("done!\n");

	// write sorted lines
	printresult(lines);

	return 0;
}

/* readargs:  returns flags based on command line arguments */
int readargs(int count, char **args)
{
	int c;

	while (--count > 0 && *(++args)[0] == '-') {
		while (NUL != (c = *++args[0]))
			switch (c) {
				case 'd':
					flags |= F_DIR;
					break;
				case 'f':
					flags |= F_FOLD;
					break;
				case 'n':
					flags |= F_NUMERIC;
					break;
				case 'r':
					flags |= F_REVERSE;
					break;
				default:
					printf("sort_lines: options usage -[dfnr]\n");
					break;
			}
	}

	if (count != 0)
		printf("sort_lines: unknown argument\n");

	return flags;
}

/* readlines:  read lines from input to memory cache */
int readlines(char *lines[])
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

/* dircpy:  copy dir chars from t to s; assumes s is large enough */
void dircpy(char *s, char *t)
{
	int c;
	while (NUL != (c = *t++))
	       if (isdirchar(c))
		       *s++ = c;
}

/* strtolower:  convert s to lowercase */
void strtolower(char *s)
{
	while (NUL != (*s = chartolower(*s++)))
		;
}

/* chartolower:  convert c to lowercase */
int chartolower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 32;

	return c;
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

/* printresult:  writes all lines stored in memory cache */
void printresult(char **s)
{
	printf("\n\n");
	printf("=== SORTED ");
	
	if (flags & F_NUMERIC)
		printf("NUMERIC ");
		
	if (flags & F_DIR)
		printf("DIRECTORY ");

	printf("INPUT IN ");

	if (flags & F_REVERSE)
		printf("DESCENDING ");
	else
		printf("ASCENDING ");

	printf("ORDER ");

	if (flags & F_FOLD)
		printf("(IGNORE CASE) ");

	printf(" ===\n");
	
	while (NULL != *s && xstrlen(*s) > 0)
		printf("%s", *s++);
}


/* qsort:  sort v using parameter comparator routine */
void qsort(void *v[], int left, int right, int isr, int (*comp)(void *, void *))
{
	int i, last;

	if (left >= right)	/* do nothing if array contains */
		return;		/* fewer than two elements */
	xswap(v, left, (left + right)/2);
	last = left;
		
	for (i = left+1; i <= right; i++) {
		if (isr) {
		       if ((*comp)(v[i], v[left]) >= 0) 
				xswap(v, ++last, i);
		} else {
		       	if ((*comp)(v[i], v[left]) < 0)
				xswap(v, ++last, i);
		}
	}
	
	xswap(v, left, last);
	qsort(v, left, last-1, isr, comp);
	qsort(v, last+1, right, isr, comp);
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

/* strcmpci:  compare two strings, case insensitive */
int strcmpci(char *s, char *t)
{
	while (chartolower(*s) == chartolower(*t)) {
		if (NUL == *s)
			return 0;
		s++, t++;
	}
	return chartolower(*s) - chartolower(*t);
}

/* dircmp:  compare two directory strings */
int dircmp(char *s, char *t)
{
	char u[xstrlen(s)];
	char v[xstrlen(t)];

	/* filter only directory characters */
	dircpy(u, s);
	dircpy(v, t);

	/* compare modified string */
	return xstrcmp(u, v);
}

/* dircmpci:  compare two directory strings, case insensitive */
int dircmpci(char *s, char *t)
{
	char u[xstrlen(s)];
	char v[xstrlen(t)];

	/* filter only directory characters */
	dircpy(u, s);
	dircpy(v, t);

	/* convert string to lowercase */
	strtolower(u);
	strtolower(v);

	/* compare modified string */
	return xstrcmp(u, v);
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

	return 0;	/* equal */
}

/* swap:  switch the contents of an array at indecies i and j in place */
void xswap(void *v[], int i, int j)
{
	void *tmp;

	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

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

	/* done if next non-digit is not point */
	if ('.' != c)
		return n;

	/* read decimal part */
	pow = 1.0;
	while (xisdigit(c = *s++)) {
		n = TEN_X_F(n) + CVAL(c);
		pow = TEN_X_F(pow);
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

int xisalpha(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int isdirchar(char c)
{
	return xisdigit(c) || xisspace(c) || xisalpha(c);
}
