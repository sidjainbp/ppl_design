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


void fill_typeEx(TreeNode* rootptr){
  TreeNode* temp_root = rootptr;
  while(temp_root-> name != declarations)
    temp_root = temp_root->next;
  temp_root = temp_root->child->child;   // NT i.e. declaration

  while(temp_root!= NULL){
    scan_declaration(TreeNode* temp_root);
  }





}




void scan_declaration(TreeNode* temp_root){   //temp_root = primitive_list
  tExNode* variables_list = NULL;     //ll of all variables
  if(temp_root == NULL)
      return;
  TreeNode* stat_node = temp_root->child;   //stat_node = declare

  while(stat_node->is_terminal)
      stat_node = stat_node->next;      // id_list
  Terminal curr_dataType;
  typeEx* templist;
  typeEx* temp_templist ;    //head of temp ll
  scan_id(stat_node);
  lastEntry ->next = temp_templist;
  while(temp_templist!= NULL){
    temp_templist->Type = curr_dataType;
    if(curr_dataType == INTEGER|| curr_dataType == BOOLEAN || curr_dataType == REAL){
      temp_templist->dataType = 0;
      temp_templist->arrType = "not_applicable";
    }
    else if (/* condition */) {
      /* code */
    }
    else if () {
      /* code */
    }
  }




/*  while(stat_node->token_name == ID){     //for all tokens

      tExNode* newEntry = (tExNode*) malloc(sizeof(tExNode));
      strcpy(newEntry-> name, stat_node->name);
      if(variables_list== NULL)
          variables_list = newEntry;
      else
          variables_list->next = newEntry;
      stat_node = stat_node->next;
  }
  stat_node = stat_node->next;        // colon to dataType

  if(stat_node-> toke)*/

void scan_id(TreeNode* curr_id){
  if(!curr_id->is_terminal){
    curr_id = curr_id->child;     // id
  while(curr_id->next->token_name == ID)
    tExNode* newEntry = (tExNode*) malloc(sizeof(tExNode));
    strcpy(newEntry-> name, curr_id->name);
    if(templist!= NULL){
        templist-> next = newEntry;    //adding new entry int table
        templist = templist->next;}
    else{
        templist = newEntry;
        temp_templist = templist;     // head of list
      }

  }
  curr_id = curr_id->next; // id_list or COLON
  scan_id(curr_id);
}
else{
      while(curr_id->is_terminal)
        curr_id = curr_id->next;
    // Now at datatype NT
      curr_id= curr_id->child;    //dataType
      curr_dataType = curr_id->token_name;
}

}





}
