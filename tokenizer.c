#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEXEME_MAX 21;
#define BUF_MAX 400
typedef enum{
	PROGRAM, BR_OP_CL, CR_OP, CR_CL, DECLARE, ID, COLON, SEMICOLON, LIST, OF, VARIABLES, ARRAY, JAGGED, SQ_OP, SQ_CL, NUMBER ,SIZE, VALUES, DOTDOT, INTEGER, REAL, BOOLEAN, ASSIGN_OP, PLUS, MINUS, MULTIPLY, DIVIDE, OR, AND, TRUE, FALSE
}Terminal;

typedef struct{
	Terminal tokenname;
	char lexeme[LEXEME_MAX];
	int line_no;
}token;

token *tokenstream;

int main(){
	
}

FILE* openfile(char * filename){  // opens grammar file
	FILE * ptr = fopen(filename, "r");
	return ptr;
}

void tokenize(FILE* ptr){
	char buf[BUF_MAX];
	token *traverse = tokenstream;  // traverse points to the last element in the tokenstream
	char *lex; // contains single lexeme from the source code
	
	int line_no = 1;
	while(fscanf(ptr, "%s%[^\n]", buf) != EOF){
		lex = strtok(buf, " ");
		while(lex != NULL){
			lex = strtok(NULL, " ");
			traverse = addtoken(lex, line_no, traverse);
		}
		line_no++;
	}
}

token* addtoken(char * lex, int line_no, token* last_token){
	
}
