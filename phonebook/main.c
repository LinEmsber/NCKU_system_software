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
#define OUT_FILE "orig.txt"
#elif _SMALL_STRUCT
#define OUT_FILE "small_struct.txt"
#elif _BST
#define OUT_FILE "bst.txt"
#endif

#define DICT_FILE "./dictionary/words__.txt"


int main(int argc, char *argv[])
{
	int i = 0;
	FILE * fp;
	char line[MAX_LAST_NAME_SIZE];
	struct timespec start, end;
	double cpu_time1, cpu_time2;

	/* open file */
	fp = fopen(DICT_FILE, "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}

	/* build the start entry for linked list or binary search tree. */

#if defined(_LIST) && defined(__GNUC__)

	entry * e;
	entry * p_head = malloc( sizeof(* p_head) );
	if (p_head == NULL)
		return 0;

	e = p_head;
	e->p_next = NULL;

	printf("size of entry : %lu bytes\n", sizeof(entry));
	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(entry));

#elif defined(_BST) && defined(__GNUC__)

	// bst_node_t * bst_head = node_create();
	bst_node_t * bst_head = NULL;
	__builtin___clear_cache((char *) bst_head, (char *) bst_head + sizeof(bst_node_t));

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

#if defined(_LIST) && defined(__GNUC__)

		/* list_append the word of this line into a linked list. */
		e = list_append(line, e);

#elif defined(_BST) && defined(__GNUC__)

		/* insert the word of this line into a binary search tree. */
		bst_head = node_insert_node_last_name(bst_head, line);

#endif

	}

	clock_gettime(CLOCK_REALTIME, &end);
	cpu_time1 = diff_in_second(start, end);

	/* After we read all content and save those content into linked list,
	 * close file as soon as possible */
	fclose(fp);


	/* the givn last name to find */
	char input[MAX_LAST_NAME_SIZE] = "zyxel";

	/* check the implementation. */
	// assert(list_find_name(input, e) && "Did you implement list_find_name() in " IMPL "?");
	// assert(0 == strcmp(list_find_name(input, e)->lastName, "zyxel"));

#if defined(_LIST) && defined(__GNUC__)

	e = p_head;
	__builtin___clear_cache((char *) p_head, (char *) p_head + sizeof(entry));

	clock_gettime(CLOCK_REALTIME, &start);
	list_find_name(input, e);
	clock_gettime(CLOCK_REALTIME, &end);

#elif defined(_BST) && defined(__GNUC__)

	__builtin___clear_cache((char *) bst_head, (char *) bst_head + sizeof(bst_node_t));

	bst_node_t * tmp;

	clock_gettime(CLOCK_REALTIME, &start);
	tmp = bst_search(bst_head, input);
	printf("The exception last name: %s\n", input);
	printf("The searched last name: %s\n", tmp->entry->lastName);
	clock_gettime(CLOCK_REALTIME, &end);


#endif


	/* compute the execution time */
	cpu_time2 = diff_in_second(start, end);



#if defined(_LIST) && defined(__GNUC__)

	FILE *output = fopen(OUT_FILE, "a");
	fprintf(output, "list_append() list_find_name() %lf %lf\n", cpu_time1, cpu_time2);
	fclose(output);
	printf("execution time of list_append() : %lf sec\n", cpu_time1);
	printf("execution time of list_find_name() : %lf sec\n", cpu_time2);

	/* free the all linked list nodes. */
	list_delete_all(p_head);

#elif defined(_BST) && defined(__GNUC__)

	FILE *output = fopen(OUT_FILE, "a");
	fprintf(output, "node_insert_node_last_name() bst_search() %lf %lf\n", cpu_time1, cpu_time2);
	fclose(output);
	printf("execution time of node_insert_node_last_name() : %lf sec\n", cpu_time1);
	printf("execution time of bst_search() : %lf sec\n", cpu_time2);
	//TODO: add node_free();

#endif


	return 0;
}
