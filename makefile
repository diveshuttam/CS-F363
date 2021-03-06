CC = gcc
CCFLAGS = -g -Wall -Wpedantic
DEFINES = __NO_DEBUG __MY_OWN_DATA_ELE 

AST_DIR = ./ast
LEXER_DIR = ./lexer
PARSER_DIR = ./parser
ST_DIR = ./symboltable
UTILS_DIR = ./utils
TYPECHECK_DIR = ./typecheck
CODEGEN_DIR = ./codegen

AST_CFILES_NAMES = ast.c semantic_functions_ast.c to_remove.c
LEXER_CFILES_NAMES = lexer.c populate_dfa.c token.c transition.c twin_buffer.c
PARSER_CFILES_NAMES = parser.c populate_grammer.c parse_table.c tree_utils.c
ST_CFILES_NAMES = symbolTable.c st_utils.c
UTILS_CFILES_NAMES = hash.c SeqList.c Stack.c tree_to_json.c
TYPECHECK_CFILES_NAMES = typecheck.c typecheck_functions.c
CODEGEN_CFILES_NAMES = code_gen.c code_gen_semantic.c

MAIN_FILE = ./driver.c

INCLUDES = $(addprefix -I , $(addsuffix /includes, $(AST_DIR) $(LEXER_DIR) $(PARSER_DIR) $(ST_DIR) $(UTILS_DIR) $(TYPECHECK_DIR) $(CODEGEN_DIR) ) )
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
TYPECHECK_CFILES = $(addprefix $(TYPECHECK_DIR)/,$(TYPECHECK_CFILES_NAMES))
TYPECHECK_OFILES = $(addsuffix .o, $(basename $(TYPECHECK_CFILES)))
CODEGEN_CFILES = $(addprefix $(CODEGEN_DIR)/,$(CODEGEN_CFILES_NAMES))
CODEGEN_OFILES = $(addsuffix .o, $(basename $(CODEGEN_CFILES)))

ALL_CFILES = $(AST_CFILES) $(LEXER_CFILES) $(PARSER_CFILES) $(ST_CFILES) $(UTILS_CFILES) $(TYPECHECK_CFILES) $(CODEGEN_CFILES)
ALL_OFILES = $(addsuffix .o, $(basename $(ALL_CFILES)))

all: compiler

compiler: $(ALL_OFILES) $(MAIN_FILE)
	$(GCC_CMD) $(ALL_OFILES) $(MAIN_FILE) -o compiler

%.o: %.c $(ALL_CFILES)
	$(GCC_CMD) -c -o $@ $<

clean:
	rm  $(ALL_OFILES)