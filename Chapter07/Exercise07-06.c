/* Exercise 7-6. Write a program to compare two files, printing the first line
   where they differ. */


#include <stdio.h>
#include <stdlib.h>     /* For "exit" */
#include <string.h>     /* For "strcmp" and "strlen" */

#define MAXLINE 1000    /* Maximum input line length */


int fcomp(FILE *a, FILE *b, char *s, char *t, int maxline);

void showblank(char *s);


/* compare two files, printing the first line where they differ. */

main(int argc, char *argv[])
{
    FILE *p1, *p2;
    char line1[MAXLINE], line2[MAXLINE];
    int result;

    if(argc != 3)
    {
        fprintf(stderr, "\n* %s ERROR *: invalid", argv[0]);

        fprintf(stderr, " number of arguments.\n\n");

        exit(1);
    }

    p1 = fopen(argv[1], "r");

    p2 = fopen(argv[2], "r");

    if(p1 == NULL || p2 == NULL)
    {
        fprintf(stderr, "\n* %s ERROR *: problems", argv[0]);

        fprintf(stderr, " opening file(s).\n\n");

        exit(2);
    }
                                                                /* Comparison */
    if( ( result = fcomp(p1, p2, line1, line2, MAXLINE) ) == EOF )
    {
        fprintf(stderr, "\n* %s ERROR *: problems", argv[0]);

        fprintf(stderr, " reading file(s).\n\n");

        exit(3);
    }
    else if(result == 0)

        printf("\nThe contents of the files are the same.\n\n");

    else
    {
        showblank(line1);

        showblank(line2);

        printf("\nFiles differ on line %d:", result);

        printf("\n\n%s\n", line1);

        printf("%s\n", line2);
    }

    fclose(p1);

    fclose(p2);

    return 0;
}


/* fcomp: compare two files; return the number of the first line where they
          differ and save the contents of the different lines in strings "s"
          and "t"; return 0 if the content is the same or EOF if an error
          occurs. */

int fcomp(FILE *a, FILE *b, char *s, char *t, int lim)
{
    char *sp, *tp;
    int n = 0;

    while( !feof(a) && !feof(b) )
    {
        sp = fgets(s, lim, a);

        tp = fgets(t, lim, b);

        n++;

        if(sp == NULL || tp == NULL)
        {
            if( ferror(a) || ferror(b) )    /* Error reading file */
                return EOF;
        }
        else if( strcmp(s, t) != 0 )        /* If the lines are different */
            return n;
    }

    if( feof(a) && !feof(b) )               /* Only one EOF */
    {
        *s = '\0';

        return n;
    }
    else if( !feof(a) && feof(b) )
    {
        *t = '\0';

        return n;
    }
    else if( sp == NULL && tp != NULL )     /* Two EOFs */
    {
        *s = '\0';

        return n;
    }
    else if( sp != NULL && tp == NULL )
    {
        *t = '\0';

        return n;
    }
    else                                    /* Same contents */
        return 0;
}


/* showblank: swap the characters '\n', ' ' or '\t' at the end of string "s"
              with visible characters. */

void showblank(char *s)
{
    int i;

    if( ( i = strlen(s) ) < MAXLINE - 1 && i > 0 )
    {
        switch(s[--i])
        {
            case '\n':

                s[i++] = '\\';

                s[i++] = 'n';

                s[i] = '\0';

                break;

            case ' ':

                s[i] = '_';

                break;

            case '\t':

               s[i++] = '\\';

               s[i++] = 't';

               s[i] = '\0';

               break;
        }
    }
}
