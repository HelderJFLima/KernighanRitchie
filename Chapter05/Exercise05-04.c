/* Exercise 5-4. Write the function "strend(s, t)", which returns 1 if the
   string "t" occurs at the end of the string "s", and zero otherwise. */


#include <string.h>     /*For "strlen" */


/* strend: returns 1 if the string "t" occurs at the end of "s", and zero
           otherwise. */

int strend(char *s, char *t)
{
    char *ss = s, *tt = t;
    enum boolean {FALSE, TRUE};

    if( strlen(t) > strlen(s) )         /* Impossible to match */
        return FALSE;

    while(*ss)                          /* Go to the end of strings. */
        ++ss;

    while(*tt)
        ++tt;
                                        /* Compare characters backwards. */
    while(*ss == *tt && ss != s && tt != t)
        --ss, --tt;

    if(tt != t)                         /* Mismatch in the middle of "t" */
        return FALSE;

    else if(*ss != *tt)                 /* Mismatch at the beginning of "t" */
        return FALSE;

    else                                /* Match */
        return TRUE;
}
