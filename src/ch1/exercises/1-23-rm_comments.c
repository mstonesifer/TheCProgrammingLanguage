#include <stdio.h>

#define TRUE 1		/* boolean true */
#define FALSE 0		/* boolean false */

int get_next_newline(void);
void find_next(char search, int print);

/* removes comments from a c program */
int main()
{
	// comments made from the double slash to the end of the line
	/* or from slash-star
	 * with star on next line
	 * and ending with star-slash */

	int c, pc, tmp;
	int iscomment = FALSE;		/* flag for tracking comments */
	int istext = FALSE;		/* flag for tracking str txt */

	pc = 0;
	/* while there is text */
	while ((c = getchar()) != EOF) {
		/* if str or char open, ignore until close */
		/* str txt "in comments" and chars 'a' should be ignored */
		if (c == '\"' && pc != '\\') {
			putchar(c);
			find_next(c, TRUE);
			putchar(c);
		/* when char is possible comment open */
		} else if (c == '/') {
			// zzz
			tmp = c;
			/* when cmt st is // continue reading till \n */
			if ((c = getchar()) != EOF && c == '/') {
				c = get_next_newline(); // should return newline
				putchar(c);
			/* when cmt st is /\* can ignore until */
			} else if (c == '*') {
				find_next('/', FALSE);
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

	// testing
	printf("// should be printed\n");
	printf("/* should also be printed */\n");
	printf("should '/''/' print\n");
	/*pri/* inside coment */printf("this is a horrible idea, but still valid\n");
	printf("4 / 2 = %d = %d", 4 / 2, 4/2);

	return 0;
}

/* get_next_newline
 * description: scans input until next newline char is found
 * return: newline char
 */
int get_next_newline()
{
	int c;
	//printf("get_next_newline()");
	while ((c = getchar()) != EOF && c != '\n'); // do nothing
	return c;
}

/* find_next
 * description: finds the next occurance of a character from input 
 * param: search: character text was started with to indicate end
 * 	  print:  flag to print searched text
 * 	ignores escaped characters
 */
void find_next(char search, int print)
{
	//printf("find_next(search = %c, print = %d)",search,print);
	int c, pc;
	int found = FALSE;

	pc = 0;			/* initialize previous char */
	while (found == FALSE && (c = getchar()) != EOF) {
		if ((c == search && pc != '\\') || (c == search && pc == '*')) {
			// end char has been found
			found = TRUE;
		} else {
			if (print == TRUE || c == '\n')
				putchar(c);
			pc = c;
		}
	}
}
