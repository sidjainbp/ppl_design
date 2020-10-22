#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEXEME_MAX 21
#define BUF_MAX 400
typedef enum{
	PROGRAM, BR_OP_CL, CR_OP, CR_CL, DECLARE, ID, COLON, SEMICOLON, LIST, OF, VARIABLES, ARRAY, JAGGED, SQ_OP, SQ_CL, NUMBER ,SIZE, VALUES, DOTDOT, INTEGER, REAL, BOOLEAN, ASSIGN_OP, PLUS, MINUS, MULTIPLY, DIVIDE, OR, AND
}Terminal;						// , TRUE, FALSE removed



typedef struct token{
	Terminal tokenname;
	char lexeme[LEXEME_MAX];
	int line_no;
	struct token* next;
}token;

FILE* openfile(char * filename);
void tokenize(FILE* ptr);
token* addtoken(char * lex, int line_no, token* last_token);
void print_tokens(token*);
