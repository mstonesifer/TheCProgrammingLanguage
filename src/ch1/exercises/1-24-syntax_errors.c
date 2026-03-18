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
		//printf("Checking char %c, and prev char is %c\n", c, pc);
		/* if current char is newline */
		if (c == '\n') {
			//printf("Newline found!\n");
			/* inc row */
			++row;
			/* set col to 1 */
			col = 1;
		/* if current char is tab */
		} else if (c == '\t') {	
			//printf("Tab found!\n");
			/* add tab cols */
			++col;
		/* check if current char is a comment */
		} else if (pc == '/') {
			/* skip comments */
			if (c == '/') {
				printf("Single line comment found!\n");
				c = goto_newline();
			} else if (c == '*') {
				printf("Multi line comment found!\n");
				while ((t = find_in_line(c, col)) != END && t == NEW_LINE) {
			 		if (t == NEW_LINE) {
						++row;
						col = 1;
					}
				}
				if (t == END)
					printf("Comment openned at line: %d, pos: %d not closed\n",
							row, col);
			}
		/* check if current char is string start */
			/* skip until end of string found */
		/* check if current char is open char */
		} else if (is_open_symbol(c, pc) == TRUE) {
			/* push to stack */
			//printf("Pushing %c to stack\n", c);
			push(c);
		/* check if current char is close char */
		} else if (is_close_symbol(c, pc) == TRUE) {
			/* pop from stack */
			t = pop();
			//printf("%c popped from stack\n", t);
			/* if stack empty */
			if (t == EMPTY_STACK)
       				/* print unmatched close */
				printf("Unmatched close char '%c' found at line: %d, pos: %d.\n",
						c, row, col);
			/* if different */
			else if ((c == ')' && t != '(')
				 || ( c == '}' && t != '{')
				 || (c == ']' && t != '['))
				/* print unmatched open */
				printf("Unmatched open char '%c' found at line: %d, pos: %d.\n",
						t, row, col);
		}
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
	//printf("Is %c an open char when %c is the previous?\n", c, pc);
	/* if prevoius char was escape, cannot be open symbol */
	if (pc == '\'' || pc == '\\') {
		//puts("no because escape");
		return FALSE;
	}
	if (c == '(' || c == '[' || c == '{') {
		//puts("yes");
		return TRUE;
	}
	//puts("no because other");
	return FALSE;
}

/* is_close_symbol: user prev char to determine if c is a close symbol,
 * return 1 if close symbol; otherwise, 0 */
int is_close_symbol(int c, int pc)
{
	//printf("Is %c a close char when %c is the previous?\n", c, pc);

	/* if prevoius char was escape, cannot be close symbol */
	if (pc == '\'' || pc == '\\') {
		//puts("no because escape");
		return FALSE;
	}
	if (c == ')' || c == ']' || c == '}') {
		//puts("yes");
		return TRUE;
	}
	//puts("no because other");
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
	int c;
	int found = FALSE;

	while (found == FALSE && (c = getchar()) != EOF) {
		if (c == search) {
			// end char has been found
			found = TRUE;
		} else {
			if (c == '\n')
				return NEW_LINE;
			else if (c == '\t')
				col += TABSIZE;
		}
	}
	if (c == EOF)
		return END;
	return col;
}

/* push: pushes a char to the global stack array */
void push(int c)
{
	extern char stack[];
	extern int sidx;
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
	printf("stack index before pop %d\n",sidx);
	if (sidx-1 < 0) {
		puts("Stack empty");
		return EMPTY_STACK;
	}

	val = stack[sidx];
	stack[sidx] = '\0';
	--sidx;

	printf("stack index after pop %d\n",sidx);
	return val;
}

