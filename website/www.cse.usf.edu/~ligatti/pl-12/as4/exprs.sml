(* This file defines several STERLING expressions. *)

(* Tell SML/NJ to print these expressions in detail *)
Control.Print.printDepth := 30;

(* Define e to represent:
   (fun f(x:int):int = f(x))
   ( (fun _(x:int->int):int = beq((x 0),0) to 1 else 0)
     (fun _(x:int):int = x+1) )
*)
val e = ApplyExpr(FunExpr(SOME "f", SOME "x",Int,Int,
                          ApplyExpr(VarExpr("f"),VarExpr("x"))),
                  ApplyExpr(FunExpr(NONE ,SOME "x",Arrow(Int,Int),Int,
                                    BeqExpr(ApplyExpr(VarExpr("x"),
                                                      IntExpr(0)),
                                            IntExpr(0),
                                            IntExpr(1),
                                            IntExpr(0))),
                            FunExpr(NONE, SOME "x",Int,Int,
                                    SuccExpr(VarExpr("x")))));

(* Define e' to represent:
   (fun x(f:int):int = x(f))
   ( (fun y(g:int->int):int = beq((g 0),0) to 1 else 0)
     (fun z(h:int):int = h+1) )
*)
val e' = ApplyExpr(FunExpr(SOME "x", SOME "f",Int,Int,
                           ApplyExpr(VarExpr("x"),VarExpr("f"))),
                   ApplyExpr(FunExpr(SOME "y" ,SOME "g",Arrow(Int,Int),Int,
                                     BeqExpr(ApplyExpr(VarExpr("g"),
                                                       IntExpr(0)),
                                             IntExpr(0),
                                             IntExpr(1),
                                             IntExpr(0))),
                             FunExpr(SOME "z", SOME "h",Int,Int,
                                     SuccExpr(VarExpr("h")))));

(* Define eBad to represent:
   (fun f(_:int):int = f(x))
   ( (fun _(y:int->int):int = beq((x 0),0) to 1 else 0)
     (fun _(x:int):int = y+1) )
*)
val eBad = ApplyExpr(FunExpr(SOME "f", NONE,Int,Int,
                             ApplyExpr(VarExpr("f"),VarExpr("x"))),
                     ApplyExpr(FunExpr(NONE ,SOME "y",Arrow(Int,Int),Int,
                                       BeqExpr(ApplyExpr(VarExpr("x"),
                                                         IntExpr(0)),
                                               IntExpr(0),
                                               IntExpr(1),
                                               IntExpr(0))),
                               FunExpr(NONE, SOME "x",Int,Int,
                                       SuccExpr(VarExpr("y")))));
 
(* Define e2 to represent:
   (fun f(x:int):int->int = 
      (fun _(_:int):int = x))
   The final x refers to the outer function's argument.
*)
val e2 = FunExpr(SOME "f", SOME "x", Int, Arrow(Int,Int),
                 FunExpr(NONE, NONE, Int, Int,
                         VarExpr("x")));

(* Define e2' to represent:
   (fun f(x:int):int->int = 
      (fun f(x:int):int = x))
   The final x refers to the inner function's argument.
*)                     
val e2'= FunExpr(SOME "f", SOME "x", Int, Arrow(Int,Int),
                 FunExpr(SOME "f", SOME "x", Int, Int,
                         VarExpr("x")));

