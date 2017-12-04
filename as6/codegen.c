/* i pledge my honor that i have not cheated, and will not cheat, on this assignment
Daniel Sawyer */

#include "codegen.h"
#include "symtbl.h"
#include <string.h>

//GLOBALS
#define MAX_DISM_ADDR 65535
FILE *fout;
unsigned int SP = 0, FP = 0, HP = 0, FPOld = 0;
int loopCount = 0, lessCount = 0, equalityCount = 0, andCount = 0, notCount = 0, ifCount = 0;
int methCount = 0;
// int **vt;

//structs
typedef struct pair{
    int meth, submeth;
}pair;
typedef struct vstruct{
    int sub;
    int mic;
    pair* methpairs;
}vstruct;

//my helper funcs
void codeGenExpr(ASTree *t, int classNumber, int methodNumber);
void codeGenExprs(ASTree *expList, int classNumber, int methodNumber);
void codeGenExprsLeave(ASTree *expList, int classNumber, int methodNumber);
int getNumObjectFields(int type);
void genPrologue(int class, int meth);
void genEpilogue(int class, int meth);
void genVT();
void genArgs(ASTree *t, int classNumber, int methodNumber);
void decSP() {
    --SP;
    fprintf(fout, "mov 1 1       ;DECSP-START\n");
    fprintf(fout, "sub 6 6 1     ;decsp-sub\n");
    fprintf(fout, "blt 6 5 #END  ;decsp-memcheck\n");
    fprintf(fout, "beq 6 5 #END  ;DECSP-END\n");
}
void incSP() {
    ++SP;
    fprintf(fout, "mov 1 1    ;INCSP-START\n");
    fprintf(fout, "add 6 6 1  ;INCSP-END\n");
}
// void incHP() {
//  ++HP;
//  fprintf(fout, "")
// }
int varNumMain(char *var) {
    int i = 0;
    while(i < numMainBlockLocals) {
        if(!strcmp(var, mainBlockST[i].varName))
            return i;
        i++;
    }
    return -4;
}
int varNumMeth(char *var, int c, int m) {
    int i = 0;
    while(i < classesST[c].methodList[m].numLocals) {
        if(!strcmp(var, classesST[c].methodList[m].localST[i].varName))
            return i;
        i++;
    }
    return -4;
}
int varNumMethParam(char *var, int c, int m) {
    int i = 0;
    while(i < classesST[c].methodList[m].numParams) {
        if(!strcmp(var, classesST[c].methodList[m].paramST[i].varName))
            return i;
        i++;
    }
    return -4;
}
int getObjType(char *var) {
    int i = 0;
    while(i < numClasses) {
        if(!strcmp(var, classesST[i].className))
            return i;
        i++;
    }
}
int numFields(int type) {
    int count = 0;
    while(type > 0) {
        count += classesST[type].numVars;
        type = classesST[type].superclass;
    }
    return count;
}
pair methCallClass(char *meth, int c) {
    pair cm;
    int i;
    for(i = 0; i < classesST[c].numMethods; i++) {
        if(!strcmp(meth, classesST[c].methodList[i].methodName)) {
            cm.meth = c;
            cm.submeth = i;
            return cm;
        }
    }
    c = classesST[c].superclass;
    while(c > 0) {
        for(i = 0; i < classesST[c].numMethods; i++) {
            if(!strcmp(meth, classesST[c].methodList[i].methodName)) {
                cm.meth = c;
                cm.submeth = i;
                return cm;
            }
        }

        c = classesST[c].superclass;
    }
    cm.meth = -4;
    cm.submeth = -4;
    return cm;
}

