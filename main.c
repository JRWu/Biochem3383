/********************************************************************************
 * main.c
 *
 * To be used as: group_gt1.c
 * Version 1.6
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


// /Users/jia_wu/Library/Developer/Xcode/DerivedData/group_gt1-aauoqiwecskiuvapyiyhjiaowbws/Build/Products/Debug
// ./group_gt1 data_BARIATRIC_PLATE1/formatted_reads.txt BARIATRIC_PLATE1
// ^^ DEBUGGER INFO ^^

#include <stdio.h>
#include <stdlib.h>
#include "bsTree.h"
#include <time.h>   // Double check the runtime of the function

int main(int argc, const char * argv[]) {

    // Allocate memory for the directories being used
    int argInLen = (int) strlen(argv[1]);
    int argOutLen = (int) strlen(argv[2]);
    int dataLen = strlen("data_");
    char* dirIn = malloc(argInLen + dataLen + 1); // +1 for null term
    char* readsInGroups = malloc(argOutLen + dataLen + strlen("/reads_in_groups.txt") + 1);
    char* groups = malloc(argOutLen + dataLen + strlen("/groups.txt") + 1);
    
    strcat (dirIn, argv[1]);
    strcpy (readsInGroups, "data_");
    strcpy (groups, "data_");
    strcat (readsInGroups, argv[2]);
    strcat (groups, argv[2]);
    strcat (readsInGroups, "/reads_in_groups.txt");
    strcat (groups, "/groups.txt");
    
    // Ensures the directory names are correct and meaningful
    printf("\n********************\n");
    printf("dirIn: %s\n", dirIn);   // output data
    printf("readsInGroupsdir:  %s\n", readsInGroups);
    printf("groupsdir:  %s\n", groups);
    printf("\n********************\n");
    
    FILE* fp = fopen(dirIn, "r");
    
    int inputs = 0; // Count total inputs
    int count = 0;  // Count unique inputs
    char buffer[MAX_BUFFER_LEN];
    
    bsTree seq;    // Data structure to store sequences
    seq = bsTree_init();
    
    if (fp == NULL)
    {
        perror("ERROR: Could not read from file!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        char id[MAX_ID_LENGTH]="";          // Sequence identifier
        char misc[MAX_ID_LENGTH]="";
        char primer[MAX_ID_LENGTH]="";
        char id_sequence[MAX_SEQ_LENGTH]=""; // Sequence l[3]
        char flag = 's';
        
        // Read file into buffer for parsing individual lines
        while ((fgets(buffer,MAX_BUFFER_LEN, fp)) != NULL) // LOOP THROUGH FILE
        {

            // Parse individual lines from file
            // Accepts whitespace-separated lines or tabbed lines
            while (sscanf(buffer, " %s %s %s %s %s %s ", id,misc,primer,id_sequence,primer,misc) == 6)
            {
                bsTree_insert(seq, id, id_sequence,flag);
                inputs++;
                break;
            }
        }
        
        count =  totalNodes(seq); // Count = number of UNIQUE entries (recursive)
        printf("Number of entries: %d\n",inputs); // DEBUG REMOVE LATER
        printf("Number of unique entries: %d \n", count); // DEBUG REMOVE LATER
        
    }
    fclose(fp);
    
    int* index = malloc(sizeof(int)); // Used to set array indices
    
    // Malloc guard
    if (index == NULL)
    {
        printf("Out of memory: ");
        perror("Out of memory: ");
        exit (EXIT_FAILURE);
    }
    
    *index = 0; // Set index to 0 for populating the array to be sorted
    bsNode* arr = malloc(sizeof(bsNode*) * count);
    populateArray(seq, (void*)arr, index);
    
    qsort(arr, count, sizeof(void*), &comparator); // Sort on gcount
    arrWrite((void*)arr, count, groups, readsInGroups); // output 2 files in this function
    
    free(arr);
    free(dirIn);
    free(readsInGroups);
    free(groups);
    free(index);
    exit(EXIT_SUCCESS);
}
