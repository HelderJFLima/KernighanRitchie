/* Exercise 1-23. Write a program to remove all comments from a C program. Don't
   forget to handle quoted strings and character constants properly. C comments
   don't nest. */


#include <stdio.h>

#define MAXLINE 3000    /* Maximum input line length */
#define CMON 1          /* Inside a comment */
#define CMOFF 0         /* Outside a comment */

int getline(char line[], int maxline);

void partialcopy(char to[], char from[], int start, int end);


/* Remove all comments from a C program. */

main()
{
    int cstate, pos;
    int fvchar, lvchar;         /* First and last valid characters to print */
    char input[MAXLINE], output[MAXLINE];

    cstate = CMOFF;

    printf("\nEnter a text:\n\n");

    while( getline(input, MAXLINE) > 0 )
    {
        fvchar = -1;

        lvchar = -1;

        pos = 0;                            /* Position in the input line */

        while(input[pos] != '\0')
        {
            if(cstate == CMOFF && input[pos] != '/')    /* Start of comment test */
            {
                if(pos == 0)
                    fvchar = 0;                             /* Start of string */

                else if(lvchar >= fvchar)
                    fvchar = pos;

                ++pos;
            }
            else if(cstate == CMOFF)
            {
                if(input[pos + 1] == '*')                   /* Start of a comment */
                {
                    cstate = CMON;

                    if(pos > 0)
                        lvchar = pos - 1;                   /* End of string */

                    if(fvchar >= 0)
                    {
                        partialcopy(output, input, fvchar, lvchar);

                        printf("%s", output);                   /** OUTPUT 1 **/
                    }
                }
                else if(pos == 0)
                    fvchar = 0;

                else if(lvchar >= fvchar)
                    fvchar = pos;

                ++pos;
            }
            else if(input[pos] != '*')
            {
                ++pos;
            }
            else
            {
                if(input[pos + 1] == '/')                   /* End of a comment */
                {
                    cstate = CMOFF;

                    pos = pos + 2;
                }
                else
                    ++pos;
            }                                           /* End of comment test */

            if(input[pos] == '\0')                  /* Start of end-of-string test */
            {
                if(cstate == CMOFF)
                {
                    lvchar = pos - 1;

                    partialcopy(output, input, fvchar, lvchar);

                    printf("%s", output);                       /** OUTPUT 2 **/

                    if(input[pos - 1] != '\n')
                        printf("\n");
                }
                else
                {
                    printf("\n");
                }
            }                                       /* End of end-of-string test */
        }
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


/* partialcopy: copy a piece of "from" into "to", from positions "a" to "b";
                assume "to" is big enough. */

void partialcopy(char to[], char from[], int a, int b)
{
    int i;

    for(i = a; i <= b; ++i)
        to[i - a] = from[i];

    to[i - a] = '\0';
}
