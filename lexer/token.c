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
	
	insert("TK_DELIM",TK_DELIM,ht);
	insert("TK_EPS",TK_EPS,ht);
	insert("TK_DOLLAR",TK_DOLLAR,ht);
	return ht;
}

void destroy_token_hasht(hashTable ht){
	//todo
	return;
}