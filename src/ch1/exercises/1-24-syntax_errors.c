#include <stdio.h>

#define TRUE 1			/* boolean true */
#define FALSE 0			/* boolean false */

#define ERR_INF_LOOP_ESC 10	/* error when infinite loop was detected */
#define ERR_UNMATCHED_SYMBOL 20	/* error when no matching close symbol found */

#define STACK_SIZE 1000		/* max number of open symbols the program will handle */
#define TABSIZE 8		/* number of columns a tab represents */

int sidx = 0;			/* current stack index */
char stack[STACK_SIZE];		/* array to track open symbols */
int row[STACK_SIZE];		/* row of corresponding open */
int col[STACK_SIZE];		/* column of corresponding open */

int scan_line(void);
int is_open_symbol(int c, int pc);
int find_next(char search, int print);
void push(int c);
int pop(void);

/* checks for basic syntax errors by validating all open symbols such as (,[,{
 * have corresponding closing symbols such as ), ], } */
int main()
{
	extern int sidx;

	int c;				/* char count of current line */
	int r = 1;			/* current row count */
	int i;				/* index for printing found errors */


	/* while there is text */
	while ((c = scan_line(r)) > 0) {
		++r;
	}

	/* check for remaining chars in the stack */
	if (sidx != 0) {
		/* print all open chars with no close */
		for (i = 0; i <= sidx; ++i) {
			printf("Row: %d, Col: %d -> Open symbol '%c' found without matching close\n",
					row[i], col[i], stack[i]);
		}
		/* print all close chars with no open */
	return 0;
}

/* scan_line
 * description: reads an input until a new line is found while storing
 * 	any open symbols
 * params: r: current row being scanned
 * returns: chars in the line 
 */
int scan_line(int r)
{
	/* unlike the rm_comments program, we do not need to print anything out.
	 * however, it would make sense to keep track of the line number, and
	 * col number for each open symbol so details about the incorrect
	 * values can be tracked and printed at the end
	 */
	int i				/* current column */
	int c, pc, tmp;

	pc = 0;
	/* while line has more chars */
	for (i = 1; (c = getchar()) != EOF && c != '\n'; ++i) {
		/* possible comment */
		if (c == '/') {
			/* if single line comment, ignore rest of line */
			if ((c = getchar()) != EOF && c == '/') {
				c = goto_newline();
			/* if multiline comment, look for end */
			} else if (c == '*') {
				/* col = 1 means exactly 1 char since tmp
				 * that is, it's the next char
				 * TODO need to check on same row */
				while ((tmp = find_next('*')) != EOF 
				       && (col = find_next('/')) != EOF
				       && col = 1)
					c = '/'
			}

			if (c == EOF)
				return 0;
			if (c == '\n')
				return i;
		}
		/* if c is open symbol, push to stack */
		else if (is_open_symbol(c, pc) == TRUE)
			push(c, r, i);

		pc = c;
	}
	return i;

	/* if str or char open, ignore until close */
	/* str txt "in comments" and chars 'a' should be ignored */
	if (c == '"' || c == '\'') {
		// if not char literal; double quote indicates string
		if (pc != '\'' && pc != '\\') {
			putchar(c);
			do
				pc = find_next(c, TRUE);
			while (pc != EOF && pc == '\\');
			if (pc == EOF)
				return 10;
		}
		putchar(c);
	/* when char is possible comment open */
	} else if (c == '/') {
		tmp = c;
		/* when cmt st is // continue reading till \n */
		if ((c = getchar()) != EOF && c == '/') {
			c = goto_newline(); // should return newline
			putchar(c);
		/* when cmt st is /\* can ignore until */
		} else if (c == '*') {
			while (pc != EOF && pc != '\\' && pc != '*')
				pc = find_next('/', FALSE);
			if (pc == EOF)
				return 10;
		/* it wasn't a cmt open, it was division op */
		} else {
			// print both characters
			putchar(tmp);
			putchar(c);
		}
	/* not a string or comment start, print as normal */
	} else {
		putchar(c);
	}

	pc = c;
}

/* is_open_symbol
 * description: compares the current char and previous char
 * 	to determine if the current char is an open symbol
 * returns: true if the current char is an open symbol
 */
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


/* goto_newline
 * description: scans remainer of line for newline character
 * returns: last input char
 */
int goto_newline()
{
	int c;
	
	while ((c = getchar()) != EOF && c != '\n');
	return c;
}

/* find_next
 * description: finds the next occurance of a character from input 
 * param: search: character text was started with to indicate end;
 * returns: column match was found
 */
int find_next(char search)
{
	extern int rows;
	int col;		/* col comment is ending on */
	int found = FALSE;

	for (col = 1; found == FALSE && (c = getchar()) != EOF; ++col) {
		if (c == search) {
			// end char has been found
			found = TRUE;
		} else {
			if (c == '\n') {
				++rows;
				c = 1;
			} else if (c == '\t') {
				col += TABSIZE;
			}
		}
	}
	if (c == EOF)
		return -1;
	return col;
}

/* push
 * description: places a charater along with row and col position into the next available
 * 	stack array element if there is space
 * param: c: the char going to the stack
 * 	  row: row position of c
 * 	  col: column position of c
 */
void push(int c, int row, int col)
{
	extern int sidx;
	extern char stack[];
	extern int row[];
	extern int col[];

	++sidx;
	
	if (sidx == STACK_SIZE) {
		puts("Stack full");
		return;
	}

	stack[sidx] = c;
	row[sidx] = row;
	col[sidx] = col;
}

/* pop
 * description: retrieves the last element in the stack and reduces the index by one
 * returns: the character stored at the last stack array element
 */
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

