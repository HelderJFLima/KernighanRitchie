/* Exercise 5-15. Add the option "-f" to fold upper and lower case together, so
   that case distinctions are not made during sorting; for example, "a" and "A"
   compare equal. */


#include <ctype.h>      /* For "tolower" */
#include <stdio.h>
#include <stdlib.h>     /* For "atof" */
#include <string.h>     /* For "strcmp" and "strcpy" */

#define BUFFSIZE 100000 /* Available buffer space size */
#define MAXLEN   1000   /* Maximum length of any input line */
#define MAXLINES 100    /* Maximum number of lines to be sorted */

char *alloc(int n);

int getline(char line[], int maxlen);

int numcmp(char *str1, char *str2);

void qsortt(void *lineptr[], int left, int right,
            int (*comp)(const void *, const void *) );

int readargs(char *args[]);

int readlines(char *lineptr[], int maxlines);

void reversep(void *arr[], int size);

int strfcmp(char *str1, char *str2);

void swap(void *arr[], int i, int j);

void writelines(char *lineptr[], int nlines);

char buffer[BUFFSIZE];          /* Buffer for input */
char *buffp = buffer;           /* Next free position */
enum boolean {FALSE, TRUE};
int fold = FALSE;               /* Is it folded sort? */
int numeric = FALSE;            /* Is it numeric sort? */
int reverse = FALSE;            /* Is it reverse sort? */


/* Sort input lines */

main(int argc, char *argv[])
{
    int nlines;                         /* Number of input lines read */
    char *lineptr[MAXLINES];            /* Pointers to text lines */
    void *func;                         /* Pointer to comparison function */

    if(argc == 2 || argc == 3 || argc == 4)
    {
        if( !readargs(argv) )
            return 1;
    }
    else if(argc != 1)
    {
        printf("\n* ERROR *: invalid number of arguments\n\n");

        return 2;
    }

    if ( ( nlines = readlines(lineptr, MAXLINES) ) >= 0 )
    {
        if(numeric)           /* Choose the function to compare the strings. */

            func = (void*)numcmp;

        else if(fold)

            func = (void*)strfcmp;

        else
            func = (void*)strcmp;

        qsortt( (void**)lineptr, 0, nlines - 1,             /* Sort strings. */
                ( int (*)(const void*, const void*) )func );

        if(reverse)                     /* Optional decreasing order output */
            reversep( (void**)lineptr, nlines);

        writelines(lineptr, nlines);

        return 0;
    }
    else
    {
        printf("\n* ERROR *: input too big to sort.\n\n");

        return 3;
    }
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


/* numcmp: compare "s1" and "s2" numerically. */

int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);

    v2 = atof(s2);

    if (v1 < v2)

        return -1;

    else if (v1 > v2)

        return 1;

    else
        return 0;
}


/* qsortt: sort "v" elements into increasing order. */

void qsortt(void *v[], int left, int right,
            int (*comp)(const void *, const void *) )
{
    int i, last;

    if (left >= right)      /* Do nothing if array contains fewer than two */
        return;             /* elements. */

    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; i++)
    {
        if ( (*comp)( v[i], v[left] ) < 0 )
            swap(v, ++last, i);
    }

    swap(v, left, last);

    qsortt(v, left, last - 1, ( int (*)(const void*, const void*) )comp);

    qsortt(v, last + 1, right, ( int (*)(const void*, const void*) )comp);
}


/* readargs: read a list of arguments; return 1 if any or all of them match
             and 0 otherwise.*/

int readargs(char *args[])
{
    while(*++args != NULL)
    {
        if(strcmp(*args, "-f") == 0)

            fold = TRUE;

        else if(strcmp(*args, "-n") == 0)

            numeric = TRUE;

        else if(strcmp(*args, "-r") == 0)

            reverse = TRUE;

        else
        {
            printf("\n* ERROR *: unknown argument: %s\n\n", *args);

            return 0;
        }
    }

    return 1;
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


/* reversep: reverse an array of pointers. */

void reversep(void *v[], int size)
{
    int i = 0;
    void *temp;

    size--;

    while(i < size)
    {
        temp = v[i];

        v[i++] = v[size];

        v[size--] = temp;
    }
}


/* strfcmp: compare string "s" to string "t" ignoring case distinctions;
            return <0 if s < t, 0 if s == t, or >0 if s > t. */

int strfcmp(char *s, char *t)
{
    while(tolower(*s) == tolower(*t) && *s != '\0' && *t != '\0')
        s++, t++;

    if(*s == '\0' && *t == '\0')                /* s == t */

        return 0;

    else if(*s != '\0' && *t != '\0')           /* s != t */

        return tolower(*s) - tolower(*t);

    else if(*s == '\0')                         /* s < t */

        return -1;

    else                                        /* s > t */
        return 1;
}


/* swap: swap two pointers in "v". */

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];

    v[i] = v[j];

    v[j] = temp;
}


/* writelines: write output lines. */

void writelines(char *lineptr[], int nlines)
{
    printf("\n\n");

    while(nlines-- > 0)
        printf("%s\n", *lineptr++);
}
