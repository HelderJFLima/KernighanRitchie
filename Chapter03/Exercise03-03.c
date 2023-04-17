/* Exercise 3-3. Write a function "expand(s1, s2)" that expands shorthand
   notations like "a-z" in the string "s1" into the equivalent complete list
   "abc...xyz" in "s2". Allow for letters of either case and digits, and be
   prepared to handle cases like "a-b-c" and "a-z0-9" and "-a-z". Arrange that
   a leading or trailing "-" is taken literally. */


/* "Taken literally" has been interpreted to mean "not a sign of a range, but
   an isolated symbol". */


#include <stdio.h>
#include <ctype.h>      /* Used by "expand" function */

#define MAXSTR 1000     /* Maximum string size */

int getline(char line[], int maxline);

void expand(char shrt[], char lng[]);


main()
{
    char shrt[MAXSTR], lng[MAXSTR];

    printf("\nEnter shorthand notations:\n\n");

    while( getline(shrt, MAXSTR) > 0 )
    {
        expand(shrt, lng);                          /** expand test **/

        printf("\n%s\n\n", lng);
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


/* expand: expand shorthand notations like "a-z" in the string "s1" into the
           equivalent complete list "abc...xyz" in "s2"; allow for letters of
           either case and digits; assume "s2" is big enough. */

void expand(char s1[], char s2[])
{
    int i, j = 0;
    char c, stp;

    for(i = 0; s1[i] == ' '; i++)               /* Jump initial blanks */
        ;

    if( s1[i] != '\0' && (isalnum(s1[i]) || s1[i] == '-') )
    {
        s2[j] = s1[i];                          /* Leading "-" is accepted. */

        i++, j++;

        while(isalnum(s1[i]) || s1[i] == '-')
        {
            if(s1[i] == '-')
            {
                if( islower(s1[i - 1]) && islower(s1[i + 1]) ||     /* Ranges */
                    isupper(s1[i - 1]) && isupper(s1[i + 1]) ||
                    isdigit(s1[i - 1]) && isdigit(s1[i + 1])    )
                {
                    stp = (s1[i + 1] >= s1[i - 1]) ? 1 : -1;

                    for(c = s1[i - 1] + stp; s2[j - 1] != s1[i + 1]; c += stp)
                        s2[j++] = c;

                    i += 2;
                }
                else if( isalnum(s1[i + 1]) )               /* Not a range */
                {
                    s2[j] = s1[i + 1];

                    i += 2, j++;
                }                                           /* Trailing "-" */
                else if(s1[i - 1] == '-' || !isalnum(s1[i + 1]) )
                {
                    s2[j] = s1[i];

                    i++, j++;
                }
            }
            else                                            /* Other cases */
            {
                s2[j] = s1[i];

                i++, j++;
            }
        }
    }

    s2[j] = '\0';
}
