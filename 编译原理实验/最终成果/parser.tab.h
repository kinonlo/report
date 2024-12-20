
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 16 "parser.y"

	int    type_int;
	float  type_float;
	char  type_char;
	char   type_id[32];
	struct ASTNode *ptr;



/* Line 1676 of yacc.c  */
#line 148 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;

