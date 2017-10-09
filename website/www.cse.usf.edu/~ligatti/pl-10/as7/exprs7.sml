(* This file defines several diML-AU expressions. *)

(* Tell SML/NJ to print these expressions in detail *)
Control.Print.printDepth := 30;

(* Define e1 to represent:
   fun f(x:unit+(int*int)):(int*int)+unit =
     case x of inl x1=> (inr x1):(int*int)+unit
             | inr x2=> let(y1,y2)=x2
                        in (inl (y2,y1)):(int*int)+unit
                        end
*)
val e1 = let val t1 = Sum(Unit,Prod(Int,Int))
             val t2 = Sum(Prod(Int,Int),Unit)
         in
           FunExpr("f","x",t1,t2,
             CaseExpr(VarExpr("x"),
                      "x1",
                      SumExpr(Right,VarExpr("x1"),t2),
                      "x2",
                      LetExpr("y1","y2",VarExpr("x2"),
                              SumExpr(Left,
                                      PairExpr(VarExpr("y2"),VarExpr("y1")),
                                      t2))))
         end;

(* Define e2 to represent:
   (inr (if false then 4 else 5, 6)):unit+(int*int)
*)
val e2 = SumExpr(Right,
                 PairExpr(IfExpr(FalseExpr,IntExpr(4),IntExpr(5)),IntExpr(6)),
                 Sum(Unit,Prod(Int,Int)));

(* Define e3 to represent:
   case e1(e2) of inl z1=> let(a1,a2)=z1 in a2 end
                | inr z2=> 88
*)
val e3 = CaseExpr(ApplyExpr(e1,e2),
                  "z1",
                  LetExpr("a1","a2",VarExpr("z1"),VarExpr("a2")),
                  "z2",
                  IntExpr(88));

(* Define rType (rolled-list type) to represent:
   rec t is unit+(int*t)
*)
val rType = Rec("t",Sum(Unit,Prod(Int,Var("t"))));

(* Define uType (unrolled-list type) to represent:
   unit+(int*rec t is unit+(int*t))
*)
val uType = Sum(Unit,Prod(Int,Rec("t",Sum(Unit,Prod(Int,Var("t"))))));

(* Define e4 to represent:
   fun reverse(L:rType):rType =
     (fun revDiffLists(Ls:rType*rType):rType =
        let (todo,done) = Ls 
        in case unroll(todo)
           of inl empty => done
            | inr nonempty => 
               let(x,xs) = nonempty
               in revDiffLists(xs, roll( (inr (x, done)):uType))
               end)
     (L, roll((inl ()):uType))
   ---
   With ML's syntactic sugar, we could write e4 as:
   fun reverse(L) = 
     let fun revDiffLists(nil,done)=done
           | revDiffLists(x::xs,done) = revDiffLists(xs, x::done)
     in revDiffLists(L,nil)
     end
*)
val e4 =
  let
    val argExpr = PairExpr(VarExpr("xs"),
                           RollExpr(SumExpr(Right,
                                            PairExpr(VarExpr("x"),
                                                     VarExpr("done")),
                                            uType)))
    val lastLetBody = ApplyExpr(VarExpr("revDiffLists"),argExpr)
    val nonemptyBody = LetExpr("x","xs",VarExpr("nonempty"),lastLetBody)
    val letBody = CaseExpr(UnrollExpr(VarExpr("todo")),
                           "empty",VarExpr("done"),"nonempty",nonemptyBody)
    val rdlBody = LetExpr("todo","done",VarExpr("Ls"),letBody)
    val f1 = FunExpr("revDiffLists","Ls",Prod(rType,rType),rType,rdlBody)
    val e = PairExpr(VarExpr("L"),RollExpr(SumExpr(Left,UnitExpr,uType)))
  in
    FunExpr("reverse","L",rType,rType,ApplyExpr(f1,e)) 
  end;

(* Define e5 to represent 2::3::4::nil, or in diML-AU:
   roll( (inr(2,
              roll( (inr(3,
                         roll( (inr (4, 
                                     roll( (inl ()):uType )
                                    )
                               ):uType
                             )
                        )
                     ):uType
                   )
             )
         ):uType
       )
*)
val e5 = 
  RollExpr(
    SumExpr(Right,
            PairExpr(
              IntExpr(2),
              RollExpr(
                SumExpr(Right,
                        PairExpr(
                          IntExpr(3),
                          RollExpr(
                            SumExpr(Right,
                                    PairExpr(
                                      IntExpr(4),
                                      RollExpr(
                                        SumExpr(Left,UnitExpr,uType)
                                    )),
                                    uType)
                        )),
                        uType)
            )),
            uType));

(* Define e6 to represent:
   e4(e5)
*)
val e6 = ApplyExpr(e4,e5);

