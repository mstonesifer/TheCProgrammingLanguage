#include <stdio.h>
#define SIZE 10 	/* size of the array */

void new_arr(char s[]);

/* test what happens when you create an array in a loop */
int main()
{
	char test[10];

	test[0] = 'c';
	test[1] = 'a';
	test[2] = 't';
	test[3] = '\n';
	test[4] = '\0';
	test[5] = 'o';
	test[6] = 'g';
	test[7] = '\0';

	printf("output:\n%s", test);
	/*int i, x;
	x = 0;
	for(i = 0; i < 4; ++i) {
		char arr[SIZE * i];
		++x;
	}
	for(i = 0; i < x; ++i) {
	}*/

	//for(int i = 0; i < SIZE; ++i)
	//	arr[i] = i;

	//char arr[SIZE * 2];

	//for (int i = 10; i < (SIZE * 2); ++i)
	//	arr[i] = i * 4;

	//for(int i = 0; i < SIZE * 2; ++i)
	//	printf("%d\n", arr[i]);
}

void new_arr(char s[])
{
	char new[SIZE * 2];

	for (int i = 0; i < SIZE; ++i)
		new[i] = s[i];
	for (int i = 0; i < SIZE * 2; ++i)
		new[i] = i * 2;

}
