#include <stdio.h>
#include <stdbool.h>

/* Print Fahrenheit-Celcius table
 * 	for temp = 0, 20, ..., 300 */

#define LOWER 0
#define UPPER 300
#define STEP 20

void print_header(bool);
void print_table(bool, bool);

void main()
{
	bool isToCelcius = true;
	bool isAsc = false;
	print_header(isToCelcius);
	print_table(isToCelcius, isAsc);
}

void print_header(bool isToCelcius)
{
	if (isToCelcius)
	{
		printf("| Fahrenheit | Celcius |\n");
		printf("|------------|---------|\n");
	}
	else
	{
		printf("| Celcius | Fahrenheit |\n");
		printf("|---------|------------|\n");
	}
}

void print_table(bool isToCelcius, bool isAsc)
{

	float fahr;

	if (isAsc)
	{
		for (fahr = LOWER; fahr <= UPPER; fahr += 20)
		{
			if (isToCelcius)
				printf("| %10.0f | %7.2f |\n",
					fahr,
					(5.0 / 9.0) * (fahr - 32));
			else
				printf("| %7.2f | %10.0f |\n",
					(5.0 / 9.0) * (fahr - 32),
					fahr);
		}
	}
	else
	{
		for (fahr = UPPER; fahr >= LOWER; fahr -= 20)
		{
			if (isToCelcius)
					printf("| %10.0f | %7.2f |\n",
					fahr,
					(5.0 / 9.0) * (fahr - 32));
			else
				printf("| %7.2f | %10.0f |\n",
					(5.0 / 9.0) * (fahr - 32),
					fahr);
		}
	}
}
