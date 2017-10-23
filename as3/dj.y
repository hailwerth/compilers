/* i pledge my honor that i have not cheated, and will not cheat, on this assignment
Daniel Sawyer */

/* DJ PARSER */

%code provides {
  #include "lex.yy.c"

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
      { return 0; }
    ;

/* class declarations */
cdec : cdec CLASS ID EXTENDS ID LBRACE vardec methdec RBRACE
     | cdec CLASS ID EXTENDS ID LBRACE vardec RBRACE
     |
     ;

/* variable */
var : NATTYPE ID
    | ID ID
    ;

/* var declarations */
vardec : vardec var SEMICOLON
       |
       ;

/* method declarations */
methdec : methdec var LPAREN pdec RPAREN LBRACE vardec elist RBRACE
        | var LPAREN pdec RPAREN LBRACE vardec elist RBRACE
        ;

/* parameter declarations */
pdec : pdec COMMA var
     | var
     |
     ;

/* expression list */
elist : elist expr SEMICOLON
      | expr SEMICOLON
      ;

/* argument expression list */
alist : alist COMMA expr
      | expr
      |
      ;

/* expressions */
expr : expr PLUS expr
     | expr MINUS expr
     | expr TIMES expr
     | expr EQUALITY expr
     | expr LESS expr
     | NOT expr
     | expr AND expr
     | NATLITERAL
     | NUL
     | IF LPAREN expr RPAREN LBRACE elist RBRACE ELSE LBRACE elist RBRACE
     | WHILE LPAREN expr RPAREN LBRACE elist RBRACE
     | NEW ID LPAREN RPAREN
     | THIS
     | PRINTNAT LPAREN expr RPAREN
     | READNAT LPAREN RPAREN
     | ID
     | expr DOT ID
     | ID ASSIGN expr
     | expr DOT ID ASSIGN expr
     | ID LPAREN alist RPAREN
     | expr DOT ID LPAREN alist RPAREN
     | LPAREN expr RPAREN
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
  /* parse the input program */
  return yyparse();
}
