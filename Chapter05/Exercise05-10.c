/* Exercise 5-10. Write the program "expr", which evaluates a reverse Polish
   expression from the command line, where each operator or operand is a
   separate argument. For example, "expr 2 3 4 + *" evaluates "2 * (3+4)". */


#include <ctype.h>      /* "isdigit" used by "readargs" */
#include <stdio.h>
#include <stdlib.h>     /* "atof" used by "readargs" */
#include <string.h>     /* "strlen" used by "readargs" */

#define MAXNUM  100     /* Maximum size of an operand */
#define MAXSTK  100     /* Maximum depth of the stack */

int sp = 0;             /* Next free stack position */
double stk[MAXSTK];     /* Value stack */
char error = 0;         /* Error flag */

double pop(void);

void push(double num);

int readargs(char *arg[]);

void sum(void);

void diff(void);

void mult(void);

void divs(void);


/* expr: Reverse Polish calculator from the command line */

main(int argc, char *argv[])
{
    int valid;
    double result;

    if(argc == 1)
    {
        printf("\n* ERROR *: no arguments given.\n\n");

        return 1;
    }

    valid = readargs(argv);     /* Read arguments and do the calculations. */

    result = pop();

    if(valid && !error)                         /* Successful calculation */
    {
        printf("\nRESULT: %.3f\n\n", result);

        return 0;
    }
    else                                        /* Errors */
    {
        if(!valid)
            printf("\nInvalid argument error\n\n");

        if(error)
            printf("\nInconsistent execution error\n\n");

        return 2;
    }
}


/* pop: pop and return top value from stack. */

double pop(void)
{
    if (sp > 0)
        return stk[--sp];
    else
    {
        printf("\n* ERROR *: stack is empty.\n\n");

        error = 1;

        return 0.0;
    }
}


/* push: push "n" onto value stack. */

void push(double n)
{
    if (sp < MAXSTK)
        stk[sp++] = n;
    else
    {
        printf("\n* ERROR *: stack is full. Can't push %f.\n\n", n);

        error = 1;
    }
}


/* readargs: read the command line and do the operations; return 0 if there is
             an error in some argument, 1 otherwise. */

int readargs(char *a[])
{
    int i, j;
    char num[MAXNUM];

    num[0] = '\0';

    i = j = 0;

    while(*++a != NULL)
    {
        while( (*a)[i] != '\0' )
        {                                               /* Read numbers. */
            if(isdigit( (*a)[i] ) || (*a)[i] == '.' && i > 0)
            {
                num[j++] = (*a)[i++];

                num[j] = '\0';
            }
            else if(strlen(num) > 0)                    /* Invalid argument */
            {
                printf("\n* ERROR *: invalid argument: %s\n\n", *a);

                return 0;
            }
            else if(strlen(*a) > 1)                     /* Invalid argument */
            {
                printf("\n* ERROR *: invalid argument: %s\n\n", *a);

                return 0;
            }
            else
            {
                switch( (*a)[i] )
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

                    default:                            /* Invalid argument */

                        printf("\n* ERROR *: invalid argument: %s\n\n", *a);

                        return 0;
                }
            }
        }

        if(strlen(num) > 0)
        {
            push( atof(num) );                      /* Save the last number. */

            num[0] = '\0';

            j = 0;
        }

        i = 0;
    }

    return 1;
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
    {
        printf("\n* ERROR *: division by zero.\n\n");

        error = 1;
    }
}
