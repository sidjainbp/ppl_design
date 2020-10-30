#include "traverseparsetree.h"

void traverse(TreeNode *root){
	TreeNode *child = root->child;

	while(child != NULL){
		if(strcmp("code",child->name)==0){
			break;
		}
		child = child->next;
	}

	traverse_declarations(child->child);
	child = child->child->next;
	//traverse_assignments(child);

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
		temp->tag = 0;
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
			strcpy(t->pri.type,"boolean");
		}

		while(param_list != NULL){					//assigns a type exp for the list of variables
			if(param_list->is_terminal == false)
				param_list = param_list->child;

			type_expression_table[ind].arr_allocation = not_applicable;		//storing in type exp table
			strcpy(type_expression_table[ind].name, param_list->name);
			type_expression_table[ind].tag = 0;
			type_expression_table[ind].type_exp = *t;
			type_expression_table[ind]._type = primitive;
			ind++;
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
		temp->arr_allocation = _static;
		temp->tag = 1;
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
		temp->tag = 1;
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
			temp->tag = 2;
			strcpy(t->jagged_2d.type, "jagged");
			t->jagged_2d.dims = 2;
			t->jagged_2d.fd_l_index = atoi(chi->child->next->name);
			t->jagged_2d.fd_r_index = atoi(chi->child->next->next->next->name);
			strcpy(t->jagged_2d.elem_type, "integer");

			sd *sd_head, *sd_trav, *sd_new;

			TreeNode *temp_trav;
			chi = chi -> next -> next -> next -> next;			//"jagged_rows" node
			int r_val = t->jagged_2d.fd_r_index;
			int l_val = t->jagged_2d.fd_l_index;

			bool flag = true;			//Flag for wrong index
			bool flag2 = true;			//Flag for wrong size-count
			TreeNode *tptr = chi;
			for(int i=l_val; i<=r_val; i++){
				tptr = tptr -> child;							//"jagged_row" node
				if(i != atoi(tptr->child->next->next->name)){
					flag = false;
					break;
				}else{
					sd_new = (sd*)malloc(sizeof(sd));
					temp_trav = tptr->child->next->next->next->next->next->next;	//NUMBER node
					sd_new->num = atoi(temp_trav->name);
					if(i == l_val){
						sd_head = sd_new;
						sd_trav = sd_new;
					}else{
						sd_trav -> next = sd_new;
						sd_trav = sd_new;
					}
					temp_trav = temp_trav->next->next->next->next;		//2d_list node
					temp_trav = temp_trav -> child;
					int size = sd_new->num;
					int count = 0;
					for(int j=0; j<size; j++){
						if(temp_trav->token_name == NUMBER){
							count++;
							if(temp_trav->next->token_name == CR_CL){
								break;
							}
							temp_trav = temp_trav -> next -> next -> child;
						}
					}
					if(count != size){
						flag2 = false;
						break;
					}
				}
			}
			t->jagged_2d.head = sd_head;
		}
		else{
			temp->tag = 3;
			strcpy(t->jagged_3d.type, "jagged");
			t->jagged_3d.dims = 3;
			t->jagged_3d.fd_l_index = atoi(chi->child->next->name);
			t->jagged_3d.fd_r_index = atoi(chi->child->next->next->next->name);
			strcpy(t->jagged_3d.elem_type, "integer");

			td *td_head, *td_new, *td_trav;

			TreeNode *temp_trav;
			chi = chi -> next -> next -> next -> next;			//"jagged_rows" node
			int r_val = t->jagged_2d.fd_r_index;
			int l_val = t->jagged_2d.fd_l_index;

			bool flag = true;			//Flag for wrong index
			bool flag2 = true;			//Flag for wrong size-count

			TreeNode *tptr = chi;
			for(int i=l_val; i<=r_val; i++){
				tptr = tptr -> child;							//"jagged_row" node
				if(i != atoi(tptr->child->next->next->name)){
					flag = false;
					break;
				}else{
					td_new = (td*)malloc(sizeof(td));
					temp_trav = tptr->child->next->next->next->next->next->next;	//NUMBER node
					td_new->n = atoi(temp_trav->name);

					if(i == l_val){
						td_head = td_new;
						td_trav = td_new;
					}else{
						td_trav -> next = td_new;
						td_trav = td_new;
					}
					temp_trav = temp_trav->next->next->next->next;		//3d_list node
					int size = td_new->n;


					sd *sd_trav, *sd_head = NULL, *sd_new;
					TreeNode *inside3d = temp_trav;				//3d_list node
					int prime_count = 0;
					while(inside3d != NULL){
						inside3d = inside3d -> child;
						prime_count++;
						TreeNode *tempinside3d = inside3d;
						int count = 0;
						while(tempinside3d != NULL){
							tempinside3d = tempinside3d->child;
							count++;
							tempinside3d = tempinside3d->next;
						}
						sd_new = (sd*)malloc(sizeof(sd));
						sd_new -> num = count;
						if(sd_head == NULL){
							sd_head = sd_new;
							sd_trav = sd_head;
						}else{
							sd_trav -> next = sd_new;
							sd_trav = sd_new;
						}
						inside3d = inside3d -> next -> next;
					}
					if(prime_count != size){
						flag2 = false;
						break;
					}
				}
			}
			t->jagged_3d.head = td_head;
		}
	}
	else if(strcmp(chi->name,"jagged_array_list")==0){
		type_expression_element *temp = (type_expression_element*)malloc(sizeof(type_expression_element));
		typeex *t = (typeex*)malloc(sizeof(typeex));

		TreeNode *jagged_row;

		chi = chi->child; //"DECLARE" node
		chi = chi->next->next->next;  // "VARIABLES" node
		chi = chi->next; //"id_list" node
		TreeNode *param_list = chi; // saving the names of variables to be entered in type exp table

		temp->_type = jagged;
		temp->arr_allocation = not_applicable;

		chi = chi -> next; //"COLON" node
		chi = chi -> next; //"JAGGED" node
		chi = chi -> next; //"ARRAY" node
		chi = chi -> next; //"jagged_dimension" node

		if(chi->child->next->next->next->next->next->next->next == NULL){
			temp->tag = 2;
			strcpy(t->jagged_2d.type, "jagged");
			t->jagged_2d.dims = 2;
			t->jagged_2d.fd_l_index = atoi(chi->child->next->name);
			t->jagged_2d.fd_r_index = atoi(chi->child->next->next->next->name);
			strcpy(t->jagged_2d.elem_type, "integer");

			sd *sd_head, *sd_trav, *sd_new;

			TreeNode *temp_trav;
			chi = chi -> next -> next -> next -> next;			//"jagged_rows" node
			int r_val = t->jagged_2d.fd_r_index;
			int l_val = t->jagged_2d.fd_l_index;

			bool flag = true;			//Flag for wrong index
			bool flag2 = true;			//Flag for wrong size-count
			TreeNode *tptr = chi;
			for(int i=l_val; i<=r_val; i++){
				tptr = tptr -> child;							//"jagged_row" node
				if(i != atoi(tptr->child->next->next->name)){
					flag = false;
					break;
				}else{
					sd_new = (sd*)malloc(sizeof(sd));
					temp_trav = tptr->child->next->next->next->next->next->next;	//NUMBER node
					sd_new->num = atoi(temp_trav->name);
					if(i == l_val){
						sd_head = sd_new;
						sd_trav = sd_new;
					}else{
						sd_trav -> next = sd_new;
						sd_trav = sd_new;
					}
					temp_trav = temp_trav->next->next->next->next;		//2d_list node
					temp_trav = temp_trav -> child;
					int size = sd_new->num;
					int count = 0;
					for(int j=0; j<size; j++){
						if(temp_trav->token_name == NUMBER){
							count++;
							if(temp_trav->next->token_name == CR_CL){
								break;
							}
							temp_trav = temp_trav -> next -> next -> child;
						}
					}
					if(count != size){
						flag2 = false;
						break;
					}
				}
			}
			t->jagged_2d.head = sd_head;
		}
		else{
			temp->tag = 3;
			strcpy(t->jagged_3d.type, "jagged");
			t->jagged_3d.dims = 3;
			t->jagged_3d.fd_l_index = atoi(chi->child->next->name);
			t->jagged_3d.fd_r_index = atoi(chi->child->next->next->next->name);
			strcpy(t->jagged_3d.elem_type, "integer");

			td *td_head, *td_new, *td_trav;

			TreeNode *temp_trav;
			chi = chi -> next -> next -> next -> next;			//"jagged_rows" node
			int r_val = t->jagged_2d.fd_r_index;
			int l_val = t->jagged_2d.fd_l_index;

			bool flag = true;			//Flag for wrong index
			bool flag2 = true;			//Flag for wrong size-count

			TreeNode *tptr = chi;
			for(int i=l_val; i<=r_val; i++){
				tptr = tptr -> child;							//"jagged_row" node
				if(i != atoi(tptr->child->next->next->name)){
					flag = false;
					break;
				}else{
					td_new = (td*)malloc(sizeof(td));
					temp_trav = tptr->child->next->next->next->next->next->next;	//NUMBER node
					td_new->n = atoi(temp_trav->name);

					if(i == l_val){
						td_head = td_new;
						td_trav = td_new;
					}else{
						td_trav -> next = td_new;
						td_trav = td_new;
					}
					temp_trav = temp_trav->next->next->next->next;		//3d_list node
					int size = td_new->n;


					sd *sd_trav, *sd_head = NULL, *sd_new;
					TreeNode *inside3d = temp_trav;				//3d_list node
					int prime_count = 0;
					while(inside3d != NULL){
						inside3d = inside3d -> child;
						prime_count++;
						TreeNode *tempinside3d = inside3d;
						int count = 0;
						while(tempinside3d != NULL){
							tempinside3d = tempinside3d->child;
							count++;
							tempinside3d = tempinside3d->next;
						}
						sd_new = (sd*)malloc(sizeof(sd));
						sd_new -> num = count;
						if(sd_head == NULL){
							sd_head = sd_new;
							sd_trav = sd_head;
						}else{
							sd_trav -> next = sd_new;
							sd_trav = sd_new;
						}
						inside3d = inside3d -> next -> next;
					}
					if(prime_count != size){
						flag2 = false;
						break;
					}
				}
			}
			t->jagged_3d.head = td_head;
		}

		temp->type_exp = *t;

		while(param_list != NULL){					//assigns a type exp for the list of variables
			if(param_list->is_terminal == false)
				param_list = param_list->child;
			strcpy(temp->name,param_list->name);
			type_expression_table[ind++] = *temp;		//storing in type exp table
			param_list = param_list->next;
		}
	}
}

