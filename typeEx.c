#include "typeEx.h"
/*typedef struct TreeNode{
	bool is_terminal;
	Terminal token_name;
	int line_no;
	char name[LEXEME_MAX];
	struct TreeNode* next;
	struct TreeNode* child;

}TreeNode;*/

/*typedef struct tExNode{
	1 char* name[char_max];
	2 int dataType;		//primitive,rectangular,jagged
	3 char* arrType;		// "static","dynamic","not_applicable

	4 union typeEx{
		Terminal Type;		// primitive- INTEGER,REAL,BOOLEAN; RECTANGULAR; JAGGED -

	}
	struct tExNode * next;

}tExNode;*/

void fill_typeEx( TreeNode* rootptr){
	TreeNode * temp_node;
	temp_node = rootptr->child;
	if(temp_node == NULL){
		return;
	}

	while(temp_node != NULL){
		fill_typeEx(temp_node);
		temp_node = temp_node->next;
	}

	tExNode* temp_tEx = (tExNode*) malloc(sizeof(tExNode));
	fill(rootptr,temp_tEx);
	if(currEntry!= NULL)
		{currEntry->next = temp_tEx;
		currEntry = currEntry->next;}
	else
		{	currEntry = temp_tEx;		//first time initialisation
			table_head = currEntry;}
	free(temp_tEx);


}


 void fill(TreeNode* rootptr,tExNode* temp_tEx){
 	strcpy(temp_tEx -> name , rootptr -> name);
 	temp_tEx -> uType.Type = rootptr-> token_name; // assuming only 5 of the described values
 	if(temp_tEx-> uType.Type == INTEGER || temp_tEx-> uType.Type== REAL || temp_tEx-> uType.Type== BOOLEAN)
 		{
 			temp_tEx -> dataType = 0;
 			strcpy(temp_tEx -> arrType , "not_applicable");
 		}
 	else if(temp_tEx -> uType.Type == JAGGED){

 		temp_tEx -> dataType = 2;
 		strcpy(temp_tEx -> arrType ,"not_applicable");

 	}
 	else if(temp_tEx->uType.Type == ARRAY){
		TreeNode* temproot = rootptr->child;
		bool ID_flag = false;
 		temp_tEx -> dataType = 1;

		while(temproot != NULL){

					TreeNode * dim_temp = temproot->child;
					while(dim_temp != NULL){
							if(dim_temp-> name == "index")			// confusiyaing
								{
									if(dim_temp->child->token_name == ID)
									{		ID_flag = true;
											break;}
								}

						dim_temp = dim_temp->next;
					}
				if(ID_flag)
					break;
			temproot = temproot->next;
		}
		if(ID_flag)
			strcpy(temp_tEx-> arrType , "dynamic");
		else
			strcpy(temp_tEx->arrType ,"static");

 	}


 }

void print_typeEx(tExNode * curr_line){
	printf("\n printing Type Expression Table");
	while(curr_line->next != NULL){

			printf("%s\t%d\t%s\n",curr_line->name,curr_line->dataType,curr_line->arrType );
			curr_line = curr_line->next;


	}



}
