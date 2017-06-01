#ifndef _PHONEBOOK_BST_H
#define _PHONEBOOK_BST_H

#define MAX_LAST_NAME_SIZE 16

/* small strutcture */
typedef struct small_PHONE_BOOK entry;

struct small_PHONE_BOOK{
	char lastName[ MAX_LAST_NAME_SIZE];
	struct small_PHONE_BOOK * p_next;
};


/* binary search tree */
typedef struct bst_node bst_node_t;

struct bst_node{
        struct small_PHONE_BOOK * entry;
        struct bst_node *left;
        struct bst_node *right;
};

bst_node_t * bst_create();
bst_node_t * bst_insert_last_name(bst_node_t * root, char * lastName);
bst_node_t * bst_search(bst_node_t *root, char * target_last_name);
void bst_remove(bst_node_t * node);

#endif
