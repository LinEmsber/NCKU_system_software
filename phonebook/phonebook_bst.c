#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "phonebook_bst.h"

/* binary search tree */
bst_node_t * bst_create()
{
	bst_node_t * bst = malloc ( sizeof( *bst) );
	bst -> entry = (entry *) malloc( sizeof(entry) );
	bst -> left = NULL;
	bst -> right = NULL;

	return bst;
}

bst_node_t * bst_insert_last_name(bst_node_t * root, char * target_last_name)
{
        if ( root == NULL ){
		bst_node_t * root = bst_create();
		strcpy(root->entry->lastName, target_last_name);
		return root;
        }

        if ( strcasecmp( root->entry->lastName, target_last_name ) >= 0 ){
		root->right = bst_insert_last_name(root->right, target_last_name);
        }else{
		root->left = bst_insert_last_name(root->left, target_last_name);
	}

        return root;
}

bst_node_t * bst_search(bst_node_t *root, char * target_last_name)
{
	int ret;

	if (root == NULL)
		return root;

	ret = strcasecmp( root->entry->lastName, target_last_name);

	if ( ret == 0 ){
		return root;

	}else if ( ret > 0 ){
		return bst_search(root->right, target_last_name);

	}else if( ret < 0 ){
		return bst_search(root->left, target_last_name);

	}

	return NULL;
}


void bst_remove(bst_node_t * node)
{
	if (node != NULL){
		bst_remove(node -> left);
		bst_remove(node -> right);
		free(node);
	}
}
