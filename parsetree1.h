#include "tokenizer.h"
//#include"typeEx.h"
typedef struct node_val{
	bool is_terminal;
	Terminal token_name;
	int line_no;
	char name[LEXEME_MAX];
}node_val;

typedef struct TreeNode{
	bool is_terminal;
	Terminal token_name;		//terminals
	int line_no;
	int dep;
	char name[LEXEME_MAX];
	struct TreeNode* next;
	struct TreeNode* child;
	int is_error;
	typeex type_exp;
}TreeNode;

typedef struct Stacknode{
	node_val node_values;
	struct Stacknode *next;
}Stacknode;

TreeNode* root1;

Stacknode* push(Stacknode *head, node_val n);
Stacknode* pop(Stacknode* head);
bool isEmpty(Stacknode *head);
token* createParseTree(TreeNode* root, token *currToken,int depth);
void printparsetree(TreeNode *root1);
//TreeNode *removechild(root->child);
