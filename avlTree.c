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
avlNode avlTree_insert_helper(avlNode *node, char* seq, char* identifier);


avlTree avlTree_init(void)
{
	avlTree tree;
	tree = (avlTree) malloc(sizeof(avlNode));
	*tree = NULL;
	return tree;
}

avlNode* avlTree_insert(avlTree tree, char* s, char* id)
{
	if (*tree == NULL)
	{
		(*tree) = (avlNode*) malloc (sizeof(avlNode));
		(*tree) -> count = 0;
		(*tree) -> seq = s;
		(*tree) -> identifier = id;
		return *tree;
	}
	else
	{
		int comparator = strcmp((*tree)->seq, s);
		if (comparator < 0) // 1 less than 2, insert right
		{
			(*tree)->right_child = avlTree_insert(&(*tree)->right_child,s,id);
			((*tree)->right_child)->parent = *tree;
		}
		else if (comparator > 0) // 1 greater than 2, insert left
		{
			(*tree)->left_child = avlTree_insert(&(*tree)->left_child,s,id);
			((*tree)->left_child)->parent = *tree;
		}
		else // Strings equivalent, increment counter
		{
			(*tree)->count ++;
			return (*tree);
		}
	}
	return *tree;
}



void inOrder_traversal(avlTree tree)
{
	if (*tree != NULL)
	{
		inOrder_traversal( &(*tree)->left_child );
		printf("Seq: %s\n", (*tree)->seq);
		inOrder_traversal( &(*tree)->right_child );
	}
}







