/*
Group No 12
ID: 2018A7PS0240P			Name: Akshay Gundewar
ID: 2018A7PS0228P 			Name: Kanishk Patidar
ID: 2018A7PS0282P 			Name: Siddhant Jain
ID: 2018A7PS0339P 			Name: Utkarsh Srivastava
*/


#include "parsetree1.h"
#define TABLE_SIZE 500

type_expression_element type_expression_table[TABLE_SIZE];
int ind;

void traverse(TreeNode *root);
void traverse_declarations(TreeNode *root);
void traverse_decl_statements(TreeNode *root);
void traverse_assignments(TreeNode *root);
void traverse_assignment(TreeNode *root);
typeex check_a_expression(TreeNode* root);
type_expression_element searchfromtable(char *name);
void check_id_or_array(TreeNode *lhs_node);
void printparsetree(TreeNode *root1);
void printtypeexpressiontable();
void printerrors();