#include <stdio.h>

/* prints the values of common chars */

void main()
{
	printf("| ascii |  val |\n");
	printf("|-------|------|\n");
	printf("|    \\  | %4d |\n", '\\');
	printf("|   \\t  | %4d |\n", '\t');
	printf("|   \\b  | %4d |\n", '\b');
	printf("| blank | %4d |\n", ' ');
	printf("|   EOF | %4d |\n", EOF);
	printf("|   \\n  | %4d |\n", '\n');
	printf("|_______|______|\n");

}
