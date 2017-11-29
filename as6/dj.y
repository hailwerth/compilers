/* i pledge my honor that i have not cheated, and will not cheat, on this assignment
Daniel Sawyer */

/* DJ PARSER */

%code provides {
  #include <stdio.h>
  #include "lex.yy.c"
  #include "ast.h"
  #include "symtbl.h"
  #include "typecheck.h"
  #include "codegen.h"
  #include <string.h>

  /* Symbols in this grammar are represented as ASTs */ 
  #define YYSTYPE ASTree *

  /* Declare global AST for entire program */
  ASTree *pgmAST;

  /* Function for printing generic syntax-error messages */
  void yyerror(const char *str) {
    printf("Syntax error on line %d at token %s\n",yylineno,yytext);
    printf("(This version of the compiler exits after finding the first ");
    printf("syntax error.)\n");
    exit(-1);
  }
}

%token MAIN CLASS EXTENDS NATTYPE IF ELSE WHILE
%token PRINTNAT READNAT THIS NEW NUL NATLITERAL 
%token ID ASSIGN PLUS MINUS TIMES EQUALITY LESS
%token AND NOT DOT SEMICOLON COMMA LBRACE RBRACE 
%token LPAREN RPAREN ENDOFFILE

%start pgm

/* operator association and precedence */
%right ASSIGN
%left AND
%nonassoc EQUALITY LESS
%left PLUS MINUS
%left TIMES
%right NOT
%left DOT

%%

/* program start */
pgm : cdec MAIN LBRACE vardec elist RBRACE ENDOFFILE 
      { $$ = newAST(PROGRAM,$1,0,NULL,yylineno); pgmAST = $$; 
        appendToChildrenList($$, $4);
        appendToChildrenList($$, $5);
        return 0; }
    ;

/* class declarations */
cdec : cdec CLASS id EXTENDS id LBRACE vardec methdec RBRACE
       { appendToChildrenList($1, newAST(CLASS_DECL, $3, 0, NULL, yylineno)); 
         appendToChildrenList($1->childrenTail->data, $5);
         appendToChildrenList($1->childrenTail->data, $7);
         appendToChildrenList($1->childrenTail->data, $8);}
     | cdec CLASS id EXTENDS id LBRACE vardec RBRACE
       { appendToChildrenList($1, newAST(CLASS_DECL, $3, 0, NULL, yylineno)); 
         appendToChildrenList($1->childrenTail->data, $5);
         appendToChildrenList($1->childrenTail->data, $7);
         appendToChildrenList($1->childrenTail->data, newAST(METHOD_DECL_LIST, NULL, 0, NULL, yylineno)); }
     |
       { $$ = newAST(CLASS_DECL_LIST, NULL, 0, NULL, yylineno); }
     ;

/* var declarations */
vardec : vardec nat id SEMICOLON
         { appendToChildrenList($1, newAST(VAR_DECL, $2, 0, NULL, yylineno)); 
           appendToChildrenList($1->childrenTail->data, $3);}
       | vardec id id SEMICOLON
         { appendToChildrenList($1, newAST(VAR_DECL, $2, 0, NULL, yylineno));
           appendToChildrenList($1->childrenTail->data, $3);}
       |
         { $$ = newAST(VAR_DECL_LIST, NULL, 0, NULL, yylineno); }
       ;

nat : NATTYPE
      { $$ = newAST(NAT_TYPE, NULL, 0, NULL, yylineno); }
    ;

id : ID
     { $$ = newAST(AST_ID, NULL, 0, yytext, yylineno); }
   ;

