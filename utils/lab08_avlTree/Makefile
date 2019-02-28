build:	BinarySearchTree.o BinaryTree.o Stack.o SeqList.o driver.o TreeIO.o
	gcc -g BinarySearchTree.o BinaryTree.o includes/SeqList.o includes/Stack.o includes/TreeIO.o driver.o -o build

BinarySearchTree.o: BinarySearchTree.c BinarySearchTree.h BinaryTree.h includes/Stack.h TreeDefinition.h
	gcc -c -g BinarySearchTree.c 

BinaryTree.o: BinaryTree.c BinaryTree.h TreeDefinition.h
	gcc -c -g BinaryTree.c

driver.o: driver.c BinarySearchTree.h includes/TreeIO.h TreeDefinition.h
	gcc -c -g driver.c

Stack.o: includes/Stack.c  includes/Stack.h includes/SeqList.h
	gcc -c -g includes/Stack.c -o includes/Stack.o

SeqList.o: includes/SeqList.c includes/SeqList.h
	gcc -c -g -D __FREEELEMENT -D __COMPARE includes/SeqList.c -o includes/SeqList.o

TreeIO.o: includes/TreeIO.c includes/TreeIO.h
	gcc -c -g includes/TreeIO.c -o includes/TreeIO.o

clean:
	rm build *.o includes/*.o
