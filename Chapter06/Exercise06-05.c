/* Exercise 6-5. Write a function "undef" that will remove a name and definition
   from the table maintained by "lookup" and "install". */


#include <stdlib.h>     /* For free */
#include <string.h>     /* For strcmp */


/* Table entry */

struct nlist { char *name;                  /* Defined name */
               char *defn;                  /* Replacement text */
               struct nlist *next; };       /* Next entry in chain */


static struct nlist *hashtab[HASHSIZE];     /* Pointer table */


/* undef: remove a name and definition from a table. */

void undef(char *name)
{
    unsigned hashval;
    struct nlist *p, *prevp;                /* Current and previous pointers */
    unsigned hash(char *);

    hashval = hash(name);

    prevp = p = hashtab[hashval];

    while(p != NULL)
    {
        if(strcmp(name, p->name) == 0)      /* Found */
        {
            free( (void *)p->name );

            free( (void *)p->defn );

            if(prevp != p)

                prevp->next = p->next;

            else                            /* First node of the list */
                hashtab[hashval] = p->next;

            free( (void *)p );

            break;
        }
        else if(prevp != p)
            prevp = p;

        p = p->next;
    }
}