/* method declarations */
methdec : methdec nat id LPAREN pdec RPAREN LBRACE vardec elist RBRACE
          { appendToChildrenList($1, newAST(METHOD_DECL, $2, 0, NULL, yylineno));
            appendToChildrenList($1->childrenTail->data, $3);
            appendToChildrenList($1->childrenTail->data, $5);
            appendToChildrenList($1->childrenTail->data, $8);
            appendToChildrenList($1->childrenTail->data, $9); }
        | methdec id id LPAREN pdec RPAREN LBRACE vardec elist RBRACE
          { appendToChildrenList($1, newAST(METHOD_DECL, $2, 0, NULL, yylineno));
            appendToChildrenList($1->childrenTail->data, $3);
            appendToChildrenList($1->childrenTail->data, $5);
            appendToChildrenList($1->childrenTail->data, $8);
            appendToChildrenList($1->childrenTail->data, $9); }
        | nat id LPAREN pdec RPAREN LBRACE vardec elist RBRACE
          { $$ = newAST(METHOD_DECL_LIST, newAST(METHOD_DECL, $1, 0, NULL, yylineno), 0, NULL, yylineno);
            appendToChildrenList($$->childrenTail->data, $2);
            appendToChildrenList($$->childrenTail->data, $4);
            appendToChildrenList($$->childrenTail->data, $7);
            appendToChildrenList($$->childrenTail->data, $8); }
        | id id LPAREN pdec RPAREN LBRACE vardec elist RBRACE
          { $$ = newAST(METHOD_DECL_LIST, newAST(METHOD_DECL, $1, 0, NULL, yylineno), 0, NULL, yylineno);
            appendToChildrenList($$->childrenTail->data, $2);
            appendToChildrenList($$->childrenTail->data, $4);
            appendToChildrenList($$->childrenTail->data, $7);
            appendToChildrenList($$->childrenTail->data, $8); }
        ;

/* parameter declarations */
pdec : pdec COMMA nat id
       { appendToChildrenList($1, newAST(PARAM_DECL, $3, 0, NULL, yylineno)); 
         appendToChildrenList($1->childrenTail->data, $4); }
     | pdec COMMA id id
       { appendToChildrenList($1, newAST(PARAM_DECL, $3, 0, NULL, yylineno)); 
         appendToChildrenList($1->childrenTail->data, $4); }
     | nat id
        { $$ = newAST(PARAM_DECL_LIST, newAST(PARAM_DECL, $1, 0, NULL, yylineno), 0, NULL, yylineno); 
         appendToChildrenList($$->childrenTail->data, $2); }
     | id id
       { $$ = newAST(PARAM_DECL_LIST, newAST(PARAM_DECL, $1, 0, NULL, yylineno), 0, NULL, yylineno); 
         appendToChildrenList($$->childrenTail->data, $2); }
     |
       { $$ = newAST(PARAM_DECL_LIST, NULL, 0, NULL, yylineno); }
     ;

/* expression list */
elist : elist expr SEMICOLON
        { appendToChildrenList($1, $2); }
      | expr SEMICOLON
        { $$ = newAST(EXPR_LIST, $1, 0, NULL, yylineno); }
      ;

/* argument expression list */
alist : alist COMMA expr
        { appendToChildrenList($1, $3); }
      | expr
        { $$ = newAST(ARG_LIST, $1, 0, NULL, yylineno); }
      |
        { $$ = newAST(ARG_LIST, NULL, 0, NULL, yylineno); }
      ;

