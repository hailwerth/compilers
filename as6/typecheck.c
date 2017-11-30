/* i pledge my honor that i have not cheated, and will not cheat, on this assignment
Daniel Sawyer */

#include "typecheck.h"

#include <string.h>
#include <stdio.h>

#define DEBUG printf("\nDUBUG\n");

//error shit
typedef enum {
    MULTI_CLASS_DECL, MULTI_VAR_DECL, CLASS_SUPER, VAR_DECL_TYPE, CLASS_SUPER_SAME, CLASS_VAR_TYPE, METH_RET, METH_VARS, METH_PARAM,
    CLASS_CYCLE, ASSIGN, ID_DNE, NOT, NEW, THIS_MAIN, PLUS, MINUS, TIMES, AND, LESS, EQUALITY, DOT_ID_L, DOT_ID_R, CLASS_VAR_DNE, PRINT,
    DOT_ASSIGN_L, DOT_ASSIGN_R, WHILE, CLASS_VAR_DUPE, CLASS_VAR_DUPE_SUPER, IF_COND, IF_EL, METH_CLASS_UNIQUE, METH_SIG, METH_RET_MIS,
    PARAM_DUPE, METH_LOCAL_DUPE, DOT_METH_CALL, OBJ_INIT
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
        case CLASS_CYCLE: printf("Class has cycle with its super\n"); break;
        case ASSIGN: printf("Assignment to incompatible types\n"); break;
        case ID_DNE: printf("ID never declared\n"); break;
        case NOT: printf("Non-nat type in NOT expression\n"); break;
        case NEW: printf("Invalid class for new expression\n"); break;
        case THIS_MAIN: printf("This cant be used in main\n"); break;
        case PLUS: printf("Plus expression using non-nat types\n"); break;
        case MINUS: printf("Minus expression using non-nat types\n"); break;
        case TIMES: printf("Times expression using non-nat types\n"); break;
        case AND: printf("And expression using non-nat types\n"); break;
        case LESS: printf("Less expression using non-nat types\n"); break;
        case EQUALITY: printf("Equality expression type mismatch\n"); break;
        case DOT_ID_L: printf("Class on left side of dot id invalid type\n"); break;
        case DOT_ID_R: printf("Id in dot id is not valid\n"); break;
        case CLASS_VAR_DNE: printf("Class/Object variable is not valid\n"); break;
        case PRINT: printf("printNat() argument invalid type, must be nat\n"); break;
        case DOT_ASSIGN_L: printf("Class on left side is not valid\n"); break;
        case DOT_ASSIGN_R: printf("Type on right side of assign not compatible with left side\n"); break;
        case WHILE: printf("While conditional isnt type nat\n"); break;
        case CLASS_VAR_DUPE: printf("Class variable duplicate\n"); break;
        case CLASS_VAR_DUPE_SUPER: printf("Class variable duplicate of a superclass\n"); break;
        case IF_COND: printf("If conditional doesn evaluate to a nat type\n"); break;
        case IF_EL: printf("If then-else expr list type mismatch\n"); break;
        case METH_CLASS_UNIQUE: printf("Duplicate method names in class\n"); break;
        case METH_SIG: printf("Duplicate method name with different signature somewhere in superclass\n"); break;
        case METH_RET_MIS: printf("Last method expression is not compatible with its return type\n"); break;
        case PARAM_DUPE: printf("Parameter variable name in method is a duplicate\n"); break;
        case METH_LOCAL_DUPE: printf("Method local variable is a duplicate\n"); break;
        case DOT_METH_CALL: printf("Invalid dot-method call\n"); break;
        case OBJ_INIT: printf("Object hasnt been initialized yet\n"); break;

        default: printf("Generic Error, check line\n");
    }

    exit(-1);
}

//pair type for static and method stuff
typedef struct pair{
    int c, m;
}pair;

