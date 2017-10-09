/* File ast.h: Abstract-syntax-tree data structure for DJ */

#ifndef AST_H
#define AST_H

#include <stdlib.h>

/* define types of AST nodes */
typedef enum {
  /* program, class, field, and method declarations: */
  PROGRAM, 
  CLASS_DECL_LIST,
  CLASS_DECL,
  VAR_DECL_LIST,
  VAR_DECL,   /* T ID; */
  METHOD_DECL_LIST,
  METHOD_DECL,  /* T ID(T ID) {E} */
  /* types, including generic IDs: */
  NAT_TYPE, 
  AST_ID, 
  /* expression-lists: */
  EXPR_LIST,
  /* expressions: */
  METHOD_CALL_EXPR,  /* F(E) */
//children of FULL_ID_EXPR are (originally dot-separated) AST_IDs
  FULL_ID_EXPR,      /* F */
  ASSIGN_EXPR,       /* F = E */
  PLUS_EXPR,         /* E + E */
  MINUS_EXPR,        /* E - E */
  TIMES_EXPR,        /* E * E */
  EQUALITY_EXPR,     /* E==E */
  GREATER_THAN_EXPR, /* E > E */
  NOT_EXPR,          /* !E */
  AND_EXPR,          /* E&&E */
  IF_THEN_ELSE_EXPR, /* if(E) then {Es} else {Es} */
  WHILE_EXPR,        /* while(E) {Es} */
  PRINT_EXPR,        /* printNat(E) */
  READ_EXPR,         /* readNat() */
  NEW_EXPR,          /* new */
  NULL_EXPR,         /* null */
  NAT_LITERAL_EXPR,  /* N */
} ASTNodeType;

/* define a list of AST nodes */
typedef struct astlistnode {
  struct astnode *data;
  struct astlistnode *next;
} ASTList;

/* define the actual AST nodes */
typedef struct astnode {
  ASTNodeType typ;
  /* list of children nodes: */
  ASTList *children;
  /* node attributes: */
  unsigned int natVal;
  char *idVal;
  /* which source-program line does this node end on: */
  unsigned int lineNumber;
} ASTree;


/* METHODS TO CREATE AND MANIPULATE THE AST */

/* Create a new AST node of type t having only one child.
   (That is, create a one-node list of children for the new tree.)
   If t is NAT_LITERAL_EXPR then the proper natAttribute should be
   given; otherwise natAttribute is ignored.
   If t is AST_ID then the proper idAttribute should be given;
   otherwise idAttribute is ignored.
*/
ASTree *newAST(ASTNodeType t, ASTree *child, unsigned int natAttribute, 
  char *idAttribute, unsigned int lineNum);

/* Prepend an AST node to a parent's list of children */
ASTree *prependToChildrenList(ASTree *childToPrepend, ASTree *parent);

/* Print the AST to stdout with indentations marking tree depth. */
void printAST(ASTree *t);

#endif

