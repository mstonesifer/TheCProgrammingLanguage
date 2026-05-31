#include <stdio.h>
#include "my_expr.h"

#define MAXVAL	100	/* maximum depth of val stack */

static int sp = 0;		/* next free stack position */
static double val[MAXVAL];	/* value stack */

/* push:  push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* peek:  return the top value from the stack without removing */
double peek(void)
{
	if (sp > 0)
		return val[sp - 1];
	else {
		printf("error: stack emtpy\n");
		return 0.0;
	}
}

/* dupe:  duplicate and push top element of stack */
void dupe(void)
{
	if (sp <= 0) {
		printf("error: stack empty\n");
		return;
	}

	if (sp < MAXVAL)
		val[sp++] = val[sp - 1];
	else
		printf("error: stack empty\n");
}

/* swap:  swap top two elements in the stack */
void swap(void)
{
	if (sp > 1) {	/* must be at least 2 elements to swap */
		int t = val[sp - 2];
		val[sp - 2] = val[sp - 1];
		val[sp - 1] = t;
	} else {
		printf("error: must be at least 2 elements in stack\n");
	}
}

/* clear:  reset the stack */
void clear(void)
{
	sp = 0;
}

