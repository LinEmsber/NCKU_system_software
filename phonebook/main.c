/* phone book */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <time.h>
#include <assert.h>

#include "generic_tools.h"
#include IMPL

#ifdef _ORIG_STRUCT

#define OUT_FILE "phonebook_orig.txt"
#define DICT_FILE "./dictionary/words.txt"

#elif _SMALL_STRUCT

#define OUT_FILE "phonebook_small_struct.txt"
#define DICT_FILE "./dictionary/words.txt"

#elif _BST

#define DICT_FILE "./dictionary/words_10_percentage.txt"
#define OUT_FILE "phonebook_bst.txt"

#elif _LIST2BST

#define DICT_FILE "./dictionary/words.txt"
#define OUT_FILE "phonebook_list2bst.txt"

#elif _HASH

#define DICT_FILE "./dictionary/words.txt"
#define OUT_FILE "phonebook_hash.txt"

#endif

// #define DICT_FILE "./dictionary/words_debug.txt"

int main(int argc, char *argv[])
{
	int i = 0;
	FILE * fp;
	char line[MAX_LAST_NAME_SIZE];
	struct timespec start, end;
	double cpu_store_data_time, cpu_search_time;

	/* open file */
	fp = fopen(DICT_FILE, "r");
	if (fp == NULL)
		return 0;


	/* Using different method to construct the phone book and search the keyword. */
#if defined(_ORIG_STRUCT) || defined(_SMALL_STRUCT) && defined(__GNUC__)

	list_node_t * en;
	list_node_t * p_head = malloc( sizeof(* p_head) );
	if (p_head == NULL)
		return 0;

	en = p_head;
	en->p_next = NULL;

	printf("size of list_node_t : %lu bytes\n", sizeof(list_node_t));
	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(list_node_t));

#elif defined(_BST) && defined(__GNUC__)

	bst_node_t * bst_head = NULL;

	printf("size of list_node_t : %lu bytes\n", sizeof(list_node_t));
	__builtin___clear_cache((char *) bst_head, (char *) bst_head + sizeof(bst_node_t));

#elif defined(_LIST2BST) && defined(__GNUC__)

	list_node_t * en;
	list_node_t * p_head = malloc( sizeof(* p_head) );
	if (p_head == NULL)
		return 0;

	en = p_head;
	en->p_next = NULL;

	int node_counter = 0;

	printf("size of list_node_t : %lu bytes\n", sizeof(list_node_t));
	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(list_node_t));


#elif defined(_HASH) && defined(__GNUC__)

	list_node_t * tmp_entry = NULL;

	hash_table_t * ht_entry = hash_table_create(HASH_TABLE_SIZE);
	if (ht_entry == NULL)
		return 0;

	printf("size of list_node_t : %lu bytes\n", sizeof(list_node_t));
	__builtin___clear_cache((char *) ht_entry, (char *) ht_entry + sizeof(hash_table_t));

#endif


	clock_gettime(CLOCK_REALTIME, &start);

	/* read file stream from file, read one line at one time. */
	while ( fgets(line, sizeof(line), fp) ) {

		/* find the terminate byte, '\0'. */
		while (line[i] != '\0'){
			i++;
		}

		line[i - 1] = '\0';

		/* reset i for caculating the next line. */
		i = 0;

#if defined(_ORIG_STRUCT) || defined(_SMALL_STRUCT) && defined(__GNUC__)

		/* list_append the word of this line into a linked list. */
		en = list_append(line, en);

#elif defined(_BST) && defined(__GNUC__)

		/* insert the word of this line into a binary search tree. */
		bst_head = bst_insert_last_name(bst_head, line);

#elif defined(_LIST2BST) && defined(__GNUC__)

		/* list_append the word of this line into a linked list. */
		en = list_append(line, en);
		node_counter++;

#elif defined(_HASH) && defined(__GNUC__)

		/* */
		// tmp_entry = list_append(line, tmp_entry);
		tmp_entry = (list_node_t *) malloc ( sizeof(list_node_t) );
		strcpy(tmp_entry->lastName, line);

		hash_table_put(ht_entry, tmp_entry->lastName, tmp_entry);

#endif

	}

	/* After we read and save all contents, close file as soon as possible. */
	fclose(fp);





#if defined(_LIST2BST) && defined(__GNUC__)

	/* convert a linked list to binary serach tree. */
	en = p_head;
	bst_node_t * bst_head = list_to_bst(&en, node_counter);

#endif




	/* calculate the time of storing data. */
	clock_gettime(CLOCK_REALTIME, &end);
	cpu_store_data_time = diff_in_second(start, end);


	/* The target words we want to find. */
	char keyword[MAX_LAST_NAME_SIZE] = "zyxel";


