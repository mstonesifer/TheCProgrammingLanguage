#include <stdio.h>
#include <ctype.h>
#include "varnames.h"

static int skip_ignored(void);

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
static int skip_ignored(void)
{
	int c[] = { NULC, NULC };	/* track last (0) and current (1) chars */
	int b;				/* circuit breaker */

	while (isspace(c[1] = getch()) && TABC == c[1]) /* skip whitespace */
		;
	/* set breaker based on start of ignored characters */ 
	switch (c[1]) {
		case PPIC:	/* preprocessor instruction */
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
