/* File ast.h: Abstract-syntax-tree data structure for DJ */

#ifndef AST_H
#define AST_H

#include <stdlib.h>

/* define types of AST nodes */
typedef enum {
  /* program, class, field, method, and parameter declarations: */
  PROGRAM, 
  CLASS_DECL_LIST,
  CLASS_DECL,
  VAR_DECL_LIST,
  VAR_DECL,   
  METHOD_DECL_LIST,
  METHOD_DECL, 
  PARAM_DECL_LIST,
  PARAM_DECL, 
  /* types, including generic IDs: */
  NAT_TYPE, 
  AST_ID, 
  /* expression-lists: */
  EXPR_LIST,
  /* expressions: */
  DOT_METHOD_CALL_EXPR, /* E.ID(As) */
  METHOD_CALL_EXPR,     /* ID(As) */
  DOT_ID_EXPR,          /* E.ID */
  ID_EXPR,              /* ID */
  DOT_ASSIGN_EXPR,      /* E.ID = E */
  ASSIGN_EXPR,          /* ID = E */
  PLUS_EXPR,            /* E + E */
  MINUS_EXPR,           /* E - E */
  TIMES_EXPR,           /* E * E */
  EQUALITY_EXPR,        /* E==E */
  GREATER_THAN_EXPR,    /* E > E */
  NOT_EXPR,             /* !E */
  AND_EXPR,              /* E&&E */
  IF_THEN_ELSE_EXPR,    /* if(E) {Es} else {Es} */
  WHILE_EXPR,           /* while(E) {Es} */
  PRINT_EXPR,           /* printNat(E) */
  READ_EXPR,            /* readNat() */
  THIS_EXPR,            /* this */
  NEW_EXPR,             /* new */
  NULL_EXPR,            /* null */
  NAT_LITERAL_EXPR,     /* N */
  /* argument-lists: */
  ARG_LIST,
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
  ASTList *children; /* head of the list of children */
  ASTList *childrenTail;
  /* node attributes: */
  unsigned int natVal;
  char *idVal;
  /* which source-program line does this node end on: */
  unsigned int lineNumber;
} ASTree;


/* METHODS TO CREATE AND MANIPULATE THE AST */

/* Create a new AST node of type t having only one child.
   (That is, create a one-node list of children for the new tree.)
   If the child argument is NULL, then the single list node in the 
   new AST node's list of children will have a NULL data field.
   If t is NAT_LITERAL_EXPR then the proper natAttribute should be
   given; otherwise natAttribute is ignored.
   If t is AST_ID then the proper idAttribute should be given;
   otherwise idAttribute is ignored.
*/
ASTree *newAST(ASTNodeType t, ASTree *child, unsigned int natAttribute, 
  char *idAttribute, unsigned int lineNum);

/* Append an AST node onto a parent's list of children */
ASTree *appendToChildrenList(ASTree *parent, ASTree *newChild);

/* Print the AST to stdout with indentations marking tree depth. */
void printAST(ASTree *t);

#endif

