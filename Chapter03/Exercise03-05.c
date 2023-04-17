/* Exercise 3-5. Write the function "itob(n, s, b)" that converts the integer
   "n" into a base "b" character representation in the string "s". In particular,
   "itob(n, s, 16)" formats "s" as a hexadecimal integer in "s". */


#include <ctype.h>      /* Used by "atoi" function */
#include <stdio.h>
#include <string.h>     /* Used by "reverse" function */

#define MAXSTR 100      /* Maximum string size */

int atoi(char string[]);

int getline(char line[], int maxline);

void reverse(char str[]);

void itob(int num, char str[], int base);


main()
{
    int n, b;
    char nstr1[MAXSTR], nstr2[MAXSTR];

    printf("\nEnter a positive integer number:\n\n");

    if( getline(nstr1, MAXSTR) > 0 )
    {
        n = atoi(nstr1);

        printf("\n\nEnter a base from 2 to 36:\n\n");

        if( getline(nstr1, MAXSTR) > 0 )
        {
            b = atoi(nstr1);

            printf("\n\nbase 10:\t%d\n", n);

            itob(n, nstr2, b);                              /** itob test **/

            printf("\nbase %2d:\t%s\n\n", b, nstr2);
        }
        else
            printf("\nNo base was given.\n");
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


/* itob: convert the integer "n" into a base "b" character representation in
         the string "s". */

void itob(int n, char s[], int b)
{
    int i = 0;
    char c;

    if(n > 0 && b >= 2 && b <= 36)      /* Just positive numbers and bases */
    {                                   /* between 2 and 36 */
        while(n > 0)
        {
            c = (char)(n % b);

            if(c <= 9)
                s[i++] = c + '0';
            else
                s[i++] = c + 'A' - 10;  /* This extends the notation used in
                                           hexadecimal to other bases, going
                                           up to the letter Z. */
            n /= b;
        }
    }
    else if(n == 0 && b >= 2 && b <= 36)
        s[i++] = '0';

    s[i] = '\0';

    reverse(s);
}
