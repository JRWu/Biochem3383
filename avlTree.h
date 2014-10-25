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
typedef struct node
{
    int count;
    char* seq;
    char* identifier;
    
    struct node* left_child;
    struct node* right_child;
    struct node* parent;
    
} node;


typedef node avlNode; // Represents an  avlNode
typedef avlNode** avlTree; // Represents a pointer to an avlTree

#endif /* defined(__group_gt1__avlTree__) */



// Function Prototypes
avlTree avlTree_init(void);
avlNode* avlTree_insert(avlTree, char* seq, char* identifier);
int node_count(avlTree, char*seq);