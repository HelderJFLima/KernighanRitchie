/* Exercise 2-3. Write a function "htoi(s)", which converts a string of
   hexadecimal digits (including an optional "0x" or "0X") into its equivalent
   integer value. The allowable digits are "0" through "9", "a" through "f",
   and "A" through "F". */


#include <stdio.h>
#include <ctype.h>                          /* Used by "htoi" function */

#define MAXLINE 1000                        /* Maximum input line length */

int getline(char line[], int maxline);

int htoi(char hex[]);


main()
{
    char hexnum[MAXLINE];

    printf("\nEnter hexadecimal numbers:\n\n");

    while( getline(hexnum, MAXLINE) > 0 )
        printf("\ndecimal value: %d\n\n", htoi(hexnum) );

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


/* htoi: convert a string of hexadecimal digits into its equivalent integer
         value. */

int htoi(char s[])
{
    int i, m, n = 0;

                                            /* Possible initial "0x" or "0X" */
    if( (s[1] == 'x' || s[1] == 'X') && s[0] == '0' )
        i = 2;
    else
        i = 0;

    while( isxdigit(s[i]) )
    {
        if( isdigit(s[i]) )
            m = s[i] - '0';

        else if(s[i] >= 'a' && s[i] <= 'f')
            m = s[i] - 'a' + 10;

        else if(s[i] >= 'A' && s[i] <= 'F')
            m = s[i] - 'A' + 10;

        n = 16 * n + m;

        ++i;
    }

    return n;
}
