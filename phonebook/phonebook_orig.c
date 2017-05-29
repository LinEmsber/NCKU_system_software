#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_orig.h"

/* original version */
entry *list_append(char lastName[], entry *e)
{
        /* allocate memory for the new entry and put lastName */
        e->p_next = (entry *) malloc(sizeof(entry));
        e = e->p_next;
        strcpy(e->lastName, lastName);
        e->p_next = NULL;

        return e;
}


entry *list_find_name(char lastName[], entry *p_head)
{
    while (p_head != NULL) {
        if (strcasecmp(lastName, p_head->lastName) == 0)
            return p_head;
        p_head = p_head->p_next;
    }
    return NULL;
}


void list_delete_all(entry * p_head)
{
        entry * tmp;
        while(p_head){
                tmp = p_head;
                p_head = p_head->p_next;
                free(tmp);
        }
}
