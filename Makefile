all: utility lexer parser driver

driver:parser lexer utility
	gcc -g -c -D DEBUG -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I parser/includes/ -I utils/ -I lexer/includes/ driver.c
	gcc populate_dfa.o driver.o token.o hash.o transition.o SeqList.o lexer.o twin_buffer.o -o stage1exe

parser:utility parser/rules/firsts.txt parser/populate.c lexer/token.c parser/includes/ parser/parse_table.c lexer/token.c utility
	gcc -g -c -D DEBUG -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I parser/includes/ -I utils/ -I lexer/includes/ ./parser/populate.c ./lexer/token.c ./parser/parse_table.c ./parser/parseTree.c
	gcc populate.o Stack.o token.o SeqList.o hash.o parse_table.o parseTree.o -o parser/parser

lexer:utility lexer/token.c lexer/includes/ lexer/transition.c lexer/lexer.c lexer/populate_dfa.c lexer/twin_buffer.c utils
	gcc -g -c -D DEBUG -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I lexer/includes/ -I utils/ lexer/token.c lexer/transition.c lexer/lexer.c lexer/populate_dfa.c lexer/twin_buffer.c

hash.o: utils/hash.c utils/hash.h utils/SeqList.h
	gcc -g -c -D DEBUG -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY utils/hash.c

StackTree.o: utils/SeqListTree.c utils/SeqListTree.h utils/StackTree.c
	gcc -g -c -D DEBUG -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY utils/StackTree.c

SeqList.o: utils/SeqList.h utils/SeqList.c
	gcc -g -c -D DEBUG -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY utils/SeqList.c

Stack.o:
	gcc -g -c -D DEBUG -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY utils/Stack.c 

utility:hash.o SeqList.o Stack.o

clean:
	rm -rf *.o