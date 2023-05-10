/* Exercise 4-12. Adapt the ideas of "printd" to write a recursive version of
   "itoa"; that is, convert an integer into a string by calling a recursive
   routine. */


#include <ctype.h>      /* Used by "atoi" function */
#include <stdio.h>

#define MAXSTR 100      /* Maximum string size */

int atoi(char string[]);

int getline(char line[], int maxline);

void itoa(int num, char str[], int start);


main()
{
    int n;
    char nstr1[MAXSTR], nstr2[MAXSTR];

    printf("\nEnter an integer number:\n\n");

    if( getline(nstr1, MAXSTR) > 0 )
    {
        n = atoi(nstr1);

        printf("\n%d\n", n);

        itoa(n, nstr2, 0);                              /** itoa test **/

        printf("\n%s\n", nstr2);
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


/* itoa: convert "n" to characters in "s", beginning from "st" position;
         recursive version. */

void itoa(int n, char s[], int st)
{
    static int i;

    if(st >= 0)
    {
        i = st;

        if(n < 0)
        {
            s[i++] = '-';

            n = -n;                     /* Make n positive. */
        }

        if(n / 10 > 0)
            itoa(n / 10, s, i);         /* Recursion */

        s[i++] = n % 10 + '0';          /* Get digit. */

        s[i] = '\0';
    }
}
