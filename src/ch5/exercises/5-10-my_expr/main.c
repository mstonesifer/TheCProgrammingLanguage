#include <stdio.h>
#include <stdlib.h>	/* for atof() */
#include <math.h>
#include "my_expr.h"

/* k&r exercise 5-10 */

int main(int argc, char *argv[])
{
	int type;
	double op2;
	char s[MAXOP];

	while (--argc > 0) {
		type = getop(s, *++argv);
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
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}

	printf("\t%.8g\n", pop());
	return 0;
}


