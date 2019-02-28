build: Stack.o driver.o SeqList.o StackIO.o
	gcc -g Stack.o driver.o ./includes/SeqList.o ./includes/StackIO.o -o build

Stack.o: Stack.c Stack.h ./includes/SeqList.h
	gcc -g -c Stack.c

SeqList.o: ./includes/SeqList.c ./includes/SeqList.h
	gcc -g -c -D __FREEELEMENT -D __COMPARE ./includes/SeqList.c -o ./includes/SeqList.o

StackIO.o: ./includes/StackIO.c ./includes/StackIO.h Stack.h
	gcc -g -c ./includes/StackIO.c -o ./includes/StackIO.o
