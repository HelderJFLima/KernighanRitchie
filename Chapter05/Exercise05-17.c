/* Exercise 5-17. Add a field-searching capability, so sorting may bee done on
   fields within lines, each field sorted according to an independent set of
   options. (The index for this book was sorted with -df for the index category
   and -n for the page numbers.) */


#include <ctype.h>      /* For "isalnum", "isblank", "isdigit", "tolower" */
#include <stdio.h>
#include <stdlib.h>     /* For "atof", "atoi" */
#include <string.h>     /* For "strcmp" and "strcpy" */

#define BUFFSIZE 100000 /* Available buffer space size */
#define MAXLEN   1000   /* Maximum length of any input line */
#define MAXLINES 100    /* Maximum number of lines to be sorted */
#define PTR      0      /* Pointer to a substring */
#define START    1      /* Start position of substring */
#define END      2      /* End position of substring */

char *alloc(int n);

int getline(char line[], int maxlen);

int ischareq(char c, char d);

int isvalidchar(int c);

int mapstr(char *str);

int numcmp(char *str1, char *str2);

void qsortt(void *lineptr[], int left, int right,
            int (*comp)(const void *, const void *) );

int readargs(char *args[]);

int readlines(char *lineptr[], int maxlines);

void reversep(void *arr[], int size);

int strdcmp(char *str1, char *str2);

int strfcmp(char *str1, char *str2);

int strscmp(char *str1, char *str2);

void strsec(char *lineptr[], int sector, int nlines);

void swap(void *arr[], int i, int j);

void writelines(char *lineptr[], int nlines);

char buffer[BUFFSIZE];          /* Buffer for input */
char *buffp = buffer;           /* Next free position */
char *limits[MAXLINES][3];      /* Pointers to limits of string sectors */
enum boolean {FALSE, TRUE};
int dir = FALSE;                /* Is it directory ordered? */
int field = FALSE;              /* Is it a sort by field? */
int fold = FALSE;               /* Is it folded sort? */
int numeric = FALSE;            /* Is it numeric sort? */
int reverse = FALSE;            /* Is it reverse sort? */


/* Sort input lines */

