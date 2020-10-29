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
			strcpy(t->pri.type,"boolean");
		}

		temp->type_exp = *t;
		type_expression_table[ind++] = *temp;

	}else if(strcmp(chi->name,"primitive_list")==0){
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
		
	}else if(strcmp(chi->name,"rectangle_array_single")==0){
		type_expression_element *temp = (type_expression_element *)malloc(sizeof(type_expression_element));
		typeex *t = (typeex*)malloc(sizeof(typeex));
		chi = chi->child; //"DECLARE" node
		chi = chi->next;  // "ID" node
		strcpy(temp->name,chi->name);
		temp->_type = rectangular;
		temp->arr_allocation = _static;
		
		chi = chi -> next; //"COLON" node
		chi = chi -> next; //"ARRAY" node
		chi = chi -> next; //"dimensions" node
		
		dim_range *rangeHead, *travPointer, *newDim;
		TreeNode *d = chi;
		int no_of_dims = 1;
		while(d != NULL){
			d = d->child;
			if(d != NULL && strcmp(d->name,"dimension")==0){
				//logic for range linked list -----too boring to write this thing. Someone else do it ploxx
				newDim = (dim_range*)malloc(sizeof(dim_range));
				newDim -> range_no = no_of_dims;
				strcpy(newDim -> l_index, d->child->next->child->name);				// [ li .. ri ]
				if(d->child->next->child->token_name == ID){
					temp->arr_allocation = dynamic;
				}
				strcpy(newDim -> r_index, d->child->next->next->next->child->name);
				if(d->child->next->next->next->child->token_name == ID){
					temp->arr_allocation = dynamic;
				}
				newDim -> next = NULL;
				if(no_of_dims == 1){
					rangeHead = newDim;
					travPointer = rangeHead;
				}else{
					travPointer -> next = newDim;
					travPointer = travPointer->next;
				}
				no_of_dims++;
			}
			d = d->next;
		}
		
		strcpy(t->rect.type,"rectangularArray");
		strcpy(t->rect.elem_type,"integer");
		t->rect.dims = no_of_dims;
		t->rect.head = rangeHead;

		temp->type_exp = *t;
		type_expression_table[ind++] = *temp;
	}
	else if(strcmp(chi->name,"rectangle_array_list")==0){
		type_expression_element *temp = (type_expression_element*)malloc(sizeof(type_expression_element));
		typeex *t = (typeex*)malloc(sizeof(typeex));

		chi = chi->child; //"DECLARE" node
		chi = chi->next->next->next;  // "VARIABLES" node
		chi = chi->next; //"id_list" node
		TreeNode *param_list = chi; // saving the names of variables to be entered in type exp table



		temp->_type = rectangular;
		temp->arr_allocation = _static;
		
		chi = chi -> next; //"COLON" node
		chi = chi -> next; //"ARRAY" node
		chi = chi -> next; //"dimensions" node
		
		dim_range *rangeHead, *travPointer, *newDim;
		TreeNode *d = chi;
		int no_of_dims = 1;
		while(d != NULL){
			d = d->child;
			if(d != NULL && strcmp(d->name,"dimension")==0){
				//logic for range linked list -----too boring to write this thing. Someone else do it ploxx
				newDim = (dim_range*)malloc(sizeof(dim_range));
				newDim -> range_no = no_of_dims;
				strcpy(newDim -> l_index, d->child->next->child->name);				// [ li .. ri ]
				if(d->child->next->child->token_name == ID){
					temp->arr_allocation = dynamic;
				}
				strcpy(newDim -> r_index, d->child->next->next->next->child->name);
				if(d->child->next->next->next->child->token_name == ID){
					temp->arr_allocation = dynamic;
				}
				newDim -> next = NULL;
				if(no_of_dims == 1){
					rangeHead = newDim;
					travPointer = rangeHead;
				}else{
					travPointer -> next = newDim;
					travPointer = travPointer->next;
				}
				no_of_dims++;
			}
			d = d->next;
		}
		
		strcpy(t->rect.type,"rectangularArray");
		strcpy(t->rect.elem_type,"integer");
		t->rect.dims = no_of_dims;
		t->rect.head = rangeHead;

		temp->type_exp = *t;

		while(param_list != NULL){					//assigns a type exp for the list of variables
			if(param_list->is_terminal == false)
				param_list = param_list->child;
			strcpy(temp->name,param_list->name);
			type_expression_table[ind++] = *temp;		//storing in type exp table
			param_list = param_list->next;
		}

	}
	else if(strcmp(chi->name,"jagged_array_single")==0){
		type_expression_element *temp = (type_expression_element*)malloc(sizeof(type_expression_element));
		typeex *t = (typeex*)malloc(sizeof(typeex));
		sd *sd_head, *sd_trav, *sd_new;
		TreeNode *jagged_row;

		chi = chi->child; //"DECLARE" node
		chi = chi->next;  // "ID" node
		strcpy(temp->name,chi->name);

		temp->_type = jagged;
		temp->arr_allocation = not_applicable;
		
		chi = chi -> next; //"COLON" node
		chi = chi -> next; //"JAGGED" node
		chi = chi -> next; //"ARRAY" node
		chi = chi -> next; //"jagged_dimension" node

		if(chi->child->next->next->next->next->next->next->next == NULL){
			strcpy(t->jagged_2d.type, "jagged");
			t->jagged_2d.dims = 2;
			t->jagged_2d.fd_l_index = atoi(chi->child->next->name);
			t->jagged_2d.fd_r_index = atoi(chi->child->next->next->next->name);
			strcpy(t->jagged_2d.elem_type, "integer");
		}

		TreeNode *temp_trav;
		chi = chi -> next -> next -> next -> next;			//"jagged_rows" node
		int r_val = t->jagged_2d.fd_r_index;
		int l_val = t->jagged_2d.fd_l_index;
		
		bool flag = true;
		TreeNode *tptr = chi;
		for(int i=l_val; i<=r_val; i++){
			tptr = tptr -> child;							//"jagged_row" node
			if(i != atoi(tptr->child->next->next->name)){
				flag = false;
			}else{
				sd_new = (sd*)malloc(sizeof(sd));
				temp_trav = tptr->child->next->next->next->next->next;	//NUMBER node
				sd_new->num = atoi(temp_trav->name);
				if(i == l_val){
					sd_head = sd_new;
					sd_trav = sd_new;
				}else{
					sd_trav -> next = sd_new;
					sd_trav = sd_new;
				}
			}
			temp_trav = temp_trav->next->next->next->next;		//2d_list node
			
		}
	}else if(strcmp(chi->name,"jagged_array_list")==0){
		//to be implemented
	}
}

void traverse_assignments(TreeNode *root){

}