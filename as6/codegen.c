/* i pledge my honor that i have not cheated, and will not cheat, on this assignment
Daniel Sawyer */

#include "codegen.h"
#include "symtbl.h"

//GLOBALS
#define MAX_DISM_ADDR 65535
FILE *fout;
unsigned int SP = 0, FP = 0, HP = 0;
int loopCount = 0, lessCount = 0, equalityCount = 0, andCount = 0, notCount = 0, ifCount = 0;

//my helper funcs
void codeGenExpr(ASTree *t, int classNumber, int methodNumber);
void codeGenExprs(ASTree *expList, int classNumber, int methodNumber);
int getNumObjectFields(int type);
void decSP() {
	--SP;
	fprintf(fout, "mov 1 1       ;DECSP-START\n");
	fprintf(fout, "sub 6 6 1     ;decsp-sub\n");
	fprintf(fout, "blt 6 5 #END  ;decsp-memcheck\n");
	fprintf(fout, "beq 6 5 #END  ;DECSP-END\n\n");
}
void incSP() {
	++SP;
	fprintf(fout, "mov 1 1    ;INCSP-START\n");
	fprintf(fout, "add 6 6 1  ;INCSP-END\n\n");
}
void incHP() {

}
int varNumMain(char *var) {
	int i = 0;
	while(i < numMainBlockLocals) {
		if(!strcmp(var, mainBlockST[i].varName))
			return i;
		i++;
	}
}

void generateDISM(FILE *fp) {

	//sets globals
	fout = fp;
	SP = FP = MAX_DISM_ADDR;
	HP = 0;

	//sets sp, hp, fp
	fprintf(fout, "#INITPTRS: mov 0 0\n");
	fprintf(fout, "mov 5 %d  ;sets HP\n", HP);
	fprintf(fout, "mov 6 %d  ;sets SP\n", SP);
	fprintf(fout, "mov 7 %d  ;sets FP\n\n", FP);

	//sets up main locals
	fprintf(fout, "#INITMAIN: mov 0 0\n");
	int i;
	for(i = 0; i < numMainBlockLocals; i++) {

		fprintf(fout, "str 6 0 0  ;sets main var %d to zero\n", i);
		decSP();
	}

	//main exprs
	fprintf(fout, "#MAINEXPRS: mov 0 0\n");
	codeGenExprs(mainExprs, 0, 0);

	//MAIN END... NIGGA
	fprintf(fout, "mov 1 69\n");
	fprintf(fout, "ptn 1\n");
	fprintf(fout, "ptn 6\n");
	fprintf(fout, "#END: hlt 0  ;END OF PROGRAM\n");
}

