debug: *.c *.h build/
	gcc -D DEBUG -g -c *.c
	gcc *.o -o build/stage1exe

all:  *.c *.h build/
	gcc -g -c *.c
	gcc *.o -o  build/stage1exe

valgrind: all
	valgrind stage1exe

gprof: all
	echo "***Todo: profiling***"

test: valgrind gprof
