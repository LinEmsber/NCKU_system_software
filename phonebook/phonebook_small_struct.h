#ifndef _PHONEBOOK_SMALL_STRUCT_H
#define _PHONEBOOK_SMALL_STRUCT_H

#define MAX_LAST_NAME_SIZE 16

/* small strutcture */
typedef struct small_PHONE_BOOK list_node_t;

struct small_PHONE_BOOK{
	char lastName[ MAX_LAST_NAME_SIZE];
	struct small_PHONE_BOOK * p_next;
};

/* linked list */
list_node_t *list_append(char lastName[], list_node_t *e);
list_node_t *list_find_name(char lastName[], list_node_t *p_head);
void list_delete_all(list_node_t * p_head);

#endif
