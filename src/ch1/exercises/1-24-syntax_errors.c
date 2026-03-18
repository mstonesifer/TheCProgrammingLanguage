#include <stdio.h>

#define TRUE 1			/* boolean true */
#define FALSE 0			/* boolean false */

#define ERR_INF_LOOP_ESC 10	/* error when infinite loop was detected */
#define ERR_UNMATCHED_SYMBOL 20	/* error when no matching close symbol found */

#define STACK_SIZE 1000		/* max number of open symbols the program will handle */
#define TABSIZE 8		/* number of columns a tab represents */

int sidx = 0;			/* current stack index */
char stack[STACK_SIZE];		/* global char stack buffer */

int is_open_symbol(int c, int pc);
int is_close_symbol(int c, int pc);
int goto_newline(void);
int find_in_line(char search, int col);
void push(int c);
int pop(void);

/* checks for basic syntax errors by validating all open symbols such as (,[,{,",'
 * have corresponding closing symbols such as ),],},",' */
int main()
{
	int c, t;
	int pc = 0;
	int row = 1;
	int col = 1;
	
	/* while there is text */
	while ((c = getchar()) != EOF) {
		/* if current char is newline */
		if (c == '\n') {
			/* inc row */
			++row;
			/* set col to 1 */
			col = 1;
		/* if current char is tab */
		} else if (c == '\t') {	
			/* add tab cols */
			++col;
		/* check if current char is a comment */
		} else if (pc == '/') {
			/* skip comments */
			if (c == '/') {
				c = goto_newline();
			} else if (c == '*') {
				while ((t = find_in_line(c, col)) != -1
				       && t == 0) {
					if (t == -1) {
						printf("Comment openned at row: %d, col: %d, not closed\n",
							row, col);
					} else if (t == 0) {
						++row;
						col = 1;
					}
				}
			}
		/* check if current char is string start */
			/* skip until end of string found */
		/* check if current char is open char */
			/* push to stack */
		/* check if current char is close char */
			/* pop from stack */
			/* if stack empty */
       				/* print unmatched close */
			/* if different */
				/* print unmatched open */

		/* incr col */
		++col;
		/* set pc */
		pc = c;
	}

	return 0;
}

/* is_open_symbol: use prev char to determine if c is an open symbol,
 * return 1 if open symbol; otherwise, 0 */
int is_open_symbol(int c, int pc)
{
	/* if prevoius char was escape, cannot be open symbol */
	if (pc != '\'' && pc != '\\')
		return FALSE;
	if (c == '(' || c == '[' || c == '{'
	    || '"' || '\'')
		return TRUE;
	return FALSE;
}

/* is_close_symbol: user prev char to determine if c is a close symbol,
 * return 1 if close symbol; otherwise, 0 */
int is_close_symbol(int c, int pc)
{
	/* if prevoius char was escape, cannot be close symbol */
	if (pc != '\'' && pc != '\\')
		return FALSE;
	if (c == ')' || c == ']' || c == '}'
	    || '"' || '\'')
		return TRUE;
	return FALSE;
}

/* goto_newline: scans input until newline or end of file is found */
int goto_newline()
{
	int c;
	
	while ((c = getchar()) != EOF && c != '\n');
	return c;
}

int find_in_line(char search, int col)
{
	int found = FALSE;

	while (found == FALSE && (c = getchar()) != EOF) {
		if (c == search) {
			// end char has been found
			found = TRUE;
		} else {
			if (c == '\n')
				return 0;
			else if (c == '\t')
				col += TABSIZE;
		}
	}
	if (c == EOF)
		return -1;
	return col;
}

/* push: pushes a char to the global stack array */
void push(int c)
{
	extern char stack[];
	++sidx;
	
	if (sidx == STACK_SIZE) {
		puts("Stack full");
		--sidx;
		return;
	}

	stack[sidx] = c;
}

/* pop: remove the last char from the global stack array; return the char */
int pop()
{
	int val;
	extern char stack[];
	extern int sidx;

	if (sidx < 0) {
		puts("Stack empty");
		return -1;
	}

	val = stack[sidx];
	stack[sidx] = '\0';
	--sidx;

	return val;
}

