/*
Group No 12
ID: 2018A7PS0240P			Name: Akshay Gundewar
ID: 2018A7PS0228P 			Name: Kanishk Patidar
ID: 2018A7PS0282P 			Name: Siddhant Jain
ID: 2018A7PS0339P 			Name: Utkarsh Srivastava
*/


#include "grammar.h"

#define LEXEME_MAX 50
#define BUF_MAX 400

typedef struct token{
	Terminal tokenname;
	char lexeme[LEXEME_MAX];
	int line_no;
	struct token* next;
}token;

token *tokenstream;
FILE* openfile(char * filename);
void tokeniseSourcecode( char *filename);
void tokenize(FILE* ptr);
void skipspaces(char *ch);
token* addtoken(char * lex, int line_no, token* last_token);
void print_tokens(token*);
