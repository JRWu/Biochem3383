# group_gt1_C
This program is an intermediate step in the processing of 16S rRNA genes. 
It generates a fasta file given an input of RNA-sequences and identifiers. 
Uses a binary tree-based algorithm to lexicographically sort and categorize RNA strings.
Sorts resulting array of pointers using quicksort by identifier count. 

group_gt1_C is written to improve the performance of the workflow_e.sh pipeline.

# Usage:
Replace group_gt1.pl with files from group_gt1_C. The inputs are exactly the same. 

'''
> make
> ./group_gt1 directory_in/input_name.txt directory_out/output_name.txt
'''

# Performance:
Given a 9.1GB rekeyed_tab.txt file with 14,246,039 RNA sequences:
1. Consumes approximately 1.85GB to the 2.55GB consumed by the Perl implementation. (~25% less memory consumption)
  1. This was profiled using the memory tool Valgrind on a Unix system.   
2. Runs in average 1m 33s vs 3m 57s across 10 pipeline instances. (>200% performance increase)
  1. This was benchmarked using the linux time function.
  2. Each instance was run on a cold boot to standardize loading time of the rekeyed_tab.txt file.

System specs:
* Late 2011 Macbook Pro.
* Intel Core i7-2760QM CPU @ 2.40 GHz. 
* 16 GB 1333MHz DDR3 RAM.
