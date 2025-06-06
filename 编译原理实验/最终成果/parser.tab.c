
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
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 3 "parser.y"

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct ASTNode *,int);
int yylex();


/* Line 189 of yacc.c  */
#line 87 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
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
     INT = 258,
     ID = 259,
     RELOP = 260,
     TYPE = 261,
     FLOAT = 262,
     CHAR = 263,
     DPLUS = 264,
     GE = 265,
     GT = 266,
     LE = 267,
     LP = 268,
     LT = 269,
     NE = 270,
     RP = 271,
     LB = 272,
     RB = 273,
     LC = 274,
     RC = 275,
     SEMI = 276,
     COMMA = 277,
     DMINUS = 278,
     LS = 279,
     RS = 280,
     PLUS = 281,
     MINUS = 282,
     STAR = 283,
     DIV = 284,
     ASSIGNOP = 285,
     AND = 286,
     OR = 287,
     NOT = 288,
     IF = 289,
     ELSE = 290,
     WHILE = 291,
     RETURN = 292,
     STRUCT = 293,
     FOR = 294,
     SWITCH = 295,
     CASE = 296,
     COLON = 297,
     DEFAULT = 298,
     BREAK = 299,
     CONTINUE = 300,
     EXT_DEF_LIST = 301,
     EXT_VAR_DEF = 302,
     FUNC_DEF = 303,
     FUNC_DEC = 304,
     EXT_DEC_LIST = 305,
     PARAM_LIST = 306,
     PARAM_DEC = 307,
     VAR_DEF = 308,
     DEC_LIST = 309,
     DEF_LIST = 310,
     COMP_STM = 311,
     STM_LIST = 312,
     EXP_STMT = 313,
     IF_THEN = 314,
     IF_THEN_ELSE = 315,
     FUNC_CALL = 316,
     ARGS = 317,
     FUNCTION = 318,
     PARAM = 319,
     ARG = 320,
     CALL = 321,
     LABEL = 322,
     GOTO = 323,
     JLT = 324,
     JLE = 325,
     JGT = 326,
     JGE = 327,
     EQ = 328,
     NEQ = 329,
     ARRAY_DEC = 330,
     ARRAY_LIST = 331,
     ARRAY_LAST = 332,
     EXP_ARRAY = 333,
     SUBASSIGNOP = 334,
     ADDASSIGNOP = 335,
     DMINUS_PREFIX = 336,
     DPLUS_PREFIX = 337,
     UMINUS = 338,
     DMINUS_SUFFIX = 339,
     DPLUS_SUFFIX = 340,
     LOWER_THEN_ELSE = 341
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 16 "parser.y"

	int    type_int;
	float  type_float;
	char  type_char;
	char   type_id[32];
	struct ASTNode *ptr;