void traverse_assignments(TreeNode *root){
	TreeNode * ass_trav;
	ass_trav = root;

	while(ass_trav != NULL){
		ass_trav = ass_trav -> child;
		traverse_assignment(ass_trav);
		ass_trav = ass_trav->next;
	}
}

void traverse_assignment(TreeNode *root){

	TreeNode *trav;
	trav = root;  //assignment

	check_id_or_array(trav->child);
	base_type lhs_base_type = return_base_type(trav->child);
	trav = trav->child->next->next;  // a_expression or l_expression

	base_type rhs_base_type;
	if(strcmp(trav->name, "a_expression") == 0){
		rhs_base_type = check_a_expression(trav);
	}
	else{
		rhs_base_type = check_l_expression(trav);
	}
	if(lhs_base_type != rhs_base_type)
		//error lhs!= rhs typex

}
base_type return_base_type(TreeNode* root){
	if(root->is_error){
		return error;
	}


		if(root->is_terminal){
				if(root->token_name == ID){
						switch(root->tag){
							case 0:{
										if(strcmp(root->type_exp.pri.type,"integer")==0)
												return integer;
										else if(strcmp(root->type_exp.pri.type,"boolean")==0)
												return boolean;
										else if(strcmp(root->type_exp.pri.type,"real")==0)
												return real;

							}
							case 1:
										return integer;
							case 2:
										return integer;
							case 3:
										return integer;

						}
				}
			else{
				return integer;
			}

		}
		else{			//non-terminal
					return integer;
		}

}

