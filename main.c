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
 * May or May NOT support free() operations, as the operating system automatically
 * frees any memory that this program has reserved
 */


#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"
#include <time.h>   // Double check the runtime of the function

int main(int argc, const char * argv[]) {
    
//    avlTree seq;          // Store original sequences
//    seq = avlTree_init();
    
    // Call file input here
    
    // Call tokenizer here
    
    
    // Insert values afterwards
    char* sequence;
    char* identifier;
//    avlTree_insert(seq, sequence, identifier);
//    Call reset root
    
    
    
    
    char* tabs = "\t"; // To append to the end of identifiers
    printf("TabTest: x,%sa  \n\n",tabs); // DEBUG PURPOSES ONLY
    
    
    
    // DEBUG PURPOSES TO MEASURE PERFORMANCE
    clock_t begin, end;
    double time_spent;
    begin = clock();
    // DEBUG PURPOSES TO MEASURE PERFORMANCE
    
    
    
    
    // Read in file
    FILE *fp; // Pointer to File
    char c;
    fp = fopen ("input.txt", "r");
    
    if (fp == NULL)
    {
        printf ("Error: Unable to read from file. \n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("File Contents:\n\n");
        int i = 0;
        while ( (c = fgetc(fp)) != EOF) // Iterate through whole file
        {
            if (c == '\t')
            {
                i++;
            }
            
            if (i == 0) // Equivalent to the ID
            {
                printf("%c",c);
            }
            
            if (i == 3) // Equivalent to split /\t/ (line 27)
            {
                // Add code to put into sequence
                printf("%c",c);
            }
            
            
            
            if (c == '\n')
            {
                printf("\n# tabs before newline = %d\n",i);
                i = 0;
            }
        }
    }
    fclose(fp);
    
    
    
    end = clock();
    time_spent =   (double)(end-begin);
    
    printf("\nTime: %fms \n", time_spent);
    
    
    
    
    
    printf("\n\n--Successful Exit!--\n\n"); // DEBUG REMOVE LATER
    return 0;
}








