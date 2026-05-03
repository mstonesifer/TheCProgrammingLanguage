#define MAXOP	100	/* max size of operand or operator */
#define NUMBER	'0'	/* signal that a number was found */

/* getop.c */
int	getop(char *, char *);

/* stack.c */
void	push(double);
double	pop(void);
double	peek(void);
void	dupe(void);
void	swap(void);
void	clear(void);

/* getch.c */
int	getch(void);
void	ungetch(int);
