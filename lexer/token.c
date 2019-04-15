#include "token.h"
#include "hash.h"

char **get_token_names(){
	char **arr_map=malloc(sizeof(char*)*(TYPES_OF_TOKEN+5));

	for (int i=0;i<TYPES_OF_TOKEN;i++){
		arr_map[i]=NULL;
	}

	arr_map[TK_ASSIGNOP] = malloc(sizeof(char*)*(strlen("TK_ASSIGNOP")+1));
	strcpy(arr_map[TK_ASSIGNOP],"TK_ASSIGNOP");
	arr_map[TK_COMMENT]=malloc(sizeof(char*)*(strlen("TK_COMMENT")+1));
	strcpy(arr_map[TK_COMMENT],"TK_COMMENT");
	arr_map[TK_FIELDID]=malloc(sizeof(char*)*(strlen("TK_FIELDID")+1));
	strcpy(arr_map[TK_FIELDID],"TK_FIELDID");
	arr_map[TK_ID]=malloc(sizeof(char*)*(strlen("TK_ID")+1));
	strcpy(arr_map[TK_ID],"TK_ID");
	arr_map[TK_NUM]=malloc(sizeof(char*)*(strlen("TK_NUM")+1));
	strcpy(arr_map[TK_NUM],"TK_NUM");
	arr_map[TK_RNUM]=malloc(sizeof(char*)*(strlen("TK_RNUM")+1));
	strcpy(arr_map[TK_RNUM],"TK_RNUM");
	arr_map[TK_FUNID]=malloc(sizeof(char*)*(strlen("TK_FUNID")+1));
	strcpy(arr_map[TK_FUNID],"TK_FUNID");
	arr_map[TK_RECORDID]=malloc(sizeof(char*)*(strlen("TK_RECORDID")+1));
	strcpy(arr_map[TK_RECORDID],"TK_RECORDID");
	arr_map[TK_SQL]=malloc(sizeof(char*)*(strlen("TK_SQL")+1));
	strcpy(arr_map[TK_SQL],"TK_SQL");
	arr_map[TK_SQR]=malloc(sizeof(char*)*(strlen("TK_SQR")+1));
	strcpy(arr_map[TK_SQR],"TK_SQR");
	arr_map[TK_COMMA]=malloc(sizeof(char*)*(strlen("TK_COMMA")+1));
	strcpy(arr_map[TK_COMMA],"TK_COMMA");
	arr_map[TK_SEM]=malloc(sizeof(char*)*(strlen("TK_SEM")+1));
	strcpy(arr_map[TK_SEM],"TK_SEM");
	arr_map[TK_COLON]=malloc(sizeof(char*)*(strlen("TK_COLON")+1));
	strcpy(arr_map[TK_COLON],"TK_COLON");
	arr_map[TK_DOT]=malloc(sizeof(char*)*(strlen("TK_DOT")+1));
	strcpy(arr_map[TK_DOT],"TK_DOT");
	arr_map[TK_OP]=malloc(sizeof(char*)*(strlen("TK_OP")+1));
	strcpy(arr_map[TK_OP],"TK_OP");
	arr_map[TK_CL]=malloc(sizeof(char*)*(strlen("TK_CL")+1));
	strcpy(arr_map[TK_CL],"TK_CL");
	arr_map[TK_PLUS]=malloc(sizeof(char*)*(strlen("TK_PLUS")+1));
	strcpy(arr_map[TK_PLUS],"TK_PLUS");
	arr_map[TK_MINUS]=malloc(sizeof(char*)*(strlen("TK_MINUS")+1));
	strcpy(arr_map[TK_MINUS],"TK_MINUS");
	arr_map[TK_MUL]=malloc(sizeof(char*)*(strlen("TK_MUL")+1));
	strcpy(arr_map[TK_MUL],"TK_MUL");
	arr_map[TK_DIV]=malloc(sizeof(char*)*(strlen("TK_DIV")+1));
	strcpy(arr_map[TK_DIV],"TK_DIV");
	arr_map[TK_AND]=malloc(sizeof(char*)*(strlen("TK_AND")+1));
	strcpy(arr_map[TK_AND],"TK_AND");
	arr_map[TK_OR]=malloc(sizeof(char*)*(strlen("TK_OR")+1));
	strcpy(arr_map[TK_OR],"TK_OR");
	arr_map[TK_NOT]=malloc(sizeof(char*)*(strlen("TK_NOT")+1));
	strcpy(arr_map[TK_NOT],"TK_NOT");
	arr_map[TK_LT]=malloc(sizeof(char*)*(strlen("TK_LT")+1));
	strcpy(arr_map[TK_LT],"TK_LT");
	arr_map[TK_LE]=malloc(sizeof(char*)*(strlen("TK_LE")+1));
	strcpy(arr_map[TK_LE],"TK_LE");
	arr_map[TK_EQ]=malloc(sizeof(char*)*(strlen("TK_EQ")+1));
	strcpy(arr_map[TK_EQ],"TK_EQ");
	arr_map[TK_GT]=malloc(sizeof(char*)*(strlen("TK_GT")+1));
	strcpy(arr_map[TK_GT],"TK_GT");
	arr_map[TK_GE]=malloc(sizeof(char*)*(strlen("TK_GE")+1));
	strcpy(arr_map[TK_GE],"TK_GE");
	arr_map[TK_LE]=malloc(sizeof(char*)*(strlen("TK_LE")+1));
	strcpy(arr_map[TK_LE],"TK_LE");
	arr_map[TK_NE]=malloc(sizeof(char*)*(strlen("TK_NE")+1));
	strcpy(arr_map[TK_NE],"TK_NE");
	arr_map[TK_WITH]=malloc(sizeof(char*)*(strlen("TK_WITH")+1));
	strcpy(arr_map[TK_WITH],"TK_WITH");
	arr_map[TK_PARAMETERS]=malloc(sizeof(char*)*(strlen("TK_PARAMETERS")+1));
	strcpy(arr_map[TK_PARAMETERS],"TK_PARAMETERS");
	arr_map[TK_END]=malloc(sizeof(char*)*(strlen("TK_END")+1));
	strcpy(arr_map[TK_END],"TK_END");
	arr_map[TK_WHILE]=malloc(sizeof(char*)*(strlen("TK_WHILE")+1));
	strcpy(arr_map[TK_WHILE],"TK_WHILE");
	arr_map[TK_TYPE]=malloc(sizeof(char*)*(strlen("TK_TYPE")+1));
	strcpy(arr_map[TK_TYPE],"TK_TYPE");
	arr_map[TK_MAIN]=malloc(sizeof(char*)*(strlen("TK_MAIN")+1));
	strcpy(arr_map[TK_MAIN],"TK_MAIN");
	arr_map[TK_GLOBAL]=malloc(sizeof(char*)*(strlen("TK_GLOBAL")+1));
	strcpy(arr_map[TK_GLOBAL],"TK_GLOBAL");
	arr_map[TK_PARAMETER]=malloc(sizeof(char*)*(strlen("TK_PARAMETER")+1));
	strcpy(arr_map[TK_PARAMETER],"TK_PARAMETER");
	arr_map[TK_LIST]=malloc(sizeof(char*)*(strlen("TK_LIST")+1));
	strcpy(arr_map[TK_LIST],"TK_LIST");
	arr_map[TK_INPUT]=malloc(sizeof(char*)*(strlen("TK_INPUT")+1));
	strcpy(arr_map[TK_INPUT],"TK_INPUT");
	arr_map[TK_OUTPUT]=malloc(sizeof(char*)*(strlen("TK_OUTPUT")+1));
	strcpy(arr_map[TK_OUTPUT],"TK_OUTPUT");
	arr_map[TK_INT]=malloc(sizeof(char*)*(strlen("TK_INT")+1));
	strcpy(arr_map[TK_INT],"TK_INT");
	arr_map[TK_REAL]=malloc(sizeof(char*)*(strlen("TK_REAL")+1));
	strcpy(arr_map[TK_REAL],"TK_REAL");
	arr_map[TK_ENDWHILE]=malloc(sizeof(char*)*(strlen("TK_ENDWHILE")+1));
	strcpy(arr_map[TK_ENDWHILE],"TK_ENDWHILE");
	arr_map[TK_IF]=malloc(sizeof(char*)*(strlen("TK_IF")+1));
	strcpy(arr_map[TK_IF],"TK_IF");
	arr_map[TK_THEN]=malloc(sizeof(char*)*(strlen("TK_THEN")+1));
	strcpy(arr_map[TK_THEN],"TK_THEN");
	arr_map[TK_ENDIF]=malloc(sizeof(char*)*(strlen("TK_ENDIF")+1));
	strcpy(arr_map[TK_ENDIF],"TK_ENDIF");
	arr_map[TK_READ]=malloc(sizeof(char*)*(strlen("TK_READ")+1));
	strcpy(arr_map[TK_READ],"TK_READ");
	arr_map[TK_WRITE]=malloc(sizeof(char*)*(strlen("TK_WRITE")+1));
	strcpy(arr_map[TK_WRITE],"TK_WRITE");
	arr_map[TK_RETURN]=malloc(sizeof(char*)*(strlen("TK_RETURN")+1));
	strcpy(arr_map[TK_RETURN],"TK_RETURN");
	arr_map[TK_CALL]=malloc(sizeof(char*)*(strlen("TK_CALL")+1));
	strcpy(arr_map[TK_CALL],"TK_CALL");
	arr_map[TK_RECORD]=malloc(sizeof(char*)*(strlen("TK_RECORD")+1));
	strcpy(arr_map[TK_RECORD],"TK_RECORD");
	arr_map[TK_ENDRECORD]=malloc(sizeof(char*)*(strlen("TK_ENDRECORD")+1));
	strcpy(arr_map[TK_ENDRECORD],"TK_ENDRECORD");
	arr_map[TK_ELSE]=malloc(sizeof(char*)*(strlen("TK_ELSE")+1));
	strcpy(arr_map[TK_ELSE],"TK_ELSE");

	arr_map[TK_DELIM]=malloc(sizeof(char*)*(strlen("TK_DELIM")+1));
	strcpy(arr_map[TK_DELIM],"TK_DELIM");
	arr_map[TK_EPS]=malloc(sizeof(char*)*(strlen("TK_EPS")+1));
	strcpy(arr_map[TK_EPS],"TK_EPS");
	arr_map[TK_DOLLAR]=malloc(sizeof(char*)*(strlen("TK_DOLLAR")+1));
	strcpy(arr_map[TK_DOLLAR],"TK_DOLLAR");

	return arr_map;
}

