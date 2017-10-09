(* This file defines several STERLING-Ag expressions. *)

(* Tell SML/NJ to print these expressions in detail *)
Control.Print.printDepth := 30;

(* Define e1 to represent:
   fun _(x:int+(int*int)):(int*int)+int =
     case x of in1 x1=> (in2 x1):(int*int)+int
             | in2 x2=> let(y1,y2)=x2
                        in (in1 (y2,y1)):(int*int)+int
                        end
*)
val e1 = let val t1 = [Int,Prod([Int,Int])]
             val t2 = [Prod([Int,Int]),Int]
         in
           FunExpr(NONE,SOME "x",Sum(t1),Sum(t2),
             CaseExpr(VarExpr("x"),
                      [("x1",
                      SumExpr(2,VarExpr("x1"),t2)),
                      ("x2",
                      LetExpr(["y1","y2"],VarExpr("x2"),
                              SumExpr(1,
                                      TupleExpr([VarExpr("y2"),VarExpr("y1")]),
                                      t2)))]))
         end;

(* Define e2 to represent:
   (in2 (beq (1,1) to 4 else 5, 6)):int+(int*int)
*)
val e2 = SumExpr(2,
                 TupleExpr([BeqExpr(IntExpr(1),IntExpr(1),
                                    IntExpr(4),IntExpr(5)),
                            IntExpr(6)]),
                 [Int,Prod([Int,Int])]);

(* Define e3 to represent:
   case e1(e2) of in1 z1 => let(a1,a2)=z1 in a2 end
                | in2 z2 => 88
*)
val e3 = CaseExpr(ApplyExpr(e1,e2),
                  [("z1", LetExpr(["a1","a2"],VarExpr("z1"),VarExpr("a2"))),
                   ("z2", IntExpr(88))]);

(* Define rType (rolled-list type) to represent:
   rec t is int+(int*t)
*)
val rType = Rec("t",Sum([Int,Prod([Int,Var("t")])]));

(* The unrolled-list type is:
   int+(int*rec t is int+(int*t))
   Define uType to be the list used to create this unrolled-list sum type.
*)
val uType = [Int,Prod([Int,rType])];

(* Define e4 to represent:
   fun reverse(L:rType):rType =
     (fun revDiffLists(Ls:rType*rType):rType =
        let (todo,done) = Ls 
        in case unroll(todo)
           of in1 empty => done
            | in2 nonempty => 
               let(x,xs) = nonempty
               in revDiffLists(xs, roll( (in2 (x, done)):uType))
               end)
     (L, roll((in1 0):uType))
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
    val argExpr = TupleExpr([VarExpr("xs"),
                           RollExpr(SumExpr(2,
                                            TupleExpr([VarExpr("x"),
                                                     VarExpr("done")]),
                                            uType))])
    val lastLetBody = ApplyExpr(VarExpr("revDiffLists"),argExpr)
    val nonemptyBody = LetExpr(["x", "xs"],VarExpr("nonempty"),lastLetBody)
    val letBody = CaseExpr(UnrollExpr(VarExpr("todo")),
                           [("empty",VarExpr("done")),("nonempty",nonemptyBody)])
    val rdlBody = LetExpr(["todo", "done"],VarExpr("Ls"),letBody)
    val f1 = FunExpr(SOME "revDiffLists", SOME "Ls", Prod([rType,rType]), rType, rdlBody)
    val e = TupleExpr([VarExpr("L"),RollExpr(SumExpr(1,IntExpr(0),uType))])
  in
    FunExpr(SOME "reverse", SOME "L",rType,rType,ApplyExpr(f1,e)) 
  end;

(* Define e5 to represent 2::3::4::nil, or in STERLING-Ag:
   roll( (in2(2,
              roll( (in2(3,
                         roll( (in2(4, 
                                    roll( (in1 0):uType )
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
    SumExpr(2,
            TupleExpr([
              IntExpr(2),
              RollExpr(
                SumExpr(2,
                        TupleExpr([
                          IntExpr(3),
                          RollExpr(
                            SumExpr(2,
                                    TupleExpr([
                                      IntExpr(4),
                                      RollExpr(
                                        SumExpr(1,IntExpr(0),uType)
                                    )]),
                                    uType)
                        )]),
                        uType)
            )]),
            uType));

(* Define e6 to represent:
   e4(e5)
*)
val e6 = ApplyExpr(e4,e5);

(* Define e7 and e8 to test some corner cases related to recursive types *)
val e7 = RollExpr(IntExpr(0));
val e8 = UnrollExpr(UnrollExpr(RollExpr(UnrollExpr(RollExpr(IntExpr(0))))));

(* Define t9 to be:
     int +
     (rec t is ((rec t is (int + rec t' is (t + (t'*t)))) +
                (t * rec t'' is (int + rec t is (t'' + (t*t''))))))
*)
val t9 = [Int,
          Rec("t",Sum( [Rec("t",Sum([Int,
                                     Rec("t'", Sum([Var("t"),
                                                    Prod([Var("t'"),
                                                          Var("t")])]))])),
                        Prod([Var("t"),
                              Rec("t''",
                                  Sum([Int,
                                       Rec("t",
                                           Sum([Var("t''"),
                                                Prod([Var("t"),
                                                      Var("t''")])]))]))])]))];

(* Define e9 to be:  
     roll((in1 0):t9)
*)
val e9 = RollExpr( SumExpr(1, IntExpr(0), t9) );

