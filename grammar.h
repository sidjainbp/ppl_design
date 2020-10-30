#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 50
/*
Group No 12
ID: 2018A7PS0240P			Name: Akshay Gundewar
ID: 2018A7PS0228P 			Name: Kanishk Patidar
ID: 2018A7PS0282P 			Name: Siddhant Jain
ID: 2018A7PS0339P 			Name: Utkarsh Srivastava
*/

#define NUM_RULES 200
#define BUF_MAX 400




typedef enum{
	PROGRAM, BR_OP, BR_CL, CR_OP, CR_CL, DECLARE, ID, COLON, SEMICOLON, LIST, OF, VARIABLES, ARRAY, JAGGED, SQ_OP, SQ_CL, NUMBER ,SIZE, 
VALUES, DOTDOT, INTEGER, REAL, BOOLEAN, ASSIGN_OP, PLUS, MINUS, MULTIPLY, DIVIDE, OR, AND, R1 
}Terminal;

typedef struct g_node{
    char token[MAX_SIZE];
    bool is_terminal;
    Terminal token_name;
    struct g_node *next;
}g_node;

typedef struct lhs{
    char token[MAX_SIZE];
    g_node *head;
}lhs;

lhs arr[NUM_RULES];
char errors[MAX_SIZE][1000];
int errind;
void readGrammar(char *filename);
void grammar(FILE* ptr);
void printgrammar();
void skipspaces(char * ch);