base_type check_a_expression(TreeNode* root){
	base_type left,right;
	//left = check_term(root->child);
	left = check_term(root->child);
	if(root->child->next != NULL){
		right = check_a_expression(root->child->next->next);
		if(left != right)
			// error
		else
				return left;
	}
	else{
		return check_term(root->child);
	}
}

base_type check_term(TreeNode* root){
	base_type left,right;
	left = check_factor(root->child);
	if(root->child->next != NULL){
		right
	}
}

type_expression_element searchfromtable(char *name){
	type_expression_element temp;
	for(int i=0; i<ind; i++){
		if(strcmp(type_expression_table[i].name, name) == 0){
			return type_expression_table[i];
		}
	}
	return temp;
}

void check_id_or_array(TreeNode *lhs_node){

	TreeNode *array_id, *index_ele;


	type_expression_element temp;

	if(lhs_node->is_terminal){   //checking id
		temp = searchfromtable(lhs_node->name);
		lhs_node->tag = temp.tag;
		lhs_node->type_exp = temp.type_exp;
	}
	else{						// checking array_element
		array_id = lhs_node->child;
		temp = searchfromtable(array_id->name);
		array_id->tag = temp.tag;
		array_id->type_exp = temp.type_exp;

		if(array_id->tag == 2){  // jagged 2d       currindex - index in array element index_ele - node of index_ele of grammar
			index_ele = array_id->next->next;
			int l = array_id->type_exp.jagged_2d.fd_l_index;
			int r = array_id->type_exp.jagged_2d.fd_r_index;
			if(index_ele->child->child->token_name == NUMBER){
				int currindex = atoi(index_ele->child->child->name);
				if(l<currindex && r>currindex){
					int count = currindex - l;
					sd *temp = array_id->type_exp.jagged_2d.head;
					while(count--){
						temp = temp->next;
					}
					int size = temp->num;
					if(index_ele->child->next->child->child->token_name == NUMBER){
						currindex = atoi(index_ele->child->next->child->child->name);
						if(currindex < 0 || currindex>=size){
							//error found bound checking in 2 dim
						}
					}
				}
				else{
					// error found bound checking in 1 dim
				}
			}
		}
		else if(array_id->tag == 3){
			index_ele = array_id->next->next;
			int l = array_id->type_exp.jagged_3d.fd_l_index;
			int r = array_id->type_exp.jagged_3d.fd_r_index;
			if(index_ele->child->child->token_name == NUMBER){
				int currindex = atoi(index_ele->child->child->name);
				if(l<currindex && r>currindex){
					int count = currindex - l;
					td *temp_td = array_id->type_exp.jagged_3d.head;
					while(count--){
						temp_td = temp_td->next;
					}
					int size = temp_td->n;
					if(index_ele->child->next->child->child->token_name == NUMBER){
						currindex = atoi(index_ele->child->next->child->child->name);
						if(currindex >= 0 && currindex < size){
							sd *temp_sd;
							temp_sd = temp_td->head;
							if(index_ele->child->next->child->next->child->child->token_name == NUMBER){
								currindex = atoi(index_ele->child->next->child->next->child->child->name);
								while(currindex--){
									if(temp_sd == NULL){
										// error in 3 dim
									}
									temp_sd = temp_sd->next;
								}
							}
						}
						else{
							//error found bound checking in 2 dim
						}
					}
				}
				else{
					// error found bound checking in 1 dim
				}
			}
		}
		else if(array_id->tag == 1){
			index_ele = array_id->next->next;
			int dims = array_id->type_exp.rect.dims;
			dim_range *temp;
			temp = array_id->type_exp.rect.head;
			for(int i=0; i<dims; i++){
				int l = atoi(temp->l_index);
				int r = atoi(temp->r_index);
				if(index_ele->child->child->token_name == NUMBER){
					int currindex = atoi(index_ele->child->child->name);
					if(currindex<l || currindex>r){
						// error in i+1 dim
						break;
					}
				}
				else{
					break;
				}

				index_ele = index_ele->child->next;
				temp = temp->next;
			}
		}
	}
}

