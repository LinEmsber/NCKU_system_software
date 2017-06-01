#ifndef _PHONEBOOK_LIST2BST_H
#define _PHONEBOOK_LIST2BST_H

#define MAX_LAST_NAME_SIZE 16

/* small strutcture */
typedef struct small_PHONE_BOOK list_node_t;

struct small_PHONE_BOOK{
	char lastName[MAX_LAST_NAME_SIZE];
	struct small_PHONE_BOOK * p_next;
};

/* linked list */
list_node_t *list_append(char lastName[], list_node_t *e);
list_node_t *list_find_name(char lastName[], list_node_t *p_head);
void list_delete_all(list_node_t * p_head);


/* binary search tree */
typedef struct bst_node bst_node_t;

struct bst_node{
        struct small_PHONE_BOOK * entry_node;
        struct bst_node * left;
        struct bst_node * right;
};


bst_node_t * list_to_bst(list_node_t ** node, int len);
bst_node_t * bst_search(bst_node_t *root, char * target_last_name);
void bst_remove(bst_node_t * node);
void bst_node_dfs( bst_node_t * node, int depth );

#endif
