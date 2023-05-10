/* Exercise 4-1. Write the function "strindex(s, t)" which returns the position
   of the rightmost occurrence of "t" in "s", or -1 if there is none. */


#include <stdio.h>

#define MAXLINE 1000        /* Maximum input line length */

int getline(char line[], int maxline);

int strindex(char source[], char searchfor[]);


char pattern[] = "ng";      /* Pattern to search for */


main()
{
    int pos;
    char line[MAXLINE];

    printf("\nEnter phrases:\n\n\n");

    while( getline(line, MAXLINE) > 0 )
    {
        pos = strindex(line, pattern);

        printf("\nRightmost position of \"%s\": %d.\n\n\n", pattern, pos);
    }

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


/* strindex: return the position of the rightmost occurrence of "t" in "s", or
             -1 if there is none; "rightmost" version. */

int strindex(char s[], char t[])
{
    int i, j, k, p = -1;

    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;

        if (k > 0 && t[k] == '\0')
            p = i;                          /* Save rightmost position. */
    }

    return p;
}
