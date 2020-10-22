#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 50
#define NUM_RULES 200
#define BUF_MAX 400

typedef struct g_node{
    char token[MAX_SIZE];
    struct g_node *next;
}g_node;

typedef struct lhs{
    char token[MAX_SIZE];
    g_node *head;
}lhs;

lhs arr[NUM_RULES];

void grammar(FILE* ptr){
	char buf[BUF_MAX]; //temporary reading buffer
	char *lex; // contains lhs of the grammar rule
    
    int i=0;
	while(fgets(buf, sizeof(buf), ptr ) != NULL){
	// while(fscanf(ptr, "%[^\n]", buf) != 0){
        // printf("%s\n",buf);
        if(strlen(buf) < 2)
            continue;

        lex = strtok(buf, " ");
        strcpy(arr[i].token,lex);
        g_node *tmp=NULL,*hd=NULL;

		while(lex != NULL){
			lex = strtok(NULL, " ");
            if(lex==NULL){
                break;
            }
            
            g_node *newnode = (g_node*) malloc(sizeof(g_node));
            strcpy(newnode->token,lex);
            newnode->next = NULL;
            
            if(tmp != NULL)
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

int main(){
    FILE* ptr = fopen("grammar.txt","r");
    if(ptr == NULL){
        printf("ERROR!!!!!!!!");
        return 1;
    }
    
    grammar(ptr);
    for(int i=0;i<88;i++){
        printf("LHS is: %s -->  ",arr[i].token);
        g_node* tmp = arr[i].head;
        while(tmp != NULL){
            printf("%s ",tmp->token);
            tmp = tmp -> next;
        }
        printf("\n");
    }
}