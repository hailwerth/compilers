#include "typecheck.h"

#include <string.h>
#include <stdio.h>

typedef enum {
	MULTI_CLASS_DECL, MULTI_VAR_DECL, CLASS_SUPER, VAR_DECL_TYPE
} SemError;

void semerror(SemError er, int l) {
	
	printf("Semantic analysis error on line %d:\n", l);

	switch(er) {

		case MULTI_CLASS_DECL: printf("Class declared multiple times\n"); break;
		case MULTI_VAR_DECL: printf("Variable declared multiple times\n"); break;
		case CLASS_SUPER: printf("Class's Superclass does not exist\n"); break;
		case VAR_DECL_TYPE: printf("Variable's class/object type does not exist\n"); break;

		default: printf("Generic Error, add it you retarded person\n");
	}
}

void typecheckProgram() {

	//vars
	int i, j;
	char *si, *sj;

	//checks class names are unique and superclasses exist
	for(i = 0; i < numClasses; i++) {

		si = classesST[i].className;
		//printf("\nClass Name = %s, Super = %d, SuperLine = %d\n", si, classesST[i].superclass, classesST[i].superclassLineNumber);

		if(i > 0 && classesST[i].superclass < 0)
			return semerror(CLASS_SUPER, classesST[i].classNameLineNumber);

		for(j = i+1; j < numClasses; j++) {

			sj = classesST[j].className;

			if(classesST[j].superclass < 0)
				return semerror(CLASS_SUPER, classesST[j].classNameLineNumber);

			if(!strcmp(si, sj))
				return semerror(MULTI_CLASS_DECL, classesST[j].classNameLineNumber);
		}
	}

	//checking main vars are unique and if class/obj exists
	for(i = 0; i < numMainBlockLocals; i++) {

		si = mainBlockST[i].varName;
		//printf("\nVar = %s, Var Line = %d, Type = %d, Type Line = %d\n", si, mainBlockST[i].varNameLineNumber, mainBlockST[i].type, mainBlockST[i].typeLineNumber);

		if(mainBlockST[i].type < -1)
			return semerror(VAR_DECL_TYPE, mainBlockST[i].typeLineNumber);

		for(j = i+1; j < numMainBlockLocals; j++) {

			sj = mainBlockST[j].varName;

			if(mainBlockST[j].type < -1)
				return semerror(VAR_DECL_TYPE, mainBlockST[j].typeLineNumber);

			if(!strcmp(si, sj))
				return semerror(MULTI_VAR_DECL, mainBlockST[j].varNameLineNumber);
		}
	}

}


/* HELPER METHODS FOR typecheckProgram(): */

/* Returns nonzero iff sub is a subtype of super */
int isSubtype(int sub, int super) {

}

/* Returns the type of the expression AST in the given context.
   Also sets t->staticClassNum and t->staticMemberNum attributes as needed.
   If classContainingExpr < 0 then this expression is in the main block of 
   the program; otherwise the expression is in the given class and method. 
*/
int typeExpr(ASTree *t, int classContainingExpr, int methodContainingExpr) {

}

/* Returns the type of the EXPR_LIST AST in the given context. */
int typeExprs(ASTree *t, int classContainingExprs, int methodContainingExprs) {

}