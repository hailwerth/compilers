(* STERLING types *)
datatype typ = Int | Arrow of typ * typ; (* i.e., Arrow(argType, returnType) *)

(* STERLING expressions *)
datatype expr = 
  IntExpr of int 
| SuccExpr of expr (* computes the successor of the int-type subexpression *)
| PredExpr of expr (* computes the predecessor of the int-type subexpression *)
| FunExpr of string option * string option * typ * typ * expr
  (* i.e.: FunExpr(funName, paramName, paramType, returnType, bodyExpr) *)
| ApplyExpr of expr * expr
  (* i.e.: ApplyExpr(funExpr, argumentExpr) *)
| VarExpr of string
| BeqExpr of expr * expr * expr * expr
  (* i.e.: BeqExpr(testExpr1, testExpr2, toBranchExpr, elseBranchExpr) *)
;