/* expressions */
expr : expr PLUS expr
       { $$ = newAST(PLUS_EXPR, $1, 0, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr MINUS expr
       { $$ = newAST(MINUS_EXPR, $1, 0, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr TIMES expr
       { $$ = newAST(TIMES_EXPR, $1, 0, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr EQUALITY expr
       { $$ = newAST(EQUALITY_EXPR, $1, 0, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr LESS expr
       { $$ = newAST(LESS_THAN_EXPR, $1, 0, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | NOT expr
       {$$ = newAST(NOT_EXPR, $2, 0, NULL, yylineno)}
     | expr AND expr
       { $$ = newAST(AND_EXPR, $1, 0, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | NATLITERAL
       { $$ = newAST(NAT_LITERAL_EXPR, NULL, atoi(yytext), NULL, yylineno); }
     | NUL
       { $$ = newAST(NULL_EXPR, NULL, 0, NULL, yylineno); }
     | IF LPAREN expr RPAREN LBRACE elist RBRACE ELSE LBRACE elist RBRACE
       { $$ = newAST(IF_THEN_ELSE_EXPR, $3, 0, NULL, yylineno);
         appendToChildrenList($$, $6);
         appendToChildrenList($$, $10); }
     | WHILE LPAREN expr RPAREN LBRACE elist RBRACE
       { $$ = newAST(WHILE_EXPR, $3, 0, NULL, yylineno);
         appendToChildrenList($$, $6); }
     | NEW id LPAREN RPAREN
       { $$ = newAST(NEW_EXPR, $2, 0, NULL, yylineno); }
     | THIS
       { $$ = newAST(THIS_EXPR, NULL, 0, NULL, yylineno); }
     | PRINTNAT LPAREN expr RPAREN
       { $$ = newAST(PRINT_EXPR, $3, 0, NULL, yylineno); }
     | READNAT LPAREN RPAREN
       { $$ = newAST(READ_EXPR, NULL, 0, NULL, yylineno); }
     | id
       { $$ = newAST(ID_EXPR, $1, 0, NULL, yylineno); }
     | expr DOT id
       {$$ = newAST(DOT_ID_EXPR, $1, 0, NULL, yylineno) ;
        appendToChildrenList($$, $3); }
     | id ASSIGN expr
       { $$ = newAST(ASSIGN_EXPR, $1, 0, NULL, yylineno);
         appendToChildrenList($$, $3); }
     | expr DOT id ASSIGN expr
       { $$ = newAST(DOT_ASSIGN_EXPR, $1, 0, NULL, yylineno); 
         appendToChildrenList($$, $3); 
         appendToChildrenList($$, $5); }
     | id LPAREN alist RPAREN
       { $$ = newAST(METHOD_CALL_EXPR, $1, 0, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr DOT id LPAREN alist RPAREN
       { $$ = newAST(DOT_METHOD_CALL_EXPR, $1, 0, NULL, yylineno); 
         appendToChildrenList($$, $3);
         appendToChildrenList($$, $5); }
     | LPAREN expr RPAREN
       { $$ = $2; }
     ;

%%

int main(int argc, char **argv) {
  if(argc < 2) {
    printf("Usage: dj-parse filename\n");
    exit(-1);
  }
  yyin = fopen(argv[1],"r");
  if(yyin==NULL) {
    printf("ERROR: could not open file %s\n",argv[1]);
    exit(-1);
  }
  
  //debug flag to print ast  
  int debug=0;
  if(argc==3) debug=1;

  //sets up output dism file bullshit, just changes extension
  FILE *fp;
  int len, i, period = -1, extlen;
  char *newFileName;
  //finds index of last period in filename
  len = strlen(argv[1]);
  for(i = 0; i < len; i++) {
    if(argv[1][i] == '.')
      period = i;
  }
  //if period not there, filename error
  if(period == -1){
    printf("File %s does not have an extension, must be *.dj file\n", argv[1]);
    return -1;
  }
  //error if extension is wrong size or not type .dj
  extlen = len - period - 1;
  if(extlen != 2 || argv[1][period+1] != 'd' || argv[1][period+2] != 'j') {
    printf("File %s must have .dj extension\n", argv[1]);
    return -1;
  }
  //copies everything up until the last period
  newFileName = (char*)calloc(len + 3, 1);
  for(i = 0; i < len; i++) {
    newFileName[i] = argv[1][i];
  }
  //changes extension to dism and opens it for writing
  newFileName[period + 1] = 'd';
  newFileName[period + 2] = 'i';
  newFileName[period + 3] = 's';
  newFileName[period + 4] = 'm';
  newFileName[period + 5] = '\0';
  fp = fopen(newFileName, "w");
  if(!fp) {
    printf("Cant save %s\n", newFileName);
    exit(-1);
  }

  /* parse, symtbl, typecheck, codegen */
  yyparse();
  setupSymbolTables(pgmAST);
  typecheckProgram();
  if(debug)
    printAST(pgmAST);
  generateDISM(fp);

  //closes output file and quits
  fclose(fp);
  fclose(yyin);
  return 0;
}
