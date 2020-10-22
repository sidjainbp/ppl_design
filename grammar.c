#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define NUM_RULES 200
#define BUF_MAX 400

typedef struct{
    char *token;
    struct g_node *next;
}g_node;

typedef struct{
    char *token;
    struct g_node *head;
}lhs;
typedef struct lhs arr[NUM_RULES];

FILE* openfile(char * filename){  // opens grammar file
	FILE * ptr = fopen(filename, "r");
	return ptr;
}

void grammar(FILE* ptr){
	char buf[BUF_MAX]; //temporary reading buffer
	char *lex; // contains lhs of the grammar rule
	
    
    int i=0;
	while(fscanf(ptr, "%s%[^\n]", buf) != EOF){
		lex = strtok(buf, " ");
        arr[i].token = lex;
        
        g_node *tmp,*hd=NULL;
		while(lex != NULL){
			lex = strtok(NULL, " ");
			g_node *newnode = (g_node*) malloc(sizeof(g_node));
            newnode->token = lex;
            newnode->next = NULL;
            tmp->next = newnode;
            tmp = newnode;
            if(hd == NULL){
                hd = newnode;
            }
		}
        arr[i].head = hd;
		i++;
	}
}