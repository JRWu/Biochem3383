/********************************************************************************
 * bsTree.c
 *
 * To be used as the BST data structure for group_gt1
 * Version 2.0
 *
 * Author: Jia Rong Wu
 * jwu424@uwo.ca
 *
 * This file is part of group_gt1.
 * group_gt1 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * group_gt1 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 * Please consider citing https://github.com/JRWu/Biochem3383 when implementing.
 *
 * bsTree.c represents a tree data structure
 * Can be used for efficient sorting or storage of any STRING/INT values.
 *******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "bsTree.h"

// Function Prototypes (private functions)
int intComparator(bsNode*, bsNode*);
void traverseWrite(bsTree sorted, FILE *fp);

/**
 * bsTree_init allocates necessary memory for a pointer to the first element in a tree
 * @return pointer to pointer of first node in tree
 */
bsTree bsTree_init(void)
{
    bsTree tree;
    tree = (bsTree) malloc(sizeof(bsNode));
    *tree = NULL;
    return tree;
}


/**
 * bsTree_insert takes a sequence and identifier, and inserts it into a tree
 * @s represents the sequence to be inserted
 * @id represents the identifier of the sequence
 * @return a pointer to the node that it was stored at
 */
bsNode* bsTree_insert(bsNode** node, char *identifier, char* sequence, char flag)
{
    if (*node == NULL)
    {
        (*node) = malloc(sizeof(bsNode));
        
        if (node == NULL)
        {
            printf("Out of memory: ");
            perror("Out of memory: ");
            exit (EXIT_FAILURE);
        }
        
        // Memcpys are used to allocate memory as per-needed basis
        // File sequences saved IFF they are unique
        
        (*node)->gcount = 1;
        (*node)->identifier = malloc(strlen(identifier)+1);
        memcpy((*node)->identifier,identifier,strlen(identifier));
        
        (*node)->seq = malloc(strlen(sequence)+1);
        memcpy((*node)->seq, sequence, strlen(sequence));
        
        (*node)->nId = setFirst((*node)->identifier);
        
        // Malloc guard
        if((*node)->identifier == NULL || (*node)->seq == NULL)
        {
            printf("Out of memory: ");
            perror("Out of Memory: ");
            exit (EXIT_FAILURE);
        }
    }
    else
    {
        int comparator = 0;

        // Check value of inserting sequence to old string
        comparator = strcmp((*node)->seq,sequence);
        
        if (comparator < 0)
        {
            bsTree_insert(&(*node)->right_child,identifier, sequence, flag);
            (*node)->right_child->parent = *node;
        }
        else if (comparator > 0)
        {
            bsTree_insert(&(*node)->left_child, identifier, sequence, flag);
            (*node)->left_child->parent = *node;
        }
        else // Sequence Already Exists
        {
            (*node)->gcount ++; // Increment occurence of sequence
            (*node)->nId = setNext(identifier, (*node)->nId); // Append identifier
        }
        return (*node);
    }
    return (*node);
}


/**
 * inOrder_traversal walks the tree from smallest to largest element
 * CAN APPEND CODE INSIDE TO CHANGE FUNCTIONALITY OF FUNCTION
 * takes O(n) runtime, n being the number of elements in the tree
 * @tree is the tree being traversed
 */
void inOrder_traversal(bsTree tree)
{
    if (*tree != NULL)
    {
        inOrder_traversal( &(*tree)->left_child );
        printf("Seq: %s\n", (*tree)->seq);
        printf("gcount: %d\n\n", (*tree)->gcount);
        inOrder_traversal( &(*tree)->right_child );
    }
}


/*
 * populateArary in-order traverses a tree and sets array indices accordingly
 * @sorted is the tree containing sequences with calculated frequencies
 * @arr is the array to be written to
 * @index is the current index of the array
 */
int populateArray(bsTree sorted, bsNode* arr[], int* index)
{
    
    if ( (*sorted) != NULL)
    {
        populateArray (&(*sorted)->left_child, arr, index);
        arr[*index] = (*sorted);
        (*index)++;
        populateArray (&(*sorted)->right_child, arr, index);
        
        return 1;
    }
    return 0;
}


/*
 * comparator is the comparator function for qsort
 * Follows the ordering and logic of the original 'group_gt1.pl'
 * @one is the pointer to element 1 being sorted
 * @two is the pointer to element 2 being sorted
 * @return greatest to smallest order
 */