//my helper functions
int join(int t1, int t2) {
    if(isSubtype(t1, t2))
        return t2;
    if(isSubtype(t2,t1))
        return t1;
    return join(classesST[t1].superclass, t2);
}
int inMainST(char *var, int l) {
    int i;
    for(i=0; i < numMainBlockLocals; i++) {
        if(!strcmp(var, mainBlockST[i].varName))
            return  mainBlockST[i].type;
    }
    semerror(ID_DNE, l);
    exit(-1);
}
int varHash(char *var, int c) {
    int i;

    if(c == 0)
        return -1;
    
    if(c < 0) {
        for(i=0; i < numMainBlockLocals; i++) {
            if(!strcmp(var, mainBlockST[i].varName)) {
                //mainInits[i] = 1;
                return  i;
            }
        }
    }

    if(c > 0) {
        for(i = 0; i < classesST[c].numVars; i++) {
            if(!strcmp(var, classesST[c].varList[i].varName))
                return i;
        }
    }

    return -1;
}
int inClassST(char *var) {
    int i;
    for(i=0; i < numClasses; i++) {
        if(!strcmp(var, classesST[i].className))
            return i;
    }
    return -1;
}
int varInClass(int c, char* var) {
    
    if(c == 0)
        return -4;

    int i;
    for(i=0;i < classesST[c].numVars; i++) {
        if(!strcmp(classesST[c].varList[i].varName, var)) {
            //printf("\nCLASS VAR TYPE = %d\n", classesST[c].varList[i].type);
            return classesST[c].varList[i].type;
        }
    }

    return varInClass(classesST[c].superclass, var);
}
int varInParam(int c, int m, char* var) {
    int i;
    for(i=0; i < classesST[c].methodList[m].numParams; i++) {
        if(!strcmp(classesST[c].methodList[m].paramST[i].varName, var))
            return classesST[c].methodList[m].paramST[i].type;
    }

    return -4;
}
int varInClassDupeChk(int c, char* var) {
    
    if(c == 0)
        return 0;

    int i;
    for(i=0;i < classesST[c].numVars; i++) {
        if(!strcmp(classesST[c].varList[i].varName, var)) {
            //printf("\nCLASS VAR TYPE = %d\n", classesST[c].varList[i].type);
            return 1;
        }
    }

    return varInClassDupeChk(classesST[c].superclass, var);
}
int methUnique(int c, MethodDecl meth) {

    if(c == 0)
        return 0;
    int i, j, k, temp;
    for(i=0; i < classesST[c].numMethods; i++) {
        if(!strcmp(classesST[c].methodList[i].methodName, meth.methodName)) {
            k = 0;
            if(classesST[c].methodList[i].returnType == meth.returnType)
            if(classesST[c].methodList[i].numParams == meth.numParams) {
                k = 1;
                for(j=0; j < meth.numParams; j++) {

                    if(classesST[c].methodList[i].paramST[j].type != meth.paramST[j].type)
                        k = 0;
                }
                if(!k) return 1;
            }
            if(!k) return 1;
        }
    }

    return methUnique(classesST[c].superclass, meth);
}
int varInMeth(int c, int m, char *var) {
    int i;
    for(i=0; i < classesST[c].methodList[m].numLocals; i++) {
        if(!strcmp(classesST[c].methodList[m].localST[i].varName, var))
            return classesST[c].methodList[m].localST[i].type;
    }
    
    return -4;
}
int varInMethNum(int c, int m, char *var) {
    int i;
    for(i=0; i < classesST[c].methodList[m].numLocals; i++) {
        if(!strcmp(classesST[c].methodList[m].localST[i].varName, var))
            return i;
    }
    
    return -4;
}
pair methInClass(int c, char *var, ASTree* argl, int ogclass, int ogmeth) {
    pair ar;
    if(c == 0) {
        ar.c = -1;
        ar.m = -1;
        return ar;
    }
    int i, j, k, temp, argtype, sub;
    
    ASTList *p = argl->children;
    for(i=0; p && p->data; i++, p = p->next){;}
    //printf("\n c = %d\n", c);
    temp = i;

    for(i=0; i < classesST[c].numMethods; i++) {
        if(!strcmp(classesST[c].methodList[i].methodName, var)) {
            //printf("\nvar = %s, numParams = %d, temp = %d\n", var, classesST[c].methodList[i].numParams, temp);
            if(classesST[c].methodList[i].numParams == temp) {
                k = 1;
                ar.c = c;
                ar.m = i;
                p = argl->children;
                for(j=0; j < temp; j++) {
                    argtype = typeExpr(p->data, ogclass, ogmeth);
                    sub = 0;
                    if(classesST[c].methodList[i].paramST[j].type > -1) sub = isSubtype(argtype, classesST[c].methodList[i].paramST[j].type);
                    //printf("\nmeth parm type = %d, argtype = %d \n", classesST[c].methodList[i].paramST[j].type, argtype);
                    if(classesST[c].methodList[i].paramST[j].type != argtype && !sub) {
                        
                        k = 0;
                    }
                    p = p->next;
                }
                if(k) return ar;
            }
        }
    }

    return methInClass(classesST[c].superclass, var, argl, ogclass, ogmeth);
}

