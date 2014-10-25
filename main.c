//
//  main.c
//  group_gt1
//
//  Created by Jia Wu on 2014-10-23.
//  Copyright (c) 2014 Jia Wu. All rights reserved.
//

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
    
    /*
     *MISC VALUES FOR TESTING
     */
    
    printf("Hello, World!\n");
    return 0;
}








