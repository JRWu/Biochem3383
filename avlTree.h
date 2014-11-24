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
#ifndef group_gt1_avlTree
#define group_gt1_avlTree
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>

#define MAX_SEQ_LENGTH 500
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) ) // Function to determine max of 2 integers
#endif

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
    int height; // Represents height of item in tree
    char* seq;
    char* identifier;
    char* nextGroupID; // Pointer to next identifier
    
    struct node* left_child;
    struct node* right_child;
    struct node* parent;
} node;

typedef node avlNode; // Represents an  avlNode
typedef avlNode** avlTree; // Represents a pointer to an avlTree

#endif /* defined group_gt1_avlTree*/


// Function Prototypes
avlTree avlTree_init(void);
source* params_init(char* arg1, char* arg2);
//avlNode* avlTree_insert(avlNode**, char* seq, char* identifier, char flag);
avlNode* avlTree_insert(avlNode**, avlNode*, char);
int node_count(avlTree, char*seq);
void inOrder_traversal(avlTree);
bool external(avlNode);
avlNode* triNodeRestructure(avlNode *grandchild,avlNode *child, avlNode *unbalanced);
void resetRoot (avlTree t);
int totalNodes(avlTree t);
void traverseInsert(avlTree unsorted,avlTree sorted);
void fileWrite(avlTree sorted);

int populateArray (avlTree sorted, avlNode* arr[], int* index);
int resetHeight(avlNode* node);
int comparator(const void* one, const void* two);
int reverseComparator(const void* one, const void* two);

void arrWrite(avlNode* arr[], int count, char* fileName);
void iterateWrite(avlNode* arr[], FILE *fp, int count);

