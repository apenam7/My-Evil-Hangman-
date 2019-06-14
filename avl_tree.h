#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>

#include "generic.h"
#include "my_string.h"
#include "generic_vector.h"

typedef void *TREE ;

typedef struct node Node ;

struct node {

    Node *left ;
    Node *right ;
    Node *parent ;
    MY_STRING key ;
	GENERIC_VECTOR data ;

} ;

typedef struct avl_tree {

	Node *root ;

} AVL_tree ;

TREE avl_tree_init_default( void ) ;

Status avl_tree_push( TREE hMy_tree, MY_STRING key, MY_STRING item ) ;

void avl_tree_destroy( TREE *phMy_tree ) ;

void avl_tree_destroy_node( Node *pNode ) ;

GENERIC_VECTOR avl_tree_get_largest_family( TREE hMy_tree, int print_val ) ;

GENERIC_VECTOR find_max_family( Node *root, int print_val ) ;

#endif
