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
 * Can be used for efficient sorting or storage of any STRING/INT values
 *******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "avlTree.h"

avlNode* root;


// Function Prototypes (private functions)
avlNode* tallerChild(avlNode* n);
int computeHeight(avlNode* node);
void MakeLeftChild (avlNode* a, avlNode* b);
void MakeRightChild (avlNode* a, avlNode* b);
bool balanced (avlNode * node);
int intComparator(avlNode*, avlNode*);
void traverseWrite(avlTree sorted, FILE *fp);

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

/*
 * params_init initializes a pointer to group_gt1's arguments
 * @arg1 is the input directory + filename
 * @arg2 is the output directory + filename
 * @return pointer with in/out directory and in/out filename
 */
source* params_init(char* arg1, char* arg2)
{
    if (arg1 == NULL) // No input argument
    {
        printf("ERROR: No source directory specified.\n");
        printf("Usage: ./group_gt1 'source_dir/filename.txt' 'destination_dir'\n");
        exit(EXIT_FAILURE);
    }
    if (arg2 == NULL) // No output argument
    {
        printf("ERROR: No destination directory specified.\n");
        printf("USAGE: ./group_gt1 'source_dir/filename.txt' 'destination_dir'\n");
        exit (EXIT_FAILURE);
    }
    source* params = malloc(sizeof(source));
    
    char argument1[strlen(arg1)]; // Hold copy- strtok consumes original
    char argument2[strlen(arg2)]; // Hold copy- strtok consumes original
    
    memcpy(argument1, arg1, strlen(arg1));
    memcpy(argument2, arg2, strlen(arg2));
    
    char* x = strtok(arg1,"/");
    while (x != NULL)
    {
        params->fileIn = x;
        x = strtok(NULL,"/");
    }
    char* y = strtok(arg2,"/");
    while (y != NULL)
    {
        params->fileOut = y;
        y = strtok(NULL,"/");
    }
    printf("In: %s\n",argument1); // Debug Info
    printf("Out: %s\n",argument2);// Debug Info
    
    
    
    return params;
}


/**
 * avlTree_insert takes a sequence and identifier, and inserts it into a tree
 * @s represents the sequence to be inserted
 * @id represents the identifier of the sequence
 * @return a pointer to the node that it was stored at
 */
avlNode* avlTree_insert(avlNode** node, avlNode* insert, char flag)
{
    if (*node == NULL)
    {
        (*node) = malloc (sizeof(avlNode));
        (*node)->gcount = insert->gcount;
        (*node)->identifier = insert->identifier;
        (*node)->seq = insert->seq;
        (*node)->height = 0;
    }
    else // Root is not null
    {
        int comparator;
        if (flag == 's')
        {
            comparator = strcmp((*node)->seq, insert->seq);
        }
        else
        {
            comparator = intComparator( (*node), insert);
        }
        avlNode* temp; //= malloc(sizeof(avlNode));
        
        if (comparator < 0)
        {
            avlTree_insert(&(*node)->right_child, insert, flag);
            temp = (*node)->right_child;
            (*node)->right_child->parent = *node;
            //            (*node)->height = computeHeight(*node);   // Bottleneck...
            //            (*node)->height = resetHeight(*node);
        }
        else if (comparator > 0)
        {
            avlTree_insert(&(*node)->left_child, insert, flag);
            temp = (*node)->left_child;
            (*node)->left_child->parent = *node;
            //            (*node)->height = computeHeight(*node);   // Bottleneck...
            //            (*node)->height = resetHeight(*node);
        }
        else
        {
            //printf("c: %d\n",(*node)->gcount);
            (*node)->gcount++;
            //free(insert->seq);
            //free(insert->identifier);
            return (*node);
        }
        
    }
    return (*node);
}


/**
 * triNodeRestructure takes an unbalanced node, its child, and its grandchild
 * compares the height differences of the nodes and restructures accordingly
 * Used to guarantee a tree with no height difference >1
 * @grandchild, @child, @unbalanced are nodes involved in restructuring
 * @return the pointer to a balanced node
 */
