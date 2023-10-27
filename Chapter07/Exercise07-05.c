/* Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use "scanf"
   and/or "sscanf" to do the input and number conversion. */


#include <stdio.h>

#define MAXLINE 1000    /* Maximum input line length */
#define MAXNUM  100     /* Maximum size of an operand */


int getline(char line[], int maxline);


/* Reverse Polish calculator */

main()
{
    char c, line[MAXLINE];
    int n1, n2;

    printf("\n*** Reverse Polish calculator ***\n");

    printf("\n\nEnter two numbers and the operator ");

    printf("to do the calculations:\n\n");

    while( getline(line, MAXLINE) > 0 )
    {
        if( sscanf(line, "%d %d %c", &n1, &n2, &c) == 3 )
        {
            switch(c)
            {
                case '+':

                    printf("\n\t%d\n\n", n1 + n2);

                    break;

                case '-':

                    printf("\n\t%d\n\n", n1 - n2);

                    break;

                case '*':

                    printf("\n\t%d\n\n", n1 * n2);

                    break;

                case '/':

                    printf("\n\t%.2f\n\n", (float)n1 / (float)n2);

                    break;

                default:

                    printf("\n* ERROR *: invalid operator.\n\n");

                    break;
            }
        }
        else
            printf("\n* ERROR *: invalid input format.\n\n");
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
