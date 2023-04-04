/* Exercise 2-5. Write the function "any(s1, s2)", which returns the first
   location in a string "s1" where any character from the string "s2" occurs,
   or -1 if "s1" contains no characters from "s2". (The standard library
   function "strpbrk" does the same job but returns a pointer to the location.) */


#include <stdio.h>

#define MAXLINE 1000                        /* Maximum input line length */

int getline(char line[], int maxline);

int any(char string1[], char string2[]);


main()
{
    int pos;
    char str1[MAXLINE], str2[MAXLINE];

    printf("\nEnter a string of characters:\n\n");

    if( getline(str1, MAXLINE) > 0 )            /* Get the 1st string. */
    {
        printf("\n\nEnter a set of characters to search in the string:\n\n");

        if( getline(str2, MAXLINE) > 0 )        /* Get the 2nd string. */
        {
            pos = any(str1, str2);              /* Find the character location. */

            if(pos >= 0)
            {
                printf("\n\nThe first location in the string where one of ");

                printf("the given characters occurs is position %d.\n", pos);
            }
            else
            {
                printf("\n\nNone of the given characters ");

                printf("were found in the string.\n");
            }
        }
        else
            printf("\nNo characters set to search.\n");
    }
    else
        printf("\nNo string was given.\n");

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


/* any: return the first location in "s1" where any character from "s2" occurs,
        or -1 if "s1" contains no characters from "s2". */

int any(char s1[], char s2[])
{
    enum boolean{FALSE, TRUE};
    int i, j, match = FALSE;

    for(i = 0; !match && s1[i] != '\0'; i++)
    {
        for(j = 0; !match && s2[j] != '\0'; j++)
        {
            if(s1[i] != '\n' && s1[i] == s2[j])
                match = TRUE;
        }
    }

    if(match)
        return i - 1;
    else
        return -1;
}
