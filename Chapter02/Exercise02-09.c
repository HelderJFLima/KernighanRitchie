/* Exercise 2-9. In a two's complement number system, "x &= (x-1)" deletes the
   rightmost 1-bit in "x". Explain why. Use this observation to write a faster
   version of "bitcount". */


/* Because of the behavior of binary notation and because the two's complement
   system preserves the order of negative numbers in binary form. */


#include <stdio.h>
#include <ctype.h>      /* Used by "atoi" function */
#include <limits.h>     /* Used by "binlength" function */

#define MAXSTR 51       /* Maximum bit string length (one place left for '\0') */

int getline(char line[], int maxline);

int atoi(char string[]);

int binlength(int num);

void inttobit(char string[], int num, int maxstr);

int bitcount(int num);


main()
{
    int x;
    char nstr[MAXSTR];

    printf("\nThis program counts the number of ");

    printf("1-bits in an integer argument.\n");

    printf("\nEnter an integer number:\n\n");

    if( getline(nstr, MAXSTR) > 0 )
    {
        x = atoi(nstr);

        inttobit(nstr, x, MAXSTR);

        printf("\n\nResults:\n\n%s\n", nstr);

        printf("%d\n", bitcount(x) );                   /** bitcount test **/
    }
    else
        printf("\nNo number was given.\n");

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


/* binlength: return the number of bits of a decimal integer; 2nd version. */

int binlength(int n)
{
    int num, p;

    if(n == 0)
        num = 1;

    else if(n > 0)
    {
        p = 1;

        for(num = 0; n >= p; num++)
            p *= 2;
    }
    else
    {
        p = INT_MAX / 2 + 1;        /* INT_MAX is the maximum value for an
                                       integer in the system. */

        for(num = 2; p > 1; num++)
            p /= 2;
    }

    return num;
}


/* inttobit: convert a decimal value into a string with its equivalent binary
             digits; 2nd version. */

void inttobit(char s[], int n, int lim)
{
    int i, test = 1;

    i = binlength(n);               /* Determine the last position of string. */

    if(i < lim)
    {
        s[i] = '\0';

        for(i -= 1; i >= 0; i--)    /* Convert to binary form. */
        {
            if(test & n)
                s[i] = '1';
            else
                s[i] = '0';

            test <<= 1;
        }
    }
    else                            /* Overflow case */
        s[0] = '\0';
}


/* bitcount: count 1 bits in x; faster version. */

int bitcount(int n)
{
    int num = 0;

    while(n != 0)
    {
        num++;

        n &= n - 1;
    }

    return num;
}
