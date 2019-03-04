all: utility lexer parser

parser:utility parser/rules/firsts.txt parser/populate.c lexer/token.c parser/includes/
	gcc -g -c -I parser/includes/ -I utils/ -I lexer/includes/ ./parser/populate.c ./lexer/token.c ./parser/parse_table.c
	gcc populate.o token.o SeqList.o hash.o parse_table.o -o parser/parser

lexer:utility lexer/driver.c lexer/token.c lexer/includes/ lexer/transition.c lexer/lexer.c lexer/populate.c utils
	gcc -g -c -I lexer/includes/ -I utils/ lexer/driver.c lexer/token.c lexer/transition.c lexer/lexer.c lexer/populate.c
	gcc populate.o driver.o token.o hash.o transition.o SeqList.o lexer.o -o ./lexer/lexer

hash.o: utils/hash.c utils/hash.h utils/SeqList.h
	gcc -g -c utils/hash.c

SeqList.o: utils/SeqList.h utils/SeqList.c
	gcc -g -c utils/SeqList.c

utility:hash.o SeqList.o


