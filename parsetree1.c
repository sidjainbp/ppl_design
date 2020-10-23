#include<stdio.h>
#include<stdlib.h>
#include"tokenizer.h"
#include"parsetree1.h"
TreeNode* root = NULL;
currToken = NULL;

int main(){}



void push(node_val){
	TreeNode* temp = (TreeNode*) malloc(sizeof(TreeNode));
	temp->node_values = node_val;
	temp->next = head;
	head = temp;


}
void pop(TreeNode* head){
	TreeNode* temp = head;
	head = head->next;
	free(temp);
}
bool isEmpty(TreeNode * head){
	if(head == NULL)
		return true;
	else
		return false;
}
createParseTree(TreeNode* root,Token* currToken){



}


