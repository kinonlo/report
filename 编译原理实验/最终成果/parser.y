%error-verbose
%locations
%{
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
%}

%union {
	int    type_int;
	float  type_float;
	char  type_char;
	char   type_id[32];
	struct ASTNode *ptr;
};

//  %type 定义非终结符的语义值类
%type  <ptr>  program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stm StmList DefList Def DecList Dec Exp Args Arraylist

//% token 定义终结符的语义值类型
%token <type_int> INT              /*指定INT的语义值是type_int，有词法分析得到的数值*/
%token <type_id> ID  RELOP TYPE    /*指定ID,RELOP 的语义值是type_id，有词法分析得到的标识符字符串*/
%token <type_float> FLOAT          /*指定FLOAT的语义值是type_float，有词法分析得到的标识符字符串*/
%token <type_char> CHAR
   

%token DPLUS GE GT LE LP LT NE RP LB RB LC RC SEMI COMMA DMINUS LS RS    /*用bison对该文件编译时，带参数-d，生成的exp.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码*/
%token PLUS MINUS STAR DIV ASSIGNOP AND OR NOT IF ELSE WHILE RETURN STRUCT FOR SWITCH CASE COLON DEFAULT BREAK CONTINUE
/*以下为接在上述token后依次编码的枚举常量，作为AST结点类型标记*/
%token EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF FUNC_DEC EXT_DEC_LIST PARAM_LIST PARAM_DEC VAR_DEF DEC_LIST DEF_LIST COMP_STM STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE
%token FUNC_CALL ARGS FUNCTION PARAM ARG CALL LABEL GOTO JLT JLE JGT JGE EQ NEQ ARRAY_DEC ARRAY_LIST ARRAY_LAST EXP_ARRAY


%left ASSIGNOP ADDASSIGNOP SUBASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right DMINUS DPLUS
%right UMINUS NOT DPLUS_PREFIX DMINUS_PREFIX
%left DPLUS_SUFFIX DMINUS_SUFFIX
%left LP RP LC RC LS RS

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE


%%

program: ExtDefList    { display($1,0); semantic_Analysis0($1);}     //显示语法树,语义分析
         ; 
ExtDefList: {$$=NULL;}
          | ExtDef ExtDefList {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=EXT_DEF_LIST;
                               $$->pos=yylineno;   $$->Def=$1;$$->DefList=$2;}//每一个EXTDEFLIST的结点，其第1棵子树对应一个外部变量声明或函数
          ;  
ExtDef:   Specifier ExtDecList SEMI   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=EXT_VAR_DEF;
                               $$->pos=yylineno;   $$->Specifier=$1;$$->DecList=$2;}                               //该结点对应外部声明
         |Specifier FuncDec CompSt   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=FUNC_DEF;  
                                $$->Specifier=$1;$$->FuncDec=$2;$$->Body=$3;
		$$->pos=$$->Body->pos=$$->Specifier->pos;  }  //该结点对应一个函数定义
         | error SEMI   {$$=NULL;}
         ;
Specifier:  TYPE    {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=TYPE;             //生成类型结点，目前仅基本类型
	             $$->pos=yylineno; strcpy($$->type_id,$1);
		if(!strcmp($1,"int"))
			$$->type=INT;
		else if(!strcmp($1,"float"))
			$$->type=FLOAT;
		else if(!strcmp($1,"char"))
			$$->type=CHAR;
		}   
              ;
    
