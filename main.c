/********************************************************************************
 * main.c
 *
 * To be used as part of: group_gt1.c
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
 *
 * main.c takes input from a tabbed file and sorts DNA sequences up to 500nt in
 * length. Utilizes a BST lexiographic categorizing with quicksort. 
 * writes a file with the output of sorted sequences by "k" frequency
 *
 * USAGE: ./group_gt1 NAME_OF_STUDY/tabbed_file.txt NAME_OF_STUDY\
 * ./group_g1 data_BARIATRIC_PLATE1/rekeyed_tab.txt BARIATRIC_PLATE1
 *******************************************************************************/


// /Users/jia_wu/Library/Developer/Xcode/DerivedData/group_gt1-aauoqiwecskiuvapyiyhjiaowbws/Build/Products/Debug

//   C:  ./group_gt1 data_BARIATRIC_PLATE1/formatted_reads.txt BARIATRIC_PLATE1
//PERL:  ./group_gt1_fileread.pl ../data_BARIATRIC_PLATE1/formatted_reads.txt BARIATRIC_PLATE1

// ^^ DEBUGGER INFO ^^

#include <stdio.h>
#include <stdlib.h>
#include "bsTree.h"

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
        char id_sequence[MAX_SEQ_LENGTH]=""; // DNA sequence l[3]
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
    
    free(dirIn);
    free(readsInGroups);
    free(groups);
    free(index);
    free(arr);
    exit(EXIT_SUCCESS);
}
