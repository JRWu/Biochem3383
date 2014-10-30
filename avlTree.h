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
#include <stdbool.h>
#include <string.h>

#define MAX_SEQ_LENGTH 300
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) ) // Function to determine max of 2 integers
#endif

/**
 * node represents a node in the tree
 */
typedef struct node
{
    int count;
    int height; // Represents height of item in tree for rebalance property
    
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
bool external(avlNode);
avlNode* triNodeRestructure(avlNode *grandchild,avlNode *child, avlNode *unbalanced);
void resetRoot (avlTree t);
char* tokenizer(char* string);


// Deletion & Memory Free not supported because not necessary to sort