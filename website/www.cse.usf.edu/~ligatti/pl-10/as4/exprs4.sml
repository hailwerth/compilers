(* This file defines several diML expressions. *)

(* Tell SML/NJ to print these expressions in detail *)
Control.Print.printDepth := 30;

(* Define e1 to represent:
   (fun f(x:bool):bool = f(x)) 
   ( (fun f2(x2:int->int):bool = x2(0)<1) 
     (fun f3(x3:int):int = x3+x3) )
*)
val e1= ApplyExpr(FunExpr("f","x",Bool,Bool,
                          ApplyExpr(VarExpr("f"),VarExpr("x"))),
                  ApplyExpr(FunExpr("f2","x2",Arrow(Int,Int),Bool,
                                    LessExpr(ApplyExpr(VarExpr("x2"),IntExpr(0)),
                                             IntExpr(1))),
                            FunExpr("f3","x3",Int,Int,
                                    PlusExpr(VarExpr("x3"),VarExpr("x3")))));

(* Define e2 to represent:
   fun f(x:int):int->int->int =
     fun f2(y:int):int->int =
       fun f3(z:int):int = x+y+z
*)
val e2 = FunExpr("f","x",Int,Arrow(Int,Arrow(Int,Int)),
                 FunExpr("f2","y",Int,Arrow(Int,Int),
                         FunExpr("f3","z",Int,Int,
                                 PlusExpr(PlusExpr(VarExpr("x"),VarExpr("y")),
                                          VarExpr("z")))));

(* Define e2bad to represent:
     fun f(x:int):int->int =
       fun g(y:int):int = x+y+z
*)
val e2bad = FunExpr("f","x",Int,Arrow(Int,Int),
              FunExpr("g","y",Int,Int,
                PlusExpr(PlusExpr(VarExpr("x"),VarExpr("y")),VarExpr("z"))));

(* Define a function that takes a natural number n and returns a function that
   takes another natural number m and returns n*m.
   This multiplication function is defined in terms of addition... diML has
     addition expressions, but not multiplication.
   The diML multiplication function is:
     fun mult(n:int):int->int =
       fun multN(m:int):int =  (* n and m are assumed to be natural numbers *)
         if m<1 then 0 else n+multN(m-1) 
*)
val mult = FunExpr("mult","n",Int,Arrow(Int,Int),
                   FunExpr("multN","m",Int,Int,
                           IfExpr(LessExpr(VarExpr("m"), IntExpr(1)),
                                  IntExpr(0),
                                  PlusExpr(VarExpr("n"),
                                           ApplyExpr(VarExpr("multN"),
                                                     PlusExpr(VarExpr("m"),
                                                              IntExpr(~1)))))));

(* Define e3 to represent:
    (fun factorial(x:int):int = if x<2 then 1 else (mult(x))(factorial(x-1)))(5)
*)
val e3 = ApplyExpr(FunExpr("factorial","x",Int,Int,
                   IfExpr(LessExpr(VarExpr("x"),IntExpr(2)), 
                          IntExpr(1),
                          ApplyExpr(ApplyExpr(mult,VarExpr("x")),
                                    ApplyExpr(VarExpr("factorial"),
                                              PlusExpr(VarExpr("x"),
                                                       IntExpr(~1)))))),
                   IntExpr(5));

