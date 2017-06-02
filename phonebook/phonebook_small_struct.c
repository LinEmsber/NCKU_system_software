#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "phonebook_small_struct.h"


/* original functions */
list_node_t * list_append(char lastName[], list_node_t * e)
{
	e->p_next = (list_node_t *) malloc ( sizeof(list_node_t) );
	e = e->p_next;
	strcpy(e->lastName, lastName);
	e->p_next = NULL;

	return e;
}


list_node_t * list_find_name(char lastName[], list_node_t * p_head)
{
	while (p_head != NULL){

		if ( strcasecmp(lastName, p_head->lastName) == 0 ){
			return p_head;
		}
		p_head = p_head->p_next;
	}

	return NULL;
}

void list_delete_all(list_node_t * p_head)
{
        list_node_t * tmp;
        while(p_head){
                tmp = p_head;
                p_head = p_head->p_next;
                free(tmp);
        }
}
