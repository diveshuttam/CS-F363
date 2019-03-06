all: utility lexer parser driver

driver:parser lexer utility
	gcc -g -c -Wall -Wpedantic -D NON_DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I parser/includes/ -I utils/ -I lexer/includes/ driver.c
	gcc driver.o populate_dfa.o populate_grammer.o token.o hash.o transition.o SeqList.o lexer.o twin_buffer.o parser.o Stack.o parse_table.o -o stage1exe

parser:utility parser/rules/firsts.txt parser/populate_grammer.c lexer/token.c parser/includes/ parser/parse_table.c lexer/token.c utility
	gcc -g -c -Wall -Wpedantic -D NON_DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I parser/includes/ -I utils/ -I lexer/includes/ ./parser/populate_grammer.c ./lexer/token.c ./parser/parse_table.c ./parser/parser.c

lexer:utility lexer/token.c lexer/includes/ lexer/transition.c lexer/lexer.c lexer/populate_dfa.c lexer/twin_buffer.c utils
	gcc -g -c -Wall -Wpedantic -D NON_DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I lexer/includes/ -I utils/ lexer/token.c lexer/transition.c lexer/lexer.c lexer/populate_dfa.c lexer/twin_buffer.c

hash.o: utils/hash.c utils/hash.h utils/SeqList.h
	gcc -g -c -Wall -Wpedantic -D NON_DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY utils/hash.c

StackTree.o: utils/SeqListTree.c utils/SeqListTree.h utils/StackTree.c
	gcc -g -c -Wall -Wpedantic -D NON_DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY utils/StackTree.c

SeqList.o: utils/SeqList.h utils/SeqList.c
	gcc -g -c -Wall -Wpedantic -D NON_DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY utils/SeqList.c

Stack.o:
	gcc -g -c -Wall -Wpedantic -D NON_DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY utils/Stack.c 

utility:hash.o SeqList.o Stack.o

clean:
	rm -rf *.o
