%option  yylineno
%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"

int yycolumn=1;
#define YY_USER_ACTION    \
	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;\
	yylloc.last_column=yycolumn+yyleng-1;\
	yycolumn+=yyleng;
		   	   
		   	   
typedef union {
	int type_int;
	float type_float;
	char type_char;
	char type_id[32];
	struct ASTNode *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL
#define LEXDEBUG 0
int lastToken;

%}

id   [A-Za-z][A-Za-z0-9]*  
int    [0-9]+
float  [0-9]*\.?[0-9]?([eE][-+]?[0-9]+)?
char    (\'.\')

%%
{int}	{
	#if (LEXDEBUG)
        		printf("第%d行,int= %s \n",yylineno,yytext);
    	#endif
	 yylval.type_int=atoi(yytext);
	return INT;
	}
{float}	{
	#if (LEXDEBUG)
        		printf("第%d行,float= %s \n",yylineno,yytext);
    	#endif
	yylval.type_float=atof(yytext);
	return FLOAT;
	}
{char}	{
	#if (LEXDEBUG)
        		printf("第%d行,char= %s \n",yylineno,yytext);
    	#endif
	yylval.type_char=yytext[1];
	return CHAR;
	}
"int"       	{
	#if (LEXDEBUG)
        		printf("第%d行,type= %s \n",yylineno,yytext);
    	#endif	
	strcpy(yylval.type_id,  yytext);
	return TYPE;
	}
"float"     	{
	#if (LEXDEBUG)
        		printf("第%d行,type= %s \n",yylineno,yytext);
    	#endif	
	strcpy(yylval.type_id,  yytext);
	return TYPE;
	}
"char"	{
	#if (LEXDEBUG)
        		printf("第%d行,type= %s \n",yylineno,yytext);
    	#endif	
	strcpy(yylval.type_id,  yytext);
	return TYPE;
	}
"return"   	{
	#if (LEXDEBUG)
        		printf("第%d行,return= %s \n",yylineno,yytext);
    	#endif	
	return RETURN;
	}
"if"        	{
	#if (LEXDEBUG)
        		printf("第%d行,if= %s \n",yylineno,yytext);
    	#endif
	return IF;
	}
"else"      	{
	#if (LEXDEBUG)
        		printf("第%d行,else= %s \n",yylineno,yytext);
    	#endif	
	return ELSE;
	}
"while"    	{
	#if (LEXDEBUG)
        		printf("第%d行,while= %s \n",yylineno,yytext);
    	#endif	
	return WHILE;
	}
"for"       	{
	#if (LEXDEBUG)
        		printf("第%d行,for= %s \n",yylineno,yytext);
    	#endif	
	return FOR;
	}
"break"	{
	#if (LEXDEBUG)
        		printf("第%d行,break= %s \n",yylineno,yytext);
    	#endif	
	return BREAK;
	}
"continue" {
	#if (LEXDEBUG)
        		printf("第%d行,continue= %s \n",yylineno,yytext);
    	#endif	
	return CONTINUE;
	}


{id}        {
	#if (LEXDEBUG)
        		printf("第%d行,id= %s \n",yylineno,yytext);
    	#endif	
	strcpy(yylval.type_id,  yytext); 
	return ID;
	}
";"	{
	#if (LEXDEBUG)
        		printf("第%d行,semi= %s \n",yylineno,yytext);
    	#endif	
	return SEMI;
	}
","	{
	#if (LEXDEBUG)
        		printf("第%d行,comma= %s \n",yylineno,yytext);
    	#endif	
	return COMMA;
	}
">"|"<"|">="|"<="|"=="|"!=" {
			#if (LEXDEBUG)
        				printf("第%d行,relop= %s \n",yylineno,yytext);
    			#endif	
			strcpy(yylval.type_id, yytext);
			return RELOP;
			}
"+="			{
			#if (LEXDEBUG)
        				printf("第%d行,addassignop= %s \n",yylineno,yytext);
    			#endif
			return ADDASSIGNOP;
			}
"-="			{
			#if (LEXDEBUG)
        				printf("第%d行,subassignop=  %s \n",yylineno,yytext);
    			#endif
			return SUBASSIGNOP;
			}
"="			{
			#if (LEXDEBUG)
        				printf("第%d行,assignop= %s \n",yylineno,yytext);
    			#endif	
			return ASSIGNOP;
			}
"++"			{
			#if (LEXDEBUG)
        				printf("第%d行,dplus= %s \n",yylineno,yytext);
    			#endif				
			return DPLUS;
			}
"+"			{
			#if (LEXDEBUG)
        				printf("第%d行,plus= %s \n",yylineno,yytext);
    			#endif	
			return PLUS;
			}
"--"			{
			#if (LEXDEBUG)
        				printf("第%d行,dminus= %s \n",yylineno,yytext);
    			#endif	
			return DMINUS;
			}
"-"			{
			#if (LEXDEBUG)
        				printf("第%d行,minus= %s \n",yylineno,yytext);
    			#endif	
			return MINUS;
			}
"*"			{
			#if (LEXDEBUG)
        				printf("第%d行,star= %s \n",yylineno,yytext);
    			#endif	
			return STAR;
			}
"/"			{
			#if (LEXDEBUG)
        				printf("第%d行,div= %s \n",yylineno,yytext);
    			#endif	
			return DIV;
			}
"&&"         		{
			#if (LEXDEBUG)
        				printf("第%d行,and= %s \n",yylineno,yytext);
    			#endif	
			return AND;
			}
"||"           			{
			#if (LEXDEBUG)
        				printf("第%d行,or= %s \n",yylineno,yytext);
    			#endif	
			return OR;
			}
"!"			{
			#if (LEXDEBUG)
        				printf("第%d行,not= %s \n",yylineno,yytext);
    			#endif	
			return NOT;
			}
"("			{
			#if (LEXDEBUG)
        				printf("第%d行,lp= %s \n",yylineno,yytext);
    			#endif	
			return LP;
			}
")"			{
			#if (LEXDEBUG)
        				printf("第%d行,rp= %s \n",yylineno,yytext);
    			#endif	
			return RP;
			}
"{"			{
			#if (LEXDEBUG)
        				printf("第%d行,lc= %s \n",yylineno,yytext);
    			#endif	
			return LC;
			}
"}"			{
			#if (LEXDEBUG)
        				printf("第%d行,rc= %s \n",yylineno,yytext);
    			#endif	
			return RC;
			}
"["			{
			#if (LEXDEBUG)
        				printf("第%d行,ls= %s \n",yylineno,yytext);
    			#endif	
			return LS;
			}
"]"			{
			#if (LEXDEBUG)
        				printf("第%d行,rs= %s \n",yylineno,yytext);
    			#endif	
			return RS;
			}
[ \r\t]     {}   
[\n]            {yycolumn=1;}
"//"(.*)     {}
"/*"[^(*/)]*"*/"   {}
   
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}

%%

/* 和bison联用时，不需要部分
void main()
{
yylex();
return 0;
}

*/
int yywrap()
{
return 1;
}
