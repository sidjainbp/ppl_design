#include<stdio.h>
#include<stdlib.h>
#include"tokenizer.h"

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
	char name[LEXEME_MAX];
	TreeNode* next;
	TreeNode* child;
	
}TreeNode;

typedef struct StackNode{
	node_val node_values;
	StackNode * next;


}StackNode;

void push(node_val);
void pop(TreeNode* head);
bool isEmpty(TreeNode * head);
createParseTree(TreeNode* root,Token* currToken);

