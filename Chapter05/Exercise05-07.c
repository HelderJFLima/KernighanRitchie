/* Exercise 5-7. Rewrite "readlines" to store lines in an array supplied by
   "main", rather than calling "alloc" to maintain storage. How much faster
   is the program? */


/* I didn't compare the speed of the algorithms. */


#include <string.h>         /* For "strcpy" */

#define MAXLEN 1000         /* Maximum length of any input line */

int getline(char *str, int lim);


/* readlines: read input lines; 2nd version. */

int readlines(char linebuf[], char *lineptr[], int maxbuf, int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;

    p = linebuf;

    while ( ( len = getline(line, MAXLEN) ) > 0 )
    {
        if (nlines >= maxlines || maxbuf - (p - linebuf) < len)
            return -1;
        else
        {
            line[len - 1] = '\0';       /* Delete newline. */

            strcpy(p, line);

            lineptr[nlines++] = p;

            p += len;
        }
    }

    return nlines;
}
