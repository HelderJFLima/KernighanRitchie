/* Exercise 5-5. Write versions of the library functions "strncpy", "strncat",
   and "strncmp", which operate on at most the first "n" characters of their
   argument strings. For example, "strncpy(s, t, n)" copies at most "n"
   characters of "t" to "s". Full descriptions are in Appendix B. */


/* strncpy: copy at most "n" characters of string "t" to "s"; return "s". Pad
            with '\0''s if "t" has fewer than "n" characters, but don't pad
            otherwise. */

char *strncpy(char *s, char *t, int n)
{
    char *sp = s;

    while(*t != '\0' && n > 0)
    {
        *sp++ = *t++;

        n--;
    }

    while(n > 0)
        *sp++ = '\0';

    return s;
}


/* strncat: concatenate at most "n" characters of string "t" to string "s",
            terminate "s" with '\0'; return "s". */

char *strncat(char *s, char *t, int n)
{
    char *sp = s;

    while(*sp != '\0')              /* Go to the end of string. */
        sp++;

    while(*t != '\0' && n > 0)
    {
        *sp++ = *t++;

        n--;
    }

    *sp = '\0';

    return s;
}


/* strncmp: compare at most "n" characters of string "s" to string "t";
            return <0 if s < t, 0 if s == t, or >0 if s > t. */

int strncmp(char *s, char *t, int n)
{
    while(*s == *t && *s != '\0' && *t != '\0' && n > 0)
        s++, t++, n--;

    if(n == 0 || *s == '\0' && *t == '\0')      /* s == t */
        return 0;

    else if(*s != '\0' && *t != '\0')           /* s != t */
        return (int)(*s - *t);

    else if(*s == '\0')                         /* s < t */
        return -1;

    else                                        /* s > t */
        return 1;
}