void generateDISM(FILE *fp) {

    //sets globals
    fout = fp;
    SP = FP = MAX_DISM_ADDR;
    HP = 1;

    //sets sp, hp, fp
    fprintf(fout, "#INITPTRS: mov 0 0\n");
    fprintf(fout, "mov 5 %d  ;sets HP\n", HP);
    fprintf(fout, "mov 6 %d  ;sets SP\n", SP);
    fprintf(fout, "mov 7 %d  ;sets FP\n", FP);

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

    //MAIN END
    fprintf(fout, "ptn 6\n"); //debug
    fprintf(fout, "#END: hlt 0  ;END OF PROGRAM\n");

    //setup methods
    int j, temp;
    for(i = 1; i < numClasses; i++) {

        for(j = 0; j < classesST[i].numMethods; j++) {
            fprintf(fout, "#Class%dMethod%d: mov 0 0  ;c%dm%d-setup\n", i, j, i, j);
            genPrologue(i, j);
            
            //pushes old FP
            fprintf(fout, "str 6 0 7\n");
            decSP();
            //FPOld = FP;

            //sets new FP
            //temp = SP + 6 +  classesST[i].methodList[j].numLocals + classesST[i].methodList[j].numParams;
            //printf("\ntemp fp = %d\n", temp);
            //FP = temp;
            fprintf(fout, "mov 1 6\n");
            fprintf(fout, "add 1 1 6\n");
            fprintf(fout, "mov 2 %d\n", classesST[i].methodList[j].numLocals);
            fprintf(fout, "add 1 1 2\n");
            fprintf(fout, "mov 2 %d\n", classesST[i].methodList[j].numParams);
            fprintf(fout, "add 1 1 2\n");
            fprintf(fout, "add 7 1 0\n");

            codeGenExprsLeave(classesST[i].methodList[j].bodyExprs, i, j);

            genEpilogue(i, j);
        }
    }

    //gens vtable vt
    genVT();
}

