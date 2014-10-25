/********************************************************************************
 * main.c
 *
 * To be used as: group_gt1.c
 * Version 1.0
 *
 * Author: Jia Rong Wu
 * jwu424@uwo.ca
 *
 * This software is Copyright 2014 Jia Rong Wu and is distrubuted under the terms
 * of the GNU General Public License.
 *
 * main.c takes input from a tabbed file and sorts sequences
 * writes a file with the output of sorted sequences by "k" frequency
 *******************************************************************************/

// TO ADD:
/**
 * Support for selecting "k" most frequent
 * Support for rebalancing tree
 * Support for comparisons if strcmp proves to be too unweildy
 */


#include <stdio.h>
#include "avlTree.h"

int main(int argc, const char * argv[]) {
    
    /*
     *MISC VALUES FOR TESTING
     */
    avlTree testTree;
    testTree = avlTree_init();
    
    char* sequence = "ATGC";
    char* identifier = "50:43";
    avlTree_insert(testTree, sequence, identifier);
    
    sequence = "ATGA";
    identifier = "51:43";
    avlTree_insert(testTree, sequence, identifier);

    sequence = "ATGG";
    identifier = "52:43";
    avlTree_insert(testTree, sequence, identifier);
    
    sequence = "ATGT";
    identifier = "54:43";
    avlTree_insert(testTree, sequence, identifier);
    
    
    sequence = "ATGT"; // Test for double insertion
    identifier = "54:43";
    avlTree_insert(testTree, sequence, identifier);
    
    
    
    
    /*
     *MISC VALUES FOR TESTING
     */
    
    inOrder_traversal(testTree); // Test for traversing tree

    printf("Hello, World!\n");
    return 0;
}