main(int argc, char *argv[])
{
    int nlines;                         /* Number of input lines read */
    int sector;                         /* Sector of string to be sorted */
    char *lineptr[MAXLINES];            /* Pointers to text lines */
    void *func;                         /* Pointer to comparison function */

    if(argc >= 2 && argc <= 7)
    {
        if( ( sector = readargs(argv) ) == 0 )
            return 1;
    }
    else if(argc != 1)
    {
        printf("\n* ERROR *: invalid number of arguments\n\n");

        return 2;
    }

    if ( ( nlines = readlines(lineptr, MAXLINES) ) >= 0 )
    {
        if(field)           /* Choose the function to compare the strings. */
        {
            func = (void*)strscmp;

                                    /* Generate array of substring pointers. */
            strsec(lineptr, sector, nlines);
        }
        else if(numeric)

            func = (void*)numcmp;

        else if(dir)

            func = (void*)strdcmp;

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


/* ischareq: compare two characters, ignoring case distinctions or not; return 1
             if they are equal, and 0 otherwise. */

int ischareq(char c, char d)
{
    return fold ? ( tolower(c) == tolower(d) ) : (c == d);
}


/* isvalidchar: check if "c" is a letter, a number or a blank character. */

int isvalidchar(int c)
{
    return isalnum(c) || isblank(c) || c == '\0';
}


/* mapstr: do a linear search and return the position of a string in the array
           of pointers; if there is no such string in the array, return -1. */

int mapstr(char *str)
{
    int i;

    for(i = 0; limits[i][PTR] != str && i < MAXLINES; i++)
        ;

    if(limits[i][PTR] == str)

        return i;

    else
        return -1;
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
    int n = 1;

    while(*++args != NULL)
    {
        if(strcmp(*args, "-d") == 0)

            dir = TRUE;

        else if(strcmp(*args, "-f") == 0)

            fold = TRUE;

        else if(strcmp(*args, "-n") == 0)

            numeric = TRUE;

        else if(strcmp(*args, "-r") == 0)

            reverse = TRUE;

        else if(strcmp(*args, "-s") == 0)

            field = TRUE;

        else if( isdigit(**args) )
        {
            n = atoi(*args);

            if(n == 0)
                printf("\n* ERROR *: invalid argument: %s\n\n", *args);
        }
        else
        {
            printf("\n* ERROR *: unknown argument: %s\n\n", *args);

            return 0;
        }
    }

    return n;
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


/* strdcmp: compare string "s" to string "t" considering only letters, numbers
            and blanks, ignoring case distinctions or not; return <0 if s < t,
            0 if s == t, or >0 if s > t. */

int strdcmp(char *s, char *t)
{
    int vs, vt;

    vs = vt = 0;                        /* Valid characters in each string */

                                        /* Jump invalid or equal characters */
    while( ( !isvalidchar(*s) || !isvalidchar(*t) || ischareq(*s, *t) ) &&
           *s != '\0' && *t != '\0' )
    {
        if( ischareq(*s, *t) )          /* Equal characters */
        {
            s++, t++;

            vs++, vt++;
        }
        else
        {
            if( !isvalidchar(*s) )

                s++;

            else
                vs++;

            if( !isvalidchar(*t) )

                t++;

            else
                vt++;
        }
    }

    if(*s == '\0' && *t == '\0')                /* s == t */

        return 0;

    else if(*s != '\0' && *t != '\0')           /* s != t */
    {
        if(fold)

            return tolower(*s) - tolower(*t);

        else
            return (int)(*s - *t);
    }
    else if(vs == vt)                           /* s == t */

        return 0;

    else                                        /* s != t */
        return (vs > vt) ? 1 : -1;
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


/* strscmp: compare string "s" to string "t" using the pre-specified
            sector/field; return <0 if s < t, 0 if s == t, or >0 if s > t.*/

int strscmp(char *s, char *t)
{
    int i, sstr, tstr;
    double n1, n2;
    char num[MAXLEN];
    char *sp, *tp;

    sstr = mapstr(s);       /* Position of string in the array of pointers */

    tstr = mapstr(t);

    sp = limits[sstr][START];       /* Substring start position */

    tp = limits[tstr][START];

    if(numeric)                     /* Copy substrings and convert to double. */
    {
        num[0] = '\0';

        for(i = 0; sp <= limits[sstr][END] && isdigit(*sp); i++, sp++)
            num[i] = *sp;

        num[i] = '\0';

        n1 = atof(num);

        num[0] = '\0';

        for(i = 0; tp <= limits[tstr][END] && isdigit(*tp); i++, tp++)
            num[i] = *tp;

        num[i] = '\0';

        n2 = atof(num);
    }
    else if(fold)       /* Search for the first characters that don't match. */
    {
        while( sp <= limits[sstr][END] && tp <= limits[tstr][END] &&
               tolower(*sp) == tolower(*tp) )
            sp++, tp++;
    }
    else
    {
        while(sp <= limits[sstr][END] && tp <= limits[tstr][END] && *sp == *tp)
            sp++, tp++;
    }

    if(numeric)
    {
        if(n1 < n2)

            return -1;

        else if(n1 > n2)

            return 1;

        else
            return 0;
    }
    else
    {                                                               /* s == t */
        if( sp > limits[sstr][END] && tp > limits[tstr][END] )

            return 0;
                                                                    /* s != t */
        else if( sp <= limits[sstr][END] && tp <= limits[tstr][END] )
        {
            if(fold)

                return tolower(*sp) - tolower(*tp);

            else
                return (int)(*sp - *tp);
        }
        else if( sp > limits[sstr][END] )                           /* s < t */

            return -1;

        else                                                        /* s > t */
            return 1;
    }
}


/* strsec: copy start and end pointers of string sectors into a two-dimensional
           array. */

void strsec(char *strptr[], int sect, int nstr)
{
    int i, j, n = 0;
    int inw = FALSE;                            /* Inside a word */

    for(i = 0; i < nstr; i++, strptr++)
    {
        limits[i][PTR] = *strptr;               /* Address of a string */

        for(j = 0; (*strptr)[j] != '\0'; j++)   /* Search in the string. */
        {
            if( !isblank( (*strptr)[j] ) )
            {
                if(inw == FALSE)                    /* Entering a word */
                {
                    inw = TRUE;

                    n++;
                                                        /* Starting address */
                    limits[i][START] = &( (*strptr)[j] );
                }
            }
            else
            {
                if(inw == TRUE)                     /* Coming out of a word */
                {
                    inw = FALSE;

                    limits[i][END] = &( (*strptr)[j - 1] ); /* Final address */

                    if(n == sect)
                        break;
                }
            }
        }

        if( (*strptr)[j] == '\0' )
        {
            inw = FALSE;

            if(n == sect)

                limits[i][END] = &( (*strptr)[j - 1] );

            else                                /* There's no such sector */
                limits[i][START] = limits[i][END] = &( (*strptr)[j] );
        }

        n = 0;
    }
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
