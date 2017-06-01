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

#define DICT_FILE "./dictionary/words_10_percentage.txt"

// #define DICT_FILE "./dictionary/words__.txt"
#define DICT_FILE "./dictionary/words.txt"

#define OUT_FILE "phonebook_list2bst.txt"

#endif

int main(int argc, char *argv[])
{
	int i = 0;
	FILE * fp;
	char line[MAX_LAST_NAME_SIZE];
	struct timespec start, end;
	double cpu_time_store_data, cpu_time_search;

	/* open file */
	fp = fopen(DICT_FILE, "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}

	/* build the start list_node_t for linked list or binary search tree. */

#if defined(_ORIG_STRUCT) || defined(_SMALL_STRUCT) && defined(__GNUC__)

	list_node_t * e;
	list_node_t * p_head = malloc( sizeof(* p_head) );
	if (p_head == NULL)
		return 0;

	e = p_head;
	e->p_next = NULL;

	printf("size of list_node_t : %lu bytes\n", sizeof(list_node_t));
	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(list_node_t));

#elif defined(_BST) && defined(__GNUC__)

	bst_node_t * bst_head = NULL;

	printf("size of list_node_t : %lu bytes\n", sizeof(list_node_t));
	__builtin___clear_cache((char *) bst_head, (char *) bst_head + sizeof(bst_node_t));

#elif defined(_LIST2BST) && defined(__GNUC__)

	list_node_t * e;
	list_node_t * p_head = malloc( sizeof(* p_head) );
	if (p_head == NULL)
		return 0;

	e = p_head;
	e->p_next = NULL;

	int node_counter = 0;

	printf("size of list_node_t : %lu bytes\n", sizeof(list_node_t));
	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(list_node_t));

#endif


	clock_gettime(CLOCK_REALTIME, &start);

	/* read file stream from file, read one line at one time. */
	while ( fgets(line, sizeof(line), fp) ) {

		/* find the terminate byte, '\0'. */
		while (line[i] != '\0')
			i++;
		line[i - 1] = '\0';

		/* reset i for caculating the next line. */
		i = 0;

#if defined(_ORIG_STRUCT) || defined(_SMALL_STRUCT) && defined(__GNUC__)

		/* list_append the word of this line into a linked list. */
		e = list_append(line, e);

#elif defined(_BST) && defined(__GNUC__)

		/* insert the word of this line into a binary search tree. */
		bst_head = bst_insert_last_name(bst_head, line);

#elif defined(_LIST2BST) && defined(__GNUC__)

		/* list_append the word of this line into a linked list. */
		e = list_append(line, e);
		node_counter++;
#endif

	}

	/* After we read and save all contents, close file as soon as possible. */
	fclose(fp);

#if defined(_LIST2BST) && defined(__GNUC__)

	/* convert a linked list to binary serach tree. */
	e = p_head;
	bst_node_t * bst_head = list_to_bst(&e, node_counter);

#endif

	/* calculate the time of storing data. */
	clock_gettime(CLOCK_REALTIME, &end);
	cpu_time_store_data = diff_in_second(start, end);


	/* The target words we want to find. */
	char input[MAX_LAST_NAME_SIZE] = "zyxel";


#if defined(_ORIG_STRUCT) || defined(_SMALL_STRUCT) && defined(__GNUC__)

	e = p_head;
	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(list_node_t));

	clock_gettime(CLOCK_REALTIME, &start);
	list_node_t * tmp = list_find_name(input, e);
	if (tmp == NULL)
		printf("NULL\n");
	printf("The exception last name: %s\n", input);
	printf("The searched last name: %s\n", tmp->lastName);
	clock_gettime(CLOCK_REALTIME, &end);

#elif defined(_BST) && defined(__GNUC__)

	__builtin___clear_cache((char *) bst_head, (char *) bst_head + sizeof(bst_node_t));

	clock_gettime(CLOCK_REALTIME, &start);
	bst_node_t * tmp = bst_search(bst_head, input);
	printf("The exception last name: %s\n", input);
	printf("The searched last name: %s\n", tmp->entry->lastName);
	clock_gettime(CLOCK_REALTIME, &end);

#elif defined(_LIST2BST) && defined(__GNUC__)

	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(list_node_t));
	clock_gettime(CLOCK_REALTIME, &start);
	bst_node_t * tmp = bst_search(bst_head, input);
	if (tmp == NULL)
		printf("NULL\n");
	printf("The exception last name: %s\n", input);
	printf("The searched last name: %s\n", tmp->entry_node->lastName);
	clock_gettime(CLOCK_REALTIME, &end);

#endif


	/* compute the execution time */
	cpu_time_search = diff_in_second(start, end);



#if defined(_ORIG_STRUCT) || defined(_SMALL_STRUCT) && defined(__GNUC__)

	FILE *output = fopen(OUT_FILE, "a");
	fprintf(output, "list_append() list_find_name() %lf %lf\n", cpu_time_store_data, cpu_time_search);
	fclose(output);
	printf("execution time of list_append() : %lf sec\n", cpu_time_store_data);
	printf("execution time of list_find_name() : %lf sec\n", cpu_time_search);

	/* free the all linked list nodes. */
	list_delete_all(p_head);

#elif defined(_BST) && defined(__GNUC__)

	FILE *output = fopen(OUT_FILE, "a");
	fprintf(output, "bst_insert_last_name() bst_search() %lf %lf\n", cpu_time_store_data, cpu_time_search);
	fclose(output);
	printf("execution time of bst_insert_last_name() : %lf sec\n", cpu_time_store_data);
	printf("execution time of bst_search() : %lf sec\n", cpu_time_search);

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

#endif

	return 0;
}
