#ifndef _PHONEBOOK_LIST2BST_H
#define _PHONEBOOK_LIST2BST_H

#define MAX_LAST_NAME_SIZE 16
#define HASH_TABLE_SIZE 400000

/* small strutcture */
typedef struct small_PHONE_BOOK list_node_t;

struct small_PHONE_BOOK{
	char lastName[MAX_LAST_NAME_SIZE];
	struct small_PHONE_BOOK * p_next;
};


/* linked list */
list_node_t * list_append(char lastName[], list_node_t * e);
list_node_t * list_find_name(char lastName[], list_node_t * p_head);
void list_delete_all(list_node_t * p_head);


/* typedef */
typedef struct hash_element hash_elem_t;
typedef struct hash_table hash_table_t;
typedef struct hash_element_iter hash_elem_iter_t;

/* strucuture */
struct hash_element {
	struct hash_element * next;
	void * data;
	char * key;
};

struct hash_table {
	unsigned int capacity;
	unsigned int element_number;
	struct hash_element ** table;
};

/* function */

unsigned int hash_table_calc_hash_BKDR(char * str);
hash_table_t * hash_table_create(unsigned int _capacity);
void * hash_table_put(hash_table_t * _ht, char * _key, void * _data);
void * hash_table_get(hash_table_t * _ht, char * _key);
void * hash_table_remove(hash_table_t * _ht, char * _key);
void hash_table_destroy(hash_table_t * _ht);

#endif