/* Line 214 of yacc.c  */
#line 219 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 244 "parser.tab.c"

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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   442

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNRULES -- Number of states.  */
#define YYNSTATES  127

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   341

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    17,    20,    22,
      24,    28,    30,    33,    37,    42,    47,    51,    53,    57,
      60,    65,    66,    69,    72,    74,    78,    84,    92,    98,
     108,   111,   114,   115,   118,   121,   125,   127,   131,   133,
     137,   141,   145,   149,   153,   157,   161,   165,   169,   173,
     176,   179,   184,   188,   190,   192,   194,   198,   202,   205,
     208,   211,   214,   217,   221
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      88,     0,    -1,    89,    -1,    -1,    90,    89,    -1,    91,
      92,    21,    -1,    91,    95,    98,    -1,     1,    21,    -1,
       6,    -1,    93,    -1,    93,    22,    92,    -1,     4,    -1,
       4,    94,    -1,    24,   105,    25,    -1,    24,   105,    25,
      94,    -1,     4,    13,    96,    16,    -1,     4,    13,    16,
      -1,    97,    -1,    97,    22,    96,    -1,    91,    93,    -1,
      19,   101,    99,    20,    -1,    -1,   100,    99,    -1,   105,
      21,    -1,    98,    -1,    37,   105,    21,    -1,    34,    13,
     105,    16,   100,    -1,    34,    13,   105,    16,   100,    35,
     100,    -1,    36,    13,   105,    16,   100,    -1,    39,    13,
     105,    21,   105,    21,   105,    16,   100,    -1,    44,    21,
      -1,    45,    21,    -1,    -1,   102,   101,    -1,     1,    21,
      -1,    91,   103,    21,    -1,   104,    -1,   104,    22,   103,
      -1,    93,    -1,    93,    30,   105,    -1,   105,    30,   105,
      -1,   105,    31,   105,    -1,   105,    32,   105,    -1,   105,
       5,   105,    -1,   105,    26,   105,    -1,   105,    27,   105,
      -1,   105,    28,   105,    -1,   105,    29,   105,    -1,    13,
     105,    16,    -1,    27,   105,    -1,    33,   105,    -1,     4,
      13,   106,    16,    -1,     4,    13,    16,    -1,     4,    -1,
       3,    -1,     7,    -1,   105,    80,   105,    -1,   105,    79,
     105,    -1,     9,   105,    -1,   105,     9,    -1,    23,   105,
      -1,   105,    23,    -1,     4,    94,    -1,   105,    22,   106,
      -1,   105,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    58,    58,    60,    61,    64,    66,    69,    71,    82,
      83,    86,    88,    91,    92,    95,    97,   101,   103,   106,
     110,   113,   114,   117,   119,   120,   122,   124,   126,   128,
     131,   133,   137,   138,   140,   142,   145,   147,   150,   151,
     155,   158,   160,   162,   165,   167,   169,   171,   173,   174,
     176,   178,   180,   182,   184,   186,   188,   189,   191,   193,
     195,   197,   201,   203,   206
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "RELOP", "TYPE", "FLOAT",
  "CHAR", "DPLUS", "GE", "GT", "LE", "LP", "LT", "NE", "RP", "LB", "RB",
  "LC", "RC", "SEMI", "COMMA", "DMINUS", "LS", "RS", "PLUS", "MINUS",
  "STAR", "DIV", "ASSIGNOP", "AND", "OR", "NOT", "IF", "ELSE", "WHILE",
  "RETURN", "STRUCT", "FOR", "SWITCH", "CASE", "COLON", "DEFAULT", "BREAK",
  "CONTINUE", "EXT_DEF_LIST", "EXT_VAR_DEF", "FUNC_DEF", "FUNC_DEC",
  "EXT_DEC_LIST", "PARAM_LIST", "PARAM_DEC", "VAR_DEF", "DEC_LIST",
  "DEF_LIST", "COMP_STM", "STM_LIST", "EXP_STMT", "IF_THEN",
  "IF_THEN_ELSE", "FUNC_CALL", "ARGS", "FUNCTION", "PARAM", "ARG", "CALL",
  "LABEL", "GOTO", "JLT", "JLE", "JGT", "JGE", "EQ", "NEQ", "ARRAY_DEC",
  "ARRAY_LIST", "ARRAY_LAST", "EXP_ARRAY", "SUBASSIGNOP", "ADDASSIGNOP",
  "DMINUS_PREFIX", "DPLUS_PREFIX", "UMINUS", "DMINUS_SUFFIX",
  "DPLUS_SUFFIX", "LOWER_THEN_ELSE", "$accept", "program", "ExtDefList",
  "ExtDef", "Specifier", "ExtDecList", "VarDec", "Arraylist", "FuncDec",
  "VarList", "ParamDec", "CompSt", "StmList", "Stm", "DefList", "Def",
  "DecList", "Dec", "Exp", "Args", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    89,    89,    90,    90,    90,    91,    92,
      92,    93,    93,    94,    94,    95,    95,    96,    96,    97,
      98,    99,    99,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   101,   102,   103,   103,   104,   104,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   106,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     3,     2,     1,     1,
       3,     1,     2,     3,     4,     4,     3,     1,     3,     2,
       4,     0,     2,     2,     1,     3,     5,     7,     5,     9,
       2,     2,     0,     2,     2,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     3,     1,     1,     1,     3,     3,     2,     2,
       2,     2,     2,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     8,     0,     2,     0,     0,     7,     1,     4,
      11,     0,     9,     0,     0,     0,    12,     5,     0,     0,
       6,    16,     0,     0,    17,    54,    53,    55,     0,     0,
       0,     0,     0,     0,    11,    10,     0,     0,    21,     0,
      19,    15,     0,     0,    62,    58,     0,    60,    49,    50,
       0,    59,    61,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    38,     0,    36,     0,     0,     0,
       0,     0,     0,    24,     0,    21,     0,    33,    18,    52,
      64,     0,    48,    43,    14,    44,    45,    46,    47,    40,
      41,    42,    57,    56,     0,    35,     0,     0,     0,     0,
       0,    30,    31,    20,    22,    23,     0,    51,    39,    37,
       0,     0,    25,     0,    63,     0,     0,     0,    26,    28,
       0,     0,     0,    27,     0,     0,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    11,    12,    16,    13,    23,
      24,    73,    74,    75,    38,    39,    65,    66,    76,    81
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -59
static const yytype_int16 yypact[] =
{
      59,    -9,   -59,    24,   -59,    59,    22,   -59,   -59,   -59,
       6,    16,     5,    19,     4,    -2,   -59,   -59,    45,   339,
     -59,   -59,    45,    35,    31,   -59,    10,   -59,    -2,    -2,
      -2,    -2,    -2,    43,    37,   -59,    41,    45,   378,   339,
     -59,   -59,    58,   386,   -59,   -59,    83,   -59,   -59,   -59,
      -2,   -59,   -59,    37,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,   -59,    48,    60,    62,    73,    74,    -2,
      76,    77,    79,   -59,    81,   378,   111,   -59,   -59,   -59,
     122,    64,   -59,    67,   -59,    27,    27,    -1,    -1,   398,
     328,   411,   398,   398,    -2,   -59,    45,    -2,    -2,   150,
      -2,   -59,   -59,   -59,   -59,   -59,    -2,   -59,   291,   -59,
     180,   208,   -59,   223,   -59,   378,   378,    -2,    68,   -59,
     252,   378,    -2,   -59,   281,   378,   -59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -59,   -59,    92,   -59,   -10,    86,   -19,   -20,   -59,    63,
     -59,    95,    42,   -58,    80,   -59,    25,   -59,   -15,    12
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -33
static const yytype_int8 yytable[] =
{
      33,    25,    26,    40,    22,    27,    44,    28,    51,    37,
       2,    29,     7,    45,    46,    47,    48,    49,    64,    14,
      21,    30,    52,    43,     8,    31,    10,    18,    80,    37,
      15,    32,    22,    84,    15,    83,    51,    17,    19,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    50,    34,
      52,    41,    51,    42,    99,    56,    57,   118,   119,    -3,
       1,    15,    63,   123,     2,     2,    52,   126,    53,    54,
      55,    56,    57,    58,    59,    60,    51,    64,    94,   108,
     107,    95,   110,   111,    96,   113,    97,    98,    50,   100,
      52,    80,    51,    54,    55,    56,    57,     9,   101,    82,
     102,   103,   120,   121,    35,    78,    52,   124,    20,    54,
      55,    56,    57,    58,    59,    60,    50,   104,   114,    77,
      51,   109,    61,    62,     0,     0,     0,    50,     0,     0,
       0,    51,   105,     0,    52,     0,     0,    54,    55,    56,
      57,    58,    59,    60,   106,    52,     0,     0,    54,    55,
      56,    57,    58,    59,    60,    50,     0,     0,     0,    51,
       0,     0,    61,    62,     0,     0,     0,     0,     0,     0,
       0,   112,     0,    52,     0,     0,    54,    55,    56,    57,
      58,    59,    60,     0,     0,    50,     0,     0,     0,    51,
      61,    62,     0,     0,     0,     0,   115,     0,     0,     0,
       0,    61,    62,    52,     0,     0,    54,    55,    56,    57,
      58,    59,    60,    50,     0,     0,     0,    51,     0,     0,
       0,     0,     0,     0,   116,     0,     0,     0,    50,    61,
      62,    52,    51,     0,    54,    55,    56,    57,    58,    59,
      60,     0,     0,     0,   117,     0,    52,     0,     0,    54,
      55,    56,    57,    58,    59,    60,     0,    50,     0,    61,
      62,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   122,     0,    52,     0,     0,    54,    55,
      56,    57,    58,    59,    60,     0,    50,    61,    62,     0,
      51,     0,     0,     0,     0,     0,    50,   125,     0,     0,
      51,     0,    61,    62,    52,     0,     0,    54,    55,    56,
      57,    58,    59,    60,    52,     0,     0,    54,    55,    56,
      57,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    50,     0,     0,     0,    51,     0,     0,
      36,     0,   -32,   -32,     0,     2,   -32,     0,   -32,     0,
       0,    52,   -32,     0,    54,    55,    56,    57,   -32,   -32,
      61,    62,   -32,     0,     0,     0,   -32,     0,     0,     0,
      61,    62,   -32,   -32,     0,   -32,   -32,     0,   -32,     0,
       0,    25,    26,   -32,   -32,    27,     0,    28,     0,    25,
      26,    29,     0,    27,     0,    28,     0,    19,     0,    29,
       0,    30,    79,    50,     0,    31,     0,    51,     0,    30,
       0,    32,    67,    31,    68,    69,    50,    70,     0,    32,
      51,    52,    71,    72,    54,    55,    56,    57,     0,    59,
      60,     0,     0,     0,    52,     0,     0,    54,    55,    56,
      57,     0,    59
};

static const yytype_int8 yycheck[] =
{
      15,     3,     4,    22,    14,     7,    26,     9,     9,    19,
       6,    13,    21,    28,    29,    30,    31,    32,    37,    13,
      16,    23,    23,    13,     0,    27,     4,    22,    43,    39,
      24,    33,    42,    53,    24,    50,     9,    21,    19,    54,
      55,    56,    57,    58,    59,    60,    61,    62,     5,     4,
      23,    16,     9,    22,    69,    28,    29,   115,   116,     0,
       1,    24,    21,   121,     6,     6,    23,   125,    25,    26,
      27,    28,    29,    30,    31,    32,     9,    96,    30,    94,
      16,    21,    97,    98,    22,   100,    13,    13,     5,    13,
      23,   106,     9,    26,    27,    28,    29,     5,    21,    16,
      21,    20,   117,    35,    18,    42,    23,   122,    13,    26,
      27,    28,    29,    30,    31,    32,     5,    75,   106,    39,
       9,    96,    79,    80,    -1,    -1,    -1,     5,    -1,    -1,
      -1,     9,    21,    -1,    23,    -1,    -1,    26,    27,    28,
      29,    30,    31,    32,    22,    23,    -1,    -1,    26,    27,
      28,    29,    30,    31,    32,     5,    -1,    -1,    -1,     9,
      -1,    -1,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,     5,    -1,    -1,    -1,     9,
      79,    80,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,
      -1,    79,    80,    23,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,     5,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,     5,    79,
      80,    23,     9,    -1,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    21,    -1,    23,    -1,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,     5,    -1,    79,
      80,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    -1,    -1,    26,    27,
      28,    29,    30,    31,    32,    -1,     5,    79,    80,    -1,
       9,    -1,    -1,    -1,    -1,    -1,     5,    16,    -1,    -1,
       9,    -1,    79,    80,    23,    -1,    -1,    26,    27,    28,
      29,    30,    31,    32,    23,    -1,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,     5,    -1,    -1,    -1,     9,    -1,    -1,
       1,    -1,     3,     4,    -1,     6,     7,    -1,     9,    -1,
      -1,    23,    13,    -1,    26,    27,    28,    29,    19,    20,
      79,    80,    23,    -1,    -1,    -1,    27,    -1,    -1,    -1,
      79,    80,    33,    34,    -1,    36,    37,    -1,    39,    -1,
      -1,     3,     4,    44,    45,     7,    -1,     9,    -1,     3,
       4,    13,    -1,     7,    -1,     9,    -1,    19,    -1,    13,
      -1,    23,    16,     5,    -1,    27,    -1,     9,    -1,    23,
      -1,    33,    34,    27,    36,    37,     5,    39,    -1,    33,
       9,    23,    44,    45,    26,    27,    28,    29,    -1,    31,
      32,    -1,    -1,    -1,    23,    -1,    -1,    26,    27,    28,
      29,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    88,    89,    90,    91,    21,     0,    89,
       4,    92,    93,    95,    13,    24,    94,    21,    22,    19,
      98,    16,    91,    96,    97,     3,     4,     7,     9,    13,
      23,    27,    33,   105,     4,    92,     1,    91,   101,   102,
      93,    16,    22,    13,    94,   105,   105,   105,   105,   105,
       5,     9,    23,    25,    26,    27,    28,    29,    30,    31,
      32,    79,    80,    21,    93,   103,   104,    34,    36,    37,
      39,    44,    45,    98,    99,   100,   105,   101,    96,    16,
     105,   106,    16,   105,    94,   105,   105,   105,   105,   105,
     105,   105,   105,   105,    30,    21,    22,    13,    13,   105,
      13,    21,    21,    20,    99,    21,    22,    16,   105,   103,
     105,   105,    21,   105,   106,    16,    16,    21,   100,   100,
     105,    35,    21,   100,   105,    16,   100
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

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

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

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
       `yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
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
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 58 "parser.y"
    { display((yyvsp[(1) - (1)].ptr),0); semantic_Analysis0((yyvsp[(1) - (1)].ptr));;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 60 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 61 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=EXT_DEF_LIST;
                               (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Def=(yyvsp[(1) - (2)].ptr);(yyval.ptr)->DefList=(yyvsp[(2) - (2)].ptr);;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 64 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=EXT_VAR_DEF;
                               (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Specifier=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->DecList=(yyvsp[(2) - (3)].ptr);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 66 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=FUNC_DEF;  
                                (yyval.ptr)->Specifier=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->FuncDec=(yyvsp[(2) - (3)].ptr);(yyval.ptr)->Body=(yyvsp[(3) - (3)].ptr);
		(yyval.ptr)->pos=(yyval.ptr)->Body->pos=(yyval.ptr)->Specifier->pos;  ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 69 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 71 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=TYPE;             //生成类型结点，目前仅基本类型
	             (yyval.ptr)->pos=yylineno; strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));
		if(!strcmp((yyvsp[(1) - (1)].type_id),"int"))
			(yyval.ptr)->type=INT;
		else if(!strcmp((yyvsp[(1) - (1)].type_id),"float"))
			(yyval.ptr)->type=FLOAT;
		else if(!strcmp((yyvsp[(1) - (1)].type_id),"char"))
			(yyval.ptr)->type=CHAR;
		;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 82 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 83 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=EXT_DEC_LIST;
                                                           (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Dec=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->DecList=(yyvsp[(3) - (3)].ptr);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 86 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=ID;
                               (yyval.ptr)->pos=yylineno; strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 88 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode));(yyval.ptr)->kind=ARRAY_DEC;strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (2)].type_id));(yyval.ptr)->Dec=(yyvsp[(2) - (2)].ptr);(yyval.ptr)->pos=yylineno;;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 91 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode));(yyval.ptr)->kind=ARRAY_LAST;(yyval.ptr)->Exp1=(yyvsp[(2) - (3)].ptr);(yyval.ptr)->pos=yylineno;;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 92 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode));(yyval.ptr)->kind=ARRAY_LIST;(yyval.ptr)->Exp1=(yyvsp[(2) - (4)].ptr);(yyval.ptr)->pos=yylineno;(yyval.ptr)->Exp2=(yyvsp[(4) - (4)].ptr);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 95 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=FUNC_DEC;
                               (yyval.ptr)->pos=yylineno;   strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id)); (yyval.ptr)->ParamList=(yyvsp[(3) - (4)].ptr);;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=FUNC_DEC;
                               (yyval.ptr)->pos=yylineno;   strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id)); (yyval.ptr)->ParamList=NULL;;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 101 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=PARAM_LIST;
                               (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Param=(yyvsp[(1) - (1)].ptr);(yyval.ptr)->ParamList=NULL;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 103 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=PARAM_LIST;
                               (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Param=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->ParamList=(yyvsp[(3) - (3)].ptr);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=PARAM_DEC;
                                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Specifier=(yyvsp[(1) - (2)].ptr);(yyval.ptr)->ID=(yyvsp[(2) - (2)].ptr);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=COMP_STM; 
                                                (yyval.ptr)->pos=(yyvsp[(2) - (4)].ptr)?(yyvsp[(2) - (4)].ptr)->pos:((yyvsp[(3) - (4)].ptr)?(yyvsp[(3) - (4)].ptr)->pos:yylineno);   (yyval.ptr)->DefList=(yyvsp[(2) - (4)].ptr);(yyval.ptr)->StmList=(yyvsp[(3) - (4)].ptr);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 114 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=STM_LIST;  
                                      if((yyvsp[(1) - (2)].ptr)) (yyval.ptr)->pos=(yyvsp[(1) - (2)].ptr)->pos;else (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Stm=(yyvsp[(1) - (2)].ptr);(yyval.ptr)->StmList=(yyvsp[(2) - (2)].ptr);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 117 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=EXP_STMT; 
                               (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (2)].ptr);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);   ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 120 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=RETURN; 
                                          (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(2) - (3)].ptr);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 122 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=IF_THEN;
                                          (yyval.ptr)->pos=(yyvsp[(3) - (5)].ptr)->pos;   (yyval.ptr)->Cond=(yyvsp[(3) - (5)].ptr); (yyval.ptr)->IfStm=(yyvsp[(5) - (5)].ptr);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=IF_THEN_ELSE;
                                          (yyval.ptr)->pos=(yyvsp[(3) - (7)].ptr)->pos;   (yyval.ptr)->Cond=(yyvsp[(3) - (7)].ptr); (yyval.ptr)->IfStm=(yyvsp[(5) - (7)].ptr);(yyval.ptr)->ElseStm=(yyvsp[(7) - (7)].ptr);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 126 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=WHILE;
                                               (yyval.ptr)->pos=(yyvsp[(3) - (5)].ptr)->pos;   (yyval.ptr)->Cond=(yyvsp[(3) - (5)].ptr); (yyval.ptr)->Body=(yyvsp[(5) - (5)].ptr);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=FOR;
                                          (yyval.ptr)->pos=(yyvsp[(3) - (9)].ptr)->pos;   (yyval.ptr)->Exp1=(yyvsp[(3) - (9)].ptr);(yyval.ptr)->Exp2=(yyvsp[(5) - (9)].ptr);(yyval.ptr)->Exp3=(yyvsp[(7) - (9)].ptr);(yyval.ptr)->Body=(yyvsp[(9) - (9)].ptr);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode));(yyval.ptr)->kind=BREAK;
		(yyval.ptr)->pos=yylineno; strcpy((yyval.ptr)->type_id,"BREAK");;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode));(yyval.ptr)->kind=CONTINUE;
		(yyval.ptr)->pos=yylineno; strcpy((yyval.ptr)->type_id,"CONTINUE");;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 137 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=DEF_LIST;   
                    if ((yyvsp[(1) - (2)].ptr)) (yyval.ptr)->pos=(yyvsp[(1) - (2)].ptr)->pos; else (yyval.ptr)->pos=yylineno;     (yyval.ptr)->Def=(yyvsp[(1) - (2)].ptr);(yyval.ptr)->DefList=(yyvsp[(2) - (2)].ptr);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=VAR_DEF;  
                                          (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Specifier=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->DecList=(yyvsp[(2) - (3)].ptr);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=DEC_LIST;
                                          (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Dec=(yyvsp[(1) - (1)].ptr);(yyval.ptr)->DecList=NULL;;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=DEC_LIST;
                                          (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Dec=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->DecList=(yyvsp[(3) - (3)].ptr);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 150 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=ASSIGNOP;
                                          (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Dec=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=ASSIGNOP;
                                             (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);strcpy((yyval.ptr)->type_id,"ASSIGNOP");;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=AND;
                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);strcpy((yyval.ptr)->type_id,"AND");;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=OR;
                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);strcpy((yyval.ptr)->type_id,"OR");;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 162 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=RELOP;
                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);
                                strcpy((yyval.ptr)->type_id,(yyvsp[(2) - (3)].type_id));;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=PLUS;
                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);strcpy((yyval.ptr)->type_id,"PLUS");;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=MINUS;
                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);strcpy((yyval.ptr)->type_id,"MINUS");;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=STAR;
                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);strcpy((yyval.ptr)->type_id,"STAR");;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=DIV;
                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);strcpy((yyval.ptr)->type_id,"DIV");;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 173 "parser.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 174 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=UMINUS;
                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(2) - (2)].ptr);strcpy((yyval.ptr)->type_id,"UMINUS");;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 176 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=NOT;
                                (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(2) - (2)].ptr);strcpy((yyval.ptr)->type_id,"NOT");;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 178 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=FUNC_CALL;
                                (yyval.ptr)->pos=yylineno; strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id));  (yyval.ptr)->Args=(yyvsp[(3) - (4)].ptr);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 180 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=FUNC_CALL;
                                (yyval.ptr)->pos=yylineno; strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id));  (yyval.ptr)->Args=NULL;;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 182 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=ID;
                               (yyval.ptr)->pos=yylineno;  strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=INT;
                               (yyval.ptr)->pos=yylineno;  (yyval.ptr)->type=INT;(yyval.ptr)->type_int=(yyvsp[(1) - (1)].type_int);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=FLOAT;
                               (yyval.ptr)->pos=yylineno; (yyval.ptr)->type=FLOAT; (yyval.ptr)->type_float=(yyvsp[(1) - (1)].type_float)=(yyvsp[(1) - (1)].type_float);;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=ADDASSIGNOP; (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);strcpy((yyval.ptr)->type_id,"ADDASSIGNOP");;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=SUBASSIGNOP; (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Exp2=(yyvsp[(3) - (3)].ptr);strcpy((yyval.ptr)->type_id,"SUBASSIGNOP");;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=DPLUS_PREFIX; strcpy((yyval.ptr)->type_id,"DPLUS_PREFIX");
                                  (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(2) - (2)].ptr);;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=DPLUS_SUFFIX;strcpy((yyval.ptr)->type_id,"DPLUS_SUFFIX");
                                  (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (2)].ptr);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=DMINUS_PREFIX;strcpy((yyval.ptr)->type_id,"DMINUS_PREFIX");
                                  (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(2) - (2)].ptr);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=DMINUS_SUFFIX;strcpy((yyval.ptr)->type_id,"DMINUS_SUFFIX");
                                  (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(1) - (2)].ptr);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 201 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=EXP_ARRAY; (yyval.ptr)->pos=yylineno;   (yyval.ptr)->Exp1=(yyvsp[(2) - (2)].ptr);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (2)].type_id));;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=ARGS;
                                               (yyval.ptr)->pos=yylineno;  (yyval.ptr)->Exp1=(yyvsp[(1) - (3)].ptr);(yyval.ptr)->Args=(yyvsp[(3) - (3)].ptr);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 206 "parser.y"
    {(yyval.ptr)=(ASTNode *)malloc(sizeof(ASTNode)); (yyval.ptr)->kind=ARGS;
                               (yyval.ptr)->pos=yylineno;  (yyval.ptr)->Exp1=(yyvsp[(1) - (1)].ptr);(yyval.ptr)->Args=NULL;;}
    break;



/* Line 1455 of yacc.c  */
#line 2158 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
#line 211 "parser.y"


int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return 0;
	yylineno=1;
	yyparse();
	return 0;
	}
#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}

