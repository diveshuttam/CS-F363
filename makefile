all: clean utility lexer parser driver graphics

graphics: parser lexer utility
	gcc -g -c -Wall -Wpedantic -D __DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I parser/includes/ -I utils/includes/ -I lexer/includes/ -I ast/includes graphics/visualize.c
	gcc visualize.o populate_dfa.o populate_grammer.o token.o hash.o transition.o SeqList.o lexer.o twin_buffer.o parser.o Stack.o parse_table.o semantic_functions.o traversal.o semantic_actions.o -o visualize_exe

driver: parser lexer utility
	gcc -g -c -Wall -Wpedantic -D __DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I parser/includes/ -I utils/includes/ -I lexer/includes/ -I ast/includes driver.c
	gcc driver.o populate_dfa.o populate_grammer.o token.o hash.o transition.o SeqList.o lexer.o twin_buffer.o parser.o Stack.o parse_table.o semantic_functions.o traversal.o semantic_actions.o -o stage1exe

parser:utility parser/rules/firsts.txt parser/populate_grammer.c lexer/token.c parser/includes/ parser/parse_table.c lexer/token.c ast/semantic_functions.c ast/traversal.c ast/semantic_actions.c utility
	gcc -g -c -Wall -Wpedantic -D __DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I parser/includes/ -I utils/includes/ -I lexer/includes/ -I ast/includes ./parser/populate_grammer.c ./lexer/token.c ./parser/parse_table.c ./parser/parser.c ./ast/semantic_functions.c ./ast/traversal.c ./ast/semantic_actions.c

lexer:utility lexer/token.c lexer/includes/ lexer/transition.c lexer/lexer.c lexer/populate_dfa.c lexer/twin_buffer.c utils
	gcc -g -c -Wall -Wpedantic -D __DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I lexer/includes/ -I utils/includes/ lexer/token.c lexer/transition.c lexer/lexer.c lexer/populate_dfa.c lexer/twin_buffer.c

hash.o: utils/hash.c utils/includes/hash.h utils/includes/SeqList.h
	gcc -g -c -Wall -Wpedantic -D __DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I utils/includes/ utils/hash.c

StackTree.o: utils/SeqListTree.c utils/SeqListTree.h utils/StackTree.c
	gcc -g -c -Wall -Wpedantic -D __DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I utils/includes/ utils/StackTree.c

SeqList.o: utils/includes/SeqList.h utils/SeqList.c
	gcc -g -c -Wall -Wpedantic -D __DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I utils/includes/ utils/SeqList.c

Stack.o:
	gcc -g -c -Wall -Wpedantic -D __DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY -I utils/includes/ utils/Stack.c 

utility:hash.o SeqList.o Stack.o

clean:
	rm -rf *.o
