#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "phonebook_small_struct.h"


/* original functions */
entry * list_append(char lastName[], entry * e)
{
	entry * tmp = (entry *) malloc(sizeof(entry));
	if (tmp == NULL)
		return NULL;

	tmp->p_next = NULL;
	strcpy(tmp->lastName, lastName);

	e->p_next = tmp;

	return e;
}


entry * list_find_name(char lastName[], entry * p_head)
{
	while (p_head != NULL){
		if ( strcasecmp(lastName, p_head->lastName) == 0 )
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
