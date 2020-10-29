#include "traverseparsetree.h"
//#include "typeEx.h"
int main(){
    printf("Shuru ho chuka h!\n");

    FILE *gptr;                 //Grammar file pointer
    gptr = fopen("grammar.txt", "r");
    grammar(gptr);

    FILE *sptr;                 //Source code file pointer
    sptr = openfile("t6.txt");
    tokenize(sptr);

    root1 = (TreeNode*)malloc(sizeof(TreeNode));
    token *currToken = tokenstream;
    
    root1 -> is_terminal = false;
    root1->dep = 0;
    strcpy(root1->name, "t");
    root1 -> next = NULL;
    root1 -> child = NULL;
    
    ind = 0;//index of type expression table

    createParseTree(root1, currToken, 0);
    //printgrammar();
    //print_tokens(tokenstream);

	//printf("\n\n");
	printparsetree(root1);
    //rootptr = root1;
    //fill_typeEx(rootptr);
    //print_typeEx(table_head);
    return 0;
}
