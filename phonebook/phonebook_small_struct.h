#ifndef _PHONEBOOK_SMALL_STRUCT_H
#define _PHONEBOOK_SMALL_STRUCT_H

#define MAX_LAST_NAME_SIZE 16

/* small strutcture */
typedef struct small_PHONE_BOOK entry;

struct small_PHONE_BOOK{
	char lastName[ MAX_LAST_NAME_SIZE];
	struct small_PHONE_BOOK * p_next;
};

/* linked list */
entry *list_append(char lastName[], entry *e);
entry *list_find_name(char lastName[], entry *p_head);
void list_delete_all(entry * p_head);

#endif
