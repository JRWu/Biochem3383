/********************************************************************************
 * bsTree.h
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
 * bsTree.h represents the typedefs and function prototypes that represent a
 * tree data structure.
 *******************************************************************************/
#ifndef group_gt1_bsTree
#define group_gt1_bsTree
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_SEQ_LENGTH 500  // Change this to accomodate sequences
#define MAX_ID_LENGTH 100   // Change this to accomodate identifiers
#define MAX_BUFFER_LEN 2048 // Buffer for reading in from file
#define K   1   // Change this to select "k" most frequent sequences


/*
 * source represents directory + filename
 */
typedef struct source
{
    char* dirIn;    // Input Directory
    char* dirOut;   // Output Directory
    char* fileIn;   // Input
    char* fileOut;  // Output
} source;

/**
 * nextId represents a link to the next identifier
 */
typedef struct nextId
{
    char* identifier;
    struct nextId* next;
}nextId;

/**
 * node represents a node in the tree
 */
typedef struct node
{
    int gcount; // Frequency of sequence
    char* seq;
    char* identifier;
	nextId* nId;
    struct node* left_child;
    struct node* right_child;
    struct node* parent;
} node;

typedef node bsNode; // Represents an  bsNode
typedef bsNode** bsTree; // Represents a pointer to an bsTree
#endif /* defined group_gt1_bsTree*/


// Function Prototypes
bsTree bsTree_init(void);
void free_tree(bsTree*);
bsNode* bsTree_insert(bsNode**, char*, char*, char);

void inOrder_traversal(bsTree);
int populateArray (bsTree sorted, bsNode* arr[], int* index);
int comparator(const void* one, const void* two);

void arrWrite(bsNode* arr[], int count, char* groups, char* readsInGroups);
void iterateWrite(bsNode* arr[], FILE *fp,char* readsInGroups, int count);

int totalNodes(bsTree t);
void resetRoot (bsTree t);

nextId* setNext(char* identifier, nextId* head);
nextId* setFirst(char* identifier);
