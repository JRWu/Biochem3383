/********************************************************************************
 * avlTree.h
 *
 * To be used as the data structure for group_gt1
 * Version 1.0
 *
 * Author: Jia Rong Wu
 * jwu424@uwo.ca
 *
 * This software is Copyright 2014 Jia Rong Wu and is distrubuted under the terms
 * of the GNU General Public License.
 *
 * avlTree.h represents the typedefs and function prototypes that represent a 
 * tree data structure with guaranteed height (AVL)
 *******************************************************************************/
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
void inOrder_traversal(avlTree);