/* Exercise 2-2. Write a loop equivalent to the "for" loop above without using "&&" or "||". */

/* The loop is the one used in the function "getline":

   for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i).

   The solution is in a new version of the function. */

#include <stdio.h>

#define MAXLINE 1000    /* Maximum input line length */

int getline(char line[], int maxline);

main()
{
    char line[MAXLINE];

        printf("\nEnter phrases:\n\n");

    while( getline(line, MAXLINE) > 0 )
        printf("%s\n\n", line);

    printf("\nEND\n");

    return 0;
}

int getline(char s[], int lim)      /* Read a line into "s"; return length. 2nd version. */
{
    enum boolean {NO, YES};
    int c;
    int eoline = NO;            /* End of line */
    int pos = 0;                /* Position in the line */

    while(!eoline)              /** NEW LOOP **/
    {
        if(pos < lim - 1)
        {
            c = getchar();

            if(c == '\n')
            {
                s[pos] = c;

                ++pos;

                eoline = YES;
            }
            else if(c == EOF)
                eoline = YES;

            else
            {
                s[pos] = c;

                ++pos;
            }
        }
        else
            eoline = YES;
    }

    s[pos] = '\0';

    return pos;
}
