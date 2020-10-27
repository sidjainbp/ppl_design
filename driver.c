//#include "parsetree1.h"
#include "typeEx.h"
int main(){
    printf("Shuru ho chuka h!\n");

    FILE *gptr;                 //Grammar file pointer
    gptr = fopen("grammar.txt", "r");
    grammar(gptr);

    FILE *sptr;                 //Source code file pointer
    sptr = openfile("t1.txt");
    tokenize(sptr);

    root1 = (TreeNode*)malloc(sizeof(TreeNode));
    token *currToken = tokenstream;

    root1 -> is_terminal = false;
    strcpy(root1->name, "program");
    root1 -> next = NULL;
    root1 -> child = NULL;
    createParseTree(root1, currToken);
    //printgrammar();
    //print_tokens(tokenstream);

	//printf("\n\n");
	//printparsetree(root1);
    rootptr = root1;
    fill_typeEx(rootptr);
    print_typeEx(table_head);
    return 0;
}
