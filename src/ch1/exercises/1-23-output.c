#include <stdio.h>

#define TRUE 1			
#define FALSE 0			

#define ERR_INF_LOOP_ESC 10	

int get_next_newline(void);
int find_next(char search, int print);


int main()
{
	
	








	int c, pc, tmp;
	int iscomment = FALSE;		
	int istext = FALSE;		

	pc = 0;
	
	while ((c = getchar()) != EOF) {
		
		
		if (c == '"' || c == '\"') {

			
			if (pc != '\'' && pc != '\\') {
				putchar(c);
				do
					pc = find_next(c, TRUE);
				while (pc != EOF && pc == '\\');
				if (pc == EOF)
					return 10;
			}
			putchar(c);
		
		} else if (c == '/') {
			
			tmp = c;
			
			if ((c = getchar()) != EOF && c == '/') {
				c = get_next_newline(); 
				putchar(c);
			
			} else if (c == '*') {
				while (pc != EOF && pc != '\\' && pc != '*')
					pc = find_next('/', FALSE);
				if (pc == EOF)
					return 10;
			
			} else {
				
				putchar(tmp);
				putchar(c);
			}
		
		} else {
			putchar(c);
		}

		pc = c;
	}

	
	printf("// should be printed\n");
	printf("/* should also be printed */\n");
	printf("should '/''/' print\n");
	printf("this is a horrible idea, but still valid\n");
	printf("Math should print in the string: 4 / 2 = %d = %d", 4 / 2, 4/2);

	return 0;
}





int get_next_newline()
{
	int c;
	
	while ((c = getchar()) != EOF && c != '\n'); 
	return c;
}








int find_next(char search, int print)
{
	
	int c, pc;
	int found = FALSE;

	pc = 0;			
	while (found == FALSE && (c = getchar()) != EOF) {
		if (c == search) {
			
			found = TRUE;
		} else {
			if (print == TRUE || c == '\n')
				putchar(c);
			pc = c;
		}
	}
	if (c == EOF)
		return c;
	return pc;
}
