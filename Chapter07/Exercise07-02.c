/* Exercise 7-2. Write a program that will print arbitrary input in a sensible
   way. As a minimum, it should print non-graphic characters in octal or
   hexadecimal according to local custom, and break long text lines. */


#include <ctype.h>          /* For isgraph */
#include <stdio.h>
#include <stdlib.h>         /* For malloc */
#include <string.h>         /* For strcat, strcpy, strlen */

#define HEXSIZE  7          /* Hexadecimal character string space */
#define LINESIZE 50         /* Maximum size of output line */
#define MAXLEN   1000       /* Maximum length of input line */
#define MAXLINES 200        /* Maximum number of lines of text data */
#define MAXBLOCK 50         /* Maximum length of a block of characters accepted */


void breakline(char *line);

int getline(char *line, int maxlen);

void writelines(char *lineptr[], int nlines);


char *lineptr[MAXLINES];        /* List of lines of text data */
int pos = 0;                    /* Position in the list */
char buffer[LINESIZE];
int rem = LINESIZE;             /* Space remaining in the buffer */


/* print arbitrary input breaking long text lines and converting non-graphic
   characters in hexadecimal. */

main()
{
    char line[MAXLEN];

    buffer[0] = '\0';

    while( getline(line, MAXLEN) > 0 )
        breakline(line);

    writelines(lineptr, pos);

    return 0;
}


/* breakline: break a string in pieces of predetermined size and save them in
              the position "pos" of a list of strings and in the following. */

void breakline(char *line)
{
    int savehex(char *, char, int);
    int saveintobuffer(char *);
    int savestr(char *, int);

    int brem, i, st;
    char block[MAXBLOCK];
    enum state {OUT, IN};       /* Out of/within a block of graphic characters */

    st = OUT;

    brem = MAXBLOCK;            /* Space remaining in he block */

    i = 0;

    while(*line != '\0')
    {
        if( isgraph(*line) && st == IN )            /* Within a block */
        {
            if(i < MAXBLOCK - 1)

                block[i++] = *line++;

            else
                printf("\n* ERROR *: block of characters longer than limit\n\n");
        }
        else if( isgraph(*line) && st == OUT )      /* Entering a block */
        {
            st = IN;

            if(i > 0)
            {
                if( !saveintobuffer(block) )
                    break;
            }

            i = 0;

            block[i++] = *line++;
        }
        else if(st == IN)                           /* Coming out of a block */
        {
            st = OUT;

            block[i] = '\0';

            if( !saveintobuffer(block) )
                break;

            block[0] = '\0';

            brem = MAXBLOCK;

            brem = savehex(block, *line, brem); /* Save non-graphic character. */

            i++;

            line++;
        }
        else                                        /* Out of a block */
        {
            if(brem >= HEXSIZE)

                brem = savehex(block, *line, brem);

            else
            {
                if( !saveintobuffer(block) )
                    break;

                block[0] = '\0';

                brem = MAXBLOCK;

                brem = savehex(block, *line, brem);
            }

            i++;

            line++;
        }
    }

    if(st == IN)                                    /* Remaining data */
        block[i] = '\0';

    if( strlen(block) > 0 )
        saveintobuffer(block);

    if(rem != LINESIZE)                             /* Flush the buffer. */
    {
        if( !savestr(buffer, LINESIZE - rem) )
            printf("\nString not saved\n\n");
    }
}


/* chartohex: convert a character to its hexadecimal value; return the length
              of the new string or -1 if there are any errors. */

int chartohex(char *s, char c)
{
    return sprintf(s, "{0x%x}", c);
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


/* savehex: concatenate a character in hexadecimal format into a string; return
            the remaining space after concatenation. */

int savehex(char *s, char c, int rem)
{
    int chartohex(char *, char);

    int len;
    char hex[HEXSIZE];

    len = chartohex(hex, c);

    if(len >= 0)
    {
        strcat(s, hex);             /* Concatenation */

        rem -= len;
    }
    else
        printf("\n* ERROR *: character not converted to hexadecimal\n\n");

    return rem;
}


/* saveintobuffer: save a short string of characters to a buffer; if the buffer
                   is full it will be saved in the list of strings; return 0 if
                   there is no space for more strings and 1 if successful. */

int saveintobuffer(char *s)
{
    int savestr(char *, int);

    int n;

    if( ( n = strlen(s) ) < rem )           /* Save characters to buffer. */
    {
        strcat(buffer, s);

        rem -= n;
    }
    else if(pos < MAXLINES)                 /* Save the buffer in the list */
    {                                       /*and then save the characters */
        if( !savestr(buffer, LINESIZE - rem) )          /* to the buffer. */
            printf("\nString not saved\n\n");

        buffer[0] = '\0';

        rem = LINESIZE;

        strcat(buffer, s);

        rem -= n;
    }
    else
    {
        printf("\n* ERROR *: no space for more data\n\n");

        return 0;
    }

    return 1;
}


/* savestr: save the string "s" in a list of lines; return 0 if there is an
            error, 1 otherwise. */

int savestr(char *s, int len)
{
    char *stralloc(int);

    char *p = stralloc(len);        /* Allocate space for string. */

    if(p != NULL)
    {
        lineptr[pos++] = strcpy(p, s);

        s[0] = '\0';

        return 1;
    }
    else
    {
        printf("\n* stralloc ERROR *: malloc returned NULL for string:\n\n");

        printf("\"%s\"\n\n", s);

        return 0;
    }
}


/* stralloc: allocate memory for a string of length "n". */

char *stralloc(int n)
{
    return (char *)malloc(n + 1);
}


/* writelines: write output lines. */

void writelines(char *lineptr[], int nlines)
{
    printf("\n\n");

    while(nlines-- > 0)
        printf("%s\n", *lineptr++);
}
