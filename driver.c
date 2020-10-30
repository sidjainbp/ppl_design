/*
Group No 12
ID: 2018A7PS0240P			Name: Akshay Gundewar
ID: 2018A7PS0228P 			Name: Kanishk Patidar
ID: 2018A7PS0282P 			Name: Siddhant Jain
ID: 2018A7PS0339P 			Name: Utkarsh Srivastava
*/

#include "traverseparsetree.h"

int main(int argc,char *argv[]){
    int option=0;
    printf("\nWelcome to our assignment. Please choose your option to execute:-");
    printf("\nInitialising...");
    printf("\nReading grammar.txt and populating the structure...");
    readGrammar("grammar.txt");
    printf("\nGrammar structre successfully created.");
    printf("\n.");
    printf("\n.");
    printf("\nReading source code and populating tokenstream...");
    tokeniseSourcecode(argv[1]);
    //print_tokens(tokenstream);
    printf("\nTokenized the source code successfully.");
    TreeNode* root;
    errind = 0;

    while(true){
        printf("\n.");
        printf("\n.");
        
        printf("\nOption 0: exit");
        printf("\nOption 1: Create parse tree.");
        printf("\nOption 2: Traverse the parse tree and print the type errors.");
        printf("\nOption 3: Print parse tree.");
        printf("\nOption 4: Print typeExpressionTable.");
        printf("\nType the option number(0/1/2/3/4): ");
        scanf("%d",&option);

        if(option < 0 || option > 4){
            printf("\nPlease type a valid option.");
        }else if(option==0){
            printf("\nExiting the execution...");
            printf("\nThank you\n");
            break;
        }else if(option == 1){
            printf("\nCreating parse tree...");
            //create parse tree logic.
            root = (TreeNode*)malloc(sizeof(TreeNode));
            token *currToken = tokenstream;

            root -> is_terminal = false;
            root->dep = 0;
            strcpy(root->name, "t");
            root -> next = NULL;
            root -> child = NULL;

            createParseTree(root, currToken, 0);

            printf("\nParse tree created successfully.");
        }else if(option==2){
            printf("\nTraversing the parse tree...");
            //traverse and error printing logic
            ind = 0;//index of type expression table
            traverse(root);
            printf("\nParse tree traversed successfully.");

            printf("\nThe following errors were found while traversing");
            printerrors();
            printf("\nErrors printed");
        }else if(option==3){
            printf("\nPrinting the parse tree...");
            printparsetree(root);
            printf("\nParse tree printed successfully.");
        }else if(option==4){
            printf("\nPrinting the type expression table...");
            printtypeexpressiontable();
            //print type expression logic
            printf("\nType expression table printed successfully.");
        }
    }
    
    // TreeNode* root;
    // root = (TreeNode*)malloc(sizeof(TreeNode));
    // token *currToken = tokenstream;


    // root -> is_terminal = false;
    // root->dep = 0;
    // strcpy(root->name, "t");
    // root -> next = NULL;
    // root -> child = NULL;

    // //print_tokens(tokenstream);

    // printf("\n\n hello1 ");
    // createParseTree(root, currToken, 0);
    // printf("\n\n hello 2");
    // ind = 0;//index of type expression table
    // printf("\n\n hello 2.1"); 
    // //printparsetree(root);
    // printf("\n\n hello 2.2\n\n");

    // traverse(root);
    // printf("\n\n hello3 ");
    // printtypeexpressiontable();
    // //printparsetree(root);
    // printf("\n\n hello4 ");
    // //printgrammar();
    return 0;
}
