/* Exercise 4-2. Extend "atof" to handle scientific notation of the form
   "123.45e-6" where a floating-point number may be followed by "e" or "E" and
   an optionally signed exponent. */


#include <ctype.h>          /* Used by "atof" function */
#include <float.h>          /* Used by "atof" function */
#include <stdio.h>

#define MAXLINE 1000        /* Maximum input line length */

int getline(char line[], int maxline);

double atof(char str[]);


main()
{
    char str[MAXLINE];

    printf("\nEnter float numbers:\n\n");

    while( getline(str, MAXLINE) > 0 )
        printf("\n\n%s%.7f\n\n\n", str, atof(str) );        /** atof test **/

    return 0;
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


/* atof: convert string "s" to double; scientific notation version. */

double atof(char s[])
{
    int exp, i, sign, xpsgn = 1;
    double val, power;

    for (i = 0; isspace(s[i]); i++)     /* Skip white spaces. */
        ;

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');

        power *= 10;
    }

    if( (s[i] == 'e' || s[i] == 'E') &&     /* Handle with scientific notation. */
        (
          (s[i + 1] == '+' || s[i + 1] == '-') && isdigit(s[i + 2]) ||
           isdigit(s[i + 1])
         )
       )
    {
        i++;

        if(s[i] == '+')
            i++;

        else if(s[i] == '-')
        {
            xpsgn = -1;

            i++;
        }
    }

    exp = 0;

    while( isdigit(s[i]) )
        exp = 10 * exp + (int)(s[i++] - '0');

    exp *= xpsgn;                                       /* Exponent sign */

    if(exp > DBL_MIN_10_EXP && exp < DBL_MAX_10_EXP)    /* If exponent is valid */
    {
        if(exp > 0)
        {
            while(exp > 0)
            {
                power /= 10;

                exp--;
            }
        }
        else if(exp < 0)
        {
            while(exp < 0)
            {
                power *= 10;

                exp++;
            }
        }
    }

    return sign * val / power;
}
