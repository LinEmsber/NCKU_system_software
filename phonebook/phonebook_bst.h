#ifndef _PHONEBOOK_BST_H
#define _PHONEBOOK_BST_H

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



/* binary search tree */
typedef struct bst_node bst_node_t;

struct bst_node{
        struct small_PHONE_BOOK * entry;
        struct bst_node *left;
        struct bst_node *right;
};

bst_node_t * node_create();
int node_input_last_name(bst_node_t *node, char * lastName);
bst_node_t * node_insert_node_last_name(bst_node_t * root, char * lastName);
bst_node_t * bst_search(bst_node_t *root, char * target_last_name);



#endif
