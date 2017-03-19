#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

#define OPT 1


/* original */
typedef struct __LAST_NAME entry;

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
	struct __PHONE_BOOK_ENTRY *pNext;
}detail;

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);


/* small strutcture */
struct __LAST_NAME{
	char lastName[ MAX_LAST_NAME_SIZE];
	struct __LAST_NAME *pNext;
};


/* binary search tree */
typedef struct bst_node bst_node_t;

struct bst_node{
        char * last_name;
        struct bst_node *left;
        struct bst_node *right;
};

bst_node_t * node_create();
bst_node_t * node_input_last_name(bst_node_t *node, char * last_name);
bst_node_t * node_insert_node_last_name(bst_node_t * root, char * last_name);
bst_node_t * search_iteratively(bst_node_t *root, char * target_last_name);



#endif
