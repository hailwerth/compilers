#include "symtbl.h"
#include <stdio.h>
#include <string.h>

//my helper funcs
int getNum(ASTree *t) {
	ASTList *p = t->children;
	int count = 0;
	while(p && p->data) {
		count++;
		p = p->next;
	}
	return count;
}
void getVars(ASTree *t, VarDecl *v, int num) {
	
	ASTList *p = t->children;
	int i;
	for(i = 0; i < num; i++) {

		//gets type and line
		v[i].type = typeNameToNumber(p->data->children->data->idVal);
		v[i].typeLineNumber = p->data->children->data->lineNumber;

		//gets var name and line
		v[i].varName = p->data->children->next->data->idVal;
		v[i].varNameLineNumber = p->data->children->next->data->lineNumber;

		p = p->next;
		//printf("\nvar type = %d, var name = %s\n", v[i].type, v[i].varName);
	}
}

//sets up symbol table
void setupSymbolTables(ASTree *fullProgramAST) {

	//sets wholeprogram global
	wholeProgram = fullProgramAST;

	//gets number of classes, runs num classes
	numClasses = 1;
	ASTList* p = wholeProgram->children->data->children;
	while(p && p->data) {
		numClasses++;
		p = p->next;
	}

	//allocated classesST and sets up object class
	classesST = (ClassDecl*)calloc(numClasses, sizeof(ClassDecl));
	classesST[0].className = "Object";
	classesST[0].classNameLineNumber = -1;
	classesST[0].superclass = -3;
	classesST[0].superclassLineNumber = -1;
	classesST[0].numVars = 0;
	classesST[0].numMethods = 0;

	//gets basic class info and allocates varlist/methlist, runs numClasses-1
	int i, j, check;
	ASTList *mvp;
	p = wholeProgram->children->data->children;
	for(i = 1; i < numClasses; i++) {

		classesST[i].className = p->data->children->data->idVal;
		classesST[i].classNameLineNumber = p->data->children->data->lineNumber;
		classesST[i].numVars = getNum(p->data->children->next->next->data);
		classesST[i].varList = (VarDecl*)calloc(classesST[i].numVars, sizeof(VarDecl));
		classesST[i].numMethods = getNum(p->data->children->next->next->next->data);
		classesST[i].methodList = (MethodDecl*)calloc(classesST[i].numMethods, sizeof(MethodDecl));

		p = p->next;
	}

	//gets super class info and class vars, runs numClasses^2
	p = wholeProgram->children->data->children;
	for(i = 1; i < numClasses; i++) {

		//checks if super exists
		check = 0;
		classesST[i].superclassLineNumber = p->data->children->next->data->lineNumber;
		for(j = 0; j < numClasses; j++) {

			if(!strcmp(p->data->children->next->data->idVal, classesST[j].className)) {
				classesST[i].superclass = j;
				check = 1;
				//printf("\n Class %s super = %d, super name = %s\n", classesST[i].className, classesST[i].superclass, p->data->children->next->data->idVal);
				break;
			}
			//if(i == 0)printf("\nSUPER = %s\n", p->data->children->next->data->idVal);			
		}

		//if super not found, sets to -4
		if(!check)
			classesST[i].superclass = -4;

		//gets class local vars
		getVars(p->data->children->next->next->data, classesST[i].varList, classesST[i].numVars);
		
		p = p->next;
	}

	//gets methods param and locals count, runs # of methods times
	p = wholeProgram->children->data->children;
	for(i = 1; i < numClasses; i++) {

		mvp = p->data->children->next->next->next->data->children;
		for(j = 0; j < classesST[i].numMethods; j++) {

			//gets method name, line, and return type
			classesST[i].methodList[j].methodName = mvp->data->children->next->data->idVal;
			classesST[i].methodList[j].methodNameLineNumber = mvp->data->children->next->data->lineNumber;
			classesST[i].methodList[j].returnType = typeNameToNumber(mvp->data->children->data->idVal);
			//printf("\nmeth name = %s\n", mvp->data->children->next->data->idVal);

			//sets param and local nums, callocs
			classesST[i].methodList[j].numParams = getNum(mvp->data->children->next->next->data);
			classesST[i].methodList[j].numLocals = getNum(mvp->data->children->next->next->next->data);
			classesST[i].methodList[j].paramST = (VarDecl*)calloc(classesST[i].methodList[j].numParams, sizeof(VarDecl));
			classesST[i].methodList[j].localST = (VarDecl*)calloc(classesST[i].methodList[j].numLocals, sizeof(VarDecl));
			//printf("\nparams = %d, locals = %d\n", classesST[i].methodList[j].numParams, classesST[i].methodList[j].numLocals);

			//sets body expr list
			classesST[i].methodList[j].bodyExprs = mvp->data->children->next->next->next->next->data;
			//printf("\nbody type = %d\n", mvp->data->children->next->next->next->next->data->typ);

			//gets params
			getVars(mvp->data->children->next->next->data, classesST[i].methodList[j].paramST, classesST[i].methodList[j].numParams);
			//printf("\nparam type = %d\n", mvp->data->children->next->next->data->typ);

			//gets locals
			getVars(mvp->data->children->next->next->next->data, classesST[i].methodList[j].localST, classesST[i].methodList[j].numLocals);
			//printf("\nlocal type = %d\n", mvp->data->children->next->next->next->data->typ);

			mvp = mvp->next;
		}
		
		p = p->next;
	}

	//sets mainExprs global
	mainExprs = wholeProgram->children->next->next->data;

	//main local count and allocation
	numMainBlockLocals = getNum(wholeProgram->children->next->data);
	mainBlockST = (VarDecl*)calloc(numMainBlockLocals, sizeof(VarDecl));

	//main locals
	getVars(wholeProgram->children->next->data, mainBlockST, numMainBlockLocals);
}

//gets class type to number
int typeNameToNumber(char *typeName) {

	if(!typeName)
		return -1;

	int i;
	for(i = 0; i < numClasses; i++) {
		if(!strcmp(typeName, classesST[i].className))
			return i;
	}
	return -4;
}