//code gen shit
void codeGenExpr(ASTree *t, int classNumber, int methodNumber) {

    int temp, type, n;
    pair cm;

    switch(t->typ) {

        case THIS_EXPR: fprintf(fout, "mov 0 0  ;THIS-START\n");
                        
                        //caller heap addr
                        fprintf(fout, "mov 1 1\n");
                        fprintf(fout, "sub 1 7 1\n");
                        fprintf(fout, "lod 2 1 0\n");

                        //put heap addr on the stack
                        fprintf(fout, "str 6 0 2\n");
                        decSP();

                        fprintf(fout, "mov 0 0  ;THIS-END\n");
                        break;

        case METHOD_CALL_EXPR: fprintf(fout, "mov 0 0  ;METH-CALL-START\n");
                               cm = methCallClass(t->children->data->idVal, classNumber);
                               if(cm.meth == -4) {
                                printf("\nERROR: Meth DNE METHOD_CALL_EXPR\n");
                                exit(-1);
                               }

                               //caller heap addr
                               fprintf(fout, "mov 1 1\n");
                               fprintf(fout, "sub 1 7 1\n");
                               fprintf(fout, "lod 2 1 0\n");

                               //stores ra on the stack
                               fprintf(fout, "mov 1 #METHRET%d  ;meth-dot-mov-ra\n", methCount);
                               fprintf(fout, "str 6 0 1  ;meth-dot-push-ra\n");
                               decSP();

                               //pushes dyn caller heap addr on stack
                               fprintf(fout, "str 6 0 2  ;meth-dot-push-caller-addr\n");
                               decSP();

                               //pushes static class
                               fprintf(fout, "mov 1 %d\n", t->staticClassNum);
                               fprintf(fout, "str 6 0 1\n");
                               decSP();

                               //pushes static method number
                               //printf("\nstatic mem# = %d\n", t->staticMemberNum);
                               fprintf(fout, "mov 1 %d\n", t->staticMemberNum);
                               fprintf(fout, "str 6 0 1\n");
                               decSP();

                               genArgs(t->childrenTail->data, classNumber, methodNumber);

                               fprintf(fout, "jmp 0 #Class%dMethod%d\n", cm.meth, cm.submeth);
                               fprintf(fout, "#METHRET%d: mov 0 0  ;METH-DOT-END\n", methCount++);
                               fprintf(fout, "mov 0 0  ;METH-CALL-END\n");
                               break;

        case DOT_METHOD_CALL_EXPR: //if(classNumber <= 0) {
                                    //temp = varNumMain(t->children->data->idVal);
                                    fprintf(fout, "mov 0 0  ;METH-DOT-START\n");
                                    codeGenExpr(t->children->data, classNumber, methodNumber);
                                    fprintf(fout, "lod 2 6 1  ;meth-dot-load-var-addr\n");
                                    fprintf(fout, "beq 0 2 #END  ;meth-dot-null-check\n");

                                    //stores ra on the stack
                                    fprintf(fout, "mov 1 #METHRET%d  ;meth-dot-mov-ra\n", methCount);
                                    fprintf(fout, "str 6 0 1  ;meth-dot-push-ra\n");
                                    //fprintf(fout, "ptn 1\n"); //debug
                                    //fprintf(fout, "sub 7 7 7  ;meth-dot-sets-fp2zero\n");
                                    //fprintf(fout, "add 7 6 0  ;meth-dot-sets-FP=SP\n");
                                    decSP();

                                    //pushes dyn caller heap addr on stack
                                    fprintf(fout, "str 6 0 2  ;meth-dot-push-caller-addr\n");
                                    decSP();

                                    //pushes static class
                                    fprintf(fout, "mov 1 %d\n", t->staticClassNum);
                                    fprintf(fout, "str 6 0 1\n");
                                    decSP();

                                    //pushes static method number
                                    //printf("\nstatic mem# = %d\n", t->staticMemberNum);
                                    fprintf(fout, "mov 1 %d\n", t->staticMemberNum);
                                    fprintf(fout, "str 6 0 1\n");
                                    decSP();

                                    //pushes arglist and arg count
                                    genArgs(t->childrenTail->data, classNumber, methodNumber);

                                    //goes to jmp table
                                    fprintf(fout, "jmp 0 #VTABLE\n");

                                    fprintf(fout, "#METHRET%d: mov 0 0  ;METH-DOT-END\n", methCount++);

                                    break;
                                   //}

        case DOT_ASSIGN_EXPR: fprintf(fout, "mov 0 0  ;DOT-ASSIGN-START\n");
                              codeGenExpr(t->childrenTail->data, classNumber, methodNumber);
                              codeGenExpr(t->children->data, classNumber, methodNumber);
                              //checks for null
                              fprintf(fout, "lod 1 6 1  ;dot-assign-null-check\n");
                              fprintf(fout, "beq 1 0 #END  ;dot-assign-halt-if-null\n");
                              fprintf(fout, "lod 2 6 2  ;dot-assign-load-value2store\n");
                              fprintf(fout, "mov 3 %d    ;dot-assign-offset\n", t->staticMemberNum + 1);
                              fprintf(fout, "sub 1 1 3  ;dot-assign-heap-address2store\n");
                              fprintf(fout, "str 1 0 2  ;dot-assign-store-val\n");
                              incSP();
                              fprintf(fout, "mov 0 0  ;DOT-ASSIGN-END\n");
                              break;

        case DOT_ID_EXPR: fprintf(fout, "mov 0 0  ;DOT-ID-START\n");
                          codeGenExpr(t->children->data, classNumber, methodNumber);
                          fprintf(fout, "lod 1 6 1  ;dot-id-null-check\n");
                          fprintf(fout, "beq 1 0 #END  ;dot-id-halt-if-null\n");
                          fprintf(fout, "mov 2 %d  ;dot-id-sub-num\n", t->staticMemberNum + 1);
                          fprintf(fout, "sub 1 1 2  ;dot-id-heap-address2read\n");
                          //fprintf(fout, "ptn 1\n"); //DEBUG
                          fprintf(fout, "lod 1 1 0   ;dot-id-loads-val\n");
                          fprintf(fout, "str 6 1 1  ;dot-id-push-val-stack\n");
                          fprintf(fout, "mov 0 0  ;DOT-ID-END\n");
                          break;

        case ASSIGN_EXPR: //printf("\nIN ASSIGN\n");    
                          if(t->staticClassNum <= 0) {
                            if(classNumber <= 0) {
                                temp = varNumMain(t->children->data->idVal);
                                fprintf(fout, "mov 0 0    ;ASSIGN-START\n");
                                codeGenExpr(t->children->next->data, 0, 0);
                                fprintf(fout, "mov 1 %d    ;assign-dest-address\n", MAX_DISM_ADDR - temp);
                                fprintf(fout, "lod 2 6 1  ;assign-expr-load\n");
                                fprintf(fout, "str 1 0 2  ;ASSIGN-END\n");
                                break;
                            }
                            
                            temp = varNumMeth(t->children->data->idVal, classNumber, methodNumber);
                            if(temp == -4) {
                                temp = varNumMethParam(t->children->data->idVal, classNumber, methodNumber);
                                if(temp == -4) {
                                    printf("\nID ERROR IN CLASS/METHOD\n");
                                    exit(-1);
                                }
                                temp += 4;
                                fprintf(fout, "mov 0 0    ;ASSIGN-START\n");
                                codeGenExpr(t->children->next->data, classNumber, methodNumber);                                
                                fprintf(fout, "mov 1 %d\n", temp); //offset
                                fprintf(fout, "sub 1 7 1\n"); //addr to store
                                fprintf(fout, "lod 2 6 1\n"); //loads value to store
                                fprintf(fout, "str 1 0 2\n"); //saves
                                fprintf(fout, "mov 0 0    ;ASSIGN-END\n");
                                break;
                            }
                            temp += 5 + classesST[classNumber].methodList[methodNumber].numParams;
                            fprintf(fout, "mov 0 0    ;ASSIGN-START\n");
                            codeGenExpr(t->children->next->data, classNumber, methodNumber);
                            fprintf(fout, "mov 1 %d\n", temp);
                            fprintf(fout, "sub 1 7 1\n");
                            fprintf(fout, "lod 2 6 1\n");
                            fprintf(fout, "str 1 0 2\n");
                            fprintf(fout, "mov 0 0    ;ASSIGN-END\n");
                            break;
                          }

                          fprintf(fout, "mov 0 0    ;ASSIGN-START\n");
                          codeGenExpr(t->children->next->data, classNumber, methodNumber);
                          //printf("\nDEBUG CLASS ASSIGN\n");
                          fprintf(fout, "mov 2 1\n");
                          fprintf(fout, "sub 1 7 2\n");
                          fprintf(fout, "lod 1 1 0\n");
                          fprintf(fout, "mov 2 %d\n", t->staticMemberNum + 1);
                          fprintf(fout, "sub 1 1 2\n");
                          fprintf(fout, "lod 2 6 1\n");
                          fprintf(fout, "str 1 0 2\n");
                          fprintf(fout, "mov 0 0    ;ASSIGN-END\n");
                          break;



        case ID_EXPR: if(t->staticClassNum <= 0 && classNumber <= 0) {
                        temp = varNumMain(t->children->data->idVal);
                        fprintf(fout, "mov 0 0    ;ID-START-LOCAL\n");
                        fprintf(fout, "mov 1 %d    ;id-load-stack-location\n", MAX_DISM_ADDR - temp);
                        fprintf(fout, "lod 1 1 0  ;id-load-from-stack\n");
                        fprintf(fout, "str 6 0 1  ;ID-END\n");
                        decSP();
                        break;
                      }
                      if(t->staticClassNum <= 0 && t->staticMemberNum <= 0 && classNumber > 0) {
                        temp = varNumMeth(t->children->data->idVal, classNumber, methodNumber);
                        //if in params
                        if(temp == -4) {
                            temp = varNumMethParam(t->children->data->idVal, classNumber, methodNumber);
                            if(temp == -4) {
                                printf("\nID ERROR IN CLASS/METHOD\n");
                                exit(-1);
                            }
                            //temp = FP - 4 - temp;
                            temp += 4;
                            fprintf(fout, "mov 1 %d\n", temp);
                            fprintf(fout, "sub 1 7 1\n");
                            fprintf(fout, "lod 1 1 0\n");
                            fprintf(fout, "str 6 0 1\n");
                            decSP();
                            break;
                        }

                        //temp = FP - 5 - classesST[classNumber].methodList[methodNumber].numParams - temp;
                        temp += 5 + classesST[classNumber].methodList[methodNumber].numParams;
                        fprintf(fout, "mov 1 %d\n", temp);
                        fprintf(fout, "sub 1 7 1\n");
                        fprintf(fout, "lod 1 1 0\n");
                        fprintf(fout, "str 6 0 1\n");
                        decSP();
                        break;      
                      }

                      fprintf(fout, "mov 2 1\n");
                      fprintf(fout, "sub 1 7 2\n");
                      fprintf(fout, "lod 1 1 0\n");
                      fprintf(fout, "mov 2 %d\n", t->staticMemberNum + 1);
                      fprintf(fout, "sub 1 1 2\n");
                      fprintf(fout, "lod 1 1 0\n");
                      fprintf(fout, "str 6 0 1\n");
                      decSP();
                      break;
                      

        case PRINT_EXPR: //printf("\nIN PRINT\n");
                         codeGenExpr(t->children->data, classNumber, methodNumber);
                         fprintf(fout, "mov 0 0    ;PRINT-START\n");
                         fprintf(fout, "lod 1 6 1  ;print-ready\n");
                         fprintf(fout, "ptn 1      ;PRINT-END\n");
                         break;

        case READ_EXPR: fprintf(fout, "mov 0 0    ;READ-START\n");
                        fprintf(fout, "rdn 1      ;reads in\n");
                        fprintf(fout, "str 6 0 1  ;READ-END\n");
                        decSP();
                        break;

        case NAT_LITERAL_EXPR: fprintf(fout, "mov 0 0    ;NATLIT-START\n");
                               fprintf(fout, "mov 1 %d    ;natlit-set\n", t->natVal);
                               fprintf(fout, "str 6 0 1  ;NATLIT-END\n");
                               decSP();
                               break;

        case PLUS_EXPR: codeGenExpr(t->children->data, classNumber, methodNumber);
                        codeGenExpr(t->children->next->data, classNumber, methodNumber);
                        fprintf(fout, "mov 0 0    ;PLUS-START\n");
                        fprintf(fout, "lod 1 6 2  ;plus-load e1\n");
                        fprintf(fout, "lod 2 6 1  ;plus-load e2\n");
                        fprintf(fout, "add 1 1 2  ;plus-add e1+e2\n");
                        fprintf(fout, "str 6 2 1  ;PLUS-END\n");
                        incSP();
                        break;

        case MINUS_EXPR: codeGenExpr(t->children->data, classNumber, methodNumber);
                         codeGenExpr(t->children->next->data, classNumber, methodNumber);
                         fprintf(fout, "mov 0 0    ;MINUS-START\n");
                         fprintf(fout, "lod 1 6 2  ;minus-load e1\n");
                         fprintf(fout, "lod 2 6 1  ;minus-load e2\n");
                         fprintf(fout, "sub 1 1 2  ;minus-minus e1+e2\n");
                         fprintf(fout, "str 6 2 1  ;MINUS-END\n");
                         incSP();
                         break;

        case TIMES_EXPR: codeGenExpr(t->children->data, classNumber, methodNumber);
                         codeGenExpr(t->children->next->data, classNumber, methodNumber);
                         fprintf(fout, "mov 0 0    ;TIMES-START\n");
                         fprintf(fout, "lod 1 6 2  ;times-load e1\n");
                         fprintf(fout, "lod 2 6 1  ;times-load e2\n");
                         fprintf(fout, "mul 1 1 2  ;times-times e1+e2\n");
                         fprintf(fout, "str 6 2 1  ;TIMES-END\n");
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
                       fprintf(fout, "lod 1 6 1            ;AND-START-load-e1\n");
                       fprintf(fout, "mov 2 1              ;and-mov-1-into-r3\n");
                       fprintf(fout, "blt 1 2 #ANDZERO%d    ;and-check-1\n", temp);
                       incSP();
                       codeGenExpr(t->childrenTail->data, classNumber, methodNumber);
                       fprintf(fout, "lod 1 6 1            ;AND-START-load-e1\n");
                       fprintf(fout, "mov 2 1              ;and-mov-1-into-r3\n");
                       fprintf(fout, "blt 1 2 #ANDZERO%d    ;and-check-1\n", temp);
                       fprintf(fout, "str 6 1 2            ;and-set-1\n");
                       fprintf(fout, "jmp 0 #ANDEND%d       ;and-jmp-end\n", temp);
                       fprintf(fout, "#ANDZERO%d: str 6 1 0 ;and-set-zero\n", temp);
                       fprintf(fout, "#ANDEND%d: mov 0 0    ;AND-END\n", temp);
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
                       //decSP();
                       break;

        case IF_THEN_ELSE_EXPR: temp = ifCount++;
                                codeGenExpr(t->children->data, classNumber, methodNumber);
                                fprintf(fout, "lod 1 6 1      ;IF-START\n");
                                fprintf(fout, "beq 1 0 #IF%d   ;if-cond\n", temp);
                                //incSP();
                                codeGenExprsLeave(t->children->next->data, classNumber, methodNumber);
                                fprintf(fout, "lod 1 6 1\n");
                                fprintf(fout, "str 6 2 1\n");
                                incSP();
                                fprintf(fout, "jmp 0 #IFEND%d  ;if-jmp-end\n", temp);
                                fprintf(fout, "#IF%d: mov 0 0  ;if-else-start\n", temp);
                                //incSP();
                                codeGenExprsLeave(t->childrenTail->data, classNumber, methodNumber);
                                fprintf(fout, "lod 1 6 1\n");
                                fprintf(fout, "str 6 2 1\n");
                                incSP();
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
                       fprintf(fout, "mov 0 0  ;NEW-START\n");
                       type = getObjType(t->children->data->idVal);
                       n = numFields(type);
                       // if(!(HP + temp + 1 < MAX_DISM_ADDR)) {
                       //      printf("\nError, ran out of memory HP >= SP\n");
                       //      exit(-1);
                       // }
                       fprintf(fout, "mov 1 1  ;new-set-1\n");
                       temp = 0;
                       while(temp < n) {
                            fprintf(fout, "str 5 0 0  ;new-alloc-%d\n", temp);
                            fprintf(fout, "add 5 5 1  ;new-incHP-%d\n", temp);
                            HP++;
                            temp++;
                       }
                       fprintf(fout, "mov 2 %d    ;new-r2=type\n", type);
                       fprintf(fout, "str 5 0 2  ;new-store-type\n");
                       fprintf(fout, "str 6 0 5  ;new-push-stack\n");
                       //fprintf(fout, "ptn 5\n"); //DEBUG
                       fprintf(fout, "add 5 5 1  ;new-incHP\n");
                       HP++;
                       decSP();
                       fprintf(fout, "mov 0 0  ;NEW-END\n");
                       //lvl2, basically does nothing
                       // fprintf(fout, "mov 0 0  ;NEW-START\n");
                       // fprintf(fout, "str 6 0 0  ;new-push-0\n");
                       // decSP();
                       // fprintf(fout, "mov 0 0  ;NEW-END\n");
                       break;

        case NULL_EXPR: fprintf(fout, "mov 0 0    ;NULL-START\n");
                        fprintf(fout, "str 6 0 0  ;null-push-zero\n");
                        decSP();
                        fprintf(fout, "mov 0 0    ;NULL-END\n");
                        break;

        default: printf("\nSOMETHING IS FUCKED UP!!! line#%d, type = %d\n", t->lineNumber, t->typ);
                 exit(-1);
    }
}

