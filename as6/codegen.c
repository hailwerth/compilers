/* i pledge my honor that i have not cheated, and will not cheat, on this assignment
Daniel Sawyer */

#include "codegen.h"
#include "symtbl.h"

//GLOBALS
#define MAX_DISM_ADDR 65535
FILE *fout;
unsigned int labelNumber = 0;

//my helper funcs
void codeGenExpr(ASTree *t, int classNumber, int methodNumber);
void codeGenExprs(ASTree *expList, int classNumber, int methodNumber);
int getNumObjectFields(int type);

void generateDISM(FILE *fp) {

	fout = fp;

	//printf("\nFirst mainExprs type %d\n", mainExprs->typ);
}