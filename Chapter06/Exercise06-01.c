/* Exercise 6-1. Our version of "getword" does not properly handle underscores,
   string constants, comments, or preprocessor control lines. Write a better
   version. */


/* getword: get next word or character from input. */

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while ( isspace( c = getch() ) )
        ;

    if(c == '\\')
    {
        if( ( c = getch() ) == '*' )                    /* Found a comment */
        {
            while( ( c = getch() ) != EOF )
            {
                if(c == '*')
                {
                    if( ( c = getch() ) == '/' )
                    {
                        c = getch();

                        break;
                    }
                    else
                        ungetch(c);
                }
            }
        }
        else
        {
            ungetch(c);

            return '\\';
        }
    }

    if(c != EOF)
        *w++ = c;

    if(!isalpha(c) && c != '_' && c != '\"' && c != '#')   /* New features */
    {
        *w = '\0';

        return c;
    }

    for( ; --lim > 0; w++)
    {
        if(!isalnum( *w = getch() ) && *w != '_' && *w != '\"' && *w != '#')
        {
            ungetch(*w);

            break;
        }
    }

    *w = '\0';

    return word[0];
}