ExtDecList:  VarDec      {$$=$1;}       /*每一个EXT_DECLIST的结点，其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
           | VarDec COMMA ExtDecList {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=EXT_DEC_LIST;
                                                           $$->pos=yylineno;   $$->Dec=$1;$$->DecList=$3;}          //外部变量名列表
           ;  
VarDec:  ID          {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ID;
                               $$->pos=yylineno; strcpy($$->type_id,$1);}                    //ID结点，标识符符号串存放结点的type_id
	| ID Arraylist {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=ARRAY_DEC;strcpy($$->type_id,$1);$$->Dec=$2;$$->pos=yylineno;}
         ;

Arraylist: LS Exp RS {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=ARRAY_LAST;$$->Exp1=$2;$$->pos=yylineno;}
                | LS Exp RS Arraylist {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=ARRAY_LIST;$$->Exp1=$2;$$->pos=yylineno;$$->Exp2=$4;}
	;

FuncDec: ID LP VarList RP     {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=FUNC_DEC;
                               $$->pos=yylineno;   strcpy($$->type_id,$1); $$->ParamList=$3;}  //函数名（存放在$$->type_id）和形参的结点
	|ID LP  RP  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=FUNC_DEC;
                               $$->pos=yylineno;   strcpy($$->type_id,$1); $$->ParamList=NULL;}  //无参函数名结点

        ;  
VarList: ParamDec  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=PARAM_LIST;
                               $$->pos=yylineno;   $$->Param=$1;$$->ParamList=NULL;}     //形式参数列表(最后一个列表结点)
        | ParamDec COMMA  VarList  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=PARAM_LIST;
                               $$->pos=yylineno;   $$->Param=$1;$$->ParamList=$3;}         //形式参数列表
        ;
ParamDec: Specifier VarDec  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=PARAM_DEC;
                                                $$->pos=yylineno;   $$->Specifier=$1;$$->ID=$2;}     //形式参数说明
         ;

CompSt: LC DefList StmList RC   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=COMP_STM; 
                                                $$->pos=$2?$2->pos:($3?$3->pos:yylineno);   $$->DefList=$2;$$->StmList=$3;}     //复合语句
       ;
StmList: {$$=NULL; }  
        | Stm StmList    {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=STM_LIST;  
                                      if($1) $$->pos=$1->pos;else $$->pos=yylineno;   $$->Stm=$1;$$->StmList=$2;}
        ;
Stm:   Exp SEMI    {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=EXP_STMT; 
                               $$->pos=yylineno;   $$->Exp1=$1;}
      | CompSt      {$$=$1;   }         //复合语句结点直接最为语句结点，不再生成新的结点
      | RETURN Exp SEMI    {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=RETURN; 
                                          $$->pos=yylineno;   $$->Exp1=$2;}
      | IF LP Exp RP Stm %prec LOWER_THEN_ELSE    {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=IF_THEN;
                                          $$->pos=$3->pos;   $$->Cond=$3; $$->IfStm=$5;}
      | IF LP Exp RP Stm ELSE Stm    {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=IF_THEN_ELSE;
                                          $$->pos=$3->pos;   $$->Cond=$3; $$->IfStm=$5;$$->ElseStm=$7;}
      | WHILE LP Exp RP Stm   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=WHILE;
                                               $$->pos=$3->pos;   $$->Cond=$3; $$->Body=$5;}
      | FOR LP Exp SEMI Exp SEMI Exp RP Stm {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=FOR;
                                          $$->pos=$3->pos;   $$->Exp1=$3;$$->Exp2=$5;$$->Exp3=$7;$$->Body=$9;}

      | BREAK SEMI {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=BREAK;
		$$->pos=yylineno; strcpy($$->type_id,"BREAK");}
      | CONTINUE SEMI {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=CONTINUE;
		$$->pos=yylineno; strcpy($$->type_id,"CONTINUE");}
      ;

DefList: {$$=NULL; }
        | Def DefList      {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=DEF_LIST;   
                    if ($1) $$->pos=$1->pos; else $$->pos=yylineno;     $$->Def=$1;$$->DefList=$2;} //局部变量定义语句序列
        | error SEMI   {$$=NULL;}
        ;
Def:    Specifier DecList SEMI  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=VAR_DEF;  
                                          $$->pos=yylineno;   $$->Specifier=$1;$$->DecList=$2;} //局部变量定义语句序列
        ;
DecList: Dec {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=DEC_LIST;
                                          $$->pos=yylineno;   $$->Dec=$1;$$->DecList=NULL;} //局部变量
       | Dec COMMA DecList   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=DEC_LIST;
                                          $$->pos=yylineno;   $$->Dec=$1;$$->DecList=$3;} //局部变量定义语句序列
	   ;
Dec:     VarDec  {$$=$1;}
       | VarDec ASSIGNOP Exp  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ASSIGNOP;
                                          $$->pos=yylineno;   $$->Dec=$1;$$->Exp2=$3;}  //局部变量初始化结点
       ;

Exp:    Exp ASSIGNOP Exp  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ASSIGNOP;
                                             $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"ASSIGNOP");}

      | Exp AND Exp  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=AND;
                                $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"AND");}
      | Exp OR Exp   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=OR;
                                $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"OR");}
      | Exp RELOP Exp {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=RELOP;
                                $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;
                                strcpy($$->type_id,$2);}  //词法分析关系运算符号自身值保存在$2中
      | Exp PLUS Exp  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=PLUS;
                                $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"PLUS");}
      | Exp MINUS Exp {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=MINUS;
                                $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"MINUS");}
      | Exp STAR Exp {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=STAR;
                                $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"STAR");}
      | Exp DIV Exp  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=DIV;
                                $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"DIV");}
      | LP Exp RP     {$$=$2;}
      | MINUS Exp %prec UMINUS  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=UMINUS;
                                $$->pos=yylineno;   $$->Exp1=$2;strcpy($$->type_id,"UMINUS");}
      | NOT Exp       {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=NOT;
                                $$->pos=yylineno;   $$->Exp1=$2;strcpy($$->type_id,"NOT");}
      | ID LP Args RP  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=FUNC_CALL;
                                $$->pos=yylineno; strcpy($$->type_id,$1);  $$->Args=$3;}
      | ID LP RP      {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=FUNC_CALL;
                                $$->pos=yylineno; strcpy($$->type_id,$1);  $$->Args=NULL;}
      | ID                 {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ID;
                               $$->pos=yylineno;  strcpy($$->type_id,$1);}                                   //变量
      | INT          {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=INT;
                               $$->pos=yylineno;  $$->type=INT;$$->type_int=$1;}    //整型常量
      | FLOAT     {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=FLOAT;
                               $$->pos=yylineno; $$->type=FLOAT; $$->type_float=$1=$1;}    //浮点常量
      | Exp ADDASSIGNOP Exp	{$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ADDASSIGNOP; $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"ADDASSIGNOP");}
      | Exp SUBASSIGNOP Exp {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=SUBASSIGNOP; $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"SUBASSIGNOP");}
      /*| Exp LS Exp RS	{$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=INDEX; $$->pos=yylineno;   $$->Exp1=$1;$$->Exp2=$3;strcpy($$->type_id,"INDEX");}*/
      | DPLUS  Exp   %prec DPLUS_PREFIX    {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=DPLUS_PREFIX; strcpy($$->type_id,"DPLUS_PREFIX");
                                  $$->pos=yylineno;   $$->Exp1=$2;}  //这里仅有前缀，还需后缀形式，以及--
      | Exp DPLUS    %prec DPLUS_SUFFIX {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=DPLUS_SUFFIX;strcpy($$->type_id,"DPLUS_SUFFIX");
                                  $$->pos=yylineno;   $$->Exp1=$1;}
      | DMINUS Exp %prec DMINUS_PREFIX {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=DMINUS_PREFIX;strcpy($$->type_id,"DMINUS_PREFIX");
                                  $$->pos=yylineno;   $$->Exp1=$2;}
      | Exp DMINUS %prec DMINUS_SUFFIX {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=DMINUS_SUFFIX;strcpy($$->type_id,"DMINUS_SUFFIX");
                                  $$->pos=yylineno;   $$->Exp1=$1;}
      /*| BREAK {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=BREAK;strcpy($$->type_id,"BREAK");}
      | CONTINUE {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=CONTINUE;strcpy($$->type_id,"CONTINUE");}*/
      | ID Arraylist  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=EXP_ARRAY; $$->pos=yylineno;   $$->Exp1=$2;strcpy($$->type_id,$1);}
      ;
Args:    Exp COMMA Args    {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ARGS;
                                               $$->pos=yylineno;  $$->Exp1=$1;$$->Args=$3;} 

       | Exp              {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ARGS;
                               $$->pos=yylineno;  $$->Exp1=$1;$$->Args=NULL;} 

       ;
       
%%

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