void destroy_token_name_table(char **arr){

	for (int i=0;i<TYPES_OF_TOKEN;i++){
		free(arr[i]);
	}
	free(arr);
}

hashTable get_token_hasht(){
	hashTable ht=newHashTable((int)(TYPES_OF_TOKEN*ALPHA_INV),HASH_A,HASH_B);
	insertInt("TK_ASSIGNOP",TK_ASSIGNOP,ht);
	insertInt("TK_COMMENT",TK_COMMENT,ht);
	insertInt("TK_FIELDID",TK_FIELDID,ht);
	insertInt("TK_ID",TK_ID,ht);
	insertInt("TK_NUM",TK_NUM,ht);
	insertInt("TK_RNUM",TK_RNUM,ht);
	insertInt("TK_FUNID",TK_FUNID,ht);
	insertInt("TK_RECORDID",TK_RECORDID,ht);
	insertInt("TK_SQL",TK_SQL,ht);
	insertInt("TK_SQR",TK_SQR,ht);
	insertInt("TK_COMMA",TK_COMMA,ht);
	insertInt("TK_SEM",TK_SEM,ht);
	insertInt("TK_COLON",TK_COLON,ht);
	insertInt("TK_DOT",TK_DOT,ht);
	insertInt("TK_OP",TK_OP,ht);
	insertInt("TK_CL",TK_CL,ht);
	insertInt("TK_PLUS",TK_PLUS,ht);
	insertInt("TK_MINUS",TK_MINUS,ht);
	insertInt("TK_MUL",TK_MUL,ht);
	insertInt("TK_DIV",TK_DIV,ht);
	insertInt("TK_AND",TK_AND,ht);
	insertInt("TK_OR",TK_OR,ht);
	insertInt("TK_NOT",TK_NOT,ht);
	insertInt("TK_LT",TK_LT,ht);
	insertInt("TK_LE",TK_LE,ht);
	insertInt("TK_EQ",TK_EQ,ht);
	insertInt("TK_GT",TK_GT,ht);
	insertInt("TK_GE",TK_GE,ht);
	insertInt("TK_LE",TK_LE,ht);
	insertInt("TK_NE",TK_NE,ht);
	insertInt("TK_WITH",TK_WITH,ht);
	insertInt("TK_PARAMETERS",TK_PARAMETERS,ht);
	insertInt("TK_END",TK_END,ht);
	insertInt("TK_WHILE",TK_WHILE,ht);
	insertInt("TK_TYPE",TK_TYPE,ht);
	insertInt("TK_MAIN",TK_MAIN,ht);
	insertInt("TK_GLOBAL",TK_GLOBAL,ht);
	insertInt("TK_PARAMETER",TK_PARAMETER,ht);
	insertInt("TK_LIST",TK_LIST,ht);
	insertInt("TK_INPUT",TK_INPUT,ht);
	insertInt("TK_OUTPUT",TK_OUTPUT,ht);
	insertInt("TK_INT",TK_INT,ht);
	insertInt("TK_REAL",TK_REAL,ht);
	insertInt("TK_ENDWHILE",TK_ENDWHILE,ht);
	insertInt("TK_IF",TK_IF,ht);
	insertInt("TK_THEN",TK_THEN,ht);
	insertInt("TK_ENDIF",TK_ENDIF,ht);
	insertInt("TK_READ",TK_READ,ht);
	insertInt("TK_WRITE",TK_WRITE,ht);
	insertInt("TK_RETURN",TK_RETURN,ht);
	insertInt("TK_CALL",TK_CALL,ht);
	insertInt("TK_RECORD",TK_RECORD,ht);
	insertInt("TK_ENDRECORD",TK_ENDRECORD,ht);
	insertInt("TK_ELSE",TK_ELSE,ht);
	
	insertInt("TK_DELIM",TK_DELIM,ht);
	insertInt("TK_EPS",TK_EPS,ht);
	insertInt("TK_DOLLAR",TK_DOLLAR,ht);
	return ht;
}

