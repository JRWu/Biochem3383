//
//  avlTree.h
//  group_gt1
//
//  Created by Jia Wu on 2014-10-24.
//  Copyright (c) 2014 Jia Wu. All rights reserved.
//

#ifndef __group_gt1__avlTree__
#define __group_gt1__avlTree__
#include <stdio.h>


#define MAX_SEQ_LENGTH 300


// avlNode represents a node in the tree
typedef struct avlNode
{
    int count;
    char seq[MAX_SEQ_LENGTH];
    
    struct avlNode* left_child;
    struct avlNode* right_child;
    struct avlNode* parent;
    
} avlNode;


typedef avlNode* avlTree; // Represents a pointer to the first node in the tree

#endif /* defined(__group_gt1__avlTree__) */



// Function Prototypes
avlTree avlTree_init(void);
void avlTree_insert(avlTree, char* seq);
int node_count(avlTree, char*seq);

























