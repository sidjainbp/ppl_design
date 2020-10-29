#include "traverseparsetree.h"

/*
typedef struct TreeNode{
	bool is_terminal;
	Terminal token_name;		//terminals
	int line_no;
	int dep;
	char name[LEXEME_MAX];
	struct TreeNode* next;
	struct TreeNode* child;
	
}TreeNode;

void printparsetree(TreeNode *root1){
	if(root1 == NULL)
		return;
	TreeNode * tempnode;
	tempnode = root1->child;
	printf("\n%s\t%d\t%d", root1->name, root1->is_terminal, root1->line_no);
	while(tempnode != NULL){
		printparsetree(tempnode);
		tempnode = tempnode->next;
	}
}

*/

void traverse(TreeNode *root){
	TreeNode *child = root->child;

	while(child != NULL){
		if(strcmp("code",child->name)==0){
			break;
		}
		child = child->next;
	}

	traverse_declarations(child->child);
	child = child->next;
	traverse_assignments(child);

	return;
}

void traverse_declarations(TreeNode *root){
	if(root == NULL){
		return;
	}
	TreeNode *tmp = root;
	while(tmp != NULL){
		traverse_decl_statements(tmp->child);
		tmp = tmp->child->next;
	}
}

/*
	WE ARE STILL POPULATING THE TYPE EXPRESSION TABLE ONLY. WE NEED TO FILL IN THE NODES WITH TYPE EXPRESSIONS TOO FOR HAVING THE 
	ASSIGNMENT STATEMENTS TYPE CHECKED FOR ERRORS.
*/

void traverse_decl_statements(TreeNode *root){
	TreeNode* chi = root->child;

	if(strcmp(chi->name,"primitive_single")==0){
		type_expression_element *temp = (type_expression_element *)malloc(sizeof(type_expression_element));
		typeex *t = (typeex*)malloc(sizeof(typeex));
		chi = chi->child; //"DECLARE" node
		chi = chi->next;  // "ID" node
		strcpy(temp->name,chi->name);
		temp->_type = primitive;
		temp->arr_allocation = not_applicable;
		
		chi = chi -> next; //"COLON" node
		chi = chi -> next; //"datatype" node
		
		if(chi->child->token_name == INTEGER){
			strcpy(t->pri.type,"integer");
		}else if(chi->child->token_name == REAL){
			strcpy(t->pri.type,"real");
		}else if(chi->child->token_name == BOOLEAN){
			strcpy(t->pri.type,"real");
		}

		temp->type_exp = *t;
		type_expression_table[ind++] = *temp;

	}
	else if(strcmp(chi->name,"primitive_list")==0){
		type_expression_element *temp = (type_expression_element *)malloc(sizeof(type_expression_element));
		typeex *t = (typeex*)malloc(sizeof(typeex));

		chi = chi->child; //"DECLARE" node
		chi = chi->next->next->next;  // "VARIABLES" node
		chi = chi->next; //"id_list" node
		TreeNode *param_list = chi; // saving the names of variables to be entered in type exp table
		
		chi = chi -> next; //"COLON" node
		chi = chi -> next; //"datatype" node
		
		if(chi->child->token_name == INTEGER){
			strcpy(t->pri.type,"integer");
		}else if(chi->child->token_name == REAL){
			strcpy(t->pri.type,"real");
		}else if(chi->child->token_name == BOOLEAN){
			strcpy(t->pri.type,"real");
		}
		
		while(param_list != NULL){					//assigns a type exp for the list of variables
			if(param_list->is_terminal == false)
				param_list = param_list->child;

			strcpy(temp->name,param_list->name);
			temp->_type = primitive;
			temp->arr_allocation = not_applicable;
			temp->type_exp = *t;
			type_expression_table[ind++] = *temp;		//storing in type exp table

			param_list = param_list->next;
		}
		
	}
	else if(strcmp(chi->name,"rectangle_array_single")==0){
		type_expression_element *temp = (type_expression_element *)malloc(sizeof(type_expression_element));
		typeex *t = (typeex*)malloc(sizeof(typeex));
		chi = chi->child; //"DECLARE" node
		chi = chi->next;  // "ID" node
		strcpy(temp->name,chi->name);
		temp->_type = rectangular;
		//temp->arr_allocation = not_applicable; //To be done while going into the dimensions rooted tree and finding the type of "index" used.
		
		chi = chi -> next; //"COLON" node
		chi = chi -> next; //"ARRAY" node
		chi = chi -> next; //"dimensions" node
		
		TreeNode *d = chi;
		int no_of_dims = 0;
		while(d != NULL){
			d = d->child;
			if(d != NULL && strcmp(d->name,"dimension")==0){
				//logic for range linked list -----too boring to write this thing. Someone else do it ploxx
				no_of_dims++;
			}
			d = d->next;
		}
		
		strcpy(t->rect.type,"rectangularArray");
		strcpy(t->rect.elem_type,"integer");
		t->rect.dims = no_of_dims;///////////////////////////////////////////
		t->rect.head = ;///////////////////////////////////////////Attach the above made linked list here
		

		temp->type_exp = *t;
		type_expression_table[ind++] = *temp;
	}
	else if(strcmp(chi->name,"rectangle_array_list")==0){
		//can be done with slight modifications in the above case. Follow the primitive_list case to pickup hints.
	}else if(strcmp(chi->name,"jagged_array_single")==0){
		//to be implemented
	}else if(strcmp(chi->name,"jagged_array_list")==0){
		//to be implemented
	}
}

void traverse_assignments(TreeNode *root){

}