#include "ast.h"
#include "parserDef.h"
#include "SeqList.h"
#include "semantic_functions_ast.h"
#include "to_remove.h"
#include "tree_utils.h"
#include "colors.h"
#define NO_OF_ATTRIBUTES 3

static func_ptr_t semantic_action_map_for_ast[NO_OF_RULES][NO_OF_ATTRIBUTES]={
        // 0,1 program ===> otherFunctions mainFunction
        {&program_rule0,NULL,NULL},
        // 1,2 mainFunction ===> TK_MAIN stmts TK_END
        {&main_rule1,NULL,NULL},
        // 2,3 otherFunctions ===> function otherFunctions
        {&otherFunctionsRule2,NULL,NULL},
        // 3,4 otherFunctions ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 4,5 function ===> TK_FUNID input_par output_par TK_SEM stmts TK_END
        {&functionRule4,NULL,NULL},
        // 5,6 input_par ===> TK_INPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
        {&input_par_Rule5,NULL,NULL},
        // 6,7 output_par ===> TK_OUTPUT TK_PARAMETER TK_LIST TK_SQL parameter_list TK_SQR
        {&output_par_Rule6,NULL,NULL},
        // 7,8 output_par ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 8,9 parameter_list ===> dataType TK_ID remaining_list
        {&parameter_listRule8,NULL,NULL},
        // 9,10 dataType ===> primitiveDatatype
        {&dataTypeRule9,NULL,NULL},
        // 10,11 dataType ===> constructedDatatype
        {&dataTypeRule10,NULL,NULL},
        // 11,12 primitiveDatatype ===> TK_INT
        {&free_single_nodes,NULL,NULL},
        // 12,13 primitiveDatatype ===> TK_REAL
        {&free_single_nodes,NULL,NULL},
        // 13,14 constructedDatatype ===> TK_RECORD TK_RECORDID
        {&free_single_nodes,NULL,NULL},
        // 14,15 remaining_list ===> TK_COMMA parameter_list
        {&remaining_listRule14,NULL,NULL},
        // 15,16 remaining_list ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 16,17 stmts ===> typeDefinitions declarations otherStmts returnStmt
        {&stmtRule16,NULL,NULL},
        // 17,18 typeDefinitions ===> typeDefinition typeDefinitions
        {&a_gives_b_a_reduce,NULL,NULL},
        // 18,19 typeDefinitions ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 19,20 typeDefinition ===> TK_RECORD TK_RECORDID fieldDefinitions TK_ENDRECORD TK_SEM
        {&typeDefinitionRule19,NULL,NULL},
        // 20,21 fieldDefinitions ===> fieldDefinition fieldDefinition moreFields
        {&free_single_nodes,NULL,NULL},
        // 21,22 fieldDefinition ===> TK_TYPE primitiveDatatype TK_COLON TK_FIELDID TK_SEM
        {&free_single_nodes,NULL,NULL},
        // 22,23 moreFields ===> fieldDefinition moreFields
        {&a_gives_b_a_reduce,NULL,NULL},
        // 23,24 moreFields ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 24,25 declarations ===> declaration declarations
        {a_gives_b_a_reduce,NULL,NULL},
        // 25,26 declarations ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 26,27 declaration ===> TK_TYPE dataType TK_COLON TK_ID global_or_not TK_SEM
        {&free_single_nodes,NULL,NULL},
        // 27,28 global_or_not ===> TK_COLON TK_GLOBAL
        {&free_single_nodes,NULL,NULL},
        // 28,29 global_or_not ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 29,30 otherStmts ===> stmt otherStmts
        {&a_gives_b_a_reduce_with_both,NULL,NULL},
        // 30,31 otherStmts ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 31,32 stmt ===> assignmentStmt
        {&free_single_nodes,NULL,NULL},
        // 32,33 stmt ===> iterativeStmt
        {&free_single_nodes,NULL,NULL},
        // 33,34 stmt ===> conditionalStmt
        {&free_single_nodes,NULL,NULL},
        // 34,35 stmt ===> ioStmt
        {&free_single_nodes,NULL,NULL},
        // 35,36 stmt ===> funCallStmt
        {&free_single_nodes,NULL,NULL},
        // 36,37 assignmentStmt ===> singleOrRecId TK_ASSIGNOP arithmeticExpression TK_SEM
        {&free_single_nodes,NULL,NULL},
        // 37,38 singleOrRecId ===> TK_ID new24
        {&singleRule37,NULL,NULL},
        // 38,39 new24 ===> TK_DOT TK_FIELDID
        {&free_single_nodes,NULL,NULL},
        // 39,40 new24 ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 40,41 funCallStmt ===> outputParameters TK_CALL TK_FUNID TK_WITH TK_PARAMETERS inputParameters TK_SEM
        {&free_single_nodes,NULL,NULL},
        // 41,42 outputParameters ===> TK_SQL idList TK_SQR TK_ASSIGNOP
        {&free_single_nodes,NULL,NULL},
        // 42,43 outputParameters ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 43,44 inputParameters ===> TK_SQL idList TK_SQR
        {&free_single_nodes,NULL,NULL},
        // 44,45 iterativeStmt ===> TK_WHILE TK_OP booleanExpression TK_CL stmt otherStmts TK_ENDWHILE
        {&iterativeStmtRule44,NULL,NULL},
        // 45,46 conditionalStmt ===> TK_IF TK_OP booleanExpression TK_CL TK_THEN stmt otherStmts elsePart
        {&free_single_nodes,NULL,NULL},
        // 46,47 elsePart ===> TK_ELSE stmt otherStmts TK_ENDIF
        {&free_single_nodes,NULL,NULL},
        // 47,48 elsePart ===> TK_ENDIF
        {&free_single_nodes,NULL,NULL},
        // 48,49 ioStmt ===> TK_READ TK_OP singleOrRecId TK_CL TK_SEM
        {&free_single_nodes,NULL,NULL},
        // 49,50 ioStmt ===> TK_WRITE TK_OP allVar TK_CL TK_SEM
        {&free_single_nodes,NULL,NULL},
        // 50,51 allVar ===> TK_ID newVar
        {&allVarRule50,NULL,NULL},
        // 51,52 allVar ===> TK_NUM
        {&free_single_nodes,NULL,NULL},
        // 52,53 allVar ===> TK_RNUM
        {&free_single_nodes,NULL,NULL},
        // 53,54 newVar ===> TK_DOT TK_FIELDID
        {&free_single_nodes,NULL,NULL},
        // 54,55 newVar ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 55,56 arithmeticExpression ===> term expPrime
        {&arithmeticExpressionRule55,NULL,NULL},
        // 56,57 expPrime ===> lowPrecedenceOperators term expPrime
        {&expPrimeRule56,NULL,NULL},
        // 57,58 expPrime ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 58,59 term ===> factor termPrime
        {&termRule58,NULL,NULL},
        // 59,60 termPrime ===> highPrecedenceOperators factor termPrime
        {termPrimeRule59,NULL,NULL},
        // 60,61 termPrime ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 61,62 factor ===> TK_OP arithmeticExpression TK_CL
        {&free_single_nodes,NULL,NULL},
        // 62,63 factor ===> all
        {&free_single_nodes,NULL,NULL},
        // 63,64 highPrecedenceOperators ===> TK_MUL
        {&free_single_nodes,NULL,NULL},
        // 64,65 highPrecedenceOperators ===> TK_DIV
        {&free_single_nodes,NULL,NULL},
        // 65,66 lowPrecedenceOperators ===> TK_PLUS
        {&free_single_nodes,NULL,NULL},
        // 66,67 lowPrecedenceOperators ===> TK_MINUS
        {&free_single_nodes,NULL,NULL},
        // 67,68 all ===> TK_NUM
        {&free_single_nodes,NULL,NULL},
        // 68,69 all ===> TK_RNUM
        {&free_single_nodes,NULL,NULL},
        // 69,70 all ===> TK_ID temp
        {&allRule69,NULL,NULL},
        // 70,71 temp ===> TK_DOT TK_FIELDID
        {&free_single_nodes,NULL,NULL},
        // 71,72 temp ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 72,73 booleanExpression ===> TK_OP booleanExpression TK_CL logicalOp TK_OP booleanExpression TK_CL
        {&free_single_nodes,NULL,NULL},
        // 73,74 booleanExpression ===> var relationalOp var
        {&free_single_nodes,NULL,NULL},
        // 74,75 booleanExpression ===> TK_NOT TK_OP booleanExpression TK_CL
        {&free_single_nodes,NULL,NULL},
        // 75,76 var ===> TK_ID
        {&free_single_nodes,NULL,NULL},
        // 76,77 var ===> TK_NUM
        {&free_single_nodes,NULL,NULL},
        // 77,78 var ===> TK_RNUM
        {&free_single_nodes,NULL,NULL},
        // 78,79 logicalOp ===> TK_AND
        {&free_single_nodes,NULL,NULL},
        // 79,80 logicalOp ===> TK_OR
        {&free_single_nodes,NULL,NULL},
        // 80,81 relationalOp ===> TK_LT
        {&free_single_nodes,NULL,NULL},
        // 81,82 relationalOp ===> TK_LE
        {&free_single_nodes,NULL,NULL},
        // 82,83 relationalOp ===> TK_EQ
        {&free_single_nodes,NULL,NULL},
        // 83,84 relationalOp ===> TK_GT
        {&free_single_nodes,NULL,NULL},
        // 84,85 relationalOp ===> TK_GE
        {&free_single_nodes,NULL,NULL},
        // 85,86 relationalOp ===> TK_NE
        {&free_single_nodes,NULL,NULL},
        // 86,87 returnStmt ===> TK_RETURN optionalReturn TK_SEM
        {&free_single_nodes,NULL,NULL},
        // 87,88 optionalReturn ===> TK_SQL idList TK_SQR
        {&free_single_nodes,NULL,NULL},
        // 88,89 optionalReturn ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
        // 89,90 idList ===> TK_ID more_ids
        {a_gives_b_a_reduce,NULL,NULL},
        // 90,91 more_ids ===> TK_COMMA idList
        {free_single_nodes,NULL,NULL},
        // 91,92 more_ids ===> TK_EPS
        {&free_single_nodes,NULL,NULL},
    };


