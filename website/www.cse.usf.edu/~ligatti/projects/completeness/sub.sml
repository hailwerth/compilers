(*                    Subtyping-Algorithm Implementation
 * This file implements, in Standard ML, a subtyping algorithm for a language with 
 * nat, real, product, (disjoint) sum, function, variable, and iso-recursive types.
 *
 * Code comments refer to figures and rules that appear in 
 * "On Subtyping-Relation Completeness, with an Application to Iso-Recursive Types"
 * by Jay Ligatti, Jeremy Blackburn, and Michael Nachtigal.
 * Thanks to Jeremy Blackburn and Michael Nachtigal for preparing an initial
 * version of this implementation.
 * Please send feedback to ligatti@cse.usf.edu
 *
 * Copyright 2013-2016, University of South Florida
 * This software is released under the GNU GPL (http://www.gnu.org/licenses/gpl.html)
 * Version 2016.02.27 (created from Version 2013.09.27 by improving the comments
 *                     and making the subh function more readable)
 *)

(* Constructors for language types.  Type variables are represented as integers, 
 * which are assumed to be named 0, 1, etc., so for all types T passed as arguments
 * to the subtype-testing function sub, the set of type variables in T is {0..n} 
 * for some n.  We also assume that T never uses undeclared variables and has been
 * alpha-converted to ensure the uniqueness of every declared variable.
 * As an example, the type A from Figure 8 could be encoded as:
 *   val A = Rec(0, Sum(Sum(Rec(1, Sum(Sum(Var(1), Nat), Var(0))), Nat), Var(0)))
 * or 
 *   val A = Rec(1, Sum(Sum(Rec(0, Sum(Sum(Var(0), Nat), Var(1))), Nat), Var(1)))
 * and the type C from Figure 8 would be encoded as:
 *   val C = Rec(0, Sum(Sum(Var(0),Real),Var(0)))
 * With A and C defined as above, sub A C evaluates to true, and sub C A to false.
 *)
datatype typ = Nat | Real | Prod of typ * typ | Sum of typ * typ | Fun of typ * typ
             | Rec of int * typ | Var of int;

(* A CEtyp is a "compressed" and "extended" type.
 * "compressed" means that all recursive types \mu n.t have been replaced by just
 *   the type variable n.  We'll still be able to look up the type to which n refers
 *   in an "unroll table", an array that maps n to (the CEtyp-version of) t.
 *   Hence, CEtyp has no case for recursive types.
 * "extended" means that the structure carries extra boolean flags to memoize whether 
 *   types are value-uninhabited.  Nat, real, and function types in this language are 
 *   always value-inhabited, so their cases of CEtyp don't need the extra flag.  
 *   Variable types also don't need the flag; we'll instead use a separate array U to 
 *   map type variables to bools indicating value-uninhabitation.
 *)
datatype CEtyp = CENat | CEReal | CEFun of CEtyp * CEtyp | CEVar of int
               | CEProd of CEtyp * CEtyp * bool | CESum of CEtyp * CEtyp * bool;

(* Returns the number of variables defined in a type. *)
fun numVars (Sum(t1,t2)) = numVars(t1) + numVars(t2)
  | numVars (Prod(t1,t2)) = numVars(t1) + numVars(t2)
  | numVars (Fun(t1,t2)) = numVars(t1) + numVars(t2)
  | numVars (Rec(_,t1)) = numVars(t1) + 1
  | numVars _ = 0;

(* Returns a bool indicating whether a given CEtyp is value-uninhabited.
 * The second parameter is an array mapping type variables to value-uninhabitation
 * flags.  I.e., U[n] iff the recursive type to which type-variable n refers is
 * value-uninhabited.
 *)
fun isUninhabited (CEProd(_,_,b)) _ = b
  | isUninhabited (CESum(_,_,b)) _ = b
  | isUninhabited (CEVar(n)) U = Array.sub(U,n)
  | isUninhabited _ _ = false; (* nat, real, and fun types are value-inhabited *)

(* This initialization function has 4 parameters:
 *   (1) a typ t
 *   (2) an unroll table UT (having size numVars(t))
 *   (3) an array U (also having size numVars(t)) mapping type variables to 
 *       value-uninhabitation flags
 *   (4) a boolean b indicating whether we're trying to commit to the 
 *       value-(un)inhabitation of some previously seen recursive type.  
 * This function returns the compressed and extended version of t, and initializes 
 * the UT and U arrays as appropriate (as side effects).  Setting the values
 * in U requires implementing the U|-val(t)=\emptyset judgment from Figure 9.
 *) 
fun init Nat _ _ _ = CENat
  | init Real _ _ _ = CEReal
  | init (Fun(t1,t2)) UT U b = CEFun(init t1 UT U b, init t2 UT U b)
  | init (Sum(t1,t2)) UT U b = 
      let val CEt1 = init t1 UT U b
          val CEt2 = init t2 UT U b
      in (* set the value-uninhabited flag based on rule U-Sum *)
        CESum(CEt1, CEt2, isUninhabited CEt1 U andalso isUninhabited CEt2 U)
      end
  | init (Prod(t1,t2)) UT U b = 
      let val CEt1 = init t1 UT U b
          val CEt2 = init t2 UT U b
      in (* set the value-uninhabited flag based on rule U-Prod *)
        CEProd(CEt1, CEt2, isUninhabited CEt1 U orelse isUninhabited CEt2 U)
      end
  | init (Rec(n,t)) UT U b =
      (* Recursive type n is value-uninhabited iff t is value-uninhabited 
       * under the assumption that n is value-uninhabited (U-Rec).
       * Once we know whether t is value-uninhabited, we can properly set U[n].
       * Finally, if b=false then we're now committed to U[n] and can move on
       * to processing t, after which we can properly set UT[n] and return
       * the compressed version of \mu n.t, which is just the variable n.
       *)
      (Array.update(U,n, true);
       Array.update(U,n, isUninhabited (init t UT U true) U);
       if b then () else Array.update(UT,n, init t UT U false);
       CEVar(n))
      (* We commit to the value-uninhabitation of recursive types in this 
       * outer-to-inner fashion to properly handle types like 
       * \mu 0.((\mu 1.0) + tau), in which the value-uninhabitation of an 
       * outer type (here, 0) determines the value-uninhabitation of an inner
       * type (here, 1).  In this example, if tau is nat then U[1]=U[0]=false,
       * but if tau is the variable 0 then U[1]=U[0]=true.
       *)
  | init (Var(n)) _ _ _  = CEVar(n);

(* Returns true iff type t1 is a subtype of type t2. *)
fun sub t1 t2 = 
let
  (* Allocate and initialize the unroll tables UT1 and UT2, the uninhabitation 
   * arrays U1 and U2, and the compressed and extended types CEt1 and CEt2. 
   *)
  val m = numVars t1
  val n = numVars t2
  val UT1 = Array.array(m,CENat)
  val UT2 = Array.array(n,CENat)
  val U1 = Array.array(m,false) 
  val U2 = Array.array(n,false)
  val CEt1 = init t1 UT1 U1 false
  val CEt2 = init t2 UT2 U2 false

  (* Allocate and initialize bit arrays for storing subtyping assumptions.
   * S1[m][n] iff recursive type m in t1 is assumed to subtype recursive type n in t2.
   * S2[n][m] iff recursive type n in t2 is assumed to subtype recursive type m in t1.
   *) 
  val S1 = Array2.array(m,n,false)
  val S2 = Array2.array(n,m,false)

  (* This helper subtyping function operates on compressed and extended types
   * CEt1 and CEt2, each of which is grouped with its unroll and uninhabitation
   * tables, and the subtyping-assumption arrays S1 and S2.  
   *)
  fun subh (CEt1,UT1,U1) (CEt2,UT2,U2) (S1,S2) =
      isUninhabited CEt1 U1                              (* S-Bottom *)
    orelse 
     (case CEt2 of CEFun(CEt2',_) => isUninhabited CEt2' U2 (* S-Top *)
      | _ => false)
    orelse
      case (CEt1, CEt2) of
        (CENat, CEReal) => true                           (* S-Base *)
      | (CENat, CENat) => true                             (* S-Nat *)
      | (CEReal, CEReal) => true                          (* S-Real *)
      | (CEFun(t1, t2), CEFun(t1', t2')) =>                (* S-Fun *)
          subh (t1',UT2,U2) (t1,UT1,U1) (S2,S1) andalso
          subh (t2,UT1,U1) (t2',UT2,U2) (S1,S2) 
      | (CESum(t1, t2, _), CESum(t1', t2', _)) =>          (* S-Sum *)
          subh (t1,UT1,U1) (t1',UT2,U2) (S1,S2) andalso
          subh (t2,UT1,U1) (t2',UT2,U2) (S1,S2)
      | (CEProd(t1, t2, _), CEProd(t1', t2', _)) =>       (* S-Prod *)
          subh (t1,UT1,U1) (t1',UT2,U2) (S1,S2) andalso
          subh (t2,UT1,U1) (t2',UT2,U2) (S1,S2)
      | (CEVar(m), CEVar(n)) =>                            (* S-Rec *)
          (* Return true if m is assumed to be a subtype of n; otherwise, assume
           * m subtypes n and return whether m-unrolled subtypes n-unrolled
           *)
          Array2.sub(S1,m,n) orelse
          (Array2.update(S1,m,n,true);
           subh (Array.sub(UT1,m),UT1,U1) (Array.sub(UT2,n),UT2,U2) (S1,S2))
          (* As an optimization, the entry for S1[m][n] isn't reset to false,
           * even if m-unrolled doesn't subtype n-unrolled.  This optimization
           * is safe because if m-unrolled doesn't subtype n-unrolled, then
           * this case of subh returns false, causing every pending call to subh
           * to return false as well---in every case where subh is called, if
           * that call to subh returns false then the caller also returns false.
           * Hence, if even one call to subh returns false then the entire sub
           * function returns false, in which case S1 needn't be updated.
           *)
      | _ => false
in subh (CEt1,UT1,U1) (CEt2,UT2,U2) (S1,S2) 
end;



print("\n\n\n--------------------------------TESTS--------------------------------\n");

(* Test types from Figure 8.  Check: sub A C evaluates to true, and sub C A to false. *)
val A = Rec(0, Sum(Sum(Rec(1, Sum(Sum(Var(1), Nat), Var(0))), Nat), Var(0)));
val C = Rec(0, Sum(Sum(Var(0),Real),Var(0)));
(* A' is alpha-equivalent to A, so A' is still a subtype of C but not vice versa. *)
val A' = Rec(1, Sum(Sum(Rec(0, Sum(Sum(Var(0), Nat), Var(1))), Nat), Var(1)));

(* The type D = \mu t.(\mu t'.t  *  real) is value-uninhabited and therefore a subtype of every type. *)
val D = Rec(0, Prod(Rec(1,Var(0)),Real));
val D' = Rec(1, Prod(Rec(0,Var(1)),Nat)); (* D' is also value-uninhabited. *)

(* On the other hand, type E = \mu t.(\mu t'.t  +  real) is value-inhabited. *)
val E = Rec(0, Sum(Rec(1,Var(0)),Real));
val E' = Rec(1, Sum(Rec(0,Var(1)),Nat));  (* E' is a subtype of E *)

(* F = \mu t.(\mu t'.t  ->  real) is value-inhabited.  
 * Note that the inner recursive type t' must therefore also be value-inhabited! 
 * Hence, rule S-Top should not apply after unrolling F.
 * Consequently, F is not a supertype of all recursive types, unlike type H below.
 *)
val F = Rec(0, Fun(Rec(1,Var(0)),Real));
val F' = Rec(1, Fun(Rec(0,Var(1)),Nat));  
(* Interesting case: F' is not a subtype of F because the contravariant subtyping of the 
 * unrolled, inner t' types would require F to subtype F' (which cannot be, due to the
 * return types of F and F'). 
 *)

(* G = \mu t.t is uninhabited. *)
val G = Rec(0,Var(0));

(* H = \mu t.( (\mu t'.(t' * t)) -> real)
 * This type is interesting because the inner recursive type t' is value-uninhabited, 
 *  while the outer recursive type t is value-inhabited.
 * Because t' is value-uninhabited and an argument type, 
 *  H is a supertype of all recursive types (and only recursive types).
 *) 
val H = Rec(0, Fun(Rec(1,Prod(Var(1),Var(0))), Real));

val P = Fun(Nat,Real);
val Q = Fun(Real,Nat);
val R = Real;

(* T = (\mu t.t)->real is a top type, a supertype of all types. *)
val T = Fun(Rec(0,Var(0)),Real);

(* A list of types for testing *)
val typList = [(A,"A"),(A',"A'"),(C,"C"),(D,"D"),(D',"D'"),(E,"E"),(E',"E'"),
               (F,"F"),(F',"F'"),(G,"G"),(H,"H"),(P,"P"),(Q,"Q"),(R,"R"),(T,"T")];

(* Return a list of all pairs of elements from a given list.
 * E.g., mkPairs [1,2,3] returns 
 * [(1,1),(1,2),(1,3),(2,1),(2,2),(2,3),(3,1),(3,2),(3,3)]
 *)
fun mkPairs L = let fun f t nil = nil
                      | f t (l::ls) = (t,l)::(f t ls)
                    fun g nil L = nil
                      | g (t::ts) L = (f t L) @ (g ts L)
                in g L L end;

(* now print the results of "sub t1 t2", for all pairs of types t1 and t2 in the typList *)
val _ = app (fn ((t1,s1),(t2,s2))=> 
              print("sub " ^ s1 ^ " " ^ s2 ^ " = " ^ Bool.toString(sub t1 t2) ^ "\n"))
            (mkPairs typList);


(* Extra tests, which were used to test value-uninhabitation *)
(* To run these tests, insert the following line at the right place (circa l.100) in the Rec case of init:
 *  if b then () else print("U["^Int.toString(n)^"]=" ^ Bool.toString(Array.sub(U,n))^" ");
 *)
(*
  (* I = \mu0.((\mu1.(\mu2.0->nat))+(\mu3.3)).  Types 0-2 are value-inhabited; Type 3 is value-uninhabited. *)
  val I = Rec(0,Sum(Rec(1,Fun(Rec(2,Var(0)),Nat)),Rec(3,Var(3))));

  (* J = \mu0.((\mu1.(\mu2.0->nat))*(\mu3.3)).  Now 1 is value-inhabited; 0,2,3 are value-uninhabited. *)
  val J = Rec(0,Prod(Rec(1,Fun(Rec(2,Var(0)),Nat)),Rec(3,Var(3))));
  
  (* K = \mu0.((\mu1.(\mu2.0*nat))+(\mu3.3)).  Now, 0-3 are value-uninhabited. *)
  val K = Rec(0,Sum(Rec(1,Prod(Rec(2,Var(0)),Nat)),Rec(3,Var(3))));

  (* L = \mu0.((\mu1.(\mu2.0*nat))->(\mu3.3)).  Again 0-2 are value-inhabited; 3 remains value-uninhabited. *)
  val L = Rec(0,Fun(Rec(1,Prod(Rec(2,Var(0)),Nat)),Rec(3,Var(3))));

  val X = sub I J;
  val Y = sub K L;
  val Z = sub I L;
*)


(* Performance tests *)
(* NOTE: When tested on a 64-bit Linux PC with 4GB RAM and running SML/NJ, 
 *       every one of the subtyping tests below ran in 2ms (CPU time) on average, median, and mode.
 *       The range was 1 to 3ms.  Number of trials was 10. 
 * (details: Red Hat Enterprise Linux Server v.6.4 (Santiago) on Intel Core i7-2600 CPU @ 3.4 GHz)
 *)
(* A worst case, quadratic time because m=(n-1): M = u0.u1...un.0 *)
val M = Rec(0,Rec(1,Rec(2,Rec(3,Rec(4,Rec(5,Rec(6,Rec(7,Rec(8,Rec(9,Rec(10,Rec(11,Rec(12,Rec(13,
        Rec(14,Rec(15,Rec(16,Rec(17,Rec(18,Rec(19,Rec(20,Rec(21,Rec(22,Rec(23,Rec(24,Rec(25,Rec(26,
        Rec(27,Rec(28,Rec(29,Rec(30,Rec(31,Rec(32,Rec(33,Var(0)))))))))))))))))))))))))))))))))));
(* Another worst, quadratic-time case: N = u0.u1...un.nat *)
val N = Rec(0,Rec(1,Rec(2,Rec(3,Rec(4,Rec(5,Rec(6,Rec(7,Rec(8,Rec(9,Rec(10,Rec(11,Rec(12,Rec(13,
        Rec(14,Rec(15,Rec(16,Rec(17,Rec(18,Rec(19,Rec(20,Rec(21,Rec(22,Rec(23,Rec(24,Rec(25,Rec(26,
        Rec(27,Rec(28,Rec(29,Rec(30,Rec(31,Rec(32,Rec(33,Nat))))))))))))))))))))))))))))))))));
(* For timing: 
 * val ct = Timer.startCPUTimer();
 *)
val s0 = sub M N; (* M is bottom, so s0=true *)
(* For timing:
 * val e = Timer.checkCPUTimer ct;
 *)
val s1 = sub N M; (* false *)
val s2 = sub M M;
val s3 = sub N N;

(* More "worst-case", quadratic-time subtyping queries.  Both S1 and S2 are inhabited *)
(* S1 = u0.(0->u1.(1->...->u21.(21->nat)...) *)
val S1 = Rec(0,Fun(Var(0),Rec(1,Fun(Var(1),Rec(2,Fun(Var(2),Rec(3,Fun(Var(3),Rec(4,Fun(Var(4),
         Rec(5,Fun(Var(5),Rec(6,Fun(Var(6),Rec(7,Fun(Var(7),Rec(8,Fun(Var(8),Rec(9,Fun(Var(9),
         Rec(10,Fun(Var(10),Rec(11,Fun(Var(11),Rec(12,Fun(Var(12),Rec(13,Fun(Var(13),Rec(14,Fun(Var(14),
         Rec(15,Fun(Var(15),Rec(16,Fun(Var(16),Rec(17,Fun(Var(17),Rec(18,Fun(Var(18),Rec(19,Fun(Var(19),
         Rec(20,Fun(Var(20),Rec(21,Fun(Var(21),Nat)))))))))))))))))))))))))))))))))))))))))))); 
(* S2 = u21.(21->u20.(20->...->u0.(0->nat)...) is alpha-equivalent to S1. *)
val S2 = Rec(21,Fun(Var(21),Rec(20,Fun(Var(20),Rec(19,Fun(Var(19),Rec(18,Fun(Var(18),Rec(17,Fun(Var(17),
         Rec(16,Fun(Var(16),Rec(15,Fun(Var(15),Rec(14,Fun(Var(14),Rec(13,Fun(Var(13),Rec(12,Fun(Var(12),
         Rec(11,Fun(Var(11),Rec(10,Fun(Var(10),Rec(9,Fun(Var(9),Rec(8,Fun(Var(8),Rec(7,Fun(Var(7),
         Rec(6,Fun(Var(6),Rec(5,Fun(Var(5),Rec(4,Fun(Var(4),Rec(3,Fun(Var(3),Rec(2,Fun(Var(2),
         Rec(1,Fun(Var(1),Rec(0,Fun(Var(0),Nat))))))))))))))))))))))))))))))))))))))))))));
val s4 = sub S1 S2; (* true *)
val s5 = sub S2 S1; (* true *)

(* Another test.  Although the type sizes are large, short-circuit evaluation in the S-Fun case of the 
 * subh function prevents the subtyping algorithm from having to compute the subtyping relationship of 
 * every pair of recursive types in this example.
 *)
(* T1 = u0.u1..u4.(0->0->0->0->0->1->..->1->..->4->..->4->(0+0+0+0+1+..+1+..+4+..+4)) *)
val T1 = Rec(0,Rec(1,Rec(2,Rec(3,Rec(4,Fun(Var(0),Fun(Var(0),Fun(Var(0),Fun(Var(0),Fun(Var(0),
          Fun(Var(1),Fun(Var(1),Fun(Var(1),Fun(Var(1),Fun(Var(1),
          Fun(Var(2),Fun(Var(2),Fun(Var(2),Fun(Var(2),Fun(Var(2),
          Fun(Var(3),Fun(Var(3),Fun(Var(3),Fun(Var(3),Fun(Var(3),
          Fun(Var(4),Fun(Var(4),Fun(Var(4),Fun(Var(4),Fun(Var(4),
         Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(
           Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Var(0),Var(0)),Var(0)),Var(0)),Var(0)),
            Var(1)),Var(1)),Var(1)),Var(1)),Var(1)),Var(2)),Var(2)),Var(2)),Var(2)),Var(2)),
            Var(3)),Var(3)),Var(3)),Var(3)),Var(3)),Var(4)),Var(4)),Var(4)),Var(4)),Var(4))
            ))))))))))))))))))))))))))))));
