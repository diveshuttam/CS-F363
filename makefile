CC = gcc
CCFLAGS = -g -c -Wall -Wpedantic
DEFINES = -D __DEBUG  -D __MY_OWN_DATA_ELE -D __WITHOUT_KEY
AST_DIR = ./ast
LEXER_DIR = ./lexer
PARSER_DIR = ./parser
ST_DIR = ./symboltable
UTILS_DIR = ./utils
INCLUDES = $(addprefix -I , $(addsuffix /includes, $(AST_DIR) $(LEXER_DIR) $(PARSER_DIR) $(ST_DIR) $(UTILS_DIR)))

GCC_CMD = $(CC) $(CCFLAGS) $(DEFINES) $(INCLUDES)

AST_CFILES_temp = ast.c semantic_functions_ast.c to_remove.c
AST_CFILES = $(addprefix $(AST_DIR)/,$(AST_CFILES_temp))
LEXER_CFILES_temp = lexer.c populate_dfa.c token.c transition.c twin_buffer.c
LEXER_CFILES = $(addprefix $(LEXER_DIR)/,$(LEXER_CFILES_temp))
PARSER_CFILES_temp = parser.c populate_grammer.c parse_table.c
PARSER_CFILES = $(addprefix $(PARSER_DIR)/,$(PARSER_CFILES_temp))
ST_CFILES_temp = symbolTable.c semantic_functions_st.c
ST_CFILES = $(addprefix $(ST_DIR)/,$(ST_CFILES_temp))
UTILS_CFILES_temp = hash.c SeqList.c Stack.c
UTILS_CFILES = $(addprefix $(UTILS_DIR)/,$(UTILS_CFILES_temp))

ALL_CFILES = $(AST_CFILES) $(LEXER_CFILES) $(PARSER_CFILES) $(ST_CFILES) $(UTILS_CFILES)
ALL_OFILES = $(addsuffix .o, $(basename $(ALL_CFILES)))
all:utils/hash.o

%.o: %.c $(ALL_CFILES)
	$(GCC_CMD) -c -o $@ $<

clean:
	rm -I $(ALL_OFILES)