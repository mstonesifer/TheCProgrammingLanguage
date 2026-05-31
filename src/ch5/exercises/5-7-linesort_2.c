#include <stdio.h>
#include <string.h>

#define MAXLINES 5000		/* max #lines to be sorted */
#define BUFSIZE 50000		/* container size for all data */

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines, char *bfr);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void)
{
	int nlines;		/* number of input lines read */
	char bfr[BUFSIZE];

	 if ((nlines = readlines(lineptr, MAXLINES, bfr)) >= 0) {
		 qsort(lineptr, 0, nlines-1);
		 writelines(lineptr, nlines);
		 return 0;
	 } else {
		 printf("error: input too big to sort\n");
		 return 1;
	 }
}

#define MAXLEN 1000		/* max length of any input line */
int get_line(char *, int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines, char *bfr)
{
	int len, nlines, pos;
	char *p, line[MAXLEN];

	nlines = 0;
	pos = 0;
	while ((len = get_line(line, MAXLEN)) > 0)
		if (nlines >= maxlines || pos >= BUFSIZE)
			return -1;
		else {
			line[len-1] = '\0';	/* delete newline */
			p = (bfr + pos);
			strcpy(p, line);
			lineptr[nlines++] = p;
			pos += len + 1;
		}
	return nlines;
}

/* write lines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines--)
		printf("%s\n", *lineptr++);
}

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)	/* do nothing if array contains */
		return;		/* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

/* swap:  interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* get_line:  reads a line of input into s; returns length */
int get_line(char *s, int n)
{
	int c, i;

	for (i = 0; i < n-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		*s++ = c;
	if (c == '\n') 
		*s++ = c;
	*s = '\0';

	return (c == EOF) ? i : ++i;
}
