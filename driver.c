#include "traverseparsetree.h"

int main(int argc,char *argv[]){
    int option=0;
    printf("\nInitialising...");
    printf("\nReading grammar.txt and populating the structure...");
    readGrammar("grammar.txt");
    printf("\nGrammar structre successfully created.");
    printf("\n.");
    printf("\n.");
    printf("\nReading source code and populating tokenstream...");
    tokeniseSourcecode(argv[1]);
    printf("\nTokenized the source code successfully.");

    // while(true){
    //     printf("\n.");
    //     printf("\n.");
    //     printf("\nWelcome to our assignment. Please choose your option to execute:-");
    //     printf("\nOption 0: exit");
    //     printf("\nOption 1: Create parse tree.");
    //     printf("\nOption 2: Traverse the parse tree and print the type errors.");
    //     printf("\nOption 3: Print parse tree.");
    //     printf("\nOption 4: Print typeExpressionTable.");
    //     printf("\nType the option number(0/1/2/3/4): ");
    //     scanf("%d",&option);

    //     if(option < 0 || option > 4){
    //         printf("\nPlease type a valid option.");
    //     }else if(option==0){
    //         printf("\nExiting the execution...");
    //         printf("\nThank you.");
    //         break;
    //     }else if(option == 1){
    //         printf("\nCreating parse tree...");
    //         //create parse tree logic.
    //         root = (TreeNode*)malloc(sizeof(TreeNode));
    //         token *currToken = tokenstream;

    //         root -> is_terminal = false;
    //         root->dep = 0;
    //         strcpy(root->name, "t");
    //         root -> next = NULL;
    //         root -> child = NULL;

    //         createParseTree(root, currToken, 0);

    //         printf("\nParse tree created successfully.");
    //     }else if(option==2){
    //         printf("\nTraversing the parse tree...");
    //         //traverse and error printing logic
    //         ind = 0;//index of type expression table
    //         traverse(root);
    //     }else if(option==3){
    //         printf("\nPrinting the parse tree...");
    //         printparsetree(root);
    //     }else if(option==4){
    //         printf("\nPrinting the type expression table...");
    //         //print type expression logic
            
    //     }
    // }
    
    root = (TreeNode*)malloc(sizeof(TreeNode));
    token *currToken = tokenstream;

    root -> is_terminal = false;
    root->dep = 0;
    strcpy(root->name, "t");
    root -> next = NULL;
    root -> child = NULL;

    createParseTree(root, currToken, 0);
    ind = 0;//index of type expression table
    traverse(root);
    printparsetree(root);

    //printgrammar();
    //print_tokens(tokenstream);
	
    return 0;
}