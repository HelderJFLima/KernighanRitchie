/* Exercise 5-8. There is no error checking in "day_of_year" or "month_day".
   Remedy this defect. */


static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} };


/* day_of_year: set day of year from month and day. */

int day_of_year(int year, int month, int day)
{
    int i, leap;

    if(year < 0 || month <= 0 || month > 12)                    /* Error */
        return -1;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if(day <= 0 || day > daytab[leap][month])                   /* Error */
        return -1;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];

    return day;
}


/* month_day: set month and day from day of year. */

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if(year < 0)                                /* Error */
    {
        *pmonth = -1;

        *pday = -1;

        return;
    }

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if(yearday <= 0               ||
       leap == 0 && yearday > 365 ||
       leap == 1 && yearday > 366   )           /* Error */
    {
        *pmonth = -1;

        *pday = -1;

        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];

    *pmonth = i;

    *pday = yearday;
}
