
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */


/* Line 189 of yacc.c  */
#line 73 "dj.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MAIN = 258,
     CLASS = 259,
     EXTENDS = 260,
     NATTYPE = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     PRINTNAT = 265,
     READNAT = 266,
     THIS = 267,
     NEW = 268,
     NUL = 269,
     NATLITERAL = 270,
     ID = 271,
     ASSIGN = 272,
     PLUS = 273,
     MINUS = 274,
     TIMES = 275,
     EQUALITY = 276,
     LESS = 277,
     AND = 278,
     NOT = 279,
     DOT = 280,
     SEMICOLON = 281,
     COMMA = 282,
     LBRACE = 283,
     RBRACE = 284,
     LPAREN = 285,
     RPAREN = 286,
     ENDOFFILE = 287
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

/* "%code provides" blocks.  */

/* Line 261 of yacc.c  */
#line 6 "dj.y"

  #include <stdio.h>
  #include "lex.yy.c"
  #include "ast.h"
  #include "symtbl.h"
  #include "typecheck.h"
  #include "codegen.h"
  #include <string.h>

  /* Symbols in this grammar are represented as ASTs */ 
  #define YYSTYPE ASTree *

  /* Declare global AST for entire program */
  ASTree *pgmAST;

  /* Function for printing generic syntax-error messages */
  void yyerror(const char *str) {
    printf("Syntax error on line %d at token %s\n",yylineno,yytext);
    printf("(This version of the compiler exits after finding the first ");
    printf("syntax error.)\n");
    exit(-1);
  }



/* Line 261 of yacc.c  */
#line 172 "dj.tab.c"

