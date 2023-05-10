/* Exercise 4-4. Add the commands to print the top elements of the stack without
   popping, to duplicate it, and to swap the top two elements. Add a command to
   clear the stack. */


#include <stdio.h>
#include <stdlib.h>     /* For "atof" */

#define MAXOP 100       /* Max size of operand or operator */
#define NUMBER '0'      /* Signal that a number was found */

int getop(char []);

double pop(void);

void push(double);

void printtop(void);

void dupstk(void);

void swaptop(void);

void clrstk(void);


/* Reverse Polish calculator */

main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ( (type = getop(s)) != EOF )
    {
        switch (type)
        {
            case NUMBER:
                push( atof(s) );

                break;

            case '+':
                push( pop() + pop() );

                break;

            case '*':
                push( pop() * pop() );

                break;

            case '-':
                op2 = pop();

                push( pop() - op2);

                break;

            case '/':
                op2 = pop();

                if (op2 != 0.0)
                    push( pop() / op2);
                else
                    printf("error: zero divisor\n");

                break;

            case '%':
                op2 = pop();

                if (op2 != 0.0)
                    push( (int)pop() % (int)op2 );

                else
                    printf("error: zero divisor\n");

                break;

            case 'p':
                printtop();

                break;

            case 'd':
                dupstk();

                break;

            case 's':
                swaptop();

                break;

            case 'c':
                clrstk();

                break;

            case '\n':
                printf("\t%.8g\n", pop() );

                break;

            default:
                printf("error: unknown command %s\n", s);

                break;
        }
    }

    return 0;
}


#define MAXVAL 100      /* Maximum depth of val stack */

int sp = 0;             /* Next free stack position */
double val[MAXVAL];     /* Value stack */


/* push: push "f" onto value stack. */

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}


/* pop: pop and return top value from stack. */

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");

        return 0.0;
    }
}


#include <ctype.h>

int getch(void);

void ungetch(int);


/* getop: get next character or numeric operand. */

int getop(char s[])
{
    int i, c;

    while ( (s[0] = c = getch()) == ' ' || c == '\t' )
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;                                   /* Not a number */

    i = 0;

    if (isdigit(c))                                 /* Collect integer part. */
        while ( isdigit( s[++i] = c = getch() ) )
            ;

    if (c == '.')                                   /* Collect fraction part. */
        while ( isdigit( s[++i] = c = getch() ) )
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}


#define BUFSIZE 100

char buf[BUFSIZE];      /* Buffer for "ungetch" */
int bufp = 0;           /* Next free position in "buf" */


/* getch: get a (possibly pushed-back) character. */

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


/* ungetch: push character back on input. */

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


/* printtop: print the top element of the stack. */

void printtop(void)
{
    if(sp > 0)
        printf("\nstack\'s top element: %f\n", val[sp - 1]);
    else
        printf("\nstack empty\n");
}


/* dupstk: duplicate the stack. */

void dupstk(void)
{
    int i;

    if( sp <= MAXVAL / 2 )
    {
        for(i = 0; i < sp; i++)
            val[sp + i] = val[i];

        sp *= 2;
    }
    else
        printf("\nerror: not enough space to duplicate stack.\n");
}


/* swaptop: swap the top two elements of the stack. */

void swaptop(void)
{
    double temp;

    if(sp >= 2)
    {
        temp = val[sp - 1];

        val[sp - 1] = val[sp - 2];

        val[sp - 2] = temp;
    }
    else
        printf("\nerror: there's less than two elements in the stack.\n");
}


/* clrstk: clear the stack. */

void clrstk(void)
{
    if(sp > 0)
        sp = 0;
    else
        printf("\nstack empty\n");
}
