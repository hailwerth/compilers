/* File symtbl.h: Enhanced symbol-table data structures for DJ */

#ifndef SYMTBL_H
#define SYMTBL_H

#include "ast.h"

/* METHOD TO SETUP GLOBALS (INCLUDING SYMBOL TABLES) */
/* Using the parameter AST representing the whole program, allocate
   and build the global symbol-table data.

   NOTE on typing conventions:
   This compiler represents types as integers.
   The DJ type denoted by int i is:
     The ith class declared in the source program, if i > 0
     Object, if i = 0
     nat, if i = -1
     "any-object" (i.e., the type of "null"), if i = -2
     "no-object" (i.e., the type of Object's superclass), if i = -3
     Undefined (i.e., an illegal type), if i < -3
   When i>=0, the symbol table for type (i.e., class) i is
   at classesST[i].

   NOTE on typechecking:
   This method does NOT perform any checks on the symbol tables
   it builds, although the entry for the Object class
   (in classesST[0]) will of course be free of errors.
   E.g., variable/method/class names may appear multiple times
   in the tables, and types may be invalid.
   If the DJ program declares a variable of an undefined type,
   that type will appear as -4 in the symbol table. */
void setupSymbolTables(ASTree *fullProgramAST);

/* TYPEDEFS FOR ENHANCED SYMBOL TABLES */
/* Encapsulate all information relevant to a DJ variable:
   the variable name, source-program line number on which the
   variable is declared, and the variable type. */
typedef struct vdecls {
  char *varName;
  int varNameLineNumber;
  int type;
} VarDecl;

/* Encapsulate all information relevant to a DJ method:
   the method name, return type, parameter name, parameter type, 
   local variables, and method body. */
typedef struct mdecls {
  char *methodName;
  int methodNameLineNumber;
  int returnType;
  int returnTypeLineNumber;
  char *paramName;
  int paramNameLineNumber;
  int paramType;
  int paramTypeLineNumber;

  //An array of this method's local variables,
  //including the method's parameter
  int numLocals; //size of the array
  VarDecl *localST; //the array itself

  //The method's executable body
  ASTree *bodyExprs; 
} MethodDecl;

/* Encapsulate all information relevant to a DJ class:
   the class name, superclass, and arrays of information
   about the class's variables and methods. */
typedef struct classinfo {
  char *className;
  int classNameLineNumber;
  int superclass;
  int superclassLineNumber;

  //array of variable-field information--the ith element of 
  //the array encapsulates information about the ith
  //variable field in this class
  int numVars;  //size of the array
  VarDecl *varList; //the array itself

  //array of method information--the ith element of the array
  //encapsulates information about the ith method in this class
  int numMethods;  //size of the array
  MethodDecl *methodList; //the array itself
} ClassDecl;

/* GLOBALS THAT GET SET IN setupSymbolTables */
// The entire program's AST
ASTree *wholeProgram;
     
// The expression list in the main block of the DJ program
ASTree *mainExprs; 

// Array (symbol table) of locals in the main block
int numMainBlockLocals;  //size of the array
VarDecl *mainBlockST;  //the array itself
   
// Array (symbol table) of class declarations
// Note that the minimum array size is 1,
//   due to the always-present Object class
int numClasses;  //size of the array
ClassDecl *classesST;  //the array itself

#endif