/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 178 "dj.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   436

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNRULES -- Number of states.  */
#define YYNSTATES  141

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    11,    21,    30,    31,    36,    41,    42,
      44,    46,    57,    68,    78,    88,    93,    98,   101,   104,
     105,   109,   112,   116,   118,   119,   123,   127,   131,   135,
     139,   142,   146,   148,   150,   162,   170,   175,   177,   182,
     186,   188,   192,   196,   202,   207,   214
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      34,     0,    -1,    35,     3,    28,    36,    41,    29,    32,
      -1,    35,     4,    38,     5,    38,    28,    36,    39,    29,
      -1,    35,     4,    38,     5,    38,    28,    36,    29,    -1,
      -1,    36,    37,    38,    26,    -1,    36,    38,    38,    26,
      -1,    -1,     6,    -1,    16,    -1,    39,    37,    38,    30,
      40,    31,    28,    36,    41,    29,    -1,    39,    38,    38,
      30,    40,    31,    28,    36,    41,    29,    -1,    37,    38,
      30,    40,    31,    28,    36,    41,    29,    -1,    38,    38,
      30,    40,    31,    28,    36,    41,    29,    -1,    40,    27,
      37,    38,    -1,    40,    27,    38,    38,    -1,    37,    38,
      -1,    38,    38,    -1,    -1,    41,    43,    26,    -1,    43,
      26,    -1,    42,    27,    43,    -1,    43,    -1,    -1,    43,
      18,    43,    -1,    43,    19,    43,    -1,    43,    20,    43,
      -1,    43,    21,    43,    -1,    43,    22,    43,    -1,    24,
      43,    -1,    43,    23,    43,    -1,    15,    -1,    14,    -1,
       7,    30,    43,    31,    28,    41,    29,     8,    28,    41,
      29,    -1,     9,    30,    43,    31,    28,    41,    29,    -1,
      13,    38,    30,    31,    -1,    12,    -1,    10,    30,    43,
      31,    -1,    11,    30,    31,    -1,    38,    -1,    43,    25,
      38,    -1,    38,    17,    43,    -1,    43,    25,    38,    17,
      43,    -1,    38,    30,    42,    31,    -1,    43,    25,    38,
      30,    42,    31,    -1,    30,    43,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    50,    50,    58,    63,    69,    73,    76,    80,    83,
      87,    92,    98,   104,   110,   119,   122,   125,   128,   132,
     136,   138,   143,   145,   148,   152,   155,   158,   161,   164,
     167,   169,   172,   174,   176,   180,   183,   185,   187,   189,
     191,   193,   196,   199,   203,   206,   210
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "CLASS", "EXTENDS", "NATTYPE",
  "IF", "ELSE", "WHILE", "PRINTNAT", "READNAT", "THIS", "NEW", "NUL",
  "NATLITERAL", "ID", "ASSIGN", "PLUS", "MINUS", "TIMES", "EQUALITY",
  "LESS", "AND", "NOT", "DOT", "SEMICOLON", "COMMA", "LBRACE", "RBRACE",
  "LPAREN", "RPAREN", "ENDOFFILE", "$accept", "pgm", "cdec", "vardec",
  "nat", "id", "methdec", "pdec", "elist", "alist", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    35,    36,    36,    36,    37,
      38,    39,    39,    39,    39,    40,    40,    40,    40,    40,
      41,    41,    42,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     7,     9,     8,     0,     4,     4,     0,     1,
       1,    10,    10,     9,     9,     4,     4,     2,     2,     0,
       3,     2,     3,     1,     0,     3,     3,     3,     3,     3,
       2,     3,     1,     1,    11,     7,     4,     1,     4,     3,
       1,     3,     3,     5,     4,     6,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     1,     0,     0,     8,    10,     0,     0,
       0,     9,     0,     0,     0,     0,    37,     0,    33,    32,
       0,     0,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,    40,    30,     0,     0,     0,    24,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     8,
       0,     0,     0,    39,     0,    46,     6,    42,     0,    23,
       7,     2,    20,    25,    26,    27,    28,    29,    31,    41,
       0,     0,     0,    38,    36,     0,    44,     0,    24,     4,
       0,     0,     0,     0,     0,    22,    43,     0,     0,     0,
       3,     0,     0,     0,     0,    45,    19,    19,     0,     0,
       0,    35,     0,     0,     0,     0,    19,    19,     0,    17,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       8,     0,     0,     0,    15,    16,     0,     0,     8,     8,
      34,     0,     0,     0,     0,    13,    14,     0,     0,    11,
      12
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     9,    22,    32,    82,   104,    24,    58,
      25
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -76
static const yytype_int16 yypact[] =
{
     -76,     1,    50,   -76,   -25,     9,   -76,   -76,    33,   124,
       9,   -76,    32,    38,    39,    41,   -76,     9,   -76,   -76,
     338,   338,     9,     3,   146,   393,    27,   338,   338,   338,
      43,    53,     7,    68,    25,    82,   338,   338,    84,    62,
     402,   338,   338,   338,   338,   338,   338,     9,   -76,   -76,
     351,   365,   379,   -76,    80,   -76,   -76,   411,    57,   411,
     -76,   -76,   -76,    15,    15,    68,   125,   125,   147,    19,
       5,    97,    98,   -76,   -76,   338,   -76,   338,   338,   -76,
       9,     9,    10,   338,   338,   411,   411,    58,    69,    70,
     -76,     9,     9,   170,   194,   -76,    54,    54,   102,   111,
     119,   -76,     9,     9,    76,    89,    54,    54,   114,   -76,
     -76,    54,   121,   123,   160,   161,   338,     9,     9,   -76,
     -76,   135,   136,   218,   -76,   -76,   124,   124,   -76,   -76,
     -76,   242,   266,   124,   124,   -76,   -76,   290,   314,   -76,
     -76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -76,   -76,   -76,   -47,     8,    -5,   -76,   -40,   -75,    74,
     -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
       8,     3,    70,     6,    23,    26,    33,    34,    93,    94,
      40,    11,    31,    50,    51,    52,    11,    35,    38,     7,
      36,     7,    57,    59,    36,     7,     7,    63,    64,    65,
      66,    67,    68,    37,    79,    43,    77,    37,    10,    90,
      47,   123,    69,    41,    42,    43,    44,    45,    46,    78,
      47,   131,   132,     4,     5,    49,    55,   105,   137,   138,
      11,    85,    27,    86,    59,    81,   114,   115,    28,    29,
       7,    30,   126,   127,    53,    88,    89,    92,    80,    40,
      40,   133,   134,    54,    75,    75,    98,    99,    76,    95,
      91,   103,   103,    47,    61,    56,    60,   109,   110,    96,
      97,   103,   103,   111,   102,   102,   118,   112,    56,    40,
      60,    74,   124,   125,   102,   102,   111,    40,    40,   117,
     113,    23,    23,    40,    40,    83,    84,   108,    23,    23,
      11,    12,   106,    13,    14,    15,    16,    17,    18,    19,
       7,   107,   116,    41,    42,    43,    -1,    -1,    20,   119,
      47,   120,    87,    12,    21,    13,    14,    15,    16,    17,
      18,    19,     7,   128,   129,    41,    42,    43,    44,    45,
      20,     0,    47,     0,     0,    39,    21,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     7,   111,   111,     0,
       0,   121,   122,     0,    20,     0,     0,     0,     0,   100,
      21,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       7,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,     0,     0,   101,    21,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     7,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,     0,     0,   130,    21,    12,
       0,    13,    14,    15,    16,    17,    18,    19,     7,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,     0,
       0,   135,    21,    12,     0,    13,    14,    15,    16,    17,
      18,    19,     7,     0,     0,     0,     0,     0,     0,     0,
      20,     0,     0,     0,     0,   136,    21,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     7,     0,     0,     0,
       0,     0,     0,     0,    20,     0,     0,     0,     0,   139,
      21,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       7,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,     0,     0,   140,    21,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     7,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,     0,     0,     0,    21,    41,
      42,    43,    44,    45,    46,     0,    47,     0,     0,     0,
       0,     0,    71,    41,    42,    43,    44,    45,    46,     0,
      47,     0,     0,     0,     0,     0,    72,    41,    42,    43,
      44,    45,    46,     0,    47,     0,     0,     0,     0,     0,
      73,    41,    42,    43,    44,    45,    46,     0,    47,    48,
      41,    42,    43,    44,    45,    46,     0,    47,    62,    41,
      42,    43,    44,    45,    46,     0,    47
};