void printparsetree(TreeNode *root1){

	if(root1 == NULL)
		return;

	TreeNode * tempnode;
	tempnode = root1->child;

	printf("\n%-20s%-3d%-3d", root1->name, root1->is_terminal,root1->dep);
	//symbol name,is_terminal,depth

	if(root1->child == NULL){ //leaf node
		printf("\t%d\t%d",root1->token_name,root1->line_no);
	}else{
		//if non-leaf----//grammar rule
		printf("\t-");

		int i=0;
		while(strcmp(type_expression_table[i].name,root1->name)==0){
			if(type_expression_table[i].tag == 0){
				printf("\t<type=%s>",type_expression_table[i].type_exp.pri.type);
			}
			else if(type_expression_table[i].tag == 1){
				int tmp = 1;
				printf("\t<type=rectangularArray, dimensions=%d, ", type_expression_table[i].type_exp.rect.dims);

				dim_range *aaa = type_expression_table[i].type_exp.rect.head;
				while(aaa != NULL){
						printf("range_R%d= (%s, %s),",tmp,aaa->l_index,aaa->r_index);
						tmp++;
						aaa = aaa -> next;
				}
				printf(" basicElementType = integer>");
			}
			else if(type_expression_table[i].tag == 2){
				printf("\t<type =jaggedArray, dimensions=2, range_R1=(%d, %d), range_R2 = (",
				type_expression_table[i].type_exp.jagged_2d.fd_l_index,type_expression_table[i].type_exp.jagged_2d.fd_r_index);

				sd *aaa = type_expression_table[i].type_exp.jagged_2d.head;
				while(aaa != NULL){
					printf("%d, ",aaa->num);
					aaa = aaa->next;
				}

				printf("), basicElementType = integer>");

			}
			else if(type_expression_table[i].tag == 3){
				printf("<type =jaggedArray, dimensions=3, range_R1=(%d, %d), range_R2 = (",
				type_expression_table[i].type_exp.jagged_3d.fd_l_index,type_expression_table[i].type_exp.jagged_3d.fd_r_index);
				td *aaa = type_expression_table[i].type_exp.jagged_3d.head;
				while(aaa != NULL){
					printf("%d [",aaa->n);
					sd *aa = aaa-> head;
					while(aa != NULL){
						printf("%d, ",aa->num);
						aa = aa->next;
					}
					printf("] ,");
					aaa = aaa->next;
				}

				printf(" ), basicElementType = integer>");
			}
			i++;
		}
	}

	while(tempnode != NULL){
		printparsetree(tempnode);
		tempnode = tempnode->next;
	}
}