void destroy_token_hasht(hashTable ht){
	//todo
	return;
}

hashTable get_keyword_hasht(){
	hashTable ht=newHashTable((int)(NUM_KEYWORDS*ALPHA_INV),HASH_A,HASH_B);
	insertInt("with",TK_WITH,ht);
	insertInt("parameters",TK_PARAMETERS,ht);
	insertInt("parameter",TK_PARAMETER,ht);
	insertInt("list",TK_LIST,ht);
	insertInt("input",TK_INPUT,ht);
	insertInt("output",TK_OUTPUT,ht);
	insertInt("int",TK_INT,ht);
	insertInt("real",TK_REAL,ht);
	insertInt("endwhile",TK_ENDWHILE,ht);
	insertInt("if",TK_IF,ht);
	insertInt("then",TK_THEN,ht);
	insertInt("endif",TK_ENDIF,ht);
	insertInt("read",TK_READ,ht);
	insertInt("write",TK_WRITE,ht);
	insertInt("return",TK_RETURN,ht);
	insertInt("call",TK_CALL,ht);
	insertInt("endrecord",TK_ENDRECORD,ht);
	insertInt("else",TK_ELSE,ht);
	insertInt("_main",TK_MAIN,ht);
	insertInt("type",TK_TYPE,ht);
	insertInt("while",TK_WHILE,ht);
	insertInt("end",TK_END,ht);
	insertInt("global",TK_GLOBAL,ht);
	insertInt("record",TK_RECORD,ht);
	return ht;
}