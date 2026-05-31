#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("argc starts at %i\n", argc);
//	while (--argc > 0 && (*++argv)[0]) {
//		printf("argc is %i\n", argc);
//		printf("*argv[0] is %c\n", *argv[0]);
//		printf("*++argv is %c\n", *++argv[0]);
//		printf("*argv is %s\n", *argv);
//	}
	printf("*argv is %c\n", *++argv[1]);
	printf("argc after loop %i\n", argc);

	
	return 0;
}
