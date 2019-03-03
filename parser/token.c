#include "token.h"
#include "hash.h"

char **get_token_names(){
	char **arr_map;
	arr_map=malloc(sizeof(char*)*TYPES_OF_TOKEN);

	for (int i=0;i<TYPES_OF_TOKEN;i++){
		arr_map[i]=malloc(sizeof(char)*TYPES_OF_TOKEN);
	}

	strcpy(arr_map[TK_ASSIGNOP],"TK_ASSIGNOP");
	strcpy(arr_map[TK_COMMENT],"TK_COMMENT");
	strcpy(arr_map[TK_FIELDID],"TK_FIELDID");
	strcpy(arr_map[TK_ID],"TK_ID");
	strcpy(arr_map[TK_NUM],"TK_NUM");
	strcpy(arr_map[TK_RNUM],"TK_RNUM");
	strcpy(arr_map[TK_FUNID],"TK_FUNID");
	strcpy(arr_map[TK_RECORDID],"TK_RECORDID");
	strcpy(arr_map[TK_SQL],"TK_SQL");
	strcpy(arr_map[TK_SQR],"TK_SQR");
	strcpy(arr_map[TK_COMMA],"TK_COMMA");
	strcpy(arr_map[TK_SEM],"TK_SEM");
	strcpy(arr_map[TK_COLON],"TK_COLON");
	strcpy(arr_map[TK_DOT],"TK_DOT");
	strcpy(arr_map[TK_OP],"TK_OP");
	strcpy(arr_map[TK_CL],"TK_CL");
	strcpy(arr_map[TK_PLUS],"TK_PLUS");
	strcpy(arr_map[TK_MINUS],"TK_MINUS");
	strcpy(arr_map[TK_MUL],"TK_MUL");
	strcpy(arr_map[TK_DIV],"TK_DIV");
	strcpy(arr_map[TK_AND],"TK_AND");
	strcpy(arr_map[TK_OR],"TK_OR");
	strcpy(arr_map[TK_NOT],"TK_NOT");
	strcpy(arr_map[TK_LT],"TK_LT");
	strcpy(arr_map[TK_LE],"TK_LE");
	strcpy(arr_map[TK_EQ],"TK_EQ");
	strcpy(arr_map[TK_GT],"TK_GT");
	strcpy(arr_map[TK_GE],"TK_GE");
	strcpy(arr_map[TK_LE],"TK_LE");
	strcpy(arr_map[TK_NE],"TK_NE");
	strcpy(arr_map[TK_WITH],"TK_WITH");
	strcpy(arr_map[TK_PARAMETERS],"TK_PARAMETERS");
	strcpy(arr_map[TK_END],"TK_END");
	strcpy(arr_map[TK_WHILE],"TK_WHILE");
	strcpy(arr_map[TK_TYPE],"TK_TYPE");
	strcpy(arr_map[TK_MAIN],"TK_MAIN");
	strcpy(arr_map[TK_GLOBAL],"TK_GLOBAL");
	strcpy(arr_map[TK_PARAMETER],"TK_PARAMETER");
	strcpy(arr_map[TK_LIST],"TK_LIST");
	strcpy(arr_map[TK_INPUT],"TK_INPUT");
	strcpy(arr_map[TK_OUTPUT],"TK_OUTPUT");
	strcpy(arr_map[TK_INT],"TK_INT");
	strcpy(arr_map[TK_REAL],"TK_REAL");
	strcpy(arr_map[TK_ENDWHILE],"TK_ENDWHILE");
	strcpy(arr_map[TK_IF],"TK_IF");
	strcpy(arr_map[TK_THEN],"TK_THEN");
	strcpy(arr_map[TK_ENDIF],"TK_ENDIF");
	strcpy(arr_map[TK_READ],"TK_READ");
	strcpy(arr_map[TK_WRITE],"TK_WRITE");
	strcpy(arr_map[TK_RETURN],"TK_RETURN");
	strcpy(arr_map[TK_CALL],"TK_CALL");
	strcpy(arr_map[TK_RECORD],"TK_RECORD");
	strcpy(arr_map[TK_ENDRECORD],"TK_ENDRECORD");
	strcpy(arr_map[TK_ELSE],"TK_ELSE");
	return arr_map;
}

