(* STERLING-Ag types *)
datatype typ = 
  Int 
| Arrow of typ * typ 
  (* i.e., Arrow(argType, returnType) *)
| Prod of typ list 
  (* To be valid, the type list must have at least 2 elements. *)
  (* e.g., int * (int->int) is Prod([Int,Arrow(Int,Int)]) *)
| Sum of typ list 
  (* To be valid, the type list must have at least 1 element. *)
  (* e.g., int + (int x int) is Sum([Int,Prod([Int,Int])]) *)
| Var of string
  (* can only be used in a recursive type declaring this variable *)
| Rec of string * typ;

(* STERLING-Ag expressions *)
datatype expr = 
  IntExpr of int  
| VarExpr of string
| SuccExpr of expr 
  (* computes the successor of the int-type subexpression *)
| PredExpr of expr 
  (* computes the predecessor of the int-type subexpression *)
| FunExpr of string option * string option * typ * typ * expr
  (* i.e.: FunExpr(funName, paramName, paramType, returnType, bodyExpr) *)
  (* Valid FunExprs must have valid argument and return types annotated. *)
| ApplyExpr of expr * expr 
  (*i.e.: ApplyExpr(funExpr, argumentExpr) *)
| BeqExpr of expr * expr * expr * expr
  (* i.e. BeqExpr(testExpr1, testExpr2, toBranchExpr, elseBranchExpr) *)
| TupleExpr of expr list 
  (* Valid tuples must have at least 2 elements. *)
| LetExpr of string list * expr * expr
  (* e.g. let (x1,x2) = e in e' end is LetExpr(["x1", "x2"], e, e') *)
  (* Let expressions are only well typed if there are exactly as many variable 
     names as there are tuple elements.  During execution, the first variable is
     bound to the first tuple-element value, the second is bound to the second, 
     etc. *)
  (* Valid LetExprs must have at least 2 elements in their string lists *)
| SumExpr of int * expr * typ list 
  (* e.g.(in3 7):int+int+int, which injects the expression 7 into the 3rd 
     component of an int+int+int sum,  is SumExpr(3,IntExpr(7),[Int,Int,Int]) *)
  (* As with functions, the annotated type in a SumExpr must be valid *)
| CaseExpr of expr * (string * expr) list
  (* e.g., case e of in1 x=>e1 | in2 y=>e2 is CaseExpr(e,[("x",e1),("y",e2)]) *)
  (* Case expressions are well typed only if they define a case for every 
     possible injection index and no others.  During execution, if a value v 
     has been injected into index i, then the entire case expression steps to 
     the expression of the ith list element with its associated variable bound 
     to v. *)
| RollExpr of expr 
| UnrollExpr of expr;

