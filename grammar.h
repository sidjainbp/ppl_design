#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 50
#define NUM_RULES 200
#define BUF_MAX 400

typedef enum{
	PROGRAM, BR_OP_CL, CR_OP, CR_CL, DECLARE, ID, COLON, SEMICOLON, LIST, OF, VARIABLES, ARRAY, JAGGED, SQ_OP, SQ_CL, NUMBER ,SIZE, 
    VALUES, DOTDOT, INTEGER, REAL, BOOLEAN, ASSIGN_OP, PLUS, MINUS, MULTIPLY, DIVIDE, OR, AND
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

void grammar(FILE* ptr);
void printgrammar();
