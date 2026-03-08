#include <stdio.h>
#define SIZE 10 	/* size of the array */

void new_arr(char s[]);

/* test what happens when you reassign an array in a function */
int main()
{
	char arr[SIZE];

	for(int i = 0; i < SIZE; ++i)
		arr[i] = i;

	char arr[SIZE * 2];

	for (int i = 10; i < (SIZE * 2); ++i)
		arr[i] = i * 4;

	for(int i = 0; i < SIZE * 2; ++i)
		printf("%d\n", arr[i]);
}

void new_arr(char s[])
{
	char new[SIZE * 2];

	for (int i = 0; i < SIZE; ++i)
		new[i] = s[i];
	for (int i = 0; i < SIZE * 2; ++i)
		new[i] = i * 2;

}
