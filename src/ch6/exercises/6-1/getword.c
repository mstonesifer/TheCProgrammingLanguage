#include <stdio.h>
#include <ctype.h>

#define NULC '\0'
#define TAB  '\t'
#define PPI  '#'
#define STR  '\"'
#define CMT  '/'
#define NL   '\n'

int getch(void);
void ungetch(int c);
int skip_ignored(void);

static int buf = NULC;

/* k&r exercise 6-1 						*/
/* Our version of getword does not properly handle underscores 	*/
/* string constants, comments, or preprocessor control lines.  	*/
/* Write a better version.					*/



/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
	int c;
  	char *w = word;

	c = skip_ignored();
	if (EOF != c)
		*w++ = c;
	if (!isalpha(c)) {
		*w = NULC;
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch()) && '_' != c) {
			ungetch(*w);
			break;
		}
	*w = NULC;
	return word[0];
}

/* skip_ignored:  get next char after ignored characters on input */
int skip_ignored(void)
{
	int c[] = { NULC, NULC };	/* track last (0) and current (1) chars */
	int b;				/* circuit breaker */

	while (isspace(c[1] = getch()) && TAB == c[1]) /* skip whitespace */
		;
	/* set breaker based on start of ignored characters */ 
	switch (c[1]) {
		case PPI:	/* preprocessor instruction */
			b = NL;
			break;
		case STR:	/* string literal */
			b = STR;
			break;
		case CMT:	/* comment */
			b = NL;
			break;
		default:	/* not start of ignore char string */
			return c[1];
			break;
	}

	/* find non-escaped breaker */
	while (EOF != (c[1] = getch())) {
		if (b == c[1] && '\\' != c[0]) 
			break;
		c[0] = c[1];
	}

	if (EOF == c[1] && NULC != c[0]) {
		ungetch(c[1]);
		return c[0]; /* return last char before EOF */
	}

	return c[1];	/* will be breaker or EOF */
}

/* getch:  gets next character from cache or input */
int getch(void)
{
	int c;
	if (NULC == buf)
		return getchar();

	c = buf;
	buf = NULC;
	return c;
}

/* ungetch:  places a character onto the character buffer */
void ungetch(int c)
{
	if (NULC != buf)
		printf("error: buffer already contains a character\n");
	else
		buf = c;
}
