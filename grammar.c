#include "grammar.h"

void grammar(FILE* ptr){
	char buf[BUF_MAX]; //temporary reading buffer
	char *lex; // contains lhs of the grammar rule
    
    int i=0;
	while(fgets(buf, sizeof(buf), ptr ) != NULL){

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
            if(isupper(lex[0])){
				newnode->is_terminal = true;
				if(strcmp(lex,"PROGRAM") == 0){
					newnode->token_name = PROGRAM;	
				}else if(strcmp(lex,"BR_OP_CL") == 0){
					newnode->token_name = BR_OP_CL;					
				}else if(strcmp(lex,"CR_OP") == 0){
					newnode->token_name = CR_OP;					
				}else if(strcmp(lex,"CR_CL") == 0){
					newnode->token_name = CR_CL;					
				}else if(strcmp(lex,"DECLARE") == 0){
					newnode->token_name = DECLARE;					
				}else if(strcmp(lex,"COLON") == 0){
					newnode->token_name = COLON;					
				}else if(strcmp(lex,"SEMICOLON") == 0){
					newnode->token_name = SEMICOLON;					
				}else if(strcmp(lex,"LIST") == 0){
					newnode->token_name = LIST;					
				}else if(strcmp(lex,"OF") == 0){
					newnode->token_name = OF;					
				}else if(strcmp(lex,"VARIABLES") == 0){
					newnode->token_name = VARIABLES;					
				}else if(strcmp(lex,"BR_OP_CL") == 0){
					newnode->token_name = BR_OP_CL;					
				}else if(strcmp(lex,"ARRAY") == 0){
					newnode->token_name = ARRAY;					
				}else if(strcmp(lex,"JAGGED") == 0){
					newnode->token_name = JAGGED;					
				}else if(strcmp(lex,"SQ_OP") == 0){
					newnode->token_name = SQ_OP;	
				}else if(strcmp(lex,"SQ_CL") == 0){
					newnode->token_name = SQ_CL;	
				}else if(strcmp(lex,"SIZE") == 0){
					newnode->token_name = SIZE;	
				}else if(strcmp(lex,"VALUES") == 0){
					newnode->token_name = VALUES;	
				}else if(strcmp(lex,"DOTDOT") == 0){
					newnode->token_name = DOTDOT;	
				}else if(strcmp(lex,"INTEGER") == 0){
					newnode->token_name = INTEGER;
				}else if(strcmp(lex,"REAL") == 0){
					newnode->token_name = REAL;
				}else if(strcmp(lex,"BOOLEAN") == 0){
					newnode->token_name = BOOLEAN;
				}else if(strcmp(lex,"ASSIGN_OP") == 0){
					newnode->token_name = ASSIGN_OP;
				}else if(strcmp(lex,"PLUS") == 0){
					newnode->token_name = PLUS;
				}else if(strcmp(lex,"MINUS") == 0){
					newnode->token_name = MINUS;
				}else if(strcmp(lex,"MULTIPLY") == 0){
					newnode->token_name = MULTIPLY;
				}else if(strcmp(lex,"DIVIDE") == 0){
					newnode->token_name = DIVIDE;
				}else if(strcmp(lex,"OR") == 0){
					newnode->token_name = OR;
				}else if(strcmp(lex,"AND") == 0){
					newnode->token_name = AND;
				}else if(strcmp(lex,"NUMBER") == 0){
					newnode->token_name = NUMBER;
				}else if(strcmp(lex,"ID") == 0){
					newnode->token_name = ID;
				}
			}else{
				newnode->is_terminal = false;
			}
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

// int main(){
//     FILE* ptr = fopen("grammar.txt","r");
//     if(ptr == NULL){
//         printf("ERROR!!!!!!!!");
//         return 1;
//     }
    
//     grammar(ptr);
//     for(int i=0;i<88;i++){
//         printf("LHS is: %s -->  ",arr[i].token);
//         g_node* tmp = arr[i].head;
//         while(tmp != NULL){
//             printf("%s ",tmp->token);
//             tmp = tmp -> next;
//         }
//         printf("\n");
//     }
// }
