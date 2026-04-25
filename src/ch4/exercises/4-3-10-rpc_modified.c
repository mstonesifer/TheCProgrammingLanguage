#include <stdio.h>
#include <stdlib.h>	/* for atof() */
#include <math.h>

/* k&r exercises 4-3 to 4-10 */

/* 
 * 4-3: DONE
 * Given the basic framework, it's straightforward to
 * extend the calculator. Add a modulus (&) operator
 * and provisions for negative numbers.
 */

/*
 * 4-4: DONE
 * Add commands to print the top element of the stack
 * without popping, to duplicate it, and to swap the
 * top two elements. Add a command to clear the stack.
 */

/*
 * 4-5: DONE
 * Add access to library functions like sin, exp, and
 * pow. See <math.h> in Appendix B, section 4.
 */

/*
 * 4-6: SKIP
 * Add commands for handling variables. (It's easy to
 * provide 26 vars with 1-letter names.) Add a var for
 * the most recently printed value.
 */

/*
 * 4-7: SKIP
 * Write a routine `ungets(s)` that will push back
 * an entire string onto the input. Should ungets know
 * about `buf` and `bufp`, or should it just use ungetch?
 */

/*
 * 4-8: DONE
 * Suppose that there will never be more than one char
 * of pushback. Modify getch and ungetch accordingly.
 */

/*
 * 4-9: DONE
 * Our getch and ungetch do not handle a pushed back EOF
 * correctly. Decide what their proerties ought to be
 * if an EOF is pushed back, then implement your design.
 */

/*
 * 4-10: EXPLAIN NO IMPL
 * An alternate organization uses `getline` to read an
 * entire input line; this makes getch and ungetch
 * unnecessary. Revise the calculator to use this approach.
 *
 * Replace the while condition in main with (l = getline(s)) > 0.
 * Now s just contains the entire input so while reading with
 * getop, we need only address by index and copy into second 
 * array so if we read to far, just decrement the indexer.
 */

/*
 * 4-11:
 * Modify `getop` so that it doesn't need to use
 * `ungetch`. Hint: use an internal static var.
 */

#define MAXOP	100	/* max size of operand or operator */
#define NUMBER	'0'	/* signal that a number was found */

int	getop(char []);
void	push(double);
double	pop(void);
double	peek(void);
void	dupe(void);
void	swap(void);
void	clear(void);

/* reverse Polish calculator */
int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push((int) pop() % (int) op2);
				else
					printf("error: zero divisor\n");
				break;
			case 's':
				push(sin(pop()));
				break;
			case 'c':
				push(cos(pop()));
				break;
			case 't':
				push(tan(pop()));
				break;
			case 'e':
				push(exp(pop()));
				break;
			case 'p':
				op2 = pop();
				push(pow(pop(), op2));
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL	100	/* maximum depth of val stack */

int sp = 0;		/* next free stack position */
double val[MAXVAL];	/* value stack */

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


#include <ctype.h>

#define MINUS 1

int isminus(int);
int getch(void);
void ungetch(int);

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	int i, c;
	static int b = EOF;		/* buffer */

	if (b != EOF && b != ' ' && b != '\t' &&
		!isdigit(b) && b != '.') {
		c = b;
		b = EOF;
		return c;
	}
	if (b == EOF || b == ' ' || b == '\t')
		while ((s[0] = c = getch()) == ' ' || c == '\t') 	
			;
	else
		s[0] = c = b;
	b = EOF;
	s[1] = '\0';
	
	if (isminus(c) || !isdigit(c) && c != '.' && c != '-')
		return c;		/* not a number */
	i = 0;
	if (isdigit(c) || c == '-')	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')			/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	b = c;
	//ungetch(c);
	return NUMBER;
}

int isminus(int c)
{
	int t;

	if (c != '-')
		return 0;			/* not a minus */

	t = getch();				/* check next char */
	ungetch(t);
	
	return (isdigit(t)) ? 0 : MINUS;	/* a digit is not a minus */
}

#define BUFSIZE	100

int buf;		/* single char buffer */
//char buf[BUFSIZE];	/* buffer for ungetch */
//int  bufp = 0;	/* next free position in buf */

/* get a (possibly pushed back) character */
int getch(void)
{
	if (buf == '\0')		/* buffer empty */
		return getchar();

	int t = buf;
	buf = '\0';
	return t;
	//return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (buf != '\0')
		printf("ungetch: buffer already has value\n");
	else
		buf = c;
	/*if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;*/
}

void stack_test(void)
{
	puts("#testing stack");
	puts("pushing 5 then 7 to stack");
	push(5.0);
	push(7.0);
	printf("peek 2 times to verify 7 without pop %f\n", peek());
	printf("peek again still 7 %f\n", peek());
	puts("now we dupe");
	dupe();
	printf("next 2 pops should be 7 %f\n", pop());
	printf("second pop %f\n", pop());
	puts("pushing another 7 then swapping");
	push(7.0);
	swap();
	printf("popping should be 5 => %f\n", pop());
	puts("pushing 9 and 12 then clearing");
	push(9.0);
	push(12.0);
	clear();
	printf("next line should be an error\n");
	pop();
}
