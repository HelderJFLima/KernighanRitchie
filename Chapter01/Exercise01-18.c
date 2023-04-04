/* Exercise 1-18. Write a program to remove trailing blanks and tabs from each
   line of input, and to delete entirely blank lines. */


#include <stdio.h>

#define MAXLINE 3000        /* Maximum input line length */

int getline(char line[], int maxline);


/* Remove trailing blanks and tabs from each line of input and delete blank
   lines. */

main()
{
    int len;                /* Current line length */
    int pos;                /* Position of a character in a line */
    char line[MAXLINE];     /* Current input line */

    printf("\nEnter lines of text:\n\n");

    while( (len = getline(line, MAXLINE)) > 0 )
    {
        pos = len - 2;

                                        /* Find the last non-blank character. */
        while( pos > 0 && (line[pos] == ' ' || line[pos] == '\t') )
            --pos;

        if(pos == len - 2 && pos > 0)
            printf("%s", line);

        else if (pos > 0)
        {
            line[pos + 1] = '\n';

            line[pos + 2] = '\0';

            printf("%s", line);
        }
    }

    return 0;
}


/* getline: read a line into "s"; return length. */

int getline(char s[],int lim)
{
    int c, i;

    for (i=0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if(c == '\n')
    {
        s[i] = c;

        ++i;
    }

    s[i] = '\0';

    return i;
}
