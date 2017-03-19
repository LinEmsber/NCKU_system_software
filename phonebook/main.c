/* phone book */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <time.h>
#include <assert.h>

#include IMPL

#ifdef OPT
#define OUT_FILE "opt.txt"
#else
#define OUT_FILE "orig.txt"
#endif

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
	struct timespec diff;
	if (t2.tv_nsec-t1.tv_nsec < 0) {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
	} else {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
	}
	return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
	FILE *fp;
	int i = 0;
	char line[MAX_LAST_NAME_SIZE];
	struct timespec start, end;
	double cpu_time1, cpu_time2;

	/* open file */
	fp = fopen(DICT_FILE, "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}

#if defined(__LIST__) && defined(__GNUC__)
	/* build the start entry for linked list*/
	entry *pHead, *e;

	pHead = malloc( sizeof(*pHead) );
	if (pHead == NULL)
		return NULL;

	e = pHead;
	e->pNext = NULL;

	printf("size of entry : %lu bytes\n", sizeof(entry));
	__builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));

#elif defined(__BST__) && defined(__GNUC__)
	/* build a start node for binary search tree */
	bst_node_t * bst_head = node_create();
	__builtin___clear_cache((char *) bst_head, (char *) bst_head + sizeof(bst_node_t));
#endif


	clock_gettime(CLOCK_REALTIME, &start);

	// read file stream from file, read one line at one time.
	while (fgets(line, sizeof(line), fp)) {

		// find the terminate byte, '\0'
		while (line[i] != '\0')
			i++;
		line[i - 1] = '\0';

		// reset i for caculating the next line
		i = 0;

#if defined(__LIST__) && defined(__GNUC__)
		// append the word of this line into a linked list.
		e = append(line, e);

#elif defined(__BST__) && defined(__GNUC__)
		// insert the word of this line into a binary search tree.
		node_insert_node_last_name(bst_head, line);
#endif

	}

	clock_gettime(CLOCK_REALTIME, &end);
	cpu_time1 = diff_in_second(start, end);

	/* After we read all content and save those content into linked list,
	 * close file as soon as possible */
	fclose(fp);


	/* the givn last name to find */
	char input[MAX_LAST_NAME_SIZE] = "zyxel";

	// assert(findName(input, e) && "Did you implement findName() in " IMPL "?");
	// assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));

#if defined(__GNUC__) && defined(__GNUC__)
	e = pHead;
	__builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));

	clock_gettime(CLOCK_REALTIME, &start);
	findName(input, e);
	clock_gettime(CLOCK_REALTIME, &end);

#elif defined(__BST__) && defined(__GNUC__)
	__builtin___clear_cache((char *) bst_head, (char *) bst_head + sizeof(bst_node_t));

	clock_gettime(CLOCK_REALTIME, &start);
	search_iteratively(bst_head, input);
	clock_gettime(CLOCK_REALTIME, &end);

#endif


	/* compute the execution time */
	cpu_time2 = diff_in_second(start, end);

	FILE *output = fopen(OUT_FILE, "a");
	fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
	fclose(output);

	printf("execution time of append() : %lf sec\n", cpu_time1);
	printf("execution time of findName() : %lf sec\n", cpu_time2);

#if defined(__GNUC__) && defined(__GNUC__)
	// free all linked list nodes
	while((e = pHead)){
		pHead = pHead->pNext;
		free(e);
	}
	free(pHead);

#elif defined(__BST__) && defined(__GNUC__)
	//TODO: add node_free();
	
#endif


	return 0;
}
