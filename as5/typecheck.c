#include "typecheck.h"

#include <string.h>
#include <stdio.h>

typedef enum {
	MULTI_CLASS_DECL, MULTI_VAR_DECL, CLASS_SUPER, VAR_DECL_TYPE, CLASS_SUPER_SAME, CLASS_VAR_TYPE, METH_RET, METH_VARS, METH_PARAM,

} SemError;

void semerror(SemError er, int l) {
	
	printf("Semantic analysis error on line %d:\n", l);

	switch(er) {

		case MULTI_CLASS_DECL: printf("Class declared multiple times\n"); break;
		case MULTI_VAR_DECL: printf("Variable declared multiple times\n"); break;
		case CLASS_SUPER: printf("Class's Superclass does not exist\n"); break;
		case VAR_DECL_TYPE: printf("Variable's class/object type does not exist\n"); break;
		case CLASS_SUPER_SAME: printf("Class cant be superclass of itself\n"); break;
		case CLASS_VAR_TYPE: printf("Class field type does not exist\n"); break;
		case METH_RET: printf("Method return type does not exist\n"); break;
		case METH_VARS: printf("Method local type does not exist\n"); break;
		case METH_PARAM: printf("Method parameter type does not exist\n"); break;

		default: printf("Generic Error jackoff, add it you retarded person\n");
	}

	return;
}

/* This method performs all typechecking for the entire DJ program. 
   This method assumes setupSymbolTables(), declared in symtbl.h,
   has already executed to set all the global variables (i.e., the 
   enhanced symbol tables) declared in symtbl.h.

   If this method finds a typing error, it reports the error and 
   exits the compiler.
*/
void typecheckProgram() {

	//vars
	int i, j, k;
	char *si, *sj;

	//checks class names are unique, superclasses exist,
	//class and super arent the same, 
	for(i = 0; i < numClasses; i++) {

		si = classesST[i].className;
		//printf("\nClass Name = %s, Super = %d, SuperLine = %d\n", si, classesST[i].superclass, classesST[i].superclassLineNumber);

		for(j = i+1; j < numClasses; j++) {

			sj = classesST[j].className;

			//makes sure class and super arent the same
			if(!i && j == classesST[j].superclass)
				return semerror(CLASS_SUPER_SAME, classesST[j].classNameLineNumber);

			//makes sure superclass exists
			if(!i && classesST[j].superclass < 0)
				return semerror(CLASS_SUPER, classesST[j].classNameLineNumber);

			//makes sure classes are unique
			if(!strcmp(si, sj))
				return semerror(MULTI_CLASS_DECL, classesST[j].classNameLineNumber);
		}

		//checks classes field types
		for(j = 0; j < classesST[i].numVars; j++) {

			if(classesST[i].varList[j].type < -1)
				return semerror(CLASS_VAR_TYPE, classesST[i].varList[j].typeLineNumber);
		}

		//checks methods return, params, and local types exist
		for(j = 0; j < classesST[i].numMethods; j++) {

			//checks return type of method is valid
			if(classesST[i].methodList[j].returnType < -1)
				return semerror(METH_RET, classesST[i].methodList[j].returnTypeLineNumber);

			//checks if meth locals exist
			for(k = 0; k < classesST[i].methodList[j].numLocals; k++) {

				if(classesST[i].methodList[j].localST[k].type < -1)
					return semerror(METH_VARS, classesST[i].methodList[j].localST[k].typeLineNumber);
			}

			//checks method param types exist
			for(k = 0; k < classesST[i].methodList[j].numParams; k++) {

				if(classesST[i].methodList[j].paramST[k].type < -1)
					return semerror(METH_PARAM, classesST[i].methodList[j].paramST[k].typeLineNumber);
			}
		}
	}

	//checking main vars are unique and if class/obj exists
	for(i = 0; i < numMainBlockLocals; i++) {

		si = mainBlockST[i].varName;
		//printf("\nVar = %s, Var Line = %d, Type = %d, Type Line = %d\n", si, mainBlockST[i].varNameLineNumber, mainBlockST[i].type, mainBlockST[i].typeLineNumber);

		//checks first var type exists
		if(!i && mainBlockST[i].type < -1)
			return semerror(VAR_DECL_TYPE, mainBlockST[i].typeLineNumber);

		for(j = i+1; j < numMainBlockLocals; j++) {

			sj = mainBlockST[j].varName;

			//checks the rest of var types exist
			if(!i && mainBlockST[j].type < -1)
				return semerror(VAR_DECL_TYPE, mainBlockST[j].typeLineNumber);

			//checks if unique
			if(!strcmp(si, sj))
				return semerror(MULTI_VAR_DECL, mainBlockST[j].varNameLineNumber);
		}
	}

	//mainExprs
	int temp = typeExprs(mainExprs, -1, -1);


	//debug
	// printAST(mainExprs->children->data->children->data);
	// for(i = 0; i < numClasses; i++) {
	// 	printf("Class %d = %s\n", i, classesST[i].className);
	// }
}


/* HELPER METHODS FOR typecheckProgram(): */

/* Returns nonzero iff sub is a subtype of super */
int isSubtype(int sub, int super) {

	//printf("\nSub = %d, Super = %d\n", sub, super);
	if(sub == super)
		return 1;

	if(sub == 0)
		return 0;

	return isSubtype(classesST[sub].superclass, super);
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

	int mofotype;

	ASTList *p = t->children;

	while(p != NULL) {

		mofotype = typeExpr(p->data, classContainingExprs, methodContainingExprs);
		p = p->next;
	}

	return mofotype;
}