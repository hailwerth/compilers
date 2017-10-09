/* File typecheck.h: Typechecker for DJ */

#ifndef TYPECHECK_H
#define TYPECHECK_H 

/* This method performs all typechecking for the entire DJ program. 
   This method assumes setupSymbolTables(), declared in symtbl.h,
   has already executed to set all the global variables (i.e., the 
   enhanced symbol tables) declared in symtbl.h.

   If this method finds a typing error, it reports the error and 
   exits the compiler.
*/
void typecheckProgram();

#endif

