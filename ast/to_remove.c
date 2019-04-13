#include "to_remove.h"

bool not_in_ast(enum token_names state_id){
    switch (state_id)
    {
        case TK_SEM:
        case TK_END:
        case TK_PARAMETER:
        case TK_LIST:
        case TK_SQL:
        case TK_SQR:
        case TK_TYPE:
        case TK_COLON:
        case TK_ASSIGNOP:
        case TK_WHILE:
        case TK_OP:
        case TK_CL:
        case TK_ENDWHILE:
        case TK_CALL:
        case TK_WITH:
        case TK_PARAMETERS:
        case TK_RETURN:
        case TK_RECORD:
        case TK_ENDRECORD:
        case TK_ENDIF:
            return true;
        default:
            return false;
    }
}