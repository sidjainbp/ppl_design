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

token * createParseTree(TreeNode* root, token *currToken){
	bool flag;
	Stacknode *auxstack = NULL, *stack = NULL;							//auxiliary stack defined
	g_node *temp_g_node;
	TreeNode *tmp_child = root->child;
	TreeNode *newnode;
	node_val *temp_node_val;
	token *tmp_currToken = currToken;

	for(int i=0; i<59; i++){
		flag = true;
		//removechild(root->child);
		currToken = tmp_currToken;
		auxstack = NULL;
		stack = NULL;
		//root->child = NULL;
		//tmp_child = root->child;
		
		if(strcmp(root->name, arr[i].token) == 0){
			temp_g_node = arr[i].head;
			
			while(temp_g_node != NULL){
				temp_node_val = (node_val *)malloc(sizeof(node_val));
				temp_node_val->is_terminal = temp_g_node-> is_terminal; 
				if(temp_node_val->is_terminal){
					temp_node_val->token_name = temp_g_node -> token_name;	
				}
				strcpy(temp_node_val -> name, temp_g_node -> token);
				auxstack = push(auxstack, *temp_node_val);
				temp_g_node = temp_g_node->next;
			}
			
			while(isEmpty(auxstack) == false){
				stack = push(stack, auxstack->node_values);
				auxstack = pop(auxstack);
			}
			
			while(isEmpty(stack) == false){
				//printf("\n%s", stack->node_values.name);
			
				if(stack->node_values.is_terminal){
					if(stack->node_values.token_name == currToken->tokenname){
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
						//printf("\nterminal not matched %s \t %s \t %s \t %d", root->name,stack->node_values.name, currToken->lexeme, currToken->line_no);
						flag = false;
					}
				}else{
					newnode = (TreeNode *) malloc(sizeof(TreeNode));
					newnode->is_terminal = false;
					newnode->line_no = currToken->line_no;
					strcpy(newnode->name,stack->node_values.name);
					newnode->next = NULL;
					newnode->child= NULL;
					
					if(strcmp(newnode->name, "") != 0){
						if(tmp_child==NULL){
							root->child = newnode;
							tmp_child = newnode;
						}else{
							tmp_child->next = newnode;
							tmp_child = newnode;
						}
					}

					currToken = createParseTree(tmp_child, currToken);
					if(currToken == NULL){
						flag = false;
						//printf("\n%s", tmp_child->name);
					}else{
						stack = pop(stack);
					}
					
					
				}
				
				if(flag == false){
					//printf("\nFlag is false %s \t\t %s \t %d", root->name, currToken->lexeme, currToken->line_no);
					//printf("%s", stack->node_values.name);
					while(isEmpty(stack)==false){
						stack = pop(stack);
					}
				}
				//printf("Flag is true");
			}

			if(flag == true){
				return currToken;
			}

		}
	}	
	//printf("\ncreate parse tree returning NULL %s %s", currToken->lexeme, root->name);
	return NULL;
}

void printparsetree(TreeNode *root1){
	if(root1 == NULL)
		return;
	TreeNode * tempnode;
	tempnode = root1->child;
	printf("\n%s\t%d", root1->name, root1->is_terminal);
	while(tempnode != NULL){
		printparsetree(tempnode);
		tempnode = tempnode->next;
	}
	
	
}

//removechild(root->child){

//}
