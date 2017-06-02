#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16


/* original version */
typedef struct __PHONE_BOOK_ENTRY {
	char lastName[MAX_LAST_NAME_SIZE];
	char firstName[16];
	char email[16];
	char phone[10];
	char cell[10];
	char addr1[16];
	char addr2[16];
	char city[16];
	char state[2];
	char zip[5];
	struct __PHONE_BOOK_ENTRY * p_next;
} list_node_t;


list_node_t *list_find_name(char lastName[], list_node_t *p_head);
list_node_t *list_append(char lastName[], list_node_t *e);
void list_delete_all(list_node_t * p_head);


#endif