//checks if var is in class or super class
pair findVarInSuper(char *var, int c) {

    int i;
    pair cm;
    cm.c = -1;
    cm.m = -1;
    while(c != 0) {

        for(i = 0; i < classesST[c].numVars; i++) {
            if(!strcmp(classesST[c].varList[i].varName, var)) {
                cm.c = c;
                cm.m = i;
                return cm;
            }
        }
        c = classesST[c].superclass;
    }
    return cm;
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
    int i, j, k, l;
    char *si, *sj;
    
    //checks class names are unique, superclasses exist,
    //class and super arent the same. checks for cycles 
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

            //checks for cycles
            // if(isSubtype(i, j) && isSubtype(j, i))
            //     return semerror(CLASS_CYCLE, classesST[i].superclassLineNumber);
        }

        //checks for cycles
        if(!isSubtype(i, 0))
            return semerror(CLASS_CYCLE, classesST[i].superclassLineNumber);

        //checks classes field types
        for(j = 0; j < classesST[i].numVars; j++) {

            if(classesST[i].varList[j].type < -1)
                return semerror(CLASS_VAR_TYPE, classesST[i].varList[j].typeLineNumber);
        }

        //checks methods return, params, and local types are valid
        for(j = 0; j < classesST[i].numMethods; j++) {

            //checks return type of method is valid
            if(classesST[i].methodList[j].returnType < -1)
                return semerror(METH_RET, classesST[i].methodList[j].returnTypeLineNumber);

            //checks if meth locals are valid
            for(k = 0; k < classesST[i].methodList[j].numLocals; k++) {

                if(classesST[i].methodList[j].localST[k].type < -1)
                    return semerror(METH_VARS, classesST[i].methodList[j].localST[k].typeLineNumber);
            }

            //checks method param types are valid
            for(k = 0; k < classesST[i].methodList[j].numParams; k++) {

                if(classesST[i].methodList[j].paramST[k].type < -1)
                    return semerror(METH_PARAM, classesST[i].methodList[j].paramST[k].typeLineNumber);
            }
        }
    }

    //check class/subclass variables are unique
    for(i = 0; i < numClasses; i++) {

        for(j = 0; j < classesST[i].numVars; j++) {

            //checks locals are unique
            for(k = j+1; k < classesST[i].numVars; k++) {

                if(!strcmp(classesST[i].varList[j].varName, classesST[i].varList[k].varName))
                    semerror(CLASS_VAR_DUPE, classesST[i].varList[k].varNameLineNumber);
            }

            //checks super classes are unique
            if(varInClassDupeChk(classesST[i].superclass, classesST[i].varList[j].varName))
                semerror(CLASS_VAR_DUPE_SUPER, classesST[i].varList[j].varNameLineNumber);
        }
    }

    //check methods signatures are unique
    for(i = 0; i < numClasses; i++) {

        for(j = 0; j < classesST[i].numMethods; j++) {

            //checks that methods within same class are unique
            for(k = j+1; k < classesST[i].numMethods; k++) {

                if(!strcmp(classesST[i].methodList[j].methodName, classesST[i].methodList[k].methodName)) {
                    semerror(METH_CLASS_UNIQUE, classesST[i].methodList[k].methodNameLineNumber);
                }
            }
            
            //checks meth sig against super classes
            k = methUnique(classesST[i].superclass, classesST[i].methodList[j]);
            if(k)
                semerror(METH_SIG, classesST[i].methodList[j].methodNameLineNumber);
            
            //checks if method return types match with end of elist and method exprs    
            k = typeExprs(classesST[i].methodList[j].bodyExprs, i, j);
            //DEBUG
            //printf("\nreturn type = %d, k = %d\n", classesST[i].methodList[j].returnType, k);
            if(classesST[i].methodList[j].returnType != k && !(isSubtype(k, classesST[i].methodList[j].returnType)))
                semerror(METH_RET_MIS, classesST[i].methodList[j].bodyExprs->childrenTail->data->lineNumber);
            //DEBUG
        }
    }

    //checks method locals/params are unique
    for(i = 0; i < numClasses; i++) {

        for(j = 0; j < classesST[i].numMethods; j++) {

            for(k = 0; k < classesST[i].methodList[j].numParams; k++) {

                for(l = k+1; l < classesST[i].methodList[j].numParams; l++) {
                    if(!strcmp(classesST[i].methodList[j].paramST[k].varName, classesST[i].methodList[j].paramST[l].varName))
                        semerror(PARAM_DUPE, classesST[i].methodList[j].paramST[l].varNameLineNumber);

                }
                //DEBUG
                l = varInMethNum(i, j, classesST[i].methodList[j].paramST[k].varName);
                if(l != -4)
                    semerror(PARAM_DUPE, classesST[i].methodList[j].localST[l].varNameLineNumber);
            }

            for(k = 0; k < classesST[i].methodList[j].numLocals; k ++) {
                for(l = k+1; l < classesST[i].methodList[j].numLocals; l++) {
                    if(!strcmp(classesST[i].methodList[j].localST[k].varName, classesST[i].methodList[j].localST[l].varName))
                        semerror(METH_LOCAL_DUPE, classesST[i].methodList[j].localST[l].varNameLineNumber);
                }
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
    
    typeExprs(mainExprs, -1, -1);
}


/* HELPER METHODS FOR typecheckProgram(): */
int isSubtype(int sub, int super) {

    if(sub == -1 || super == -1)
        return 0;
    if(sub == -2)
        return 1;
    if(sub == super)
        return 1;
    if(sub == 0)
        return 0;
    if(super == -2)
        return 0;

    int ar[numClasses];
    memset(ar, 0, sizeof(int)*numClasses);
    while(sub != super) {
        if(ar[sub])
            return 0;
        ar[sub] = 1;
        sub = classesST[sub].superclass;
    }
    return 1;
}

/* Returns the type of the expression AST in the given context.
   Also sets t->staticClassNum and t->staticMemberNum attributes as needed.
   If classContainingExpr < 0 then this expression is in the main block of 
   the program; otherwise the expression is in the given class and method. 
*/
int typeExpr(ASTree *t, int classContainingExpr, int methodContainingExpr) {

    int lhs, rhs, mid;
    ASTList *p;
    pair cm;

    switch(t->typ) {

        case ASSIGN_EXPR: if(classContainingExpr < 0) {
                            t->staticClassNum = 0;
                            t->staticMemberNum = 0;
                          }

                          else {
                            t->staticClassNum = classContainingExpr;
                            cm = findVarInSuper(t->children->data->idVal, classContainingExpr);
                            if(cm.c == -1) {
                                t->staticClassNum = 0;
                                t->staticMemberNum = 0;
                            }
                            else {
                                t->staticClassNum = cm.c;
                                t->staticMemberNum = cm.m;
                            }
                          }
                          
                          rhs = typeExpr(t->children->next->data, classContainingExpr, methodContainingExpr);
                          lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);

                          if(lhs == rhs || isSubtype(rhs, lhs)) return lhs;
                          semerror(ASSIGN, t->lineNumber);

        case PLUS_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                        rhs = typeExpr(t->children->next->data, classContainingExpr, methodContainingExpr);
                        if(lhs == -1 && rhs == -1)
                            return lhs;
                        semerror(PLUS, t->lineNumber);

        case MINUS_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                         rhs = typeExpr(t->children->next->data, classContainingExpr, methodContainingExpr);
                         if(lhs == -1 && rhs == -1)
                             return lhs;
                         semerror(MINUS, t->lineNumber);

        case TIMES_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                         rhs = typeExpr(t->children->next->data, classContainingExpr, methodContainingExpr);
                         if(lhs == -1 && rhs == -1)
                             return lhs;
                         semerror(TIMES, t->lineNumber);

        case AND_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                       rhs = typeExpr(t->children->next->data, classContainingExpr, methodContainingExpr);
                       if(lhs == -1 && rhs == -1)
                          return lhs;
                       semerror(AND, t->lineNumber);

        case LESS_THAN_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                         rhs = typeExpr(t->children->next->data, classContainingExpr, methodContainingExpr);
                         if(lhs == -1 && rhs == -1)
                             return lhs;
                         semerror(LESS, t->lineNumber);

        case EQUALITY_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                            rhs = typeExpr(t->children->next->data, classContainingExpr, methodContainingExpr);
                            //printf("\nequality lhs = %d, rhs = %d\n", lhs, rhs);
                            if(lhs == -1 && rhs == -1)
                                return lhs;
                            if(isSubtype(lhs, rhs) || isSubtype(rhs, lhs))
                               return -1;
                            semerror(EQUALITY, t->lineNumber);

        case DOT_ID_EXPR: //printf("\nIN DOT_ID_EXPR\n");
                          lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                          if(lhs < 0) semerror(DOT_ID_L, t->lineNumber);
                          t->staticClassNum = lhs;
                          if(t->children->data->typ == THIS_EXPR) {

                            rhs = typeExpr(t->children->next->data, lhs, -1);
                            
                            t->staticMemberNum = varHash(t->childrenTail->data->idVal, lhs);
                            //printf("\nIN DOT_ID_EXPR\n");
                          }
                          else { 
                            rhs = typeExpr(t->children->next->data, lhs, methodContainingExpr);
                          
                            t->staticMemberNum = varHash(t->childrenTail->data->idVal, lhs);
                          }

                          if(t->staticMemberNum == -1) {
                            cm = findVarInSuper(t->childrenTail->data->idVal, classesST[lhs].superclass);
                            t->staticClassNum = cm.c;
                            t->staticMemberNum = cm.m;
                          }

                          if(rhs > -2)
                            return rhs;
                          semerror(DOT_ID_R, t->lineNumber);

        case DOT_ASSIGN_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                              if(lhs < 0) semerror(DOT_ASSIGN_L, t->lineNumber);
                              mid = typeExpr(t->children->next->data, lhs, methodContainingExpr);
                              rhs = typeExpr(t->childrenTail->data, classContainingExpr, methodContainingExpr);

                              cm = findVarInSuper(t->children->next->data->idVal, lhs);
                              t->staticClassNum = cm.c;
                              t->staticMemberNum = cm.m;

                              if(mid == rhs || isSubtype(rhs, mid)) return rhs;
                              semerror(DOT_ASSIGN_R, t->lineNumber);

        case DOT_METHOD_CALL_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr); 
                                   if(lhs < 0) semerror(DOT_METH_CALL, t->children->data->lineNumber);
                                   //printf("\nlhs type = %d\n", lhs);
                                   //DEBUG
                                   rhs = typeExpr(t->childrenTail->data, classContainingExpr, methodContainingExpr);
                                   //DEBUG
                                   cm = methInClass(lhs, t->children->next->data->idVal, t->childrenTail->data, classContainingExpr, methodContainingExpr);
                                   //DEBUG
                                   if(cm.c == -1) semerror(DOT_METH_CALL, t->lineNumber);
                                   //DEBUG

                                   t->staticClassNum = cm.c;
                                   t->staticMemberNum = cm.m;

                                   return classesST[cm.c].methodList[cm.m].returnType;
                                   //return lhs;

        case METHOD_CALL_EXPR: lhs = classContainingExpr;
                               if(lhs < 0) semerror(-1, t->lineNumber);
                               rhs = typeExpr(t->childrenTail->data, classContainingExpr, methodContainingExpr);
                               cm = methInClass(lhs, t->children->data->idVal, t->childrenTail->data, classContainingExpr, methodContainingExpr);
                               t->staticMemberNum = cm.m;
                               t->staticClassNum - cm.c;
                               if(cm.c == -1) semerror(-1, t->lineNumber);
                               return classesST[cm.c].methodList[cm.m].returnType;
                                   
        case ARG_LIST: p = t->children;
                       while(p && p->data) {
                            typeExpr(p->data, classContainingExpr, methodContainingExpr);
                            p = p->next;
                       }
                       return 0;
                       
                          
        case WHILE_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                         if(lhs != -1) semerror(WHILE, t->children->data->lineNumber);
                         rhs = typeExprs(t->children->next->data, classContainingExpr, methodContainingExpr);
                         return -1;

        case IF_THEN_ELSE_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                                if(lhs != -1) semerror(IF_COND, t->children->data->lineNumber);
                                mid = typeExprs(t->children->next->data, classContainingExpr, methodContainingExpr);
                                rhs = typeExprs(t->childrenTail->data, classContainingExpr, methodContainingExpr);
                                if(mid == -1 && rhs == -1)
                                    return rhs;
                                if(mid == -1 || rhs == -1)
                                    semerror(IF_EL, t->lineNumber);
                                if(mid == rhs)
                                    return rhs;
                                
                                if(mid < -2 || rhs < -2)
                                    semerror(IF_EL, t->lineNumber);
                                lhs = join(mid, rhs);
                                //printf("\nite join = %d mid = %d, rhs = %d\n", lhs, mid, rhs);
                                return lhs;



        case NOT_EXPR: rhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                       if(rhs != -1) semerror(NOT, t->lineNumber);
                       return -1;

        case NEW_EXPR: rhs = inClassST(t->children->data->idVal);
                       if(rhs > -1) {
                        //printf("\nnew rhs = %d\n", rhs);
                        return rhs;
                       }
                       semerror(NEW, t->lineNumber);

        case THIS_EXPR:  if(classContainingExpr < 0) semerror(THIS_MAIN, t->lineNumber);

                        return classContainingExpr;


        case AST_ID: if(classContainingExpr < 0) {

                        return inMainST(t->idVal, t->lineNumber);
                     }
                     if(methodContainingExpr < 0) {
                        lhs = varInClass(classContainingExpr, t->idVal);
                        if(lhs == -4) semerror(CLASS_VAR_DNE, t->lineNumber);
                        //rhs = varHash(t->idVal, classContainingExpr);

                        return lhs;
                     }
                     
                    //printf("\nDEBUG\n");
                    lhs = varInParam(classContainingExpr, methodContainingExpr, t->idVal);
                    if(lhs >= -1) return lhs;
                    lhs = varInMeth(classContainingExpr, methodContainingExpr, t->idVal);
                    if(lhs >= -1) return lhs;
                    lhs = varInClass(classContainingExpr, t->idVal);
                    if(lhs >= -1) return lhs;
                    
                    //DEBUG
                    semerror(CLASS_VAR_DNE, t->lineNumber);

        case NULL_EXPR: return -2;
        case READ_EXPR: return -1;
        case PRINT_EXPR: lhs = typeExpr(t->children->data, classContainingExpr, methodContainingExpr);
                         //DEBUG
                         if(lhs == -1) return lhs;
                         semerror(PRINT, t->lineNumber);
        case NAT_LITERAL_EXPR: return -1;
        
        case ID_EXPR: if(classContainingExpr < 0) {
                        t->staticClassNum = 0;
                        t->staticMemberNum = 0;
                      } 

                      else {

                        cm = findVarInSuper(t->children->data->idVal, classContainingExpr);
                        if(cm.c == -1) {
                            t->staticClassNum = 0;
                            t->staticMemberNum = 0;
                        }
                        else {
                            t->staticMemberNum = cm.m;
                            t->staticClassNum = cm.c;
                        }
                      }

                      return typeExpr(t->children->data, classContainingExpr, methodContainingExpr);


        case EXPR_LIST: return typeExprs(t, classContainingExpr, methodContainingExpr);

        default: semerror(-1, t->lineNumber);
    }
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