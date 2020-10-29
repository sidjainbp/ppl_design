#include "tokenizer.h"




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
    struct td* next;
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
    int tag;
}type_expression_element;

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
    int tag;
	typeex type_exp;
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
