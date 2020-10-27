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
		fill_typeEx(tempnode);
		temp_node = temp_node->next;
	}
	
	tExNode* temp_tEx = (tExNode*) malloc(sizeof(tExNode));
	fill(TreeNode* rootptr,tExNode* temp_tEx);


}


 void fill(TreeNode* rootptr,tExNode* temp_tEx){
 	temp_tEx -> name = rootptr -> name;
 	temp_tEx -> typeEx -> Type = rootptr-> token_name; // assuming only 5 of the described values
 	if(temp_tEx-> Type == INTEGER || temp_tEx-> Type == REAL || temp_tEx-> Type == BOOLEAN)
 		{
 			temp_tEx -> dataType = 0;
 			temp_tEx -> arrType = "not_applicable";
 		}
 	else if(temp_tEx -> Type == JAGGED){
 		
 		temp_tEx -> dataType = 2;
 		temp_tEx -> arrType = "not_applicable";
 	 			
 	}
 	else{
 		
 		temp_tEx -> dataType = 1;
 		if(){}
 		
 	
 	
 	}
 
 
 }

