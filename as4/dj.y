/* i pledge my honor that i have not cheated, and will not cheat, on this assignment
Daniel Sawyer */

/* DJ PARSER */

%code provides {
  #include <stdio.h>
  #include "lex.yy.c"
  #include "ast.h"

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
      { $$ = newAST(PROGRAM,$1,NULL,NULL,yylineno); pgmAST = $$; 
        appendToChildrenList($$, $4);
        appendToChildrenList($$, $5);
        return 0; }
    ;

/* class declarations */
cdec : cdec CLASS id EXTENDS id LBRACE vardec methdec RBRACE
       { appendToChildrenList($1, newAST(CLASS_DECL, $3, NULL, NULL, yylineno)); 
         appendToChildrenList($1->childrenTail->data, $5);
         appendToChildrenList($1->childrenTail->data, $7);
         appendToChildrenList($1->childrenTail->data, $8);}
     | cdec CLASS id EXTENDS id LBRACE vardec RBRACE
       { appendToChildrenList($1, newAST(CLASS_DECL, $3, NULL, NULL, yylineno)); 
         appendToChildrenList($1->childrenTail->data, $5);
         appendToChildrenList($1->childrenTail->data, $7);
         appendToChildrenList($1->childrenTail->data, newAST(METHOD_DECL_LIST, NULL, NULL, NULL, yylineno)); }
     |
       { $$ = newAST(CLASS_DECL_LIST, NULL, NULL, NULL, yylineno); }
     ;

/* var declarations */
vardec : vardec nat id SEMICOLON
         { appendToChildrenList($1, newAST(VAR_DECL, $2, NULL, NULL, yylineno)); 
           appendToChildrenList($1->childrenTail->data, $3);}
       | vardec id id SEMICOLON
         { appendToChildrenList($1, newAST(VAR_DECL, $2, NULL, NULL, yylineno));
           appendToChildrenList($1->childrenTail->data, $3);}
       |
         { $$ = newAST(VAR_DECL_LIST, NULL, NULL, NULL, yylineno); }
       ;

nat : NATTYPE
      { $$ = newAST(NAT_TYPE, NULL, NULL, NULL, yylineno); }
    ;

id : ID
     { $$ = newAST(AST_ID, NULL, NULL, yytext, yylineno); }
   ;

/* method declarations */
methdec : methdec nat id LPAREN pdec RPAREN LBRACE vardec elist RBRACE
          { appendToChildrenList($1, newAST(METHOD_DECL, $2, NULL, NULL, yylineno));
            appendToChildrenList($1->childrenTail->data, $3);
            appendToChildrenList($1->childrenTail->data, $5);
            appendToChildrenList($1->childrenTail->data, $8);
            appendToChildrenList($1->childrenTail->data, $9); }
        | methdec id id LPAREN pdec RPAREN LBRACE vardec elist RBRACE
          { appendToChildrenList($1, newAST(METHOD_DECL, $2, NULL, NULL, yylineno));
            appendToChildrenList($1->childrenTail->data, $3);
            appendToChildrenList($1->childrenTail->data, $5);
            appendToChildrenList($1->childrenTail->data, $8);
            appendToChildrenList($1->childrenTail->data, $9); }
        | nat id LPAREN pdec RPAREN LBRACE vardec elist RBRACE
          { $$ = newAST(METHOD_DECL_LIST, newAST(METHOD_DECL, $1, NULL, NULL, yylineno), NULL, NULL, yylineno);
            appendToChildrenList($$->childrenTail->data, $2);
            appendToChildrenList($$->childrenTail->data, $4);
            appendToChildrenList($$->childrenTail->data, $7);
            appendToChildrenList($$->childrenTail->data, $8); }
        | id id LPAREN pdec RPAREN LBRACE vardec elist RBRACE
          { $$ = newAST(METHOD_DECL_LIST, newAST(METHOD_DECL, $1, NULL, NULL, yylineno), NULL, NULL, yylineno);
            appendToChildrenList($$->childrenTail->data, $2);
            appendToChildrenList($$->childrenTail->data, $4);
            appendToChildrenList($$->childrenTail->data, $7);
            appendToChildrenList($$->childrenTail->data, $8); }
        ;

/* parameter declarations */
pdec : pdec COMMA nat id
       { appendToChildrenList($1, newAST(PARAM_DECL, $3, NULL, NULL, yylineno)); 
         appendToChildrenList($1->childrenTail->data, $4); }
     | pdec COMMA id id
       { appendToChildrenList($1, newAST(PARAM_DECL, $3, NULL, NULL, yylineno)); 
         appendToChildrenList($1->childrenTail->data, $4); }
     | nat id
        { $$ = newAST(PARAM_DECL_LIST, newAST(PARAM_DECL, $1, NULL, NULL, yylineno), NULL, NULL, yylineno); 
         appendToChildrenList($$->childrenTail->data, $2); }
     | id id
       { $$ = newAST(PARAM_DECL_LIST, newAST(PARAM_DECL, $1, NULL, NULL, yylineno), NULL, NULL, yylineno); 
         appendToChildrenList($$->childrenTail->data, $2); }
     |
       { $$ = newAST(PARAM_DECL_LIST, NULL, NULL, NULL, yylineno); }
     ;

/* expression list */
elist : elist expr SEMICOLON
        { appendToChildrenList($1, $2); }
      | expr SEMICOLON
        { $$ = newAST(EXPR_LIST, $1, NULL, NULL, yylineno); }
      ;

/* argument expression list */
alist : alist COMMA expr
        { appendToChildrenList($1, $3); }
      | expr
        { $$ = newAST(ARG_LIST, $1, NULL, NULL, yylineno); }
      |
        { $$ = newAST(ARG_LIST, NULL, NULL, NULL, yylineno); }
      ;

/* expressions */
expr : expr PLUS expr
       { $$ = newAST(PLUS_EXPR, $1, NULL, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr MINUS expr
       { $$ = newAST(MINUS_EXPR, $1, NULL, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr TIMES expr
       { $$ = newAST(TIMES_EXPR, $1, NULL, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr EQUALITY expr
       { $$ = newAST(EQUALITY_EXPR, $1, NULL, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr LESS expr
       { $$ = newAST(LESS_THAN_EXPR, $1, NULL, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | NOT expr
       {$$ = newAST(NOT_EXPR, $2, NULL, NULL, yylineno)}
     | expr AND expr
       { $$ = newAST(AND_EXPR, $1, NULL, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | NATLITERAL
       { $$ = newAST(NAT_LITERAL_EXPR, NULL, atoi(yytext), NULL, yylineno); }
     | NUL
       { $$ = newAST(NULL_EXPR, NULL, 0, NULL, yylineno); }
     | IF LPAREN expr RPAREN LBRACE elist RBRACE ELSE LBRACE elist RBRACE
       { $$ = newAST(IF_THEN_ELSE_EXPR, $3, NULL, NULL, yylineno);
         appendToChildrenList($$, $6);
         appendToChildrenList($$, $10); }
     | WHILE LPAREN expr RPAREN LBRACE elist RBRACE
       { $$ = newAST(WHILE_EXPR, $3, NULL, NULL, yylineno);
         appendToChildrenList($$, $6); }
     | NEW id LPAREN RPAREN
       { $$ = newAST(NEW_EXPR, $2, NULL, NULL, yylineno); }
     | THIS
       { $$ = newAST(THIS_EXPR, NULL, NULL, NULL, yylineno); }
     | PRINTNAT LPAREN expr RPAREN
       { $$ = newAST(PRINT_EXPR, $3, NULL, NULL, yylineno); }
     | READNAT LPAREN RPAREN
       { $$ = newAST(READ_EXPR, NULL, NULL, NULL, yylineno); }
     | id
       { $$ = newAST(ID_EXPR, $1, NULL, NULL, yylineno); }
     | expr DOT id
       {$$ = newAST(DOT_ID_EXPR, $1, NULL, NULL, yylineno) ;
        appendToChildrenList($$, $3); }
     | id ASSIGN expr
       { $$ = newAST(ASSIGN_EXPR, $1, NULL, NULL, yylineno);
         appendToChildrenList($$, $3); }
     | expr DOT id ASSIGN expr
       { $$ = newAST(DOT_ASSIGN_EXPR, $1, NULL, NULL, yylineno); 
         appendToChildrenList($$, $3); 
         appendToChildrenList($$, $5); }
     | id LPAREN alist RPAREN
       { $$ = newAST(METHOD_CALL_EXPR, $1, NULL, NULL, yylineno); 
         appendToChildrenList($$, $3); }
     | expr DOT id LPAREN alist RPAREN
       { $$ = newAST(DOT_METHOD_CALL_EXPR, $1, NULL, NULL, yylineno); 
         appendToChildrenList($$, $3);
         appendToChildrenList($$, $5); }
     | LPAREN expr RPAREN
       { $$ = $2; }
     ;

%%

int main(int argc, char **argv) {
  if(argc!=2) {
    printf("Usage: dj-parse filename\n");
    exit(-1);
  }
  yyin = fopen(argv[1],"r");
  if(yyin==NULL) {
    printf("ERROR: could not open file %s\n",argv[1]);
    exit(-1);
  }
  
  int debug=1;
  /*if(argc==3) debug=1;*/

  /* parse and interpret the program */
  yyparse();
  if(debug) {
    /*printf("****** begin abstract syntax tree for DISM program ********\n");*/
    printAST(pgmAST);
    /*printf("******* end abstract syntax tree for DISM program *********\n\n");*/
  }

  /*interpret(pgmAST);*/
  return 0;


  /* parse the input program */
  /*return yyparse();*/
}