Tree post_order_traversal(Tree root){
    if(root==NULL || root->t.type=='t' || root->gr_no<0)
        return NULL;

    debug_msg("traversing %s\n",root->t.s.nt->name);
    for(int i=0; i<(root->num_child);i++){
        if(root->child!=NULL){
            post_order_traversal((root->child)[i]);
        }
    }
    debug_msg("traversing back %s\n",root->t.s.nt->name);
    func_ptr_t *SemanticActions = semantic_action_map_for_ast[root->gr_no];
    for(int i=0;i<NO_OF_ATTRIBUTES&&root!=NULL&&root->t.type=='n';i++){
        if((SemanticActions!=NULL) && (SemanticActions)[i]!=NULL)
            ((SemanticActions)[i])(root);
    }
    return root;
}

Tree convert_parse_to_ast(Tree t){
    t=post_order_traversal(t);
    return t;
}

Tree getASTFromFile(char *testcasefile){
    Tree ast = convert_parse_to_ast(getParsedTreeFromFile(testcasefile));
    return ast;
}

void printASTOutput(char *testcasefile){
    Tree ast=getASTFromFile(testcasefile);
    if(errors==true){
            printf(ANSI_COLOR_RED "Errors found in while generating AST\n" ANSI_COLOR_RESET);
    }
    else{
        inorder(ast);
        printf(ANSI_COLOR_GREEN "AST Creation Successful. No Lexical/Syntactic Errors.\n" ANSI_COLOR_RESET);
    }
}

void printRatioParseAndAST(char *testcasefile){
    Tree pt=getParsedTreeFromFile(testcasefile);
    int pt_nodes=count_nodes(pt);
    float pt_size=(float)get_size_tree_node(pt);
    
    pt=convert_parse_to_ast(pt);
    int ast_nodes=count_nodes(pt);
    float ast_size=(float)get_size_tree_node(pt);
    printf("Parse tree Number of nodes = %d\tAllocated Memory = %f Bytes\n",pt_nodes, pt_size);
    printf("AST Number of nodes = %d\t\tAllocated Memory = %f Bytes\n",ast_nodes,ast_size);
    float cp = ((pt_size-ast_size)*100.0)/pt_size;
    printf("Compression percentage = %f\n",cp);
}