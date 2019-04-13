CC = gcc
CCFLAGS = -g -Wall -Wpedantic
DEFINES = __DEBUG __MY_OWN_DATA_ELE __WITHOUT_KEY
AST_DIR = ./ast
LEXER_DIR = ./lexer
PARSER_DIR = ./parser
ST_DIR = ./symboltable
UTILS_DIR = ./utils
AST_CFILES_NAMES = ast.c semantic_functions_ast.c to_remove.c
LEXER_CFILES_NAMES = lexer.c populate_dfa.c token.c transition.c twin_buffer.c
PARSER_CFILES_NAMES = parser.c populate_grammer.c parse_table.c
ST_CFILES_NAMES = symbolTable.c semantic_functions_st.c
UTILS_CFILES_NAMES = hash.c SeqList.c Stack.c tree_to_json.c
MAIN_FILE = ./driver.c
VISUALIZE_FILE = ./graphics/visualize.c

INCLUDES = $(addprefix -I , $(addsuffix /includes, $(AST_DIR) $(LEXER_DIR) $(PARSER_DIR) $(ST_DIR) $(UTILS_DIR)))
DEFINE_ARGS = $(addprefix -D ,$(DEFINES))
GCC_CMD = $(CC) $(CCFLAGS) $(DEFINE_ARGS) $(INCLUDES)

AST_CFILES = $(addprefix $(AST_DIR)/,$(AST_CFILES_NAMES))
AST_OFILES = $(addsuffix .o, $(basename $(AST_CFILES)))
LEXER_CFILES = $(addprefix $(LEXER_DIR)/,$(LEXER_CFILES_NAMES))
LEXER_OFILES = $(addsuffix .o, $(basename $(LEXER_CFILES)))
PARSER_CFILES = $(addprefix $(PARSER_DIR)/,$(PARSER_CFILES_NAMES))
PARSER_OFILES = $(addsuffix .o, $(basename $(PARSER_CFILES)))
ST_CFILES = $(addprefix $(ST_DIR)/,$(ST_CFILES_NAMES))
ST_OFILES = $(addsuffix .o, $(basename $(ST_CFILES)))
UTILS_CFILES = $(addprefix $(UTILS_DIR)/,$(UTILS_CFILES_NAMES))
UTILS_OFILES = $(addsuffix .o, $(basename $(UTILS_CFILES)))

ALL_CFILES = $(AST_CFILES) $(LEXER_CFILES) $(PARSER_CFILES) $(ST_CFILES) $(UTILS_CFILES)
ALL_OFILES = $(addsuffix .o, $(basename $(ALL_CFILES)))

all: stage2exe visualize_exe

stage2exe: $(ALL_OFILES)
	$(GCC_CMD) $(ALL_OFILES) $(MAIN_FILE) -o stage2exe

visualize_exe: $(ALL_OFILES)
	$(GCC_CMD) $(ALL_OFILES) $(VISUALIZE_FILE) -o visualize_exe

%.o: %.c $(ALL_CFILES)
	$(GCC_CMD) -c -o $@ $<

clean:
	rm -I $(ALL_OFILES)