(* T2 is T1 except that i->i->i->i->i becomes 0->1->2->3->4 (and similarly for sum types) *)
val T2 = Rec(0,Rec(1,Rec(2,Rec(3,Rec(4,Fun(Var(0),Fun(Var(1),Fun(Var(2),Fun(Var(3),Fun(Var(4),
          Fun(Var(0),Fun(Var(1),Fun(Var(2),Fun(Var(3),Fun(Var(4),
          Fun(Var(0),Fun(Var(1),Fun(Var(2),Fun(Var(3),Fun(Var(4),
          Fun(Var(0),Fun(Var(1),Fun(Var(2),Fun(Var(3),Fun(Var(4),
          Fun(Var(0),Fun(Var(1),Fun(Var(2),Fun(Var(3),Fun(Var(4),
         Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(
           Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Sum(Var(0),Var(1)),Var(2)),Var(3)),Var(4)),
            Var(0)),Var(1)),Var(2)),Var(3)),Var(4)),Var(0)),Var(1)),Var(2)),Var(3)),Var(4)),
            Var(0)),Var(1)),Var(2)),Var(3)),Var(4)),Var(0)),Var(1)),Var(2)),Var(3)),Var(4))
            ))))))))))))))))))))))))))))));
val s6 = sub T1 T2; (* false *)
val s7 = sub T2 T1; (* false *)
val s8 = sub T1 T1;
val s9 = sub T2 T2;

(* Interesting test cases from Donald Ray: *)
val tau = Rec(0, Fun(Rec(1, Var 1), Fun(Var 0, Rec(2, Var 2))));
val tau' = Rec(0, Fun(Fun(Rec(1, Var 1), Rec(2, Var 2)), Fun(Var 0, Fun(Rec(3, Var 3), Rec(4, Var 4)))));
val s10 = sub tau tau'
val s11 = sub tau' tau
(* Note that tau is really u0.T, so s11=true, though s10=false *)

