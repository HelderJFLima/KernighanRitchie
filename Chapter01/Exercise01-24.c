/* Exercise 1-24. Write a program to check a C program for rudimentary syntax
   errors like unmatched parentheses, brackets and braces. Don't forget about
   quotes, both single and double, escape sequences, and comments. (This program
   is hard if you do it in full generality.) */


#include<stdio.h>

#define MAXLINE 3000    /* Maximum input line length */
#define PARENTHESES 0   /* Reference numbers of types of characters */
#define BRACKETS 1
#define BRACES 2
#define SQUOTES 3
#define DQUOTES 4
#define COMMENTS 5

int getline(char line[], int maxline);


/* This is EXTREMELY RUDIMENTARY and does not work perfectly... */

main()
{
    int i, pos;
    int dqstep, sqstep;
    int check[6];
    char line[MAXLINE];

    pos = 0;                    /* Position in the input line */

    dqstep = sqstep = 1;        /* Steps used for double and single quotes */

    for(i = 0; i < 6; ++i)
        check[i] = 0;

    printf("\nEnter a code:\n\n");

    while( getline(line, MAXLINE) > 0 )
    {
        while(line[pos] != '\0')
        {
            if(line[pos] == '(')
                ++check[PARENTHESES];

            else if(line[pos] == ')')
                --check[PARENTHESES];

            else if(line[pos] == '{')
                ++check[BRACES];

            else if(line[pos] == '}')
                --check[BRACES];

            else if(line[pos] == '[')
                ++check[BRACKETS];

            else if(line[pos] == ']')
                --check[BRACKETS];

            else if(line[pos] == '\'')
            {
                check[SQUOTES] = check[SQUOTES] + sqstep;

                if(sqstep > 0)
                    sqstep = -1;
                else
                    sqstep = 1;
            }
            else if(line[pos] == '\"')
            {
                check[DQUOTES] = check[DQUOTES] + dqstep;

                if(dqstep > 0)
                    dqstep = -1;
                else
                    dqstep = 1;
            }
            else if(pos >= 1)
            {
                if(line[pos - 1] == '/' && line[pos] == '*')
                    ++check[COMMENTS];

                if(line[pos - 1] == '*' && line[pos] == '/')
                    --check[COMMENTS];
            }

            ++pos;
        }

        pos = 0;

        dqstep = sqstep = 1;
    }

    if(check[PARENTHESES] != 0)
        printf("\nThere were parentheses errors.\n");

    if(check[BRACKETS] != 0)
        printf("\nThere were brackets errors.\n");

    if(check[BRACES] != 0)
        printf("\nThere were braces errors.\n");

    if(check[SQUOTES] != 0)
        printf("\nThere were single quotes errors.\n");

    if(check[DQUOTES] != 0)
        printf("\nThere were double quotes errors.\n");

    if(check[COMMENTS] != 0)
        printf("\nThere were comments errors.\n");

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