void destroy_token_name_table(char **arr){

	for (int i=0;i<TYPES_OF_TOKEN;i++){
		free(arr[i]);
	}
	free(arr);
}

hashTable *get_token_hasht(){
	hashTable* ht=newHashTable((int)(TYPES_OF_TOKEN*1.33),5,5381);
	insert("TK_ASSIGNOP",TK_ASSIGNOP,ht);
	insert("TK_COMMENT",TK_COMMENT,ht);
	insert("TK_FIELDID",TK_FIELDID,ht);
	insert("TK_ID",TK_ID,ht);
	insert("TK_NUM",TK_NUM,ht);
	insert("TK_RNUM",TK_RNUM,ht);
	insert("TK_FUNID",TK_FUNID,ht);
	insert("TK_RECORDID",TK_RECORDID,ht);
	insert("TK_SQL",TK_SQL,ht);
	insert("TK_SQR",TK_SQR,ht);
	insert("TK_COMMA",TK_COMMA,ht);
	insert("TK_SEM",TK_SEM,ht);
	insert("TK_COLON",TK_COLON,ht);
	insert("TK_DOT",TK_DOT,ht);
	insert("TK_OP",TK_OP,ht);
	insert("TK_CL",TK_CL,ht);
	insert("TK_PLUS",TK_PLUS,ht);
	insert("TK_MINUS",TK_MINUS,ht);
	insert("TK_MUL",TK_MUL,ht);
	insert("TK_DIV",TK_DIV,ht);
	insert("TK_AND",TK_AND,ht);
	insert("TK_OR",TK_OR,ht);
	insert("TK_NOT",TK_NOT,ht);
	insert("TK_LT",TK_LT,ht);
	insert("TK_LE",TK_LE,ht);
	insert("TK_EQ",TK_EQ,ht);
	insert("TK_GT",TK_GT,ht);
	insert("TK_GE",TK_GE,ht);
	insert("TK_LE",TK_LE,ht);
	insert("TK_NE",TK_NE,ht);
	insert("TK_WITH",TK_WITH,ht);
	insert("TK_PARAMETERS",TK_PARAMETERS,ht);
	insert("TK_END",TK_END,ht);
	insert("TK_WHILE",TK_WHILE,ht);
	insert("TK_TYPE",TK_TYPE,ht);
	insert("TK_MAIN",TK_MAIN,ht);
	insert("TK_GLOBAL",TK_GLOBAL,ht);
	insert("TK_PARAMETER",TK_PARAMETER,ht);
	insert("TK_LIST",TK_LIST,ht);
	insert("TK_INPUT",TK_INPUT,ht);
	insert("TK_OUTPUT",TK_OUTPUT,ht);
	insert("TK_INT",TK_INT,ht);
	insert("TK_REAL",TK_REAL,ht);
	insert("TK_ENDWHILE",TK_ENDWHILE,ht);
	insert("TK_IF",TK_IF,ht);
	insert("TK_THEN",TK_THEN,ht);
	insert("TK_ENDIF",TK_ENDIF,ht);
	insert("TK_READ",TK_READ,ht);
	insert("TK_WRITE",TK_WRITE,ht);
	insert("TK_RETURN",TK_RETURN,ht);
	insert("TK_CALL",TK_CALL,ht);
	insert("TK_RECORD",TK_RECORD,ht);
	insert("TK_ENDRECORD",TK_ENDRECORD,ht);
	insert("TK_ELSE",TK_ELSE,ht);
	return ht;
}

void destroy_token_hasht(hashTable *ht){
	//todo
	return;
}