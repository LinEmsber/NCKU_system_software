#include <stdlib.h>
#include <string.h>


#include "phonebook_opt.h"


/* original functions */
entry *findName(char lastName[], entry *pHead)
{

	while (pHead != NULL) {
		if (strcasecmp(lastName, pHead->lastName) == 0)
			return pHead;
		pHead = pHead->pNext;
	}

	return NULL;
}

entry *append(char lastName[], entry *e)
{
	e->pNext = (entry *) malloc(sizeof(entry));
	e = e->pNext;
	strcpy(e->lastName, lastName);
	e->pNext = NULL;

	return e;
}


/* binary search tree */
bst_node_t *search_iteratively(bst_node_t *root, char * target_last_name)
{
	bst_node_t *current = root;

	while ( current != NULL){

		if ( strcasecmp( root->last_name, last_name) ==0 ){
			return current;
			break;

		}else if ( strcasecmp( root->last_name, last_name) > 0 ){
			search_iteratively(root->right, target_last_name);

		}else if( strcasecmp( root->last_name, last_name) < 0 ){
			search_iteratively(root->left, target_last_name);

		}
	}

	return NULL;
}
