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
#include <unistd.h>


#define MAX_SEQ_LENGTH 500
#define MAX_ID_LENGTH 100
#define MAX_BUFFER_LEN 2048
#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) ) // Function to determine max of 2 integers
#endif

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
    int height; // Represents height of item in tree
    char* seq;
    char* identifier;
	nextId* nId;
	
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
void free_params(source* p);

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

void arrWrite(avlNode* arr[], int count, source* parameters);
void iterateWrite(avlNode* arr[], FILE *fp, int count);

nextId* setFirst(char* identifier);
nextId* setNext(char* identifier, nextId* head);