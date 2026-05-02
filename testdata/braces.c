#include <stdio.h>

int main) // no open ( on 3,9
{
	/* testing [[ multi
	 * line comments [ are correctly
	 * ignored ]}{}{)}{(}{}}]{ */int t[2; // and code still evals no close [ 7,43
	int i = 1;
	while i < 10) { // no matching open ( on 9,14
		printf("Hello, World!" // no close  on 10,23
		printf]"goodbye"); // no open ] 11,23 ) 11,33
	// no close } 9,23
	return 0;
	) // no open ( 14, 9
	  // no close 4,1
