#include "grammar.h"

#define LEXEME_MAX 21
#define BUF_MAX 400

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
