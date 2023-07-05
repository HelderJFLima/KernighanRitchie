/* Exercise 5-3. Write a pointer version of the function "strcat" that we showed
   in Chapter 2: "strcat(s, t)" copies the string "t" to the end of "s". */


/* strcat: concatenate "t" to end of "s"; "s" must be big enough;
           pointer version. */

void strcat(char *s, char *t)
{
    while (*s != '\0')                      /* Find end of "s". */
        s++;

    while (*s++ = *t++)                     /* Copy "t". */
        ;
}
