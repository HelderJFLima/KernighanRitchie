/* Exercise 3-2. Write a function "escape(s, t)" that converts characters like
   newline and tab into visible escape sequences like "\n" and "\t" as it copies
   the string "t" to "s". Use a switch. Write a function for the other direction
   as well, converting escape sequences into the real characters. */


#include <stdio.h>

#define STRSIZE 50                      /* Maximum string size */

void escape(char to[], char from[]);

void revescape(char to[], char from[]);


main()
{
    int i;
    char c;
    char s[STRSIZE], t[STRSIZE], u[STRSIZE];


    t[0] = c = 'a';                     /* A string with the alphabet and tabs
                                           and new lines between letters */

    for(i = 1; c < 'z'; i++)
    {
        if(i % 5 == 0)
            t[i] = '\t';

        else if(i % 7 == 0)
            t[i] = '\n';

        else
            t[i] = ++c;
    }

    t[i] = '\0';

    printf("\n%s\n", t);

    escape(s, t);                       /** escape test **/

    printf("\n%s\n", s);

    revescape(u, s);                    /** reverse operation test **/

    printf("\n%s\n\n", u);

    return 0;
}


/* escape: converts characters newline and tab into visible escape sequences
           "\n" and "\t" as it copies the string "t" to "s"; assume "s" is
           big enough. */

void escape(char s[], char t[])
{
    int i, j;

    i = j = 0;

    while(t[i] != '\0')
    {
        switch (t[i])
        {
        case '\t':

            s[j] = '\\';

            s[j + 1] = 't';

            i++;

            j += 2;

            break;

        case '\n':

            s[j] = '\\';

            s[j + 1] = 'n';

            i++;

            j += 2;

            break;

        default:

            s[j] = t[i];

            i++;

            j++;

            break;
        }
    }

    s[j] = '\0';
}


/* revescape: do the reverse operation of "escape", converting escape sequences
              "\t" and "\n" into the real characters. */

void revescape(char s[], char t[])
{
    int i, j;

    i = j = 0;

    while(t[i] != '\0')
    {
        if(t[i] == '\\' && t[i + 1] == 't')
        {
            s[j++] = '\t';

            i += 2;
        }
        else if(t[i] == '\\' && t[i + 1] == 'n')
        {
            s[j++] = '\n';

            i += 2;
        }
        else
        {
            s[j] = t[i];

            i++;

            j++;
        }
    }

    s[j] = '\0';
}
