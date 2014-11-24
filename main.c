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
 * Support for rebalancing tree to guarantee height balance
 * Support for comparisons if strcmp proves to be too unweildy
 *
 * frees any memory that this program has reserved
 */


#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"
#include <time.h>   // Double check the runtime of the function

int main(int argc, const char * argv[]) {
    
    char* directoryIn = (char*) argv[1];
    char* directoryOut = (char*) argv[2];
    
    // Handle arguments to program
    source* parameters = params_init(directoryIn, directoryOut);
    
    printf("In: %s\n",parameters->fileIn); // DEBUG
    printf("Out: %s\n",parameters->fileOut); // DEBUG
    
    
    
    free(parameters); // Done with parameters
    exit(EXIT_SUCCESS);

    
    /*DETERMINE RUNTIME*/
    clock_t begin, end;
    double time_spent;
    begin = clock();
    /*DETERMINE RUNTIME*/
    
    int inputs = 0;
    char buffer[2048];
    FILE *fp = fopen(parameters->fileIn, "r");
    // Split the string on delimiters here
    
    avlTree seq;          // Store original sequences
    seq = avlTree_init();
    int count = 0;
    
    if (fp == NULL)
    {
        perror("ERROR: Could not read from file.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        char a[100]="";
        char b[100]="";
        char c[100]="";
        char d[MAX_SEQ_LENGTH]="";
        char e[100]="";
        char f[100]="";
        char flag = 's';
        
        while ((fgets(buffer,1024, fp)) != NULL) // LOOP THROUGH FILE
        {
            avlNode* insert = malloc (sizeof(avlNode)); // AD
            
            // Parse individual Newlines
            while (sscanf(buffer, " %s %s %s %s %s %s ", a,b,c,d,e,f) == 6)
            {
                //                printf("%s\n\n", a); // Represents gid
                //                printf("%s\n\n", b);
                //                printf("%s\n\n", c);
                //                printf("%s\n\n", d); // Represents the value we want
                //                printf("%s\n\n", e);
                //                printf("%s\n\n", f);
                
                
                char* sequence = malloc(strlen(d)+1); // + 1 byte for null term
                char* identifier = malloc(strlen(a)+1); // + 1 byte for null term
                strncpy(sequence,d,strlen(d));   // Copy buffer to mem
                strncpy(identifier,a,strlen(a)); // Coppy id to mem
                
                /*
                 NOTE: ID needs to be kept till read into groups file
                 NOTE: SEQ can be discarded if another identical one is encountered
                 */
                insert->seq = sequence;          // Set seq
                insert->identifier = identifier; // Set id
                insert->gcount = 1;              // Assume 1st
                inputs ++;                       // Debug purposes
                break;                           // Inserted file info
            }
            
            avlTree_insert(seq, insert, flag);
            resetRoot(seq);
        }
        count =  totalNodes(seq);
        printf("Number of unique entries: %d\n", count);
    }
    fclose(fp);
    
    //    inOrder_traversal(seq);   // Debug info later
    
    int* index = malloc(sizeof(int)); // Used to set array indices
    *index = 0;
    avlNode* arr[count];
    
    populateArray(seq, arr, index);
    // Build input array here, pass reference into the program
    // During recurisve traversal increment the index and insertt he node
    // Call qsort on the array which stores the data
    
    
    // INSERT FLAG FOR ORDERING FILE HERE
    qsort((void*)&arr, count, sizeof(void*), &comparator); // sort array
    //qsort((void*)&arr, count, sizeof(void*), &reverseComparator);
    /*--DEBUGGING PURPOSES REMOVE LATER--*/
    
    arrWrite(arr, count, directoryOut);
    
    end = clock();
    time_spent =   ((double)(end-begin)*1000)/CLOCKS_PER_SEC;
    
    printf("\nNumber of entries: %d",inputs);
    printf("\nTime: %fms \n", time_spent);
    
    
    
    
    /*USE THIS TO OBTAIN RUNTIME DATA FOR LABBOOK*/
    //    FILE *output;
    //    output = fopen("rekeyed_tab_time.txt","a");
    //    fprintf(output, "Inputs: %d \n",inputs);
    //    fprintf(output, "Time: %fms \n", time_spent);
    //    fprintf(output, "\n\n");
    //    fclose(output);
    free(index);
    printf("\n\n--Successful Exit!--\n\n"); // DEBUG REMOVE LATER
    exit(EXIT_SUCCESS);
}
