/* Exercise 4-10. An alternate organization uses "getline" to read an entire
   input line; this makes "getch" and "ungetch" unnecessary. Revise the
   calculator to use this approach. */


#include <ctype.h>      /* Used by "read" */
#include <stdio.h>
#include <stdlib.h>     /* For "atof" */
#include <string.h>     /* For "strlen" */

#define MAXLINE 1000    /* Maximum input line length */
#define MAXNUM  100     /* Maximum size of an operand */
#define MAXSTK  100     /* Maximum depth of the stack */

int sp = 0;             /* Next free stack position */
double stk[MAXSTK];     /* Value stack */

int getline(char line[], int maxline);

double pop(void);

void push(double num);

void read(char str[]);

void sum(void);

void diff(void);

void mult(void);

void divs(void);


/* Reverse Polish calculator */

main()
{
    char line[MAXLINE];

    printf("\n*** Reverse Polish calculator ***\n");

    printf("\n\nEnter positive numbers and the commands ");

    printf("to do the calculations:\n\n");

    while( getline(line, MAXLINE) > 0 )
    {
        read(line);

        printf("\n\t%.3f\n\n", pop() );
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


/* push: push "n" onto value stack. */

void push(double n)
{
    if (sp < MAXSTK)
        stk[sp++] = n;
    else
        printf("\n* ERROR *: stack is full. Can't push %f.\n\n", n);
}


/* pop: pop and return top value from stack. */

double pop(void)
{
    if (sp > 0)
        return stk[--sp];
    else
    {
        printf("\n* ERROR *: stack is empty.\n\n");

        return 0.0;
    }
}


/* read: read the input line with commands and do the operations. */

void read(char s[])
{
    int i, j = 0;
    char num[MAXNUM];

    for(i = 0; isblank(s[i]); i++)      /* Jump blanks. */
        ;

    num[0] = '\0';

    while(s[i] != '\0')
    {
        if(isdigit(s[i]) ||                     /* Read numbers. */
           s[i] == '.' && isdigit(s[i - 1]) )
        {
            num[j] = s[i++];

            num[j + 1] = '\0';

            j++;
        }
        else                                    /* Not a number */
        {
            if(strlen(num) > 0)
            {
                push( atof(num) );              /* Save the last number. */

                num[0] = '\0';

                j = 0;
            }

            switch(s[i])
            {
                case '+':

                    sum();

                    i++;

                    break;

                case '-':

                    diff();

                    i++;

                    break;

                case '*':

                    mult();

                    i++;

                    break;

                case '/':

                    divs();

                    i++;

                    break;

                default:

                    i++;

                    break;
            }
        }
    }
}


/* sum: do a sum with the top two numbers of stack. */

void sum(void)
{
    push( pop() + pop() );
}


/* diff: do a subtraction with the top two numbers of stack. */

void diff(void)
{
    double op2;

    op2 = pop();

    push( pop() - op2 );
}


/* mult: do a multiplication with the top two numbers of stack. */

void mult(void)
{
    push( pop() * pop() );
}


/* divs: do a division with the top two numbers of stack. */

void divs(void)
{
    double op2;

    op2 = pop();

    if(op2 != 0.0)
        push( pop() / op2 );

    else
        printf("\n* ERROR *: division by zero.\n\n");
}