static const yytype_int16 yycheck[] =
{
       5,     0,    49,    28,     9,    10,    20,    21,    83,    84,
      24,     6,    17,    27,    28,    29,     6,    22,    23,    16,
      17,    16,    36,    37,    17,    16,    16,    41,    42,    43,
      44,    45,    46,    30,    29,    20,    17,    30,     5,    29,
      25,   116,    47,    18,    19,    20,    21,    22,    23,    30,
      25,   126,   127,     3,     4,    28,    31,    97,   133,   134,
       6,    75,    30,    77,    78,    70,   106,   107,    30,    30,
      16,    30,   119,   120,    31,    80,    81,    82,    70,    93,
      94,   128,   129,    30,    27,    27,    91,    92,    31,    31,
      82,    96,    97,    25,    32,    26,    26,   102,   103,    30,
      30,   106,   107,    27,    96,    97,   111,    31,    26,   123,
      26,    31,   117,   118,   106,   107,    27,   131,   132,   111,
      31,   126,   127,   137,   138,    28,    28,     8,   133,   134,
       6,     7,    30,     9,    10,    11,    12,    13,    14,    15,
      16,    30,    28,    18,    19,    20,    21,    22,    24,    28,
      25,    28,    78,     7,    30,     9,    10,    11,    12,    13,
      14,    15,    16,    28,    28,    18,    19,    20,    21,    22,
      24,    -1,    25,    -1,    -1,    29,    30,     7,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    27,    27,    -1,
      -1,    31,    31,    -1,    24,    -1,    -1,    -1,    -1,    29,
      30,     7,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    30,     7,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    30,     7,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    30,     7,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    29,    30,     7,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      30,     7,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    30,     7,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,    18,
      19,    20,    21,    22,    23,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    31,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    31,    18,    19,    20,
      21,    22,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      31,    18,    19,    20,    21,    22,    23,    -1,    25,    26,
      18,    19,    20,    21,    22,    23,    -1,    25,    26,    18,
      19,    20,    21,    22,    23,    -1,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    35,     0,     3,     4,    28,    16,    38,    36,
       5,     6,     7,     9,    10,    11,    12,    13,    14,    15,
      24,    30,    37,    38,    41,    43,    38,    30,    30,    30,
      30,    38,    38,    43,    43,    38,    17,    30,    38,    29,
      43,    18,    19,    20,    21,    22,    23,    25,    26,    28,
      43,    43,    43,    31,    30,    31,    26,    43,    42,    43,
      26,    32,    26,    43,    43,    43,    43,    43,    43,    38,
      36,    31,    31,    31,    31,    27,    31,    17,    30,    29,
      37,    38,    39,    28,    28,    43,    43,    42,    38,    38,
      29,    37,    38,    41,    41,    31,    30,    30,    38,    38,
      29,    29,    37,    38,    40,    40,    30,    30,     8,    38,
      38,    27,    31,    31,    40,    40,    28,    37,    38,    28,
      28,    31,    31,    41,    38,    38,    36,    36,    28,    28,
      29,    41,    41,    36,    36,    29,    29,    41,    41,    29,
      29
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 51 "dj.y"
    { (yyval) = newAST(PROGRAM,(yyvsp[(1) - (7)]),0,NULL,yylineno); pgmAST = (yyval); 
        appendToChildrenList((yyval), (yyvsp[(4) - (7)]));
        appendToChildrenList((yyval), (yyvsp[(5) - (7)]));
        return 0; ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 59 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (9)]), newAST(CLASS_DECL, (yyvsp[(3) - (9)]), 0, NULL, yylineno)); 
         appendToChildrenList((yyvsp[(1) - (9)])->childrenTail->data, (yyvsp[(5) - (9)]));
         appendToChildrenList((yyvsp[(1) - (9)])->childrenTail->data, (yyvsp[(7) - (9)]));
         appendToChildrenList((yyvsp[(1) - (9)])->childrenTail->data, (yyvsp[(8) - (9)]));;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 64 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (8)]), newAST(CLASS_DECL, (yyvsp[(3) - (8)]), 0, NULL, yylineno)); 
         appendToChildrenList((yyvsp[(1) - (8)])->childrenTail->data, (yyvsp[(5) - (8)]));
         appendToChildrenList((yyvsp[(1) - (8)])->childrenTail->data, (yyvsp[(7) - (8)]));
         appendToChildrenList((yyvsp[(1) - (8)])->childrenTail->data, newAST(METHOD_DECL_LIST, NULL, 0, NULL, yylineno)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 69 "dj.y"
    { (yyval) = newAST(CLASS_DECL_LIST, NULL, 0, NULL, yylineno); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 74 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (4)]), newAST(VAR_DECL, (yyvsp[(2) - (4)]), 0, NULL, yylineno)); 
           appendToChildrenList((yyvsp[(1) - (4)])->childrenTail->data, (yyvsp[(3) - (4)]));;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 77 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (4)]), newAST(VAR_DECL, (yyvsp[(2) - (4)]), 0, NULL, yylineno));
           appendToChildrenList((yyvsp[(1) - (4)])->childrenTail->data, (yyvsp[(3) - (4)]));;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 80 "dj.y"
    { (yyval) = newAST(VAR_DECL_LIST, NULL, 0, NULL, yylineno); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 84 "dj.y"
    { (yyval) = newAST(NAT_TYPE, NULL, 0, NULL, yylineno); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 88 "dj.y"
    { (yyval) = newAST(AST_ID, NULL, 0, yytext, yylineno); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 93 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (10)]), newAST(METHOD_DECL, (yyvsp[(2) - (10)]), 0, NULL, yylineno));
            appendToChildrenList((yyvsp[(1) - (10)])->childrenTail->data, (yyvsp[(3) - (10)]));
            appendToChildrenList((yyvsp[(1) - (10)])->childrenTail->data, (yyvsp[(5) - (10)]));
            appendToChildrenList((yyvsp[(1) - (10)])->childrenTail->data, (yyvsp[(8) - (10)]));
            appendToChildrenList((yyvsp[(1) - (10)])->childrenTail->data, (yyvsp[(9) - (10)])); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 99 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (10)]), newAST(METHOD_DECL, (yyvsp[(2) - (10)]), 0, NULL, yylineno));
            appendToChildrenList((yyvsp[(1) - (10)])->childrenTail->data, (yyvsp[(3) - (10)]));
            appendToChildrenList((yyvsp[(1) - (10)])->childrenTail->data, (yyvsp[(5) - (10)]));
            appendToChildrenList((yyvsp[(1) - (10)])->childrenTail->data, (yyvsp[(8) - (10)]));
            appendToChildrenList((yyvsp[(1) - (10)])->childrenTail->data, (yyvsp[(9) - (10)])); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 105 "dj.y"
    { (yyval) = newAST(METHOD_DECL_LIST, newAST(METHOD_DECL, (yyvsp[(1) - (9)]), 0, NULL, yylineno), 0, NULL, yylineno);
            appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(2) - (9)]));
            appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(4) - (9)]));
            appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(7) - (9)]));
            appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(8) - (9)])); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 111 "dj.y"
    { (yyval) = newAST(METHOD_DECL_LIST, newAST(METHOD_DECL, (yyvsp[(1) - (9)]), 0, NULL, yylineno), 0, NULL, yylineno);
            appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(2) - (9)]));
            appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(4) - (9)]));
            appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(7) - (9)]));
            appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(8) - (9)])); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 120 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (4)]), newAST(PARAM_DECL, (yyvsp[(3) - (4)]), 0, NULL, yylineno)); 
         appendToChildrenList((yyvsp[(1) - (4)])->childrenTail->data, (yyvsp[(4) - (4)])); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 123 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (4)]), newAST(PARAM_DECL, (yyvsp[(3) - (4)]), 0, NULL, yylineno)); 
         appendToChildrenList((yyvsp[(1) - (4)])->childrenTail->data, (yyvsp[(4) - (4)])); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 126 "dj.y"
    { (yyval) = newAST(PARAM_DECL_LIST, newAST(PARAM_DECL, (yyvsp[(1) - (2)]), 0, NULL, yylineno), 0, NULL, yylineno); 
         appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(2) - (2)])); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 129 "dj.y"
    { (yyval) = newAST(PARAM_DECL_LIST, newAST(PARAM_DECL, (yyvsp[(1) - (2)]), 0, NULL, yylineno), 0, NULL, yylineno); 
         appendToChildrenList((yyval)->childrenTail->data, (yyvsp[(2) - (2)])); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 132 "dj.y"
    { (yyval) = newAST(PARAM_DECL_LIST, NULL, 0, NULL, yylineno); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 137 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)])); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 139 "dj.y"
    { (yyval) = newAST(EXPR_LIST, (yyvsp[(1) - (2)]), 0, NULL, yylineno); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 144 "dj.y"
    { appendToChildrenList((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 146 "dj.y"
    { (yyval) = newAST(ARG_LIST, (yyvsp[(1) - (1)]), 0, NULL, yylineno); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 148 "dj.y"
    { (yyval) = newAST(ARG_LIST, NULL, 0, NULL, yylineno); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 153 "dj.y"
    { (yyval) = newAST(PLUS_EXPR, (yyvsp[(1) - (3)]), 0, NULL, yylineno); 
         appendToChildrenList((yyval), (yyvsp[(3) - (3)])); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 156 "dj.y"
    { (yyval) = newAST(MINUS_EXPR, (yyvsp[(1) - (3)]), 0, NULL, yylineno); 
         appendToChildrenList((yyval), (yyvsp[(3) - (3)])); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 159 "dj.y"
    { (yyval) = newAST(TIMES_EXPR, (yyvsp[(1) - (3)]), 0, NULL, yylineno); 
         appendToChildrenList((yyval), (yyvsp[(3) - (3)])); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 162 "dj.y"
    { (yyval) = newAST(EQUALITY_EXPR, (yyvsp[(1) - (3)]), 0, NULL, yylineno); 
         appendToChildrenList((yyval), (yyvsp[(3) - (3)])); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 165 "dj.y"
    { (yyval) = newAST(LESS_THAN_EXPR, (yyvsp[(1) - (3)]), 0, NULL, yylineno); 
         appendToChildrenList((yyval), (yyvsp[(3) - (3)])); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 168 "dj.y"
    {(yyval) = newAST(NOT_EXPR, (yyvsp[(2) - (2)]), 0, NULL, yylineno);}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 170 "dj.y"
    { (yyval) = newAST(AND_EXPR, (yyvsp[(1) - (3)]), 0, NULL, yylineno); 
         appendToChildrenList((yyval), (yyvsp[(3) - (3)])); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 173 "dj.y"
    { (yyval) = newAST(NAT_LITERAL_EXPR, NULL, atoi(yytext), NULL, yylineno); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 175 "dj.y"
    { (yyval) = newAST(NULL_EXPR, NULL, 0, NULL, yylineno); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 177 "dj.y"
    { (yyval) = newAST(IF_THEN_ELSE_EXPR, (yyvsp[(3) - (11)]), 0, NULL, yylineno);
         appendToChildrenList((yyval), (yyvsp[(6) - (11)]));
         appendToChildrenList((yyval), (yyvsp[(10) - (11)])); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 181 "dj.y"
    { (yyval) = newAST(WHILE_EXPR, (yyvsp[(3) - (7)]), 0, NULL, yylineno);
         appendToChildrenList((yyval), (yyvsp[(6) - (7)])); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 184 "dj.y"
    { (yyval) = newAST(NEW_EXPR, (yyvsp[(2) - (4)]), 0, NULL, yylineno); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 186 "dj.y"
    { (yyval) = newAST(THIS_EXPR, NULL, 0, NULL, yylineno); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 188 "dj.y"
    { (yyval) = newAST(PRINT_EXPR, (yyvsp[(3) - (4)]), 0, NULL, yylineno); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 190 "dj.y"
    { (yyval) = newAST(READ_EXPR, NULL, 0, NULL, yylineno); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 192 "dj.y"
    { (yyval) = newAST(ID_EXPR, (yyvsp[(1) - (1)]), 0, NULL, yylineno); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 194 "dj.y"
    {(yyval) = newAST(DOT_ID_EXPR, (yyvsp[(1) - (3)]), 0, NULL, yylineno) ;
        appendToChildrenList((yyval), (yyvsp[(3) - (3)])); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 197 "dj.y"
    { (yyval) = newAST(ASSIGN_EXPR, (yyvsp[(1) - (3)]), 0, NULL, yylineno);
         appendToChildrenList((yyval), (yyvsp[(3) - (3)])); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 200 "dj.y"
    { (yyval) = newAST(DOT_ASSIGN_EXPR, (yyvsp[(1) - (5)]), 0, NULL, yylineno); 
         appendToChildrenList((yyval), (yyvsp[(3) - (5)])); 
         appendToChildrenList((yyval), (yyvsp[(5) - (5)])); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 204 "dj.y"
    { (yyval) = newAST(METHOD_CALL_EXPR, (yyvsp[(1) - (4)]), 0, NULL, yylineno); 
         appendToChildrenList((yyval), (yyvsp[(3) - (4)])); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 207 "dj.y"
    { (yyval) = newAST(DOT_METHOD_CALL_EXPR, (yyvsp[(1) - (6)]), 0, NULL, yylineno); 
         appendToChildrenList((yyval), (yyvsp[(3) - (6)]));
         appendToChildrenList((yyval), (yyvsp[(5) - (6)])); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 211 "dj.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;



/* Line 1455 of yacc.c  */
#line 1894 "dj.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 214 "dj.y"


int main(int argc, char **argv) {
  if(argc < 2) {
    printf("Usage: dj-parse filename\n");
    exit(-1);
  }
  yyin = fopen(argv[1],"r");
  if(yyin==NULL) {
    printf("ERROR: could not open file %s\n",argv[1]);
    exit(-1);
  }
  
  //debug flag to print ast  
  int debug=0;
  if(argc==3) debug=1;

  //sets up output dism file bullshit, just changes extension
  FILE *fp;
  int len, i, period = -1, extlen;
  char *newFileName;
  //finds index of last period in filename
  len = strlen(argv[1]);
  for(i = 0; i < len; i++) {
    if(argv[1][i] == '.')
      period = i;
  }
  //if period not there, filename error
  if(period == -1){
    printf("File %s does not have an extension, must be *.dj file\n", argv[1]);
    return -1;
  }
  //error if extension is wrong size or not type .dj
  extlen = len - period - 1;
  if(extlen != 2 || argv[1][period+1] != 'd' || argv[1][period+2] != 'j') {
    printf("File %s must have .dj extension\n", argv[1]);
    return -1;
  }
  //copies everything up until the last period
  newFileName = (char*)calloc(len + 3, 1);
  for(i = 0; i < len; i++) {
    newFileName[i] = argv[1][i];
  }
  //changes extension to dism and opens it for writing
  newFileName[period + 1] = 'd';
  newFileName[period + 2] = 'i';
  newFileName[period + 3] = 's';
  newFileName[period + 4] = 'm';
  newFileName[period + 5] = '\0';
  fp = fopen(newFileName, "w");
  if(!fp) {
    printf("Cant save %s\n", newFileName);
    exit(-1);
  }

  /* parse, symtbl, typecheck, codegen */
  yyparse();
  setupSymbolTables(pgmAST);
  typecheckProgram();
  if(debug)
    printAST(pgmAST);
  generateDISM(fp);

  //closes output file and quits
  fclose(fp);
  fclose(yyin);
  return 0;
}