//pops the last expr of elist off of stack
void codeGenExprs(ASTree *expList, int classNumber, int methodNumber) {

    ASTList *p = expList->children;

    while(p && p->data) {
        codeGenExpr(p->data, classNumber, methodNumber);
        incSP();
        p = p->next;
    }
}

//leaves last expr of elist on the stack
void codeGenExprsLeave(ASTree *expList, int classNumber, int methodNumber) {

    ASTList *p = expList->children;

    while(p && p->data) {
        codeGenExpr(p->data, classNumber, methodNumber);
        if(p->next && p->next->data)
            incSP();
        p = p->next;
    }
}

void genPrologue(int class, int meth) {

    int i;
    fprintf(fout, "mov 0 0  ;PROLOGUE-START\n");
    for(i = 0; i < classesST[class].methodList[meth].numLocals; i++) {

        fprintf(fout, "str 6 0 0\n");
        decSP();
    }
    fprintf(fout, "mov 0 0  ;PROLOGUE-END\n");
}

void genEpilogue(int class, int meth) {

    fprintf(fout, "mov 0 0  ;EPILOGUE-START\n");
    fprintf(fout, "lod 1 6 1\n"); //result
    fprintf(fout, "lod 2 6 2\n"); //old FP
    fprintf(fout, "lod 3 7 0\n"); //ra

    fprintf(fout, "str 7 0 1\n"); //replaces ra with result
    
    //resets SP to fp
    fprintf(fout, "sub 6 6 6\n");
    fprintf(fout, "add 6 7 0\n");
    //SP = FP;

    //sets fp to old fp
    fprintf(fout, "sub 7 7 7\n");
    fprintf(fout, "add 7 2 0\n");
    //FP = FPOld;

    fprintf(fout, "jmp 3 0  ;EPILOGUE-END\n");
}

