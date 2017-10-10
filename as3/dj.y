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

%right ASSIGN NOT LESS DOT COMMA
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

clexp : LBRACE field RBRACE
      | LBRACE method RBRACE
      | LBRACE field method RBRACE
      | LBRACE RBRACE
      ;

field : field NATTYPE ID SEMICOLON
      | field ID ID SEMICOLON
      | NATTYPE ID SEMICOLON
      | ID ID SEMICOLON
      ;

method : method ID ID LPAREN pexp RPAREN LBRACE vbexp RBRACE
       | method NATTYPE ID LPAREN pexp RPAREN LBRACE vbexp RBRACE
       | ID ID LPAREN pexp RPAREN LBRACE vbexp RBRACE
       | NATTYPE ID LPAREN pexp RPAREN LBRACE vbexp RBRACE
       ;

pexp : pexp NATTYPE ID
     | pexp NATTYPE ID COMMA
     | pexp ID ID
     | pexp ID ID COMMA
     | 
     ;

main : MAIN LBRACE vbexp RBRACE
     ;

vbexp : field exp SEMICOLON
      | vbexp exp SEMICOLON
      | exp SEMICOLON
      ;

elist : elist exp SEMICOLON
      | exp SEMICOLON
      ;

alist : alist COMMA exp
      | exp
      ;

exp : NATLITERAL
    | exp PLUS exp
    | exp MINUS exp
    | exp TIMES exp
    | exp EQUALITY exp
    | exp LESS exp
    | NOT exp
    | exp AND exp
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
    | NUL
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

