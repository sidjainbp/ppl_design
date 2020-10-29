#include "parsetree1.h"
#define TABLE_SIZE 500

enum type{primitive, rectangular, jagged};
enum allocation{_static, dynamic, not_applicable};

typedef struct pri_exp{
    char type[MAX_SIZE];
}pri_exp;

typedef struct dim_range{
    int range_no;
    char l_index[MAX_SIZE];
    char r_index[MAX_SIZE];
    struct dim_range *next;
}dim_range;

typedef struct rect_exp{
    char type[MAX_SIZE];
    int dims;
    dim_range *head;
    char elem_type[MAX_SIZE];
}rect_exp;

typedef struct sd{
    int num;
    struct sd *next;
}sd;

typedef struct jagged_2d_exp{
    char type[MAX_SIZE];
    int dims;
    int fd_l_index;
    int fd_r_index;
    sd *head;
    char elem_type[MAX_SIZE];
}jagged_2d_exp;

typedef struct td{
    int n;
    sd *head;
    td* next;
}td;

typedef struct jagged_3d_exp{
    char type[MAX_SIZE];
    int dims;
    int fd_l_index;
    int fd_r_index;
    td *head;
    char elem_type[MAX_SIZE];
}jagged_3d_exp;

typedef union typeex{
    pri_exp pri;
    rect_exp rect;
    jagged_2d_exp jagged_2d;
    jagged_3d_exp jagged_3d;
}typeex;


typedef struct type_expression_element{                 //row struct in type expression table
	char name[MAX_SIZE];
	enum type _type;
	enum allocation arr_allocation;
    typeex type_exp;
}type_expression_element;

type_expression_element type_expression_table[TABLE_SIZE];
int ind = 0;

void traverse(TreeNode *root);
void traverse_declarations(TreeNode *root);
void traverse_assignments(TreeNode *root);
void traverse_decl_statements(TreeNode *root);
void traverse_assignemnt(TreeNode *root)