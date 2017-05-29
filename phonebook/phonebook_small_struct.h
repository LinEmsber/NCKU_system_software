#ifndef _PHONEBOOK_SMALL_STRUCT_H
#define _PHONEBOOK_SMALL_STRUCT_H

#define MAX_LAST_NAME_SIZE 16

#ifdef _ORIG_STRUCT

/* original structure */
typedef struct _PHONE_BOOK entry;

struct _PHONE_BOOK {
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
	struct _PHONE_BOOK * p_next;
};


#elif _SMALL_STRUCT

/* small strutcture */
typedef struct small_PHONE_BOOK entry;

struct small_PHONE_BOOK{
	char lastName[ MAX_LAST_NAME_SIZE];
	struct small_PHONE_BOOK * p_next;
};

#endif

/* linked list */
entry *list_append(char lastName[], entry *e);
entry *list_find_name(char lastName[], entry *p_head);
void list_delete_all(entry * p_head);

#endif
