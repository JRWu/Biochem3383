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

#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"
#include <time.h>   // Double check the runtime of the function

int main(int argc, const char * argv[]) {
    FILE* fp;
    char* dir = malloc(MAX_SEQ_LENGTH*sizeof(char));
    char* directoryIn = (char*) argv[1];
    char* directoryOut = (char*) argv[2];
    
    // Handle arguments to program
    source* parameters = params_init(directoryIn, directoryOut);
    
    DIR* dIn; // Source Directory
    dIn = opendir(parameters->dirIn);
    if (dIn == NULL)
    {
        fp = fopen(parameters->fileIn, "r");
    }
    else
    {
        getcwd(dir,MAX_SEQ_LENGTH);
        chdir(parameters->dirIn); // Change directory to directory with file
        fp = fopen(parameters->fileIn, "r");
    }
    
    chdir(dir); // Go back to working directory
    
    int inputs = 0; // Count total inputs
    int count = 0;  // Count unique inputs
    bool reset = true;
    char buffer[MAX_BUFFER_LEN];
    
    avlTree seq;    // Data structure to store sequences
    seq = avlTree_init();
    
    if (fp == NULL)
    {
        perror("ERROR: Could not read from file");
        exit(EXIT_FAILURE);
    }
    else
    {
        char id[MAX_ID_LENGTH]="";          // Sequence identifier
        char misc[MAX_ID_LENGTH]="";
        char primer[MAX_ID_LENGTH]="";
        char id_sequence[MAX_SEQ_LENGTH]=""; // Sequence l[3]
        char flag = 's';
        
        avlNode* insert = malloc (sizeof(avlNode));
        
        // Read file into buffer for parsing individual lines
        while ((fgets(buffer,MAX_BUFFER_LEN, fp)) != NULL) // LOOP THROUGH FILE
        {

            // Parse individual lines from file
            // Accepts whitespace-separated lines or tabbed lines
            while (sscanf(buffer, " %s %s %s %s %s %s ", id,misc,primer,id_sequence,primer,misc) == 6)
            {
                char* sequence = malloc(strlen(id_sequence)+1); // + 1 byte for null term
                char* identifier = malloc(strlen(id)+1); // + 1 byte for null term
                
                // Malloc guard
                if (sequence == NULL || identifier == NULL)
                {
                    perror("Out of memory: ");
                    exit (EXIT_FAILURE);
                }
                
                strncpy(sequence,id_sequence,strlen(id_sequence));   // Copy buffer to mem
                strncpy(identifier,id,strlen(id)); // Copy id to mem
                
                /*
                 NOTE: ID needs to be kept till read into groups file
                 NOTE: SEQ can be discarded if another identical one is encountered
                 */
                insert->seq = sequence;          // Set seq
                insert->identifier = identifier; // Set id
                insert->gcount = 1;              // Assume 1st encounter
                inputs ++;                       // Debug purposes
                break;                           // Inserted file info
            }
            
            avlTree_insert(seq, insert, flag);  // Add sequence to data structure
            if (reset)
            {
                resetRoot(seq); // Can fix to remove later (better performance)
                reset = false; // Comparisons are cheaper than traversals
            }
        }
        
        count =  totalNodes(seq); // Count = number of UNIQUE entries
//        printf("Number of entries: %d\n",inputs); // DEBUG REMOVE LATER
//        printf("Number of unique entries: %d\n", count); // DEBUG REMOVE LATER
        free(insert);
    }
    fclose(fp);
    
    int* index = malloc(sizeof(int)); // Used to set array indices
    
    // Malloc guard
    if (index == NULL)
    {
        perror("Out of memory: ");
        exit (EXIT_FAILURE);
    }
    
    *index = 0;
    avlNode* arr[count];    // Create array of pointers to nodes
    populateArray(seq, arr, index);
    
    qsort((void*)&arr, count, sizeof(void*), &comparator); // Sort on gcount
    arrWrite(arr, count, parameters); // output 2 files in this function
    
    free(dir);
    free(parameters);
    free(index);
    exit(EXIT_SUCCESS);
}
