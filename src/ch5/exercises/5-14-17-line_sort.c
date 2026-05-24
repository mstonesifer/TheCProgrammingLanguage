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

static int flags = 1;		/* set to 1 for debug mode */

int readargs(int, char **);
int xreadlines(char **s);
int xgetline(char *, int);
int xstrlen(char *);
void xstrcpy(char *, char *);
char *cache_alloc(int);
void printresult(char **s);
void xqsort(void **, int, int, int, int (*)(void *, void *));
double xatof(char *);
int xstrcmp(char *, char *);
int numcmp(char *, char *);
void xswap(void **, int, int);
void wdbg(char *);

/* line_sort:  sort input lines by various criteria */
int main(int argc, char *argv[])
{
	int lc;
	char *lines[MAX_LINE_COUNT];	/* line collection */

	// read clargs
	flags = readargs(argc, argv);
	
	// read in lines
	lc = xreadlines(lines);

	printf("line_sort: sorting %i lines...", lc);
	// sort by flags
	xqsort((void**) lines, 0, lc-1, (flags & F_REVERSE), 
			(int (*)(void*, void*))((flags & F_NUMERIC) ? numcmp : xstrcmp)); 
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

/* printresult:  writes all lines stored in memory cache */
void printresult(char **s)
{
	printf("\n\n");
	printf("=== SORTED ");
	
	if (flags & F_NUMERIC)
		printf("NUMERIC ");
		
	printf("INPUT IN ");

	if (flags & F_REVERSE)
		printf("DESCENDING ");
	else
		printf("ASCENDING ");

	printf("ORDER ===\n");
	
	while (NULL != *s && xstrlen(*s) > 0)
		printf("%s", *s++);
}


/* qsort:  sort v using parameter comparator routine */
void xqsort(void *v[], int left, int right, int isr, int (*comp)(void *, void *))
{
	wdbg("sorting");
	int i, last;

	if (left >= right)	/* do nothing if array contains */
		return;		/* fewer than two elements */
	wdbg("swapping left with mid");
	xswap(v, left, (left + right)/2);
	last = left;

		
	for (i = left+1; i <= right; i++) {
		for (int z = 0; z < 5; z++) {
			printf("%s", (char*)v[z]);
		}
		printf("\n");
		//wdbg("checking against mid");
		printf("left = %s\n", (char*)v[left]);
		if (isr) {
		       if ((*comp)(v[i], v[left]) >= 0) 
				xswap(v, ++last, i);
		} else {
		       	if ((*comp)(v[i], v[left]) < 0)
				xswap(v, ++last, i);
		}
	}
	wdbg("swapping left with last");
	xswap(v, left, last);
	wdbg("calling qsort for left side");
	xqsort(v, left, last-1, isr, comp);
	wdbg("calling qsort for right side");
	xqsort(v, last+1, right, isr, comp);
	wdbg("done!");
}

/* strcmp:  compare two strings, asciibetically */
int xstrcmp(char *s, char *t)
{
	wdbg("compare strings");
	while (*s == *t) {
		wdbg("is s = t?");
		if (NUL == *s) {
			wdbg("yes!");
			return 0;
		}
		s++, t++;
	}

	wdbg("no.");

	return *s - *t;
}

/* numcmp:  compare two strings, numerically */
int numcmp(char *s, char *t)
{
	wdbg("compare nums");
	double u, v;

	u = xatof(s);
	v = xatof(t);

	printf("[DBG]: is %f > %f?\n", u, v);
	if (u > v) {
		wdbg("yes");
		return 1;
	}
	if (u < v) {
		wdbg("no");
		return -1;
	}

	wdbg("they are eq");
	return 0;
}

/* swap:  switch the contents of an array at indecies i and j in place */
void xswap(void *v[], int i, int j)
{
	//wdbg("swapping");
	printf("swapping %s with %s\n", (char*)v[i], (char*)v[j]);
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

void wdbg(char *s)
{
	if (flags & F_DEBUG)
		printf("[DBG]: %s\n", s);
}

