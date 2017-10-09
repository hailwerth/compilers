/* DJ PARSER */

%{
  #include <stdio.h> 
  #include "lex.yy.c"
 
  void yyerror(const char *str) {
    printf("Syntax error on line %d at token %s\n",yylineno,yytext);
    printf("(This version of the compiler exits after finding the first ");
    printf("syntax error.)\n");
    exit(-1);
  }
%}

%token MAIN CLASS EXTENDS NATTYPE IF THEN ELSE WHILE 
%token PRINTNAT READNAT NEW VAR NUL NATLITERAL 
%token ID ASSIGN PLUS MINUS TIMES EQUALITY GREATER 
%token AND NOT DOT SEMICOLON LBRACE RBRACE LPAREN 
%token RPAREN ENDOFFILE

%start pgm

%right ASSIGN

%%

pgm : ENDOFFILE 
	{ return 0; }
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

