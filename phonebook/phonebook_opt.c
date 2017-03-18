#include <stdlib.h>
#include <string.h>


#include "phonebook_opt.h"


/* original functions */
entry *findName(char lastName[], entry *pHead)
{

	while (pHead != NULL) 
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

bst_node_t *node_create()
{
	bst_node_t *bn;
        bn = malloc ( sizeof( *bst_node_t) );
	return bn;
}

bst_node_t *node_init(bst_node_t *node)
{
        node -> last_name = NULL;
	node -> left = NULL;
	node -> right = NULL;
	return node;
}

bst_node_t *node_input_last_name(bst_node_t *node, char * last_name)
{
        char * ret;
	ret = strcpy(node -> last_name, last_name);

        if (ret == NULL){
                perror("strcpy");
                return NULL;
        } else {
                return node;
        }
}

bst_node_t * node_insert_node_last_name(bst_node_t * root, char * last_name)
{
        if ( root = NULL ){
                // create, init, and input last_name into a new node
                bst_node_t * bn = node_create();

                // is this method work? without any problem?
                bn = node_init(bn);

                bn = node_input_last_name(bn, last_name);

                return bn;

        }else{
                // insert new node into tree, search the properly position from root

                int comare_ret = strcasecmp( root->last_name, last_name );

                if (compare_ret >= 0){
                        root->right == node_insert_node_last_name(root->right, last_name)

                }else{
                        root->left == node_insert_node_last_name(root->left, last_name)
                }

                return bn;
        }
}

bst_node_t *search_iteratively(bst_node_t *root, char * target_last_name)
{
	bst_node_t *current = root;

	while ( current != NULL){

		if ( strcasecmp( root->last_name, last_name) == 0 ){
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