#if defined(_ORIG_STRUCT) || defined(_SMALL_STRUCT) && defined(__GNUC__)

	en = p_head;
	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(list_node_t));

	clock_gettime(CLOCK_REALTIME, &start);
	list_node_t * tmp = list_find_name(keyword, en);
	clock_gettime(CLOCK_REALTIME, &end);

	if (tmp == NULL){
		printf("The keyword: %s not be found.\n", keyword);
	} else{
		printf("The exception last name: %s\n", keyword);
		printf("The searched last name: %s\n", tmp->lastName);
	}

#elif defined(_BST) && defined(__GNUC__)

	__builtin___clear_cache((char *) bst_head, (char *) bst_head + sizeof(bst_node_t));

	clock_gettime(CLOCK_REALTIME, &start);
	clock_gettime(CLOCK_REALTIME, &end);
	bst_node_t * tmp = bst_search(bst_head, keyword);

	if (tmp == NULL){
		printf("The keyword: %s not be found.\n", keyword);
	} else{
		printf("The exception last name: %s\n", keyword);
		printf("The searched last name: %s\n", tmp->entry_node->lastName);
	}

#elif defined(_LIST2BST) && defined(__GNUC__)

	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(list_node_t));

	clock_gettime(CLOCK_REALTIME, &start);
	bst_node_t * tmp = bst_search(bst_head, keyword);
	clock_gettime(CLOCK_REALTIME, &end);

	if (tmp == NULL){
		printf("The keyword: %s not be found.\n", keyword);

	}else{
		printf("The exception last name: %s\n", keyword);
		printf("The searched last name: %s\n", tmp->entry_node->lastName);
	}

#elif defined(_HASH) && defined(__GNUC__)

	__builtin___clear_cache((char *) ht_entry, (char *) ht_entry + sizeof(hash_table_t));

	clock_gettime(CLOCK_REALTIME, &start);
	hash_elem_t * tmp = hash_table_get(ht_entry, keyword);
	clock_gettime(CLOCK_REALTIME, &end);

	if (tmp == NULL){
		printf("The keyword: %s not be found.\n", keyword);

	}else{
		printf("The exception last name: %s\n", keyword);
		printf("The searched last name: %s\n", ( (list_node_t *) tmp )->lastName);
	}

#endif


	/* compute the execution time */
	cpu_search_time = diff_in_second(start, end);



#if defined(_ORIG_STRUCT) || defined(_SMALL_STRUCT) && defined(__GNUC__)

	FILE *output = fopen(OUT_FILE, "a");
	fprintf(output, "list_append() list_find_name() %lf %lf\n", cpu_store_data_time, cpu_search_time);
	fclose(output);

	printf("execution time of list_append() : %lf sec\n", cpu_store_data_time);
	printf("execution time of list_find_name() : %lf sec\n", cpu_search_time);

	/* free the all linked list nodes. */
	list_delete_all(p_head);

#elif defined(_BST) && defined(__GNUC__)

	FILE *output = fopen(OUT_FILE, "a");
	fprintf(output, "bst_insert_last_name() bst_search() %lf %lf\n", cpu_store_data_time, cpu_search_time);
	fclose(output);

	printf("execution time of bst_insert_last_name() : %lf sec\n", cpu_store_data_time);
	printf("execution time of bst_search() : %lf sec\n", cpu_search_time);

	/* free the binary search tree. */
	bst_remove(bst_head);


#elif defined(_LIST2BST) && defined(__GNUC__)

	FILE *output = fopen(OUT_FILE, "a");
	fprintf(output, "bst_insert_last_name() bst_search() %lf %lf\n", cpu_time_store_data, cpu_time_search);
	fclose(output);
	
	printf("execution time of list_append() + list_to_bst() : %lf sec\n", cpu_time_store_data);
	printf("execution time of bst_search() : %lf sec\n", cpu_time_search);

	/* free the binary search tree. */
	bst_remove(bst_head);


#elif defined(_HASH) && defined(__GNUC__)


	FILE *output = fopen(OUT_FILE, "a");
	fprintf(output, "hash_table_put() hash_table_get() %lf %lf\n", cpu_store_data_time, cpu_search_time);
	fclose(output);

	printf("execution time of hash_table_put() : %lf sec\n", cpu_store_data_time);
	printf("execution time of hash_table_get() : %lf sec\n", cpu_search_time);

	// TODO:
	// void hash_table_destroy(hash_table_t * _ht);
	// hash_table_destroy(ht_entry);

#endif

	return 0;
}
