#Makefile for group_gt1
#Copyright (c) 2014 Jia Rong Wu. All Rights Reserved.
#Usage under the GNU license
all: group_gt1
group_gt1: main.o avlTree.o
	gcc -Wall -o group_gt1 main.o avlTree.o
main.o: main.c avlTree.c avlTree.h
	gcc -Wall -c main.c 
avlTree.o: avlTree.c avlTree.h
	gcc -Wall -c avlTree.c avlTree.h
clean:
	rm -f sample *.o core *.gch