int comparator(const void* one, const void* two)
{
    bsTree x = (bsNode**)one;
    bsTree y = (bsNode**)two;
    
    int x1 = (*x)->gcount;
    int x2 = (*y)->gcount;
    
    if (x1 > x2)
    {
        return -1;
    }
    else if (x1 < x2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 * arrWrite takes an array of pointers to nodes, and writes its
 * contents to a file
 * @arr[] is the array being read from
 * @count is the number of elements in the array
 */
void arrWrite(bsNode* arr[], int count, char* groups, char* readsInGroups)
{
    FILE* fp;
    
    fp = fopen(groups, "w");
    if (fp == NULL)
    {
        perror("ERROR: Unable to write to file");
        exit(EXIT_FAILURE);
    }
    else
    {
        iterateWrite(arr,fp, readsInGroups, count); // Iteratively write elements to file
    }
    fclose(fp); // Close file
}

/*
 * iterateWrite iteratively steps through an array
 * It handles freeing of allocated memory and writing to the file
 * @arr[] is the array being traversed
 * @fp is the pointer to the file being written into
 * @count is the count of the file
 */
void iterateWrite(bsNode* arr[], FILE *fp,char* readsInGroups, int count)
{
    FILE* fwp = fopen(readsInGroups, "w");

    int index; // Index of the array
    for (index = 0; index < count; index ++) // Iterate through all seq's
    {
        if ((*(arr[index])).gcount > K) // Add selection here for number
        {
            /*groups.txt*/
            fprintf(fp, ">lcl|%d|num|%d\t", index, (*(arr[index])).gcount);
            fprintf(fp, "%s\n", (*(arr[index])).seq);

            free( (*(arr[index])).seq);     // free memory for DNA
            /*groups.txt*/
            
            /*reads_in_groups.txt*/
            fprintf(fwp, "%d",index); // Represents $groups{$k}
            while ((*arr[index]).nId != NULL)
            {
                fprintf(fwp,"%s",(*arr[index]).nId->identifier); // $gname{k}
                free((*arr[index]).nId->identifier);    // free memory for IDENTIFIER
                
                (*arr[index]).nId = (*arr[index]).nId->next;
            }
            fprintf(fwp, "\n");
            /*reads_in_groups.txt*/
        }
        free((arr[index])); // Free the data pointed to in array
    }
    fclose(fwp);
}


/*
 * totalNodes recursively counts the number of nodes in a specified tree
 * @tree is the tree that's being counted
 * @return number of nodes in the tree (NOT INCLUDING LEAFS)
 */
int totalNodes(bsTree tree)
{
    int l = 0;
    int r = 0;
    
    if (*tree != NULL)
    {
        l = totalNodes( &(*tree)->left_child);
        r = totalNodes( &(*tree)->right_child);
        return (l + r + 1);
    }
    return 0;
}

/**
 * resetRoot resets the pointer to the root node after rebalance
 * @t is the tree being reset
 */
void resetRoot (bsTree t)
{
    if (t == NULL)
    {
        //   break;
    }
    else if ( (*t)-> parent == NULL)
    {
        // Do nothing, root is correct
    }
    else
    {
        while ( (*t)->parent != NULL) // Iterate up till the root
        {
            (*t) = (*t)->parent;
        }
    }
}

/*
 * setNext adds and identifier to the head of the "pseudo-linked-list"
 * Will create list in "reverse" order, reverse relative to original program
 * @identifier is the ID being added for a sequence
 * @head is the CURRENT head of the linked list
 * @return the head of the list
 */
nextId* setNext(char* identifier, nextId* head)
{
    nextId* next = malloc(sizeof(nextId)); // Create new node
       next->identifier = malloc(strlen(identifier)+1);
    memcpy(next->identifier,identifier,strlen(identifier));
    next->next = head;
    return next;
}


/*
 * setFirst will set the first identifier for a unique sequence
 * @identifier is the first identifier
 * @return a pointer to the first identifier
 */
nextId* setFirst(char* identifier)
{
    nextId* first = malloc(sizeof(nextId));
    first->identifier= identifier;
    first->next = malloc(sizeof(NULL));
    first->next = NULL;
    
    return first;
}