avlNode* triNodeRestructure(avlNode* grandchild,avlNode* child, avlNode* unbalanced)
{
    avlNode* x = x = grandchild;
    avlNode* y = y = child;
    avlNode* z = z = unbalanced;
    
    // CASES
    // ADD STRCMP HERE
    // NOTE: If strcmp is too unweildy must fix this here (BOTTLENECK)
    int zx = strcmp(z->seq, x->seq);
    int xy = strcmp(x->seq, y->seq);
    int zy = strcmp(z->seq, y->seq);
    
    // Might have to call malloc for these
    avlNode* a;
    avlNode* b;
    avlNode* c;
    
    if(zx <= 0 && xy <= 0) // If z <= x and x<=y
   	{
        a = z;
        b = x;
        c = y;
   	}
    if (zx >= 0 && xy >= 0) // If z>=x and x >=y
   	{
        a = y;
        b = x;
        c = z;
   	}
   	if (zy <= 0 && xy >=0) // If z<=y and y <=x
   	{
        a = z;
        b = y;
        c = x;
   	}
   	if(zy >=0 && xy <=0)//, or If z>=y and y >=x
   	{
        a = x;
        b = y;
        c = z;
   	}
   	
    
    if (z->parent == NULL ) // Reached root
    {
        // Set left and right of b as z's left and right
        // set left parent and right parent of z as b
        // Remove parent of b
        b->parent = NULL;
    }
    else // Replacing Z
    {
        if (z->parent->left_child == z)
        {
            MakeLeftChild(z->parent, b);
        }
        else
        {
            MakeRightChild(z->parent,b);
        }
    }
    
    if (b->left_child != x && b->left_child != y && b->left_child != z)
    {
        MakeRightChild(a, b->left_child);
    }
    
    if (b->right_child != x && b->right_child != y && b->right_child != z)
    {
        MakeLeftChild(c, b->right_child);
    }
    
    MakeLeftChild(b,a);
    MakeRightChild(b,c);
    
    return b;
}


/**
 * tallerChild takes a node and returns the taller of the 2 subtrees
 * If even heights are returned, it will return subtree based on parental origin
 * @n is the node being compared
 * @return higher subtree given a node
 */
avlNode* tallerChild(avlNode* n)
{
    int left = 0;
    int right = 0;
    
    if (n->left_child != NULL)
    {
        left = n->left_child->height;
    }
    if (n->right_child != NULL)
    {
        right = n->right_child->height;
    }
    
    if (left > right)
    {
        return n->left_child;
    }
    else if(left < right)
    {
        return n->right_child;
    }
    
    else
    {
        int comparator = strcmp (n->seq, n->parent->seq);
        if (comparator < 0) // < 0 if n->seq less than n->parent->seq
        {
            return n->left_child;
        }
        else
        {
            return n->right_child;
        }
    }
    
}



/**
 * MakeLeftChild takes a node, and makes it the left child of another
 * @a is the parent
 * @b becomes left child of a
 */
void MakeLeftChild (avlNode* a, avlNode* b)
{
    a->left_child = b;
    if (b!=NULL)
    {
        b->parent = a;
    }
}

/**
 * MakeRightChild takes a node, and makes it the right child of another
 * @a is the parent
 * @b becomes right child of a
 */
void MakeRightChild (avlNode* a, avlNode* b)
{
    a->right_child = b;
    if (b!= NULL)
    {
        b->parent = a;
    }
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
        printf("Height: %d\n", (*tree)->height);    // DEBUG, REMOVE LATER
        printf("Seq: %s\n", (*tree)->seq);          // DEBUG, REMOVE LATER
        printf("gcount: %d\n\n", (*tree)->gcount);    // DEBUG, REMOVE LATER
        inOrder_traversal( &(*tree)->right_child );
    }
}

void traverseInsert(avlTree unsorted,avlTree sorted)
{
    if (*unsorted != NULL)
    {
        traverseInsert(&(*unsorted)->left_child,sorted);
        
        // Every insertion coupled with a reset
        if ( (*unsorted)->gcount > 1)
        {
            avlTree_insert(sorted,*unsorted, 'i');
            resetRoot(sorted);
            //            printf("gcount: %d\n", (*unsorted)->gcount);
        }
        traverseInsert(&(*unsorted)->right_child,sorted);
        //        free(*unsorted); // DEBUG MIGHT HAVE TO REMOVE
    }
}




//void populateArray (avlNode* arr, avlTree sorted)
//{
//    int i = 0;
//    arr[i] = **sorted;
//}

/*
 // As you traverse the tree, increment the node
 int populateArray (avlTree sorted, avlNode arr[])
 {
 int index = 0; // Index to access the array
 
 if ( (*sorted) != NULL) // Haven't reached external
 {
 index = index + populateArray(  &(*sorted)->left_child, arr);
 
 // Do insertion into array
 arr[index] = *((*sorted));
 
 index = index + populateArray( &(*sorted)->right_child, arr);
 return index;
 }
 else
 {
 return - 1;
 }
 }//*/

int populateArray(avlTree sorted, avlNode* arr[], int* index)
{
    
    if ( (*sorted) != NULL)
    {
        populateArray (&(*sorted)->left_child, arr, index);
        //        printf("sizeofarr[]:%lu\n", sizeof(arr[*index])); // correct size
        //      printf("index: %d\n",*index);
        //    printf("count: %d\n",*(&(*sorted)->gcount));
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
    avlTree x = (avlNode**)one;
    avlTree y = (avlNode**)two;
    
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
 * reverseComparator is a comparator function for qsort
 * Is the opposite of the ordering and logic of the original 'group_gt1.pl'
 * @one is the pointer to element 1 being sorted
 * @two is the pointer to element 2 being sorted
 * @return smallest to greatest order
 */
int reverseComparator (const void* one, const void* two)
{
    avlTree x = (avlNode**) one;
    avlTree y = (avlNode**) two;
    
    int x1 = (*x)->gcount;
    int x2 = (*y)->gcount;
    
    if (x1 > x2)
    {
        return 1; // Element 1 is bigger
    }
    else if (x1 < x2)
    {
        return -1; // Element 1 is smaller
    }
    else
    {
        return 0; // Same (return 0 for stability issues)
    }
    
}


/*
 * arrWrite takes an array of pointers to nodes, and writes its
 * contents to a file
 * @arr[] is the array being read from
 * @count is the number of elements in the array
 */
void arrWrite(avlNode* arr[], int count, char* fileName)
{
    FILE *fp;
    fp = fopen ("groups.txt", "w");
    if (fp == NULL)
    {
        perror("ERROR: Unable to write to file.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        iterateWrite(arr,fp, count); // Iteratively write elements to file
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
void iterateWrite(avlNode* arr[], FILE *fp, int count)
{
    // MUST ADD HADNLING FOR ARRAY
    int index; // Index of the array
    for (index = 0; index < count; index ++)
    {
        if ((*(arr[index])).gcount > 1) // Add selection here for number
        {
            fprintf(fp, ">lcl|%d|num|%d|\t", index, (*(arr[index])).gcount);
            fprintf(fp, "%s\n", (*(arr[index])).seq);
        }
        // Write code to free the pointers to data and seq as well
        free((arr[index])); // Free the data pointed to in array
    }
}


/*
 * fileWrite invokes traverseWrite to write sorted information to a file
 * @sorted is the sorted tree data structure
 */
void fileWrite(avlTree sorted)
{
    FILE *fp;
    fp = fopen ("groups_from_c.txt","w");
    if (fp == NULL)
    {
        printf("Error, unable to write to file.\n");
    }
    else
    {
        /* DEFAULT FORMAT FOLLOW THIS*/
        //	print OUTG ">lcl|$groups{$k}|num|$gcount{$k}\t$k\n" if $gcount{$k} > 1;
        //    print OUTN "$groups{$k}$gname{$k}\n" if $gcount{$k} > 1;
        traverseWrite(sorted, fp);
    }
    fclose(fp);
}

/*
 * traverseWrite traverses a sorted tree to write its contents to a file
 * @sorted is the sorted tree
 * @fp is a pointer to the file being written to
 */
void traverseWrite(avlTree sorted, FILE *fp)
{
    if (*sorted != NULL)
    {
        traverseWrite(&(*sorted)->right_child, fp);
        fprintf(fp, ">lcl|xxx|num|%d|\n", (*sorted)->gcount);
        fprintf(fp, "%s\n", (*sorted)->seq);
        traverseWrite(&(*sorted)->left_child, fp);
        free(*sorted); // DEBUG MIGHT HAVE TO REMOVE
    }
}


/*
 * totalNodes recursively counts the number of nodes in a specified tree
 * @tree is the tree that's being counted
 * @return number of nodes in the tree (NOT INCLUDING LEAFS)
 */
int totalNodes(avlTree tree)
{
    int l = 0;
    int r = 0;
    
    if (*tree != NULL)
    {
        (*tree)->height = computeHeight(*tree); // DEBUG REMOVE LATER
        l = totalNodes( &(*tree)->left_child);
        r = totalNodes( &(*tree)->right_child);
        return (l + r + 1);
    }
    return 0;
}







/**
 * external determines if a given node is a leaf node
 * @node represents the node being checked
 * @return true if the node is external, false otherwise
 */
bool external(avlNode node)
{
    if ((node).right_child == NULL && (node).left_child == NULL)
    {
        return true;
    }
    
    return false;
}

int resetHeight(avlNode* node)
{
    int left = 0;
    int right = 0;
    if (node == NULL)
    {
        return 0;
    }
    if (node->left_child != NULL && node->seq != NULL)
    {
        left = (node->right_child)->height;
    }
    if (node -> right_child != NULL && node->seq != NULL)
    {
        right = (node->right_child)->height;
    }
    
    return max(left, right);
}

/**
 * computeHeight takes a given node and recursively calculates its height
 * @node is the node whose height is being calculated
 * @return the height of the node
 */
int computeHeight(avlNode * node)
{
    int left = 0;
    int right = 0;
    
    
    if (node->left_child != NULL)
    {
        left = computeHeight(node->left_child);
    }
    if (node -> right_child != NULL)
    {
        right = computeHeight(node->right_child);
    }
    
    return (1 + max(left, right));
}


/*
 * balanced takes a node and returns if its subtrees differ by 2
 * @node is the node being compared
 * @return true if the height of subtrees is not 1, false otherwise
 */
bool balanced (avlNode * node)
{
    int left = 0;
    int right = 0;
    
    if (node->left_child != NULL)
    {
        left = node->left_child->height;
    }
    if (node->right_child != NULL)
    {
        right = node->right_child->height;
    }
    
    if ( (abs(left - right)) > 1) // If height differs by > 1
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * resetRoot resets the pointer to the root node after rebalance
 * @t is the tree being reset
 */
void resetRoot (avlTree t)
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

/**
 * intComparator takes 2 numbers, compares them
 * @num1 is first number to be compared
 * @num2 is 2nd number to be compared
 * returns >0 if 1 > 2, <0 if 1 < 2, or 0 if equal
 */
int intComparator(avlNode* one, avlNode* two)
{
    if (one->gcount > two->gcount)
    {
        return 1;
    }
    else if (one->gcount < two->gcount)
    {
        return -1;
    }
    else
    {
        return 1; // Fix this because inserting is O(n) at some points
        //        return strcmp(one->seq, two->seq);
    }
    
}


nextId* setNext(char* identifier)
{
    nextId* next = malloc(sizeof(nextId)); // Set memory
    char* id = identifier;
    next->next = NULL;
    
    return next;
}




