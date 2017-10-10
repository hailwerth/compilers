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

%right ASSIGN NOT LESS DOT
%left PLUS MINUS TIMES AND EQUALITY

%%

pgm : instlist ENDOFFILE 
	{ return 0; }
    ;

instlist : class main
         ;

class : class CLASS ID EXTENDS ID clexp
      |
      ;

/* class expressions */
clexp : LBRACE field RBRACE
      | LBRACE method RBRACE
      | LBRACE field method RBRACE
      | LBRACE RBRACE
      ;

/* field expressions */
field : field NATTYPE ID SEMICOLON
      | field ID ID SEMICOLON
      | NATTYPE ID SEMICOLON
      | ID ID SEMICOLON
      ;

/* method expressions */
method : method ID ID LPAREN pexp RPAREN LBRACE vbexp RBRACE
       | method NATTYPE ID LPAREN pexp RPAREN LBRACE vbexp RBRACE
       | ID ID LPAREN pexp RPAREN LBRACE vbexp RBRACE
       | NATTYPE ID LPAREN pexp RPAREN LBRACE vbexp RBRACE
       ;

/* parameter expressions */
pexp : pexp NATTYPE ID
     | pexp NATTYPE ID COMMA
     | pexp ID ID
     | pexp ID ID COMMA
     | 
     ;

main : MAIN LBRACE vbexp RBRACE
     ;

/* variable expression block */
vbexp : field exp SEMICOLON
      | vbexp exp SEMICOLON
      | exp SEMICOLON
      ;

/* expression list */
elist : elist exp SEMICOLON
      | exp SEMICOLON
      ;

/* argument list */
alist : alist COMMA exp
      | exp
      |
      ;

/* general expressions */
exp : exp PLUS exp
    | exp MINUS exp
    | exp TIMES exp
    | exp EQUALITY exp
    | exp LESS exp
    | NOT exp
    | exp AND exp
    | NATLITERAL
    | NUL
    | IF LPAREN exp RPAREN LBRACE elist RBRACE ELSE LBRACE elist RBRACE
    | WHILE LPAREN exp RPAREN LBRACE elist RBRACE
    | NEW ID LPAREN RPAREN
    | THIS
    | PRINTNAT LPAREN exp RPAREN
    | READNAT LPAREN RPAREN
    | ID
    | exp DOT ID
    | ID ASSIGN exp
    | exp DOT ID ASSIGN exp
    | ID LPAREN alist RPAREN
    | exp DOT ID LPAREN alist RPAREN
    | LPAREN exp RPAREN
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

