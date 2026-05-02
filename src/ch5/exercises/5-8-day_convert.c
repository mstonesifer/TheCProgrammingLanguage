#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int, int, int);
int month_day(int, int, int *, int *);
char *month_name(int);

int main(int argc, char *argv)
{
	int days, day, month, year;
	char *name;

	month = 3;
	day = 17;
	year = 1987;
	days = day_of_year(year, month, day);
	if (days)
		printf("%i/%i/%i is the %i day of the year\n", month, day, year, days);
	else {
		printf("An invalid date was provided.\n");
		return 1;
	}
	
	if (month_day(year, days, &month, &day)) {
		name = month_name(month);
		printf("The %i day of the year %i is %s %i\n",
				days, year, name, day);
	} else {
		printf("An invalid number of days was provided.\n");
		return 1;
	}
	
	return 0;
}

/* day_of_year:  set day of year from month & day */
/* this one uses pointer - pointer syntax to address daytab */
int day_of_year(int year, int month, int day)
{
	int i, leap;
	char *name;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (month < 1 || month > 12) {
		printf("error: invalid month (%i)\n", month);
		return 0;
	}
	if (day > *( *(daytab + leap) + month)) {
		name = month_name(month);
		printf("error: invalid day for month: %s\n", name);
		return 0;
	}
	for (i = 1; i < month; i++)
		day += *( *(daytab + leap) + i);
	return day;
}

/* month_day:  set month, day from day of year */
/* this one uses pointer - index syntax to address daytab */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (yearday < 1 || yearday > (365 + leap)) {
		printf("error: invalid number of days\n");
		return 0;
	}
	for (i = 1; yearday > (*(daytab + leap))[i]; i++)
		yearday -= (*(daytab + leap))[i];
	*pmonth = i;
	*pday = yearday;

	return 1;
}

/* month_name:  return name of n-th month */
char *month_name(int n)
{
	static char *name[] = {
		"Illeagal month",
		"January", "Februrary", "March", "April",
		"May", "June", "July", "August", "September",
		"October", "November", "December"
	};

	return (n < 1 || n > 12) ? name[0] : name[n];
}
