#include "grammar.h"

TreeNode * rootptr = NULL;
tExNode* currEntry = NULL;


/*typedef struct TreeNode{
	bool is_terminal;
	Terminal token_name;		
	int line_no;
	char name[LEXEME_MAX];
	struct TreeNode* next;
	struct TreeNode* child;
	
}TreeNode;*/

typedef struct tExNode{
	char* name[char_max];
	int dataType;		//primitive,rectangular,jagged
	char* arrType;		// "static","dynamic","not_applicable
	
	union typeEx{
		Terminal Type;		// primitive- INTEGER,REAL,BOOLEAN; RECTANGULAR; JAGGED
	
	}
	struct tExNode * next;

}tExNode;

