#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "phonebook_list2bst.h"


/* original functions */
list_node_t * list_append(char lastName[], list_node_t * e)
{
	e->p_next = (list_node_t *) malloc ( sizeof(list_node_t) );
	e = e->p_next;
	strcpy(e->lastName, lastName);
	e->p_next = NULL;

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

void list_delete_all(list_node_t * p_head)
{
	list_node_t * tmp;
	while(p_head){
		tmp = p_head;
		p_head = p_head->p_next;
		free(tmp);
	}
}


/* linked list to binary serach tree. */
bst_node_t * list_to_bst(list_node_t ** e, int len)
{
	if(len <= 0)
		return NULL;

	/* Recursively construct the left subtree. */
	bst_node_t * left = list_to_bst(e, len >> 1 );

	bst_node_t * root = (bst_node_t *) malloc( sizeof(bst_node_t) );

	root->entry_node = (list_node_t *) malloc( sizeof(list_node_t) );

	strcpy(root->entry_node->lastName, (*e)->lastName);

	root->left = left;

	*e = (*e)->p_next;

	/* Recursively construct the right subtree. */
	root->right = list_to_bst(e, len - (len >> 1) - 1);

	return root;
}

bst_node_t * bst_search(bst_node_t * root, char * target_last_name)
{
	if (root == NULL || (root->entry_node)->lastName == NULL)
		return NULL;

	int ret;
	ret = strcasecmp(target_last_name, (root->entry_node)->lastName);

	if ( ret == 0 ){
		return root;

	}else if ( ret > 0 ){
		return bst_search(root->right, target_last_name);

	}else if( ret < 0 ){
		return bst_search(root->left, target_last_name);

	}

	return NULL;
}


void bst_remove(bst_node_t * bn)
{
	if (bn != NULL){
		bst_remove(bn -> left);
		bst_remove(bn -> right);
		free(bn);
	}
}

void bst_node_dfs( bst_node_t * node, int depth )
{
        if( node->left )
                bst_node_dfs( node->left, depth + 2 );

        printf( "%s\n", node->entry_node->lastName );

        if( node->right )
                bst_node_dfs( node->right, depth + 2 );
}
