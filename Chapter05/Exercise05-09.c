/* Exercise 5-9. Rewrite the routines "day_of_year" and "month_day" with
   pointers instead of indexing. */


static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} };


/* day_of_year: set day of year from month and day; pointer version. */

int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    if(year < 0 || month <= 0 || month > 12)                    /* Error */
        return -1;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    p = &daytab[leap][1];

    if(day <= 0 || day > daytab[leap][month])                   /* Error */
        return -1;

    month--;

    while(month-- > 0)
        day += *p++;

    return day;
}


/* month_day: set month and day from day of year; pointer version. */

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p;

    if(year < 0)                                /* Error */
    {
        *pmonth = -1;

        *pday = -1;

        return;
    }

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    p = &daytab[leap][1];

    if(yearday <= 0               ||
       leap == 0 && yearday > 365 ||
       leap == 1 && yearday > 366   )           /* Error */
    {
        *pmonth = -1;

        *pday = -1;

        return;
    }

    *pmonth = 1;

    while(yearday > *p)
    {
        yearday -= *p++;

        (*pmonth)++;
    }

    *pday = yearday;
}
