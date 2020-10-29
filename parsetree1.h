#include "tokenizer.h"

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

}TreeNode;

typedef struct Stacknode{
	node_val node_values;
	struct Stacknode *next;
}Stacknode;

TreeNode* root;

Stacknode* push(Stacknode *head, node_val n);
Stacknode* pop(Stacknode* head);
bool isEmpty(Stacknode *head);
token* createParseTree(TreeNode* root, token *currToken,int depth);
void printparsetree(TreeNode *root1);