#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "phonebook_hash.h"


/* original functions */
list_node_t * list_append(char lastName[], list_node_t * e)
{
	e = (list_node_t *) malloc ( sizeof(list_node_t) );
	strcpy(e->lastName, lastName);

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


/* Hash function use BKDR hash algorithm.  */
unsigned int hash_table_calc_hash_BKDR(char * str)
{
	unsigned int hash = 0;
	unsigned int seed = 131;

	while ( *str ){
		hash = (hash * seed) + (*str);
		str++;
	}

	return hash;
}

/* Create a hash table with the capacity.
 * According to the capacity to create the hash elements, and save them in a table.
 */
hash_table_t * hash_table_create(unsigned int _capacity)
{
	hash_table_t * hash_table_entry = malloc( sizeof(*hash_table_entry) );
	if(!hash_table_entry)
		return NULL;

	hash_table_entry->table = malloc( sizeof(hash_elem_t) * _capacity );
	if(hash_table_entry->table == NULL){
		free(hash_table_entry);
		return NULL;
	}

	unsigned int i;
	hash_table_entry->capacity = _capacity;
	hash_table_entry->element_number = 0;

	for(i = 0; i < _capacity; i++)
		hash_table_entry->table[i] = NULL;

	return hash_table_entry;
}

/* Store data in the hash table with the specific key.
 * If the collision of the keys occurs, we replace the old data with the new data , and return the old data.
 */
void * hash_table_put(hash_table_t * _ht, char * _key, void * _data)
{
	if(_data == NULL)
		return NULL;

	/* check the remaining space of the hash table. */
	if (_ht->capacity <= _ht->element_number){
		printf("out of space of the hash table.\n");
		return NULL;
	}

	unsigned int hash_code = hash_table_calc_hash_BKDR(_key) % _ht->capacity;
	hash_elem_t * he = _ht->table[hash_code];

	/* If the hash element have already occupied by the other data. */
	while( he != NULL ){
		if( !strcmp(he->key, _key) ) {

			/* replace the old data with the new data, and return the old data. */
			void * ret = he->data;
			he->data = _data;

			return ret;
		}
		he = he->next;
	}

	/* Getting here means the key does not already exist, and no collision occurs. */
	he = malloc( sizeof(hash_elem_t) );
	if(he == NULL)
		return NULL;

	he->key = _key;
	he->data = _data;

	/* Add the element at the beginning of the linked list. */
	he->next = _ht->table[hash_code];

	_ht->table[hash_code] = he;
	_ht->element_number ++;

	return NULL;
}

/* Using the key to retrieve data from the hash table */
void * hash_table_get(hash_table_t * _ht, char * _key)
{
	unsigned int hash_code = hash_table_calc_hash_BKDR(_key) % _ht->capacity;
	hash_elem_t * he = _ht->table[hash_code];

	while(he != NULL) {

		if(!strcmp(he->key, _key)){
			return he->data;
		}

		he = he->next;
	}
	return NULL;
}


/* Remove the data from the hash table according to the key.
 * Return the data removed from the table, so that we can free its memory if needed.
 */
void * hash_table_remove(hash_table_t * _ht, char * _key)
{
	unsigned int hash_code = hash_table_calc_hash_BKDR(_key) % _ht->capacity;
	hash_elem_t * he = _ht->table[hash_code];
	hash_elem_t * prev = NULL;

	while(he != NULL) {

		if( !strcmp(he->key, _key) ) {

			void * ret = he->data;

			if(prev != NULL)
				prev->next = he->next;
			else
				_ht->table[hash_code] = he->next;

			free(he);
			he = NULL;

			_ht->element_number--;

			return ret;
		}

		prev = he;
		he = he->next;
	}

	return NULL;
}

// TODO:
// void hash_table_destroy(hash_table_t * _ht);
// {
//
// }
