(* This file defines several diML+P expressions. *)

(* Tell SML/NJ to print these expressions in detail *)
(* note: if you get an error from this line on your home computer, *)
(* make sure that you have installed the libsmlnj-smlnj package *)
Control.Print.printDepth := 40;

(* Define e1 to represent:
   (fun f:bool->bool x = f(x)) 
   ( (fun f:(int->int)->bool x = (x 0) < 1) 
     (fun f:int->int x = x + x) )
*)
val e1 =
  ApplyExpr
    (FunExpr
       ("f",Bool,Bool,[(VarPattern "x",ApplyExpr (VarExpr "f",VarExpr "x"))]),
     ApplyExpr
       (FunExpr
          ("f",Arrow (Int,Int),Bool,
           [(VarPattern "x",
             LessExpr (ApplyExpr (VarExpr "x",IntExpr 0),IntExpr 1))]),
        FunExpr
          ("f",Int,Int,[(VarPattern "x",PlusExpr (VarExpr "x",VarExpr "x"))])))

(* Define e2 to represent:
   fun f:int->int->int->int x =
     fun f:int->int->int y =
       fun f:int->int z = x+y+z
*)
val e2 = 
  FunExpr
    ("f",Int,Arrow (Int,Arrow (Int,Int)),
     [(VarPattern "x",
       FunExpr
         ("f",Int,Arrow (Int,Int),
          [(VarPattern "y",
            FunExpr
              ("f",Int,Int,
               [(VarPattern "z",
                 PlusExpr (PlusExpr (VarExpr "x",VarExpr "y"),VarExpr "z"))]))]))])

(* Define e2bad to represent:
     fun f:int->int->int->int x =
       fun f:int->int->int y = x+y+z
*)
val e2bad = 
  FunExpr
    ("f",Int,Arrow (Int,Arrow (Int,Int)),
     [(VarPattern "x",
       FunExpr
         ("f",Int,Arrow (Int,Int),
          [(VarPattern "y",
            PlusExpr (PlusExpr (VarExpr "x",VarExpr "y"),VarExpr "z"))]))])

(* Define a function that takes a natural number n and returns a function that
   takes another natural number m and returns n*m.
   This multiplication function is defined in terms of addition... diML has
     addition expressions, but not multiplication.
   A diML+P function for multiplying natural numbers is:
     fun mult:int->int->int n =
       fun multN:int->int 0 = 0
                        | m = n + multN(m + ~1) 
*)
val mult = 
  FunExpr
    ("mult",Int,Arrow (Int,Int),
     [(VarPattern "n",
       FunExpr
         ("multN",Int,Int,
          [(IntPattern 0,IntExpr 0),
           (VarPattern "m",
            PlusExpr
              (VarExpr "n",
               ApplyExpr (VarExpr "multN",
                          PlusExpr (VarExpr "m",
                                    IntExpr ~1))))]))])

(* Define e3 to represent:
    (fun factorial:int->int 0 = 1
                          | x = mult x (factorial(x-1))) 5
   As with mult above, this function assumes the argument is a natural number
   (not a good assumption to make in practice).
*)
val e3 = 
  ApplyExpr
    (FunExpr
       ("factorial",Int,Int,
        [(IntPattern 0,IntExpr 1),
         (VarPattern "x",
          ApplyExpr
            (ApplyExpr
               (mult,
                VarExpr "x"),
             ApplyExpr 
               (VarExpr "factorial",
                PlusExpr 
                  (VarExpr "x",
                   IntExpr ~1))))]),
     IntExpr 5)

