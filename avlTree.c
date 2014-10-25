//
//  avlTree.c
//  group_gt1
//
//  Created by Jia Wu on 2014-10-24.
//  Copyright (c) 2014 Jia Wu. All rights reserved.
//

#include <stdlib.h>
#include "avlTree.h"


/**
 *
 */
avlTree avlTree_init(void)
{
	avlTree tree;
	tree = (avlTree) malloc(sizeof(avlNode));
	tree = NULL;
	return tree;
}

void avlTree_insert(avlTree tree, char* seq, char* identifier)
{
	if (tree == NULL) //Case where root is empty
	{
		tree->count = 0;
		tree->left_child = malloc(sizeof(avlNode));
		tree->right_child = malloc(sizeof(avlNode));
	}
}
