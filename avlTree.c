/********************************************************************************
 * avlTree.c
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
 * avlTree.c represents a tree data structure with guaranteed height (AVL)
 *******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "avlTree.h"


// Function Prototypes (private functions)
int computeHeight(avlNode node);
void reset_Height(avlTree tree);

/**
 * avlTree_init allocates necessary memory for a pointer to the first element in a tree
 * @return pointer to pointer of first node in tree
 */
avlTree avlTree_init(void)
{
    avlTree tree;
    tree = (avlTree) malloc(sizeof(avlNode));
    *tree = NULL;
    return tree;
}

/**
 * avlTree_insert takes a sequence and identifier, and inserts it into a tree
 * @s represents the sequence to be inserted
 * @id represents the identifier of the sequence
 * @return a pointer to the node that it was stored at
 */
avlNode* avlTree_insert(avlTree tree, char* s, char* id)
{
    if (*tree == NULL) // Unique sequence [BASE CASE]
    {
        (*tree) = (avlNode*) malloc (sizeof(avlNode));
        (*tree) -> count = 1;       // Increment to 1 because unique
        (*tree) -> seq = s;         // Set sequence
        (*tree) -> identifier = id; // Set id
        
        (*tree) -> height = 0;      // Height is zero by default
        
        /*/ NOT SURE IF NEEDED***************************
        if ( (*tree)->left_child != NULL)
        {
            (*tree)-> height = max((*tree)->height, (*tree)->left_child->height);
        }
        if ( (*tree)->right_child != NULL)
        {
            (*tree)-> height = max((*tree)->height, (*tree)->right_child->height);
        }
        // NOT SURE IF NEEDED****************************/
        
        return *tree;
    }
    else
    {
        int comparator = strcmp((*tree)->seq, s);
        if (comparator < 0) // New seq is larger, insert right
        {
            (*tree)->right_child = avlTree_insert(&(*tree)->right_child,s,id);
            ((*tree)->right_child)->parent = *tree; // Set parent of new node
            (*tree)->height = computeHeight(**tree); //ERROR
        }
        else if (comparator > 0) // New seq is less, insert left
        {
            (*tree)->left_child = avlTree_insert(&(*tree)->left_child,s,id);
            ((*tree)->left_child)->parent = *tree; // Set parent of new node
            (*tree)->height = computeHeight(**tree); //ERROR

        }
        else // Strings equivalent, increment counter for seq
        {
            (*tree)->count ++; // Increment seq counter
            return (*tree);
        }
    }
    return *tree;
}


/**
 * inOrder_traversal walks the tree from smallest to largest element
 * takes O(n) runtime, n being the number of elements in the tree
 * @tree is the tree being traversed
 */
void inOrder_traversal(avlTree tree)
{
    if (*tree != NULL)
    {
        inOrder_traversal( &(*tree)->left_child );
        printf("Height: %d\n", (*tree)->height);
        printf("Seq: %s\n", (*tree)->seq);
        printf("Count: %d\n\n", (*tree)->count);
        inOrder_traversal( &(*tree)->right_child );
    }
}


void reset_Height(avlTree tree)
{
    if ((*tree)->left_child == NULL || (*tree)->right_child == NULL) // Cannot do
    {
//        max(a, b)
    }
    (*tree)->height = (1+ max((*tree)->left_child->height, (*tree)->right_child->height    ));
    
}

bool external(avlNode node)
{
    if ((node).right_child == NULL && (node).left_child == NULL)
    {
        return true;
    }
    
    return false;
}



int computeHeight(avlNode node)
{
    int left = 0;
    int right = 0;
    // Need to handle null node checking here
    if (external(node))
    {
        return 0;
    }
    if (node.left_child != NULL)
    {
        left = computeHeight(*(node.left_child));
    }
    if (node.right_child!=NULL)
    {
        right = computeHeight(*(node.right_child));
    }

    return (1+ max(left,right));
}




