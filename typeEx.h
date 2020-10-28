//#include "grammar.h"
#include "parsetree1.h"



/*typedef struct TreeNode{
	bool is_terminal;
	Terminal token_name;
	int line_no;
	char name[LEXEME_MAX];
	struct TreeNode* next;
	struct TreeNode* child;

}TreeNode;*/

typedef struct tExNode{
	char name[LEXEME_MAX];
	int dataType;		//primitive,rectangular,jagged
	char arrType[16];		// "static","dynamic","not_applicable

//	union typeEx{
		Terminal Type;		// primitive- INTEGER,REAL,BOOLEAN; RECTANGULAR; JAGGED

	//}uType;
	struct tExNode * next;

}tExNode;
void fill_typeEx( TreeNode* rootptr);
void fill(TreeNode* rootptr,tExNode* temp_tEx);
void print_typeEx(tExNode * curr_line);

//TreeNode * rootptr;
tExNode* currEntry;
tExNode* table_head ;
