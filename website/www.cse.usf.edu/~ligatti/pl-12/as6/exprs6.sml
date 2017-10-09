(* This file defines several STERLING expressions. *)

(* Tell SML/NJ to print these expressions in detail *)
Control.Print.printDepth := 30;

(* Define e to represent:
   (fun f(x:int):int = f(x))
   ( (fun _(y:int->int):int = beq((y 0),0) to 1 else 0)
     (fun _(z:int):int = z+1) )
*)
val e = ApplyExpr(FunExpr(SOME "f", SOME "x",Int,Int,
                          ApplyExpr(VarExpr("f"),VarExpr("x"))),
                  ApplyExpr(FunExpr(NONE ,SOME "y",Arrow(Int,Int),Int,
                                    BeqExpr(ApplyExpr(VarExpr("y"),
                                                      IntExpr(0)),
                                            IntExpr(0),
                                            IntExpr(1),
                                            IntExpr(0))),
                            FunExpr(NONE, SOME "z",Int,Int,
                                    SuccExpr(VarExpr("z")))));

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
      (fun g(y:int):int = y))
*)                     
val e2'= FunExpr(SOME "f", SOME "x", Int, Arrow(Int,Int),
                 FunExpr(SOME "g", SOME "y", Int, Int,
                         VarExpr("y")));

(* Define a function that takes ints a and b and 
   returns 1 if a<b and 0 otherwise. *)
val lessThan =
  let    
    val helper = 
      FunExpr(SOME "helper", SOME "x", Int, Arrow(Int,Int),
              FunExpr(NONE, SOME "y", Int, Int,
                      BeqExpr(VarExpr("x"),
                              VarExpr("b"),
                              IntExpr(1),
                              BeqExpr(VarExpr("y"),
                                      VarExpr("b"),
                                      IntExpr(0),
                                      ApplyExpr(
                                        ApplyExpr(VarExpr("helper"),
                                                  SuccExpr(VarExpr("x"))),
                                        PredExpr(VarExpr("y")))))))
  in  
    FunExpr(SOME "lessThan", SOME "a", Int, Arrow(Int, Int),
            FunExpr(NONE, SOME "b", Int, Int,
                    BeqExpr(VarExpr("a"), VarExpr("b"), IntExpr(0),
                            ApplyExpr(ApplyExpr(helper,
                                                SuccExpr(VarExpr("a"))),
                                      PredExpr(VarExpr("a"))))))
  end;

val e3 = ApplyExpr(ApplyExpr(lessThan, IntExpr(3)),IntExpr(5));

