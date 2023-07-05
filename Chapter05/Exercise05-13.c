/* Exercise 5-13. Write the program "tail", which prints the last "n" lines of
   its input. By default, "n" is set to 10, let us say, but it can be changed
   by an optional argument so that "tail -n" prints the last "n" lines. The
   program should behave rationally no matter how unreasonable the input or the
   value of "n". Write the program so it makes the best use of available storage;
   lines should be stored as in the sorting program of Section 5.6, not in a
   two-dimensional array of fixed size. */


#include <ctype.h>      /* "isdigit" used by "copyarg" */
#include <stdio.h>
#include <stdlib.h>     /* "atoi" used by "readarg" */
#include <string.h>     /* "strcpy" used by "readlines" */

#define BUFFSIZE 100000 /* Available buffer space size */
#define MAXARG   10     /* Maximum size of an argument */
#define MAXLEN   1000   /* Maximum length of any input line */
#define MAXLINES 100    /* Maximum number of lines to be read */
#define N        10     /* Default value of argument "n" */

char *alloc(int n);

int copyarg(char num[], char arg[]);

int getline(char line[], int maxlen);

int readarg(int *argint, char *argch[]);

int readlines(char *lineptr[], int maxlines);

void writelines(char *lineptr[], int nlines);

char buffer[BUFFSIZE];      /* Buffer for input */
char *buffp = buffer;       /* Next free position */


/* tail: print the last "n" lines of its input; "n" is given by an argument,
         like "tail -n" or is a default value if no argument is given. */

main(int argc, char *argv[])
{
    int n, nlines;
    char *lineptr[MAXLINES];

    if(argc == 2)                   /* From argument */
    {
        if( !readarg(&n, argv) )
            return 1;
    }
    else if(argc == 1)              /* No argument */

        n = N;

    else
    {
        printf("\n* ERROR *: invalid number of arguments\n\n");

        return 2;
    }

    if( ( nlines = readlines(lineptr, MAXLINES) ) > 0 )             /* Input */
    {
        if(nlines < n)
        {
            printf("\n\n*The number of input lines is ");

            printf("below the expected output.*\n");

            n = nlines;
        }

        writelines(lineptr + nlines - n, n);    /* Print the last "n" lines. */

        printf("\n");
    }
    else
        printf("\nNo input provided.\n\n");

    return 0;
}


/* alloc: allocate space for "n" characters in a buffer and return a pointer to
          it; return NULL if there is not enough space. */

char *alloc(int n)
{
    if (buffer + BUFFSIZE - buffp >= n)     /* It fits */
    {
        buffp += n;

        return buffp - n;
    }
    else                                    /* Not enough room */
        return NULL;
}


/* copyarg: copy an argument to an array; return 0 if there is any problem with
            the argument and 1 otherwise. */

int copyarg(char num[], char arg[])
{
    int i = 0;

    while(*arg != '\0')
    {
        if(isdigit(*arg) && i < MAXARG - 1)

            num[i++] = *arg++;

        else
            return 0;
    }

    num[i] = '\0';

    if(i > 0)

        return 1;

    else
        return 0;
}


/* getline: read a line into "s"; return length; pointer version */

int getline(char *s, int lim)
{
    int c, n = 0;

    while(lim - 1 > 0 && (c = getchar()) != EOF && c != '\n')
    {
        *s++ = c;

        lim--;

        n++;
    }

    if(c == '\n')
    {
        *s++ = c;

        n++;
    }

    *s = '\0';

    return n;
}


/* readarg: read an argument and convert it to an integer; return 0 if there is
            some error and 1 otherwise.*/

int readarg(int *argint, char *argch[])
{
    char num[MAXARG];

    if(*++argch != NULL)                    /* If there is an argument */
    {
        if(**argch == '-')                  /* Argument "-n" */
        {
            if( copyarg(num, *argch + 1) )  /* Copy and convert to integer. */

                *argint = atoi(num);

            else
            {
                printf("\n* ERROR *: invalid argument: %s\n\n", *argch);

                return 0;
            }
        }
        else
        {
            printf("\n* ERROR *: unknown argument: %s\n\n", *argch);

            return 0;
        }

        return 1;
    }
    else
    {
        printf("\n* ERROR *: no argument given.\n\n");

        return 0;
    }
}


/* readlines: read input lines and store them in a buffer; return the number of
              lines read or -1 if there was an overflow. */

int readlines(char *linep[], int max)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;

    while ( ( len = getline(line, MAXLEN) ) > 0 )   /* Read a line. */
    {
        if (nlines >= max || ( p = alloc(len) ) == NULL)

            return -1;

        else
        {
            line[len - 1] = '\0';                   /* Delete newline. */

            strcpy(p, line);

            linep[nlines++] = p;
        }
    }

    return nlines;
}


/* writelines: write output lines. */

void writelines(char *lineptr[], int nlines)
{
    printf("\n\n");

    while(nlines-- > 0)
        printf("%s\n", *lineptr++);
}
