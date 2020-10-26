#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"
#include "parsetree1.h"

TreeNode* root = NULL;
currToken = NULL;

/*
typedef struct node_val{
	bool is_terminal;
	Terminal token_name;		
	int line_no;
	char name[LEXEME_MAX];
}node_val;


typedef struct TreeNode{
	bool is_terminal;
	Terminal token_name;		//terminals
	int line_no;
	char name[LEXEME_MAX];
	TreeNode* next;
	TreeNode* child;
	
}TreeNode;

typedef struct StackNode{
	node_val node_values;
	StackNode * next;
}StackNode;

*/
int main(){

}

Stacknode* push(Stacknode *head, node_val){
	TreeNode* temp = (TreeNode*) malloc(sizeof(TreeNode));
	temp->node_values = node_val;
	temp->next = head;
	head = temp;
	return head;
}

Stacknode* pop(Stacknode* head){
	if(isEmpty(head))
		return NULL;
	Stacknode* temp = head;
	head = head->next;
	free(temp);
	return head;
}

bool isEmpty(Stacknode *head){
	return head == NULL;
}

bool createParseTree(TreeNode* root,Token* currToken){
	bool flag = true;
	Stacknode *auxstack = NULL, *stack = NULL;							//auxiliary stack defined
	int index = -1;
	g_node *temp_g_node;
	node_val *temp_node_val;
	for(int i=0; i<88; i++){
		if(strcmp(root->name, arr[i].token) == 0){
			temp_g_node = arr[i].head;
			while(temp_g_node != NULL){
				temp_node_val->is_terminal = isupper(temp_g_node->token[0]); 
				if(temp_node_val->is_terminal){
					temp_node_val->token_name = 
				}
				//                 fill temp_node_val
				
				auxstack = push(auxstack, temp_node_val);
				temp_g_node = temp_g_node->next;
			}
			
			while(isEmpty(auxstack) == false){
				stack = push(stack, auxstack->node_values);
				auxstack = pop(auxstack);
			}
			
			while(isEmpty(stack) == false){
				if(stack->node_values->is_terminal){
					if(strcmp(stack.node_values->name, currToken->lexeme) == 0){
						flag = flag & true;
					}else{
						flag = false;
					}
				}else{
					flag = flag & createParseTree(root->child, stack.node_values->name);
				}
			}
		}
	}	
}


