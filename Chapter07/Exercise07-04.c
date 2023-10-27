/* Exercise 7-4. Write a private version of "scanf" analogous to "minprintf"
   from the previous section. */


#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMLEN 100      /* Maximum number of characters of a number */


/* minscanf: minimal "scanf" with variable argument list */

int minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, c, num[NUMLEN], *sval;
    int i, *ival, match;
    double *dval;

    va_start(ap, fmt);

    num[0] = '\0';

    i = match = 0;

    for(p = fmt; *p; p++)
    {
        if(*p != '%')
        {
            if( ( c = getchar() ) == *p )

                continue;

            else
                return match;
        }

        switch(*++p)
        {
            case 'd':

                ival = va_arg(ap, int *);

                while( isdigit( c = getchar() ) )
                    num[i++] = c;

                num[i] = '\0';

                if( strlen(num) > 0 )
                {
                    *ival = atoi(num);

                    match++;
                }
                else
                    return match;

                i = 0;

                num[i] = '\0';

                if(*++p != c)
                    return match;

                break;

            case 'f':

                dval = va_arg(ap, double *);

                while( isdigit( c = getchar() ) )
                    num[i++] = c;

                if(c == '.')
                {
                    num[i++] = c;

                    while( isdigit( c = getchar() ) )
                        num[i++] = c;
                }

                num[i] = '\0';

                if( strlen(num) > 0 )
                {
                    *dval = atof(num);

                    match++;
                }
                else
                    return match;

                i = 0;

                num[i] = '\0';

                if(*++p != c)
                    return match;

                break;

            case 's':

                sval = va_arg(ap, char *);

                while( ( c = getchar() ) != EOF )
                {
                    *sval++ = c;
                }

                *sval = '\0';

                break;

            default:

                return match;
        }
    }

    va_end(ap);

    return match;
}
