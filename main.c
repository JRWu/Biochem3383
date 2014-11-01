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
    // Call file input here
    // Call tokenizer here
    
    // Insert values afterwards
//    avlTree_insert(seq, sequence, identifier);
//    Call reset root
    
    
    
    
//    char* tabs = "\t"; // To append to the end of identifiers
//    printf("TabTest: x,%sa  \n\n",tabs); // DEBUG PURPOSES ONLY
    
    
    
    // DEBUG PURPOSES TO MEASURE PERFORMANCE
    clock_t begin, end;
    double time_spent;
    begin = clock();
    // DEBUG PURPOSES TO MEASURE PERFORMANCE
    
    int inputs = 0;
    

    
    
    char buffer[2048];
    FILE *fp = fopen("rekeyed_tab.txt", "r");
    avlTree seq;          // Store original sequences
    seq = avlTree_init();
    
    if (fp == NULL)
    {
    }
    else
    {
        char a[300]="";
        char b[300]="";
        char c[300]="";
        char d[300]="";
        char e[300]="";
        char f[300]="";

        
        while ( (fgets(buffer,2048, fp)) != NULL) // LOOP THROUGH FILE
        {
            char* sequence = malloc(sizeof(d));
            char* identifier = malloc(sizeof(a));
            // LOOP THROUGH THE LINES
            while (sscanf(buffer, " %s  %s %s %s %s %s ", a,b,c,d,e,f) == 6)
            {
                
//                printf("%s\n\n", a); // Represents gid
//                printf("%s\n\n", b);
//                printf("%s\n\n", c);
//                printf("%s\n\n", d); // Represents the value we want
//                printf("%s\n\n", e);
//                printf("%s\n\n", f);
                strncpy(sequence,d,300);
                strncpy(identifier,a,300);

                inputs ++;
                break;
            }
            // D is not being reset, the act of sscanf in- will change it
            
            avlTree_insert(seq, sequence, identifier);
            resetRoot(seq);
            
//            free(sequence);
//            free (identifier);
            
        }
        int count =  totalNodes(seq);
        printf("Total nodes: %d", count);
        
    }
    fclose(fp);
    
    

    
    
    
    end = clock();
    time_spent =   ((double)(end-begin)*1000)/CLOCKS_PER_SEC;
    
    printf("\nInputs: %d",inputs);
    printf("\nTime: %fms \n", time_spent);
    
    
    FILE *output;
    output = fopen("rekeyed_tab_time.txt","a");
    fprintf(output, "Inputs: %d \n",inputs);
    fprintf(output, "Time: %fms \n", time_spent);
    fprintf(output, "\n\n");
    fclose(output);
    
    
    printf("\n\n--Successful Exit!--\n\n"); // DEBUG REMOVE LATER
    return 0;
}








