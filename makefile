group_gt1: main.o avlTree.o
	cc -o group_gt1 main.o avlTree.o
main.o: main.c avlTree.h
	cc -c main.c avlTree.h
avlTree.o: avlTree.c avlTree.h
	cc -c avlTree.c avlTree.h
clean:
	rm -f sample *.o core *.gch

