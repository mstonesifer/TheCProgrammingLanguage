#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define BUF_SZ 1000
#define TABSIZE 8
#define MAXWIDTH 80

int dtab(char *, int, int, int *);
void ntab(char *, int, int, int *); 
int try_parse_ints(int, char **, int *);

int main(int argc, char *argv[])
{
	int c, ts, len;
	char entab = 0;		/* default detab */
	int n[BUF_SZ];
	char s[BUF_SZ];

	/* step through args to find (en/de)tab */
	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
				case 'e':
					entab = 1;
					break;
				case 'd':
					break;
				default:
					printf("retab: illegal option %c\n", c);
					argc = 0;
					break;
			}

	/* if any params remaining, they will be tabstops */
	ts = try_parse_ints(argc, argv, n);

	if (argc == 0) {
		ts = 1;
		*n = TABSIZE;
	} else if (ts == 0)
		return 1;

	if (entab)
		ntab(s, BUF_SZ, ts, n);
	else {
		while((len = dtab(s, BUF_SZ, ts, n)) > 0)
			printf("%s", s);
	}
	putchar('\n');
	return 0;
}

/* dtab:  read input into s while convert tab chars to specified number spaces */
int dtab(char *s, int size, int ts, int *stops)
{
	/* read s to buffer converting tabs to stops spaces*/
	int c, i, j;
	int stop = *stops;	/* current tabstop */

	/* i keeps track of the current column */
	/* stops contains the list of the tab stops from params */
	/* a tab symbol just moves to the next tabstop */
	/* so if the tabstop is 10 and we are in col 5, insert
	 * 5 spaces to get to column 10 */
	/* i will need to be reset every time there is a new line */
	/* stops will also need to be reset back to idx 0 */
	/* a possible way around this from a logic standpoint */
	/* might be to just add a println func which will gather */
	/* the input until a newline char is found, then just print */
	/* the current buffer */

	/* two things that need to be tracked:
	 * 1. current column
	 * 2. current tab stop
	 * if current column is past current tab stop,
	 * need to update current stop to next stop
	 * beyond current column.
	 * if only one param, tab stop is just multiple
	 * of the param.
	 * if multiple param, traverse list of stops
	 * until no more at which point, max width is used.*/
	
	/* if ts is 1, there is only 1 param stop should be 1 stop */
	/* multiple higher than the current column */
	/* for example, if stop is 8 and the current column is 10 */
	/* then the next stop will be 16 (8 * 2 is first multiple */
	/* higher than 10 */

	if (ts == 1) {
		int stopm = stop;	/* stop multiplier */
		for (i = 0; i < size && (c = getchar()) != EOF && c != '\n'; i++, s++) {
			if (i >= stop)
				stop = ((i / stopm) + 1) * stopm;
			if (c == '\t') {
				while (i++ <= stop)
					*(s++) = ' ';
				s--;
			}
			else
				*s = c;
		}
	} else {
		j = 1;
		for (i = 0; i < size && i < MAXWIDTH && (c = getchar()) != EOF && c != '\n'; i++, s++) {
			while (i > stop && stop != MAXWIDTH) { /* curr col gt stop, need to update stop */
				stop = (j < ts) ? *(stops + j++) : MAXWIDTH;
			}
			if (c == '\t') {
				while (i++ <= stop)
					*(s++) = ' ';
				s--;
			}
			else
				*s = c;
		}
	}

	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return i;
}



/* ntab:  convert spaces to correct number of tabs to reach
 * the specified tab stops */
void ntab(char *s, int size, int ts, int *stops)
{
	int c, i;
	char arr[TABSIZE + 1];		/* space char buffer */

	i = 0;
	/* while there is text */
	while ((c = getchar()) != EOF) {
		/* if arr is full */
		if (i == TABSIZE-1) {
			putchar('\t');		/* put a tab */
			i = 0;			/* reset index */
		/* otherwise, if current char is space */
		} else if (c == ' ') {
			arr[i] = c;		/* put in array */
			++i;			/* incr to next index */
		/* otherwise, if tab and spaces exist, replace spaces */
		} else if (c == '\t' && i != 0) {
			putchar(c);
			i = 0;
		/* otherwise, if current char is tab or nl or spaces in buffer */
		} else if (c == '\n' || i != 0) {
			arr[i] = c;		/* put in array */
			arr[i+1] = '\0';	/* term array */
			printf("%s", arr);	/* print array */
			i = 0;			/* reset index */
		/* otherwise */
		} else {
			putchar(c);	/* put the char */
			i = 0;		/* reset index */
		}
	}
	putchar('\n');
}

/* parse_ints:  parse integers from s into n; returns count on success */
int try_parse_ints(int p, char *s[], int *n)
{
	int c, i, count;
	char buf[BUF_SZ];
	char *t;

	count = 0;
	/* go through each param */
	while (p-- > 0 && isdigit((*s)[0])) {
		t = *s;
		for (i = 0; (c = *t++) != '\0'; i++) {
			/* be sure to check for a digit before trying to convert */
			if (!isdigit(c) && c != ',') {
				printf("retab: invalid parameter %c\n", c);
				return 0;
			}
			/* read each char into a buffer */
			buf[i] = c;
			if (c == ',') {	/* if a comma, dump buffer */
				buf[i] = '\0';
				/* convert the buffer to int and store in n */
				*n++ = atoi(buf);
				// verify asc order
				if (*(n-1) < *(n-2)) {
					printf("retab: parameters must be in ascending order %i %i\n",
							*(n-2), *(n-1));
					return 0;
				}
				count++;
			}
		}
		if (i > 0) {
			*n++ = atoi(buf); /* add remaining buf val to n if exists */
			count++;
		}
		if (*(n-1) < *(n-2)) {
			printf("retab: parameters must be in ascending order %i %i\n",
					*(n-2), *(n-1));
			return 0;
		}
		*s++;
	}

	return count;
}
