#include "typecheck.h"

#include <string.h>
#include <stdio.h>

typedef enum {
MULTI_CLASS_DECL
} SemError;

void semerror(SemError er, int l) {
	printf("Semantic analysis error on line %d:\n", l);

	switch(er) {

		case MULTI_CLASS_DECL: printf("Class declared multiple times\n"); break;

		default: printf("Generic Error You Retard\n");
	}
}

void typecheckProgram() {

	//checks class names are unique
	int i, j;
	char *si, *sj;
	for(i = 0; i < numClasses; i++) {

		si = classesST[i].className;
		printf("\nClass Name = %s, Super = %d, SuperLine = %d\n", si, classesST[i].superclass, classesST[i].superclassLineNumber);

		for(j = i+1; j < numClasses; j++) {

			sj = classesST[j].className;

			if(!strcmp(si, sj))
				return semerror(MULTI_CLASS_DECL, classesST[j].classNameLineNumber);
		}
	}


	
}
