debug: *.c *.h build/
	gcc -D DEBUG -g -c *.c
	gcc *.o -o build/stage1exe

all:  *.c *.h build/
	gcc -g -c *.c
	gcc *.o -o build/stage1exe


