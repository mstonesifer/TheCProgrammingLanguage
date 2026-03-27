#include <stdio.h>

#define TRUE 1			/* boolean true */
#define FALSE 0			/* boolean false */

#define ERR_INF_LOOP_ESC 10	/* error when infinite loop was detected */
#define ERR_UNMATCHED_SYMBOL 20	/* error when no matching close symbol found */

#define STACK_SIZE 1000		/* max number of open symbols the program will handle */
#define TABSIZE 8		/* number of columns a tab represents */

#define EMPTY_STACK -1		/* sentinel return for empty stack */
#define END -1			/* sentinel return for end of file */
#define NEW_LINE 0		/* sentinel return for new line found */

int sidx = 0;			/* current stack index */
char stack[STACK_SIZE];		/* global char stack buffer */
int rows[STACK_SIZE];
int cols[STACK_SIZE];

int is_open_symbol(int c, int pc);
int is_close_symbol(int c, int pc);
int goto_newline(void);
int find_comment_end(int col);
void push(int c, int r, int col);
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
			//printf("Newline found!\n");
			/* inc row */
			++row;
			/* set col to 0 */
			col = 0;
		/* if current char is tab */
		} else if (c == '\t') {	
			/* add tab cols */
			col += (TABSIZE - 1);
		/* check if current char is a comment */
		} else if (pc == '/') {
			/* skip comments */
			if (c == '/') {
				c = goto_newline();
				++row;
				col = 0;
			} else if (c == '*') {
				while ((t = find_comment_end(col)) != END && t == NEW_LINE) {
			 		if (t == NEW_LINE) {
						++row;
						col = 0;
					}
				}
				if (t == END)
					printf("Comment openned at line: %d, pos: %d not closed\n",
							row, col);
				col = t;
			}
		/* check if current char is string start */
		} else if (c == '"') {
			t = col;
			/* string should close on same line it's opened on */
			while ((c = getchar()) != EOF && c != '\n') {
				/* string close found when not escaped */
				if (c == '"' && pc != '\\')
					break;
				++col;
				pc = c;
			}
			if (c == EOF || c == '\n') {
				printf("String openned at line: %d, pos: %d not closed\n",
						row, t);
				++row;
				col = 0;
			}
		/* check if current char is char start */
		} else if (c == '\'') {
			t = col;
			/*  should close on same line it's opened on */
			while ((c = getchar()) != EOF && c != '\n') {
				/* char close found when not escaped */
				if (c == '"' && pc != '\\')
					break;
				++col;	
				pc = c;
			}
			if (c == EOF || c == '\n') {
				printf("Char openned at line: %d, pos: %d not closed\n",
						row, t);
				++row;
				col = 0;
			}
		/* check if current char is open char */
		} else if (is_open_symbol(c, pc) == TRUE) {
			/* push to stack */
			push(c, row, col);
		/* check if current char is close char */
		} else if (is_close_symbol(c, pc) == TRUE) {
			/* pop from stack */
			t = pop();
			/* if stack empty */
			if (t == EMPTY_STACK)
       				/* print unmatched close */
				printf("Unmatched close char '%c' found at line: %d, pos: %d.\n",
						c, row, col);
			/* if different */
			else if ((c == ')' && t != '(')
				 || ( c == '}' && t != '{')
				 || (c == ']' && t != '[')) {
				/* print unmatched open - mismatch means 2 error chars */
				printf("Unmatched open char '%c' found at line: %d, pos: %d.\n",
						t, rows[sidx], cols[sidx]);
				printf("Unmatched close char '%c' found at line: %d, pos: %d.\n",
						c, row, col);
			}
		}
		/* incr col */
		++col;
		/* set pc */
		pc = c;
	}

	/* print any remaining items in the stack */
	if (sidx != 0) {
		for (int i = 0; i < sidx; ++i) {
			printf("Unmatched open char '%c' found at line: %d, pos: %d.\n",
				stack[i], rows[i], cols[i]);
		}
	}

	return 0;
}

/* is_open_symbol: use prev char to determine if c is an open symbol,
 * return 1 if open symbol; otherwise, 0 */
int is_open_symbol(int c, int pc)
{
	/* if prevoius char was escape, cannot be open symbol */
	if (pc == '\'' || pc == '\\') {
		return FALSE;
	}
	if (c == '(' || c == '[' || c == '{') {
		return TRUE;
	}
	return FALSE;
}

/* is_close_symbol: user prev char to determine if c is a close symbol,
 * return 1 if close symbol; otherwise, 0 */
int is_close_symbol(int c, int pc)
{
	/* if prevoius char was escape, cannot be close symbol */
	if (pc == '\'' || pc == '\\') {
		return FALSE;
	}
	if (c == ')' || c == ']' || c == '}') {
		return TRUE;
	}
	return FALSE;
}

/* goto_newline: scans input until newline or end of file is found */
int goto_newline()
{
	int c;
	
	while ((c = getchar()) != EOF && c != '\n');
	return c;
}

int find_comment_end(int col)
{
	int c, pc;
	int found = FALSE;

	pc = 0;
	while (found == FALSE && (c = getchar()) != EOF) {
		if (c == '/' && pc == '*') {
			// comment end has been found
			found = TRUE;
		} else {
			if (c == '\n')
				return NEW_LINE;
			else if (c == '\t')
				col += (TABSIZE - 1);
		}
		++col;
		pc = c;
	}
	if (c == EOF)
		return END;
	return col;
}

/* push: pushes a char to the global stack array */
void push(int c, int r, int col)
{
	extern char stack[];
	extern int rows[];
	extern int cols[];
	extern int sidx;
	
	if (sidx == STACK_SIZE) {
		puts("Stack full");
		return;
	}

	stack[sidx] = c;
	rows[sidx] = r;
	cols[sidx] = col;

	++sidx;
}

/* pop: remove the last char from the global stack array; return the char */
int pop()
{
	int val;
	extern char stack[];
	extern int sidx;
	
	if ((sidx - 1) < 0) {
		//puts("Stack empty");
		return EMPTY_STACK;
	}

	--sidx;
	val = stack[sidx];
	stack[sidx] = '\0';

	return val;
}

