/* Exercise 2-4. Write an alternative version of "squeeze(s1, s2)" that deletes
   each character in "s1" that matches any character in the string "s2". */


#include <stdio.h>

#define MAXLINE 1000                            /* Maximum input line length */

int getline(char line[], int maxline);

void squeeze(char string1[], char string2[]);


main()
{
    char str1[MAXLINE], str2[MAXLINE];

    printf("\nEnter a string of characters:\n\n");

    if( getline(str1, MAXLINE) > 0 )
    {
        printf("\n\nEnter a set of characters to delete from the string:\n\n");

        if( getline(str2, MAXLINE) > 0 )
        {
            squeeze(str1, str2);

            printf("\n\nSqueezed string:\n\n%s\n", str1);
        }
        else
            printf("\nNo characters set to delete.\n");
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


/* squeeze: delete each character in "s1" that matches any character in "s2". */

void squeeze(char s1[], char s2[])
{
    enum boolean{FALSE, TRUE};
    int i, j, k, match = FALSE;

    for(i = j = 0; s1[i] != '\0'; i++)
    {
        for(k = 0; !match && s2[k] != '\0'; k++)
        {
            if(s1[i] == s2[k])
                match = TRUE;
        }

        if(!match)
            s1[j++] = s1[i];

        match = FALSE;
    }

    s1[j] = '\0';
}
