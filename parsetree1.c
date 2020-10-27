#include "parsetree1.h"

Stacknode* push(Stacknode *head, node_val n){
	Stacknode* temp = (Stacknode*) malloc(sizeof(Stacknode));
	temp->node_values = n;
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

bool createParseTree(TreeNode* root){
	bool flag;
	Stacknode *auxstack = NULL, *stack = NULL;							//auxiliary stack defined
	int index = -1;
	g_node *temp_g_node;
	TreeNode *tmp_child = root->child;
	TreeNode *newnode;
	node_val *temp_node_val;
	token *tmp_currToken = currToken;

	for(int i=0; i<88; i++){
		flag = true;
		if(strcmp(root->name, arr[i].token) == 0){
			temp_g_node = arr[i].head;
			while(temp_g_node != NULL){
				temp_node_val = (node_val *)malloc(sizeof(node_val));
				temp_node_val->is_terminal = temp_g_node-> is_terminal; 
				if(temp_node_val->is_terminal){
					temp_node_val->token_name = temp_g_node -> token_name;
					strcpy(temp_node_val -> name, temp_g_node -> token);
				}

				auxstack = push(auxstack, *temp_node_val);
				temp_g_node = temp_g_node->next;
			}
			
			while(isEmpty(auxstack) == false){
				stack = push(stack, auxstack->node_values);
				auxstack = pop(auxstack);
			}
			
			while(isEmpty(stack) == false){
				if(stack->node_values.is_terminal){
					if(stack->node_values.token_name == currToken->tokenname){
						flag = true;
						newnode = (TreeNode *) malloc(sizeof(TreeNode));
						newnode->is_terminal = true;
						newnode->token_name = currToken->tokenname;
						newnode->line_no = currToken->line_no;
						strcpy(newnode->name,currToken->lexeme);
						newnode->next = NULL;
						newnode->child= NULL;

						if(tmp_child==NULL){
							root->child = newnode;
							tmp_child = newnode;
						}else{
							tmp_child->next = newnode;
							tmp_child = newnode;
						}

						stack = pop(stack);
						currToken = currToken->next;
					}else{
						flag = false;
					}
				}else{
					newnode = (TreeNode *) malloc(sizeof(TreeNode));
					newnode->is_terminal = false;
					newnode->line_no = currToken->line_no;
					strcpy(newnode->name,stack->node_values.name);
					newnode->next = NULL;
					newnode->child= NULL;

					if(tmp_child==NULL){
						root->child = newnode;
						tmp_child = newnode;
					}else{
						tmp_child->next = newnode;
						tmp_child = newnode;
					}

					flag = flag & createParseTree(tmp_child);
					stack = pop(stack);
				}
				
				if(flag == false){
					printf("Flag is false");
					printf("%s", stack->node_values.name);
					while(isEmpty(stack)==false){
						stack = pop(stack);
					}
				}
				printf("Flag is true");
			}

			if(flag == true){
				return true;
			}

		}
	}	
	
	printf("\ncreate parse tree end");
}

void printparsetree(TreeNode *root1){
	TreeNode * tempnode;
	tempnode = root1->child;
	if(tempnode == NULL){
		return;
	}
	
	while(tempnode != NULL){
		printparsetree(tempnode);
		tempnode = tempnode->next;
	}
	
	printf("\n%s\t%d", root1->name, root1->is_terminal);
}
