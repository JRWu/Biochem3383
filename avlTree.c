//
//  avlTree.c
//  group_gt1
//
//  Created by Jia Wu on 2014-10-24.
//  Copyright (c) 2014 Jia Wu. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "avlTree.h"


// Function Prototypes (private functions)
avlNode avlTree_insert_helper(avlNode node, char* seq, char* identifier);


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

void avlTree_insert(avlTree tree, avlNode node, char* seq, char* identifier)
{
	if (tree == NULL) //Case where root is empty
	{
		tree->count = 0;
		tree->left_child = malloc(sizeof(avlNode));
		tree->right_child = malloc(sizeof(avlNode));
	}
	else // Info exists at node
	{
		int comparator = strcmp(tree->seq, seq);
		if (comparator < 0) // 1 less than 2, insert right
		{
			*tree->right_child = avlTree_insert_helper(node, seq, identifier);
		}
		else if (comparator > 0) // 1 greater than 2, insert left
		{
			*tree->left_child = avlTree_insert_helper(node, seq, identifier);
		}
		else // Strings equivalent
		{
			
		}

	}
}

avlNode avlTree_insert_helper(avlNode node, char* seq, char* identifier)
{
	
	return node;
}













