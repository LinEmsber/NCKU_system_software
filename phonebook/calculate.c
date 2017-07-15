#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i = 0;
	// TODO: check why is 50
	char append[50], find[50];

	FILE * fp;
	FILE * output = fopen("output.txt", "w");


	/* original */
	fp = fopen("phonebook_orig.txt", "r");
	if (!fp) {
		printf("ERROR opening input file phonebook_orig.txt\n");
		exit(0);
	}

	double orig_sum_a = 0.0, orig_sum_f = 0.0, orig_a = 0.0, orig_f = 0.0;
	for (i = 0; i < 100; i++) {
		if (feof(fp)) {
			printf("ERROR: You need 100 datum instead of %d\n", i);
			printf("run 'make run' longer to get enough information\n\n");
			exit(0);
		}
		fscanf(fp, "%s %s %lf %lf\n", append, find, &orig_sum_a, &orig_sum_f);
		orig_sum_a += orig_a;
		orig_sum_f += orig_f;
	}
	fclose(fp);

	/* small structure */
	fp = fopen("phonebook_small_struct.txt", "r");
	if (!fp) {
		// TODO: should we do double check ?
		fp = fopen("phonebook_orig.txt", "r");
		if (!fp) {
			printf("ERROR opening input file phonebook_small_struct.txt\n");
			exit(0);
		}
	}

	double small_struct_sum_a = 0.0, small_struct_sum_f = 0.0, small_struct_a = 0.0, small_struct_f = 0.0;
	for (i = 0; i < 100; i++) {
		if (feof(fp)) {
			printf("ERROR: You need 100 datum instead of %d\n", i);
			printf("run 'make run' longer to get enough information\n\n");
			exit(0);
		}
		fscanf(fp, "%s %s %lf %lf\n", append, find, &small_struct_sum_a, &small_struct_sum_f);
		small_struct_sum_a += small_struct_a;
		small_struct_sum_f += small_struct_f;
	}
	fclose(fp);

	/* list2bst */
	fp = fopen("phonebook_list2bst.txt", "r");
	if (!fp) {
		printf("ERROR opening input file phonebook_list2bst.txt\n");
		exit(0);
	}

	double list2bst_sum_a = 0.0, list2bst_sum_f = 0.0, list2bst_a = 0.0, list2bst_f = 0.0;
	for (i = 0; i < 100; i++) {
		if (feof(fp)) {
			printf("ERROR: You need 100 datum instead of %d\n", i);
			printf("run 'make run' longer to get enough information\n\n");
			exit(0);
		}
		fscanf(fp, "%s %s %lf %lf\n", append, find, &list2bst_sum_a, &list2bst_sum_f);
		list2bst_sum_a += list2bst_a;
		list2bst_sum_f += list2bst_f;
	}
	fclose(fp);

	/* hash */
	fp = fopen("phonebook_hash.txt", "r");
	if (!fp) {
		printf("ERROR opening input file phonebook_hash.txt\n");
		exit(0);
	}

	double hash_sum_a = 0.0, hash_sum_f = 0.0, hash_a = 0.0, hash_f = 0.0;
	for (i = 0; i < 100; i++) {
		if (feof(fp)) {
			printf("ERROR: You need 100 datum instead of %d\n", i);
			printf("run 'make run' longer to get enough information\n\n");
			exit(0);
		}
		fscanf(fp, "%s %s %lf %lf\n", append, find, &hash_sum_a, &hash_sum_f);
		hash_sum_a += hash_a;
		hash_sum_f += hash_f;
	}
	fclose(fp);

	fprintf(output, "append() %lf %lf %.8lf %.8lf\n",orig_sum_a/100.0, small_struct_sum_a/100.0, list2bst_sum_a/100.00, hash_sum_a/100.0);
	fprintf(output, "findName() %lf %lf %.8lf %.8lf\n", orig_sum_f/100.0, small_struct_sum_f/100.0, list2bst_sum_f/100.00, hash_sum_f/100.0);

	fclose(output);

	return 0;
}