void printtypeexpressiontable(){
	printf("\nField-1\t\tField-2\t\tField-3\t\tField-4");
	for(int i=0; i<ind; i++){
		printf("\n%s\t",type_expression_table[i].name);

		printf("\t%d\t",type_expression_table[i]._type);

		char f3[15];
		switch (type_expression_table[i].arr_allocation)
		{
		case 0:
			strcpy(f3, "static");
			break;
		case 1:
			strcpy(f3, "dynamic");
			break;
		default:
			strcpy(f3, "not_applicable");
			break;
		}
		printf("\t%s\t",f3);

		switch (type_expression_table[i]._type)
		{
		case 0:
			printf("\t<type=%s>\n", type_expression_table[i].type_exp.pri.type);
			break;
		case 1:
			printf("\t<type=rectangularArray,dimensions=%d,",
						type_expression_table[i].type_exp.rect.dims);
			for(int i=1; i<=type_expression_table[i].type_exp.rect.dims; i++){
				printf("range_R%d=(",i);
				printf("%d,%d),", atoi(type_expression_table[i].type_exp.rect.head->l_index),
							atoi(type_expression_table[i].type_exp.rect.head->r_index));
			}
			printf("basicElementType=%s>\n",
							type_expression_table[i].type_exp.rect.elem_type);
			break;
		case 2:
			if(type_expression_table[i].tag == 2){
				jagged_2d_exp aaa = type_expression_table[i].type_exp.jagged_2d;
				printf("\t<type=jaggedArray,dimensions=2,");
				printf("range_R1=(%d,%d),",aaa.fd_l_index,aaa.fd_r_index);
				printf("range_R2=(");
				sd* temp = type_expression_table[i].type_exp.jagged_2d.head;
				while(temp != NULL){
					if(temp->next != NULL){
						printf("%d, ",temp->num);
					}else{
						printf("%d),", temp->num);
					}
					temp = temp->next;
				}
				printf("basicElementType=%s>\n",
							type_expression_table[i].type_exp.jagged_2d.elem_type);
			}else if(type_expression_table[i].tag == 3){
				jagged_3d_exp aaa = type_expression_table[i].type_exp.jagged_3d;
				printf("\t<type=jaggedArray,dimensions=3,");
				printf("range_R1=(%d,%d),",aaa.fd_l_index,aaa.fd_r_index);
				printf("range_R2=(");
				td* tdtemp = type_expression_table[i].type_exp.jagged_3d.head;
				while(tdtemp != NULL){
					printf("%d [ ", tdtemp->n);
					sd* sdtemp = type_expression_table[i].type_exp.jagged_3d.head->head;
					while(sdtemp != NULL){
						if(sdtemp->next != NULL){
							printf("%d, ",sdtemp->num);
						}else if(sdtemp->next == NULL && tdtemp->next != NULL){
							printf("%d], ", sdtemp->num);
						}else if(sdtemp->next == NULL && tdtemp->next == NULL){
							printf("%d] ", sdtemp->num);
						}
						sdtemp = sdtemp -> next;
					}
					tdtemp = tdtemp->next;
				}
				printf("), basicElementType=%s>\n",
							type_expression_table[i].type_exp.jagged_3d.elem_type);
			}
			break;
		}
	}
}
