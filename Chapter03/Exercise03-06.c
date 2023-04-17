/* Exercise 3-6. Write a version of "itoa" that accepts three arguments instead
   of two. The third argument is a minimum field width; the converted number
   must be padded with blanks on the left if necessary to make it wide enough. */


#include <ctype.h>      /* Used by "atoi" function */
#include <limits.h>     /* Used by "itoa" function */
#include <stdio.h>
#include <string.h>     /* Used by "reverse" function */

#define MAXSTR 100      /* Maximum string size */

int atoi(char string[]);

int getline(char line[], int maxline);

void reverse(char str[]);

void itoa(int num, char str[], int field);


main()
{
    int f, n;
    char nstr1[MAXSTR], nstr2[MAXSTR];

    printf("\nEnter an integer number:\n\n");

    if( getline(nstr1, MAXSTR) > 0 )
    {
        n = atoi(nstr1);

        printf("\nEnter a positive field size:\n\n");

        if( getline(nstr1, MAXSTR) > 0 )
        {
            f = atoi(nstr1);

            printf("\n%d\n", n);

            itoa(n, nstr2, f);                              /** itoa test **/

            printf("\n%s\n", nstr2);
        }
        else
            printf("\nNo field size was given.\n");
    }
    else
        printf("\nNo number was given.\n");

    return 0;
}


/* atoi: convert a string of decimal digits into its equivalent integer value;
         2nd version. */

int atoi(char s[])
{
    int i, n = 0;

    if(s[0] == '-')                 /* If the number is negative */
        i = 1;
    else
        i = 0;

    while( isdigit(s[i]) )
          n = 10 * n + (int)(s[i++] - '0');

    if(s[0] == '-')
        n *= -1;

    return n;
}


/* getline: read a line into "s"; return length. */

int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if(c == '\n')
    {
        s[i] = c;

        ++i;
    }

    s[i] = '\0';

    return i;
}


/* reverse: reverse string "s" in place. */

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];

        s[i] = s[j];

        s[j] = c;
    }
}


/* itoa: convert "n" to characters in "s" with a minimum field of "f";
         field version. */

void itoa(int n, char s[], int f)
{
    int i, sign;

    if( (sign = n) < 0 && n == INT_MIN )    /* Largest negative number case */
    {                                       /* Record sign. */
        n++;

        n = -n;                             /* Make n positive. */

        s[0] = n % 10 + '0' + 1;            /* Handle the last digit. */

        n /= 10;

        i = 1;
    }
    else if(sign < 0)
    {
        n = -n;

        i = 0;
    }
    else
        i = 0;

    do                                      /* Generate digits in reverse */
    {                                       /* order. */

        s[i++] = n % 10 + '0';              /* Get next digit. */

    } while ( (n /= 10) > 0 );              /* Delete it. */

    if (sign < 0)
        s[i++] = '-';

    if(i < f)                               /* Adjust the field. */
    {
        while(i < f)
            s[i++] = ' ';
    }

    s[i] = '\0';

    reverse(s);
}