//code gen shit
void codeGenExpr(ASTree *t, int classNumber, int methodNumber) {

	int temp;

	switch(t->typ) {

		case ASSIGN_EXPR: //printf("\nIN ASSIGN\n");	
						  if(t->staticClassNum <= 0) {
							temp = varNumMain(t->children->data->idVal);
							codeGenExpr(t->children->next->data, 0, 0);
							fprintf(fout, "mov 0 0    ;ASSIGN-START\n");
							fprintf(fout, "mov 1 %d    ;assign-dest-address\n", MAX_DISM_ADDR - temp);
							fprintf(fout, "lod 2 6 1  ;assign-expr-load\n");
							fprintf(fout, "str 1 0 2  ;ASSIGN-END\n\n");
							break;
						  }

		case ID_EXPR: if(t->staticClassNum <= 0) {
						temp = varNumMain(t->children->data->idVal);
						fprintf(fout, "mov 0 0    ;ID-START-LOCAL\n");
						fprintf(fout, "mov 1 %d    ;id-load-stack-location\n", MAX_DISM_ADDR - temp);
						fprintf(fout, "lod 1 1 0  ;id-load-from-stack\n");
						fprintf(fout, "str 6 0 1  ;ID-END\n\n");
						decSP();
					  }
					  break;

		case PRINT_EXPR: //printf("\nIN PRINT\n");
						 codeGenExpr(t->children->data, classNumber, methodNumber);
						 fprintf(fout, "mov 0 0    ;PRINT-START\n");
						 fprintf(fout, "lod 1 6 1  ;print-ready\n");
						 fprintf(fout, "ptn 1      ;PRINT-END\n\n");
						 break;

		case READ_EXPR: fprintf(fout, "mov 0 0    ;READ-START\n");
						fprintf(fout, "rdn 1      ;reads in\n");
						fprintf(fout, "str 6 0 1  ;READ-END\n\n");
						decSP();
						break;

		case NAT_LITERAL_EXPR: fprintf(fout, "mov 0 0    ;NATLIT-START\n");
							   fprintf(fout, "mov 1 %d    ;natlit-set\n", t->natVal);
							   fprintf(fout, "str 6 0 1  ;NATLIT-END\n\n");
							   decSP();
							   break;

		case PLUS_EXPR: codeGenExpr(t->children->data, classNumber, methodNumber);
						codeGenExpr(t->children->next->data, classNumber, methodNumber);
						fprintf(fout, "mov 0 0    ;PLUS-START\n");
						fprintf(fout, "lod 1 6 2  ;plus-load e1\n");
						fprintf(fout, "lod 2 6 1  ;plus-load e2\n");
						fprintf(fout, "add 1 1 2  ;plus-add e1+e2\n");
						fprintf(fout, "str 6 2 1  ;PLUS-END\n\n");
						incSP();
						break;

		case MINUS_EXPR: codeGenExpr(t->children->data, classNumber, methodNumber);
						 codeGenExpr(t->children->next->data, classNumber, methodNumber);
						 fprintf(fout, "mov 0 0    ;MINUS-START\n");
						 fprintf(fout, "lod 1 6 2  ;minus-load e1\n");
						 fprintf(fout, "lod 2 6 1  ;minus-load e2\n");
						 fprintf(fout, "sub 1 1 2  ;minus-minus e1+e2\n");
						 fprintf(fout, "str 6 2 1  ;MINUS-END\n\n");
						 incSP();
						 break;

		case TIMES_EXPR: codeGenExpr(t->children->data, classNumber, methodNumber);
						 codeGenExpr(t->children->next->data, classNumber, methodNumber);
						 fprintf(fout, "mov 0 0    ;TIMES-START\n");
						 fprintf(fout, "lod 1 6 2  ;times-load e1\n");
						 fprintf(fout, "lod 2 6 1  ;times-load e2\n");
						 fprintf(fout, "mul 1 1 2  ;times-times e1+e2\n");
						 fprintf(fout, "str 6 2 1  ;TIMES-END\n\n");
						 incSP();
						 break;

		case LESS_THAN_EXPR: temp = lessCount++;
							 codeGenExpr(t->children->data, classNumber, methodNumber);
							 codeGenExpr(t->childrenTail->data, classNumber, methodNumber);
							 fprintf(fout, "lod 1 6 2           ;LESS-START-load-e1\n");
							 fprintf(fout, "lod 2 6 1           ;less-load-e2\n");
							 fprintf(fout, "blt 1 2 #LESS%d      ;less-cond-check\n", temp);
							 fprintf(fout, "str 6 2 0           ;less-stores-zero\n");
							 fprintf(fout, "jmp 0 #LESSEND%d     ;less-jmp-to-end\n", temp);
							 fprintf(fout, "#LESS%d: mov 1 1     ;less-sets-1\n", temp);
							 fprintf(fout, "str 6 2 1           ;less-store-1\n");
							 fprintf(fout, "#LESSEND%d: mov 0 0  ;less-end-noop\n", temp);
							 incSP();
							 break;

		case EQUALITY_EXPR: temp = equalityCount++;
							codeGenExpr(t->children->data, classNumber, methodNumber);
							codeGenExpr(t->childrenTail->data, classNumber, methodNumber);
							fprintf(fout, "lod 1 6 2            ;EQUAL-START-load-e1\n");
							fprintf(fout, "lod 2 6 1            ;equal-load-e2\n");
							fprintf(fout, "beq 1 2 #EQUAL%d      ;equal-cond-check\n", temp);
							fprintf(fout, "str 6 2 0            ;equal-stores-zero\n");
							fprintf(fout, "jmp 0 #EQUALEND%d     ;equal-jmp-to-end\n", temp);
							fprintf(fout, "#EQUAL%d: mov 1 1     ;equal-sets-1\n", temp);
							fprintf(fout, "str 6 2 1            ;equal-store-1\n");
							fprintf(fout, "#EQUALEND%d: mov 0 0  ;equal-end-noop\n", temp);
							incSP();
							break;

		case AND_EXPR: temp = andCount++;
					   codeGenExpr(t->children->data, classNumber, methodNumber);
					   codeGenExpr(t->childrenTail->data, classNumber, methodNumber);
					   fprintf(fout, "lod 1 6 2            ;AND-START-load-e1\n");
					   fprintf(fout, "lod 2 6 1            ;and-load-e2\n");
					   fprintf(fout, "mov 3 1              ;and-mov-1-into-r3\n");
					   fprintf(fout, "blt 1 3 #ANDZERO%d    ;and-check-1\n", temp);
					   fprintf(fout, "blt 2 3 #ANDZERO%d    ;and-check-1\n", temp);
					   fprintf(fout, "str 6 2 3            ;and-set-1\n");
					   fprintf(fout, "jmp 0 #ANDEND%d       ;and-jmp-end\n", temp);
					   fprintf(fout, "#ANDZERO%d: str 6 2 0 ;and-set-zero\n", temp);
					   fprintf(fout, "#ANDEND%d: mov 0 0    ;AND-END\n", temp);
					   incSP();
					   break;

		case NOT_EXPR: temp = notCount++;
					   codeGenExpr(t->children->data, classNumber, methodNumber);
					   fprintf(fout, "lod 1 6 1            ;NOT-START-load-expr\n");
					   fprintf(fout, "beq 1 0 #NOT%d        ;not-cond\n", temp);
					   fprintf(fout, "str 6 1 0            ;not-set-zero\n");
					   fprintf(fout, "jmp 0 #NOTEND%d       ;not-jmp-end\n", temp);
					   fprintf(fout, "#NOT%d: mov 1 1       ;not-set-r1=1\n", temp);
					   fprintf(fout, "str 6 1 1            ;not-set-1\n");
					   fprintf(fout, "#NOTEND%d: mov 0 0    ;NOT-END\n", temp);
					   break;

		case IF_THEN_ELSE_EXPR: temp = ifCount++;
								codeGenExpr(t->children->data, classNumber, methodNumber);
								fprintf(fout, "lod 1 6 1      ;IF-START\n");
								fprintf(fout, "beq 1 0 #IF%d   ;if-cond\n", temp);
								//incSP();
								codeGenExprs(t->children->next->data, classNumber, methodNumber);
								fprintf(fout, "jmp 0 #IFEND%d  ;if-jmp-end\n", temp);
								fprintf(fout, "#IF%d: mov 0 0  ;if-else-start\n", temp);
								//incSP();
								codeGenExprs(t->childrenTail->data, classNumber, methodNumber);
								fprintf(fout, "#IFEND%d: mov 0 0 ;IF-END\n", temp);
								break;

		case WHILE_EXPR: temp = loopCount++;
						 fprintf(fout, "#LOOP%d: mov 0 0       ;WHILE-START\n", temp);
						 codeGenExpr(t->children->data, classNumber, methodNumber);
						 fprintf(fout, "mov 1 1               ;while-cond-start\n");
						 fprintf(fout, "lod 2 6 1             ;while-load-conditional-outcome\n");
						 //incSP();
						 fprintf(fout, "blt 2 1 #LOOPEND%d     ;while-cond-end\n", temp);
						 incSP();
						 codeGenExprs(t->childrenTail->data, classNumber, methodNumber);
						 fprintf(fout, "jmp 0 #LOOP%d          ;loop-jmp-end\n", temp);
						 fprintf(fout, "#LOOPEND%d: str 6 1 0  ;WHILE-END\n", temp);
						 break;

		case NEW_EXPR: //lvl3
					   NULL;
					   //lvl2, basically does nothing
					   fprintf(fout, "mov 0 0  ;NEW-START\n");
					   fprintf(fout, "str 6 0 0  ;new-push-0\n");
					   decSP();
					   fprintf(fout, "mov 0 0  ;NEW-END\n");
					   break;

		case NULL_EXPR: fprintf(fout, "mov 0 0    ;NULL-START\n");
						fprintf(fout, "str 6 0 0  ;null-push-zero\n");
						decSP();
						fprintf(fout, "mov 0 0    ;NULL-END\n");
						break;

		default: printf("\nSOMETHING IS FUCKED UP!!! line#%d\n", t->lineNumber);
				 exit(-1);
	}
}

void codeGenExprs(ASTree *expList, int classNumber, int methodNumber) {

	ASTList *p = expList->children;

	while(p && p->data) {
		codeGenExpr(p->data, classNumber, methodNumber);
		//if(p->next && p->next->data)
			incSP();
		p = p->next;
	}
}