#include"tokenizer.h"

// int main(){
// 	FILE* fptr;
// 	fptr = openfile("test1.txt");
// 	tokenstream = NULL;
// 	tokenize(fptr);
// 	print_tokens(tokenstream);
// 	fclose(fptr);
// }

FILE* openfile(char * filename){  // opens grammar file
	FILE * ptr = fopen(filename, "r");
	if(ptr == NULL)
		perror("fopen");
	return ptr;
}

void tokenize(FILE* ptr){
	char buf[BUF_MAX];
	//char *buf = NULL;
	//int len = BUF_MAX;
	token *traverse = tokenstream;  // traverse points to the last element in the tokenstream
	char *lex; // contains single lexeme from the source code
	
	int line_no = 1;
	while(fgets(buf, sizeof(buf), ptr ) != NULL){
	//while(fscanf(ptr, "%[^\n]", buf) != EOF){
	//while(getline(&buf, &len, ptr) != -1){
		//printf("hello");
		lex = strtok(buf, " \t");
		skipspaces(lex);
		if(strlen(lex) != 0){
			
			if(lex != NULL)
				traverse = addtoken(lex, line_no, traverse);
		}
		while(lex != NULL){
			lex = strtok(NULL, " \t");
			
			if(lex == NULL)
				break;
				
			skipspaces(lex);
			if(strlen(lex) != 0){		
				
				traverse = addtoken(lex, line_no, traverse);
			}
		}
		line_no++;
	}
}

token* addtoken(char * lex, int line_no, token* last_token){
	
	token * new_token = (token*)malloc(sizeof(token));
	
	strcpy(new_token->lexeme,lex);
	new_token->line_no = line_no;
	new_token->next = NULL;
	if(last_token!= NULL){
	last_token->next = new_token;
	}
	else{
		tokenstream = new_token;
	}
	last_token = new_token;
					// updating last token
	
	
	//comparison**********************************************************************
	
	if(strcmp(lex,"program") == 0){
		new_token -> tokenname = PROGRAM;
		
	}
	
	else if(strcmp(lex,"(") == 0){
		new_token -> tokenname = BR_OP;
		
	}
	
	else if(strcmp(lex,")") == 0){
		new_token -> tokenname = BR_CL;
		
	}
	
	else if(strcmp(lex,"{") == 0){
		new_token -> tokenname = CR_OP;
		
	}
	else if(strcmp(lex,"}") == 0){
		new_token -> tokenname = CR_CL;
		
	}
	else if(strcmp(lex,"declare") == 0){
		new_token -> tokenname = DECLARE;
		
	}
	else if(strcmp(lex,":") == 0){
		new_token -> tokenname = COLON;
		
	}
	else if(strcmp(lex,";") == 0){
		new_token -> tokenname = SEMICOLON;
		
	}
	else if(strcmp(lex,"list") == 0){
		new_token -> tokenname = LIST;
		
	}
	else if(strcmp(lex,"of") == 0){
		new_token -> tokenname = OF;
		
	}
	else if(strcmp(lex,"variables") == 0){
		new_token -> tokenname = VARIABLES;
		
	}
	else if(strcmp(lex,"array") == 0){
		new_token -> tokenname = ARRAY;
		
	}
	else if(strcmp(lex,"jagged") == 0){
		new_token -> tokenname = JAGGED;
		
	}
	else if(strcmp(lex,"[") == 0){
		new_token -> tokenname = SQ_OP;
		
	}
	else if(strcmp(lex,"]") == 0){
		new_token -> tokenname = SQ_CL;
		
	}
	else if(strcmp(lex,"size") == 0){
		new_token -> tokenname = SIZE;
		
	}
	else if(strcmp(lex,"values") == 0){
		new_token -> tokenname = VALUES;
		
	}
	else if(strcmp(lex,"..") == 0){
		new_token -> tokenname = DOTDOT;
		
	}else if(strcmp(lex,"integer") == 0){
		new_token -> tokenname = INTEGER;
		
	}else if(strcmp(lex,"real") == 0){
		new_token -> tokenname = REAL;
		
	}else if(strcmp(lex,"boolean") == 0){
		new_token -> tokenname = BOOLEAN;
		
	}else if(strcmp(lex,"=") == 0){
		new_token -> tokenname = ASSIGN_OP;
		
	}else if(strcmp(lex,"+") == 0){
		new_token -> tokenname = PLUS;
		
	}else if(strcmp(lex,"-") == 0){
		new_token -> tokenname = MINUS;
		
	}else if(strcmp(lex,"*") == 0){
		new_token -> tokenname = MULTIPLY;
		
	}else if(strcmp(lex,"/") == 0){
		new_token -> tokenname = DIVIDE;
		
	}else if(strcmp(lex,"|||") == 0){
		new_token -> tokenname = OR;
		
	}else if(strcmp(lex,"R1") == 0){
		new_token -> tokenname = R1;
		
	}
	else if(strcmp(lex,"&&&") == 0){
		new_token -> tokenname = AND;
		
	}
	else if(isdigit(lex[0])){
		new_token -> tokenname = NUMBER;
		
	}else {
		new_token -> tokenname = ID;	
	}
	return last_token;		
}

void tokeniseSourcecode(char *filename){
	FILE *sptr;                 //Source code file pointer
    sptr = openfile(filename);  //arguement as the tc file
    tokenize(sptr);
}
void print_tokens(token* head_token){
	token* temp = head_token;
	while(temp!= NULL){
		printf("\n--------------------------------------------\n");
		printf("%d\t%s\t%d",temp->tokenname,temp->lexeme,temp->line_no);
		temp = temp->next;
			
	}
}