void genArgs(ASTree *t, int classNumber, int methodNumber) {

    ASTList *p = t->children;
    int count = 0;
    //printf("\nIN genArgs\n");
    while(p && p->data) {
        codeGenExpr(p->data, classNumber, methodNumber);
        count++;
        p = p->next;
    }

    fprintf(fout, "mov 1 %d  ;arlist-mov-count\n", count);
    fprintf(fout, "str 6 0 1  ;arglist-push-arg-count\n");
    decSP();
}

void genVT() {
    /* gen vtable */

    //get sub class counts
    int **vt;
    int i, j;
    int *subClassCounts = (int*)malloc(sizeof(int)*numClasses);
    memset(subClassCounts, 0, sizeof(int)*numClasses);
    int nextClass;
    for(i = 0; i < numClasses; i++) {

        nextClass = classesST[i].superclass;
        while(nextClass >= 0) {
            subClassCounts[nextClass]++;
            nextClass = classesST[nextClass].superclass;
        }
    }
    // //print subclass counts, DEBUG
    // for(i = 0; i < numClasses; i++)
    //  printf("\nClass %d has %d subclasses\n", i, subClassCounts[i]);

    //gets the actual classes that are subs
    int **subClasses = (int**)malloc(sizeof(int*)*numClasses);
    int temp;
    for(i = 0; i < numClasses; i++) {
        subClasses[i] = (int*)malloc(sizeof(int)*subClassCounts[i]);
        temp = 0;
        for(j = i+1; j < numClasses; j++) {

            if(isSubtype(j, i)) {
                subClasses[i][temp] = j;
                temp++;
            }
        }
    }
    //prints subtypes DEBUG
    // for(i = 0; i < numClasses; i++) {

    //  printf("\nClass %d has subtypes: ", i);
    //  for(j = 0; j < subClassCounts[i]; j++) {
    //      printf("%d ", subClasses[i][j]);
    //  }
    // }
    // printf("\n");

    //finds methods in common
    int **numMethodsIC = (int**)malloc(sizeof(int*)*numClasses);
    for(i = 0; i < numClasses; i++) {
        numMethodsIC[i] = (int*)malloc(sizeof(int)*subClassCounts[i]);
        memset(numMethodsIC[i], 0, sizeof(int)*subClassCounts[i]);
    }

    int k, l;
    for(i = 1; i < numClasses; i++) {

        for(j = 0; j < subClassCounts[i]; j++) {
            temp = subClasses[i][j];

            for(k = 0; k < classesST[i].numMethods; k++) {

                for(l = 0; l < classesST[temp].numMethods; l++) {
                    if(!strcmp(classesST[i].methodList[k].methodName, classesST[temp].methodList[l].methodName)) {
                        numMethodsIC[i][j]++;
                    }
                }
            }
        }
    }
    // for(i = 0; i < numClasses; i++) {

    //  printf("\nClass %d has subtypes (st, mic): ", i);
    //  for(j = 0; j < subClassCounts[i]; j++) {
    //      printf("(%d, %d) ", subClasses[i][j], numMethodsIC[i][j]);
    //  }
    // }
    // printf("\n");

    //malloc final shit
    vstruct **vtable = (vstruct**)malloc(sizeof(vstruct*)*numClasses);
    for(i = 0; i < numClasses; i++) {
        
        vtable[i] = (vstruct*)malloc(sizeof(vstruct)*subClassCounts[i]);
        for(j = 0; j < subClassCounts[i]; j++) {
            vtable[i][j].sub = subClasses[i][j];
            vtable[i][j].mic = numMethodsIC[i][j];

            if(vtable[i][j].mic) {
                
                vtable[i][j].methpairs = (pair*)malloc(sizeof(pair)*vtable[i][j].mic);

                temp = 0;
                for(k = 0; k < classesST[i].numMethods; k++) {

                    for(l = 0; l < classesST[subClasses[i][j]].numMethods; l++) {
                        if(!strcmp(classesST[i].methodList[k].methodName, classesST[subClasses[i][j]].methodList[l].methodName)) {
                            vtable[i][j].methpairs[temp].meth = k;
                            vtable[i][j].methpairs[temp].submeth = l;
                            temp++;
                            break;
                        }
                    }
                }
            }
        }
    }
    //prints vtable info DEBUG
    // for(i = 0; i < numClasses; i++) {

    //  printf("\nClass %d:\n", i);
    //  for(j = 0; j < subClassCounts[i]; j++) {
            
    //      printf("\t%d. Sub %d Meths In Common (meth, submeth):\n", j+1, vtable[i][j].sub);
    //      for(k = 0; k < vtable[i][j].mic; k++) {
    //          printf("\t\t%d. (%d, %d)\n", k+1, vtable[i][j].methpairs[k].meth, vtable[i][j].methpairs[k].submeth);
    //      }
    //  }
    // }

    //create vtable logic using vstruct vtable and subClassesCounts
    int vtsize = 0;
    for(i = 0; i < numClasses; i++) {
        vtsize += (1 + subClassCounts[i]) * classesST[i].numMethods;
    }
    //printf("\nvtsize = %d\n", vtsize);

    vt = (int**)malloc(sizeof(int*)*vtsize);
    for(i = 0; i < vtsize; i++) {
        vt[i] = (int*)malloc(sizeof(int)*5);
        memset(vt[i], 0, sizeof(int)*5);
    }

    int class, meth, flag;
    temp = 0;
    for(i = 0; i < numClasses; i++) {

        for(j = 0; j < classesST[i].numMethods; j++) {

            vt[temp][0] = i;
            vt[temp][1] = j;
            vt[temp][2] = i;
            vt[temp][3] = i;
            vt[temp][4] = j;
            temp++;
            for(k = 0; k < subClassCounts[i]; k++) {

                vt[temp][0] = i;
                vt[temp][1] = j;
                vt[temp][2] = subClasses[i][k];

                flag = 0;
                if(vtable[i][k].mic) {
                    for(l = 0; l < vtable[i][k].mic; l++) {
                        if(j == vtable[i][k].methpairs[l].meth) {
                            flag = 1;
                            class = subClasses[i][k];
                            meth = vtable[i][k].methpairs[l].submeth;
                            break;
                        }
                    }
                }
                if(flag) {
                    vt[temp][3] = class;
                    vt[temp][4] = meth;
                }
                else {
                    vt[temp][3] = i;
                    vt[temp][4] = j;
                }

                temp++;
            }
        }
    }
    //prints vt DEBUG
    // printf("VTABLE:\n");
    // for(i = 0; i < vtsize; i++) {

    //  printf("%d. ", i+1);
    //  for(j = 0; j < 5; j++) {
    //      printf("%d ", vt[i][j]);
    //  }
    //  printf("\n");
    // }

    //gets num static classes in vt
    int check = -1, scCount = 0;
    for(i = 0; i < vtsize; i++) {
        if(check != vt[i][0]) {
            scCount++;
            check = vt[i][0];
        }
    }
    //printf("\nStatic Class Count = %d\n", scCount);
    
    int *vtclist = (int*)malloc(sizeof(int)*scCount);
    check = -1;
    temp = 0;
    for(i = 0; i < vtsize; i++) {
        if(check != vt[i][0]) {
            vtclist[temp++] = vt[i][0];
            check = vt[i][0];
        }   
    }
    // //debug
    // printf("\nClasses in vt: ");
    // for(i = 0; i < scCount; i++) {
    //  printf("%d ", vtclist[i]);
    // }
    // printf("\n");



    //codegens vtable
    int count = 0;
    fprintf(fout, "#VTABLE: mov 0 0 ;VTABLE-START\n");
    
    //gets position on stack
    fprintf(fout, "add 4 6 0\n");
    fprintf(fout, "mov 1 1\n");
    fprintf(fout, "add 4 4 1\n"); //r4 = #arg addr
    fprintf(fout, "lod 1 4 0\n"); //r1 = #args
    //fprintf(fout, "ptn 1\n"); //ptns num args debug
    fprintf(fout, "add 4 4 1\n");

    //sets r3 = static method
    fprintf(fout, "lod 3 4 1\n");

    //sets r2 = static class
    fprintf(fout, "lod 2 4 2\n");

    //sets r1 = dyn type
    fprintf(fout, "lod 1 4 3\n");
    fprintf(fout, "lod 1 1 0\n");

    //debug
    // fprintf(fout, "ptn 1\n");
    // fprintf(fout, "ptn 2\n");
    // fprintf(fout, "ptn 3\n");

    for(i = 0; i < scCount; i++) {
        fprintf(fout, "mov 4 %d\n", vtclist[i]);
        fprintf(fout, "beq 2 4 #VTCLASS%d  ;vt-class-branch\n", vtclist[i]);
    }
    fprintf(fout, "mov 4 777  ;vt-class-dne\n");
    fprintf(fout, "ptn 4\n");
    fprintf(fout, "jmp 0 #END\n");



    for(i = 0; i < scCount; i++) {

        fprintf(fout, "#VTCLASS%d: mov 0 0\n", vtclist[i]);
        for(j = 0; j < classesST[vtclist[i]].numMethods; j++) {

            fprintf(fout, "mov 4 %d\n", j);
            fprintf(fout, "beq 3 4 #VTCLASS%dMETH%d\n", vtclist[i], j);
        }
    }
    fprintf(fout, "mov 4 777  ;vt-class-dne\n");
    fprintf(fout, "ptn 4\n");
    fprintf(fout, "jmp 0 #END  ;vt-meth-dne\n");



    count = 0;
    for(i = 0; i < scCount; i++) {

        for(j = 0; j < classesST[vtclist[i]].numMethods; j++) {

            fprintf(fout, "#VTCLASS%dMETH%d: mov 0 0 \n", vtclist[i], j);

            for(k = 0; k < (1 + subClassCounts[vtclist[i]]); k++) {

                count += k;

                fprintf(fout, "mov 4 %d\n", vt[count][2]);
                fprintf(fout, "beq 1 4 #Class%dMethod%d\n", vt[count][3], vt[count][4]);
            }
            count++;
        }
    }
    fprintf(fout, "mov 4 777  ;vt-class-dne\n");
    fprintf(fout, "ptn 4\n");
    fprintf(fout, "jmp 0 #END\n");
}