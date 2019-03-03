populate:rules/firsts.txt populate.c ../utils/hash.c ../utils/SeqList.c token.c includes/
	gcc -g -c -I includes/ -I ../utils/ populate.c token.c
	gcc -I includes/ -I ../utils/ populate.o token.o ../utils/SeqList.o ../utils/hash.o -o populate