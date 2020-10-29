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