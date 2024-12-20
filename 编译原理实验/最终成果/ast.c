#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "def.h"
#include "parser.tab.h"

#define DEBUG1 1
int arr_index = 0;
int arr_flag = 0;

void display(struct ASTNode *T, int indent)
{//对抽象语法树的先根遍历
	int i = 1;
	struct ASTNode *T0;
	if (T)
	{
		switch (T->kind) {
		case EXT_DEF_LIST:  
			display(T->Def, indent);         //显示该外部定义（外部变量和函数）列表中的第一个
			display(T->DefList, indent);    //显示该外部定义列表中的其它外部定义
			break;
		case EXT_VAR_DEF:   
			printf("%*c外部变量定义：(%d)\n", indent, ' ', T->pos);
			display(T->Specifier, indent + 3);        //显示外部变量类型
			printf("%*c变量名：\n", indent + 3, ' ');
			display(T->DecList, indent + 6);          //显示变量列表
			break;
		case TYPE:          
			printf("%*c类型： %s\n", indent, ' ', T->type_id);
			break;
		case EXT_DEC_LIST:  
			/*if (T->Dec->Dec != NULL)
			{
				printf("%*c数组名：%s\n", indent, ' ', T->Dec->type_id);
				printf("%*c数组大小：\n", indent, ' ');
			}*/
			display(T->Dec, indent);     //依次显示外部变量名，
			display(T->DecList, indent); //后续还有相同的，仅显示语法树此处理代码可以和类似代码合并
			break;
		case ARRAY_DEC:
			printf("%*c数组名：%s\n", indent, ' ', T->type_id);
			printf("%*c数组大小：\n", indent, ' ');
			display(T->Dec, indent+3);
			break;
		case FUNC_DEF:      
			printf("%*c函数定义：(%d)\n", indent, ' ', T->pos);
			display(T->Specifier, indent + 3);      //显示函数返回类型
			display(T->FuncDec, indent + 3);         //显示函数名和参数
			display(T->Body, indent + 3);      //显示函数体
			break;
		case FUNC_DEC:      
			printf("%*c函数名：%s\n", indent, ' ', T->type_id);
			if (T->ParamList) {
				printf("%*c函数形参：\n", indent, ' ');
				display(T->ParamList, indent + 3);  //显示函数参数列表
			}
			else printf("%*c无参函数\n", indent + 3, ' ');
			break;
		case PARAM_LIST:    
			display(T->Param, indent);     //依次显示全部参数类型和名称，
			display(T->ParamList, indent);
			break;
		case PARAM_DEC:    
			if (T->Specifier->type == INT) {
				printf("%*c类型：%s, 参数名：%s\n", indent, ' ', "int", T->ID->type_id);
			}
			else if (T->Specifier->type == FLOAT) {
				printf("%*c类型：%s, 参数名：%s\n", indent, ' ', "float", T->ID->type_id);
			}
			else {
				printf("%*c类型：%s, 参数名：%s\n", indent, ' ', "char", T->ID->type_id);
			}
			break;
		case EXP_STMT:      
			printf("%*c表达式语句：(%d)\n", indent, ' ', T->pos);
			display(T->Exp1, indent + 3);
			break;
		case RETURN:        
			printf("%*c返回语句：(%d)\n", indent, ' ', T->pos);
			display(T->Exp1, indent + 3);
			break;
		case COMP_STM:      
			printf("%*c复合语句：(%d)\n", indent, ' ', T->pos);
			if (T->DefList)
			{
				printf("%*c复合语句的变量定义部分：\n", indent + 3, ' ');
				display(T->DefList, indent + 6);      //显示定义部分
			}
			if (T->StmList)
			{
				printf("%*c复合语句的语句部分：\n", indent + 3, ' ');
				display(T->StmList, indent + 6);      //显示语句部分
			}
			break;
		case STM_LIST:      
			display(T->Stm, indent);      //显示第一条语句
			display(T->StmList, indent);        //显示剩下语句
			break;
		case WHILE:         
			printf("%*c循环语句：(%d)\n", indent, ' ', T->pos);
			printf("%*c循环条件：\n", indent + 3, ' ');
			display(T->Cond, indent + 6);      //显示循环条件
			printf("%*c循环体：(%d)\n", indent + 3, ' ', T->pos);
			display(T->Body, indent + 6);      //显示循环体
			break;
		case FOR:
			printf("%*cFOR循环语句：(%d)\n", indent, ' ', T->pos);
			printf("%*c循环变量定义：\n", indent + 3, ' ');
			display(T->Exp1, indent + 6);      //变量赋值
			printf("%*c循环条件：\n", indent + 3, ' ');
			display(T->Exp2, indent + 6);      //循环条件
			printf("%*c更新语句：\n", indent + 3, ' ');
			display(T->Exp3, indent + 6);      //更新语句
			printf("%*c循环体：(%d)\n", indent + 3, ' ', T->pos);
			display(T->Body, indent + 6);      //循环体
			break;
		case BREAK:
			printf("%*cBREAK： (%d)\n", indent, ' ',T->pos);
			break;
		case CONTINUE:
			printf("%*cCONTINUE： (%d)\n", indent, ' ',T->pos);
			break;
		case IF_THEN:       
			printf("%*c条件语句(IF_THEN)：(%d)\n", indent, ' ', T->pos);
			printf("%*c条件：\n", indent + 3, ' ');
			display(T->Cond, indent + 6);      //显示条件
			printf("%*cIF子句：(%d)\n", indent + 3, ' ', T->pos);
			display(T->IfStm, indent + 6);      //显示if子句
			break;
		case IF_THEN_ELSE:  
			printf("%*c条件语句(IF_THEN_ELSE)：(%d)\n", indent, ' ', T->pos);
			printf("%*c条件：\n", indent + 3, ' ');
			display(T->Cond, indent + 6);      //显示条件
			printf("%*cIF子句：(%d)\n", indent + 3, ' ', T->pos);
			display(T->IfStm, indent + 6);      //显示if子句
			printf("%*cELSE子句：(%d)\n", indent + 3, ' ', T->pos);
			display(T->ElseStm, indent + 6);      //显示else子句
			break;
		case DEF_LIST:      
			display(T->Def, indent);    //显示该局部变量定义列表中的第一个
			display(T->DefList, indent);    //显示其它局部变量定义
			break;
		case VAR_DEF:       
			printf("%*c局部变量定义：(%d)\n", indent, ' ', T->pos);
			display(T->Specifier, indent + 3);   //显示变量类型
			display(T->DecList, indent + 3);   //显示该定义的全部变量名
			break;
		case DEC_LIST:      
			printf("%*c变量名：\n", indent, ' ');
			T0 = T;
			while (T0) {
				if (T0->Dec->kind == ID)
					printf("%*c %s\n", indent + 6, ' ', T0->Dec->type_id);
				else if (T0->Dec->kind == ASSIGNOP)
				{
					printf("%*c %s ASSIGNOP\n ", indent + 6, ' ', T0->Dec->Dec->type_id);
					display(T0->Dec->Exp1, indent + strlen(T0->Dec->Dec->type_id) + 7);        //显示初始化表达式
				}
				else if (T0->Dec->kind == ARRAY_DEC) {
					printf("%*c数组名：%s\n", indent+3, ' ', T0->Dec->type_id);
					printf("%*c数组大小：\n", indent+3, ' ');
					display(T0->Dec->Dec, indent + 3);
				}
				T0 = T0->DecList;
			}
			break;
		case ID:	        
			printf("%*cID： %s\n", indent, ' ', T->type_id);
			break;
		/*case ARRAY:         
			display(T->Dec, indent);
			printf("%*c 维度大小[%d]\n", indent, ' ', T->arrsize);
			break;*/
		case ARRAY_LIST:
			display(T->Exp1, indent);
			display(T->Exp2, indent);
			break;
		case ARRAY_LAST:
			display(T->Exp1, indent);
			break;
		case INT:	        
			printf("%*cINT：%d\n", indent, ' ', T->type_int);
			break;
		case FLOAT:	        
			printf("%*cFLAOT：%f\n", indent, ' ', T->type_float);
			break;
		case CHAR:	        
			printf("%*cCHAR：%c\n", indent, ' ', T->type_char);
			break;
		case ASSIGNOP:
		case ADDASSIGNOP:
		case SUBASSIGNOP:
		case AND:
		case OR:
		case RELOP:
		case PLUS:
		case MINUS:
		case STAR:
		case DIV:
			printf("%*c%s\n", indent, ' ', T->type_id);
			display(T->Exp1, indent + 3);
			display(T->Exp2, indent + 3);
			break;
		/*case INDEX:
			printf("%*c%s\n", indent, ' ', T->type_id);
			display(T->Exp1, indent + 3);
			display(T->Exp2, indent + 3);
			break;*/
		case EXP_ARRAY:
			printf("%*c数组名： %s\n", indent, ' ', T->type_id);
			printf("%*c访问下标：\n", indent, ' ');
			display(T->Exp1, indent + 3);
			break;
		case DPLUS_PREFIX:
		case DPLUS_SUFFIX:
		case DMINUS_PREFIX:
		case DMINUS_SUFFIX:
		case NOT:
		case UMINUS:    
			printf("%*c%s\n", indent, ' ', T->type_id);
			display(T->Exp1, indent + 3);
			break;
		case FUNC_CALL: 
			printf("%*c函数调用：(%d)\n", indent, ' ', T->pos);
			printf("%*c函数名：%s\n", indent + 3, ' ', T->type_id);
			if (T->Args)
				display(T->Args, indent + 3);
			else printf("%*c 无参数\n", indent + 3, ' ');
			break;
		case ARGS:      
			i = 1;
			while (T) {  //ARGS表示实际参数表达式序列结点，其第一棵子树为其一个实际参数表达式，第二棵子树为剩下的
				struct ASTNode *T0 = T->Exp1;
				printf("%*c第%d个实际参数表达式：\n", indent, ' ', i++);
				display(T0, indent + 3);
				T = T->Args;
			}
			printf("\n");
			break;
		}
	}
}

int compute_width(struct ASTNode *T) {
	if (T) {
		if (T->type == INT) {
			return T->type_int;
		}
		return T->Exp1->type_int*compute_width(T->Exp2);
	}
	else
	{
		return 1;
	}
}

int compute_arraywidth(int *array, int index) {
	int res = 1;
	while (array[index] != 0 && index < 10) {
		res *= array[index];
		index++;
	}
	return res;
}

int compute_width0(struct ASTNode *T, int *array, int index) {
	if (T) {
		if (T->type == INT) {
			return T->type_int;
		}
		if (T->Exp1->kind == ID) {
			int rtn = searchSymbolTable(T->Exp1->type_id);
			return (symbolTable.symbols[rtn].const_int) * compute_arraywidth(array, index + 1) + compute_width0(T->Exp2, array, index + 1);
		}
		else
			return (T->Exp1->type_int) * compute_arraywidth(array, index + 1) + compute_width0(T->Exp2, array, index + 1);
	}
	else {
		return 1;
	}
}

/*连接两个char数组*/
char *strcat0(char *s1, char *s2) {
	static char result[10];
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

/*生成别名编号*/
char *newAlias() {
	static int no = 1;
	char s[10];
	itoa(no++, s, 10);
	return strcat0("v", s);
}

/*生成label编号*/
char *newLabel() {
	static int no = 1;
	char s[10];
	itoa(no++, s, 10);
	return strcat0("label", s);
}

/*生成temp编号*/
char *newTemp() {
	static int no = 1;
	char s[10];
	itoa(no++, s, 10);
	return strcat0("temp", s);
}

//中间代码生成：生成一条TAC代码的结点组成的双向循环链表，返回头指针
struct codenode *genIR(int op, struct opn opn1, struct opn opn2, struct opn result) {
	struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
	h->op = op;
	h->opn1 = opn1;
	h->opn2 = opn2;
	h->result = result;
	h->next = h->prior = h;
	return h;
}

//中间代码生成：生成一条标号语句，返回头指针
struct codenode *genLabel(char *label) {
	struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
	h->op = LABEL;
	strcpy(h->result.id, label);
	h->next = h->prior = h;
	return h;
}

//中间代码生成：生成GOTO语句，返回头指针
struct codenode *genGoto(char *label) {
	struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
	h->op = GOTO;
	strcpy(h->result.id, label);
	h->next = h->prior = h;
	return h;
}

//中间代码生成：合并多个中间代码的双向循环链表，首尾相连
struct codenode *merge(int num, ...) {
	struct codenode *h1, *h2, *t1, *t2;
	va_list ap;
	va_start(ap, num);
	h1 = va_arg(ap, struct codenode *);
	while (--num > 0) {
		h2 = va_arg(ap, struct codenode *);
		if (h1 == NULL) h1 = h2;
		else if (h2) {
			t1 = h1->prior;
			t2 = h2->prior;
			t1->next = h2;
			t2->next = h1;
			h1->prior = t2;
			h2->prior = t1;
		}
	}
	va_end(ap);
	return h1;
}

//中间代码生成：输出中间代码
void prnIR(struct codenode *head)
{
	char opnstr1[32], opnstr2[32], resultstr[32];
	struct codenode *h = head;
	do {
		if (h->opn1.kind == INT)
			sprintf(opnstr1, "#%d", h->opn1.const_int);
		if (h->opn1.kind == FLOAT)
			sprintf(opnstr1, "#%f", h->opn1.const_float);
		if (h->opn1.kind == CHAR)
			sprintf(opnstr1, "#%c", h->opn1.const_char);
		if (h->opn1.kind == ID)
			sprintf(opnstr1, "%s", h->opn1.id);
		if (h->opn2.kind == INT)
			sprintf(opnstr2, "#%d", h->opn2.const_int);
		if (h->opn2.kind == FLOAT)
			sprintf(opnstr2, "#%f", h->opn2.const_float);
		if (h->opn2.kind == CHAR)
			sprintf(opnstr2, "#%c", h->opn2.const_char);
		if (h->opn2.kind == ID)
			sprintf(opnstr2, "%s", h->opn2.id);
		sprintf(resultstr, "%s", h->result.id);
		switch (h->op)
		{
		case ASSIGNOP:  printf("  %s := %s\n", resultstr, opnstr1);
			break;
		case PLUS:
		case MINUS:
		case STAR:
		case DIV: printf("  %s := %s %c %s\n", resultstr, opnstr1, \
			h->op == PLUS ? '+' : h->op == MINUS ? '-' : h->op == STAR ? '*' : '\\', opnstr2);
			break;
		case FUNCTION: printf("\nFUNCTION %s :\n", h->result.id);
			break;
		case PARAM:    printf("  PARAM %s\n", h->result.id);
			break;
		case LABEL:    printf("LABEL %s :\n", h->result.id);
			break;
		case GOTO:     printf("  GOTO %s\n", h->result.id);
			break;
		case JLE:      printf("  IF %s <= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case JLT:      printf("  IF %s < %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case JGE:      printf("  IF %s >= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case JGT:      printf("  IF %s > %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case EQ:       printf("  IF %s == %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case NEQ:      printf("  IF %s != %s GOTO %s\n", opnstr1, opnstr2, resultstr);
			break;
		case ARG:      printf("  ARG %s\n", h->result.id);
			break;
		case CALL:     
			if (!strcmp(opnstr1, "write"))
				printf("  CALL  %s\n", opnstr1);
			else
				printf("  %s := CALL %s\n", resultstr, opnstr1);
			break;
		case RETURN:  
			if (h->result.kind)
				printf("  RETURN %s\n", resultstr);
			else
				printf("  RETURN\n");
			break;

		}
		h = h->next;
	} while (h != head);
}

void semantic_error(int line, char *msg1, char *msg2) {
	//这里可以只收集错误信息，最后一次显示
	printf("在%d行,%s %s\n", line, msg1, msg2);
}

void prn_symbol() { //显示符号表
	int i = 0;
	char tempType[10];
	printf("%6s %6s %6s  %6s %4s %6s\n", "变量名", "别 名", "层 号", "类  型", "标记", "偏移量");
	for (i = 0; i < symbolTable.index; i++)
	{
		if (symbolTable.symbols[i].type == INT)
			strcpy(tempType, "int");
		else if (symbolTable.symbols[i].type == FLOAT)
			strcpy(tempType, "float");
		else if (symbolTable.symbols[i].type == CHAR)
			strcpy(tempType, "char");
		printf("%6s %6s %6d  %6s %4c %6d\n", symbolTable.symbols[i].name, \
			symbolTable.symbols[i].alias, symbolTable.symbols[i].level, \
			tempType, \
			symbolTable.symbols[i].flag, symbolTable.symbols[i].offset);
	}
}

/*检测某个ID是否存在在符号表中，不存在返回-1*/
int searchSymbolTable(char *name) {
	int i, flag = 0;
	for (i = symbolTable.index - 1; i >= 0; i--) {
		if (symbolTable.symbols[i].level == 0)
			flag = 1;
		if (flag && symbolTable.symbols[i].level == 1)
			continue;   //跳过前面函数的形式参数表项
		if (!strcmp(symbolTable.symbols[i].name, name))  return i;
	}
	return -1;
}

/*添加一行符号到符号表*/
int fillSymbolTable(char *name, char *alias, int level, int type, char flag, int offset)
{
	//首先根据name查符号表，不能重复定义 重复定义返回-1
	int i;
	/*符号查重，考虑外部变量声明前有函数定义，
	其形参名还在符号表中，这时的外部变量与前函数的形参重名是允许的*/
	if (name)
		for (i = symbolTable.index - 1; i >= 0 && (symbolTable.symbols[i].level == level || level == 0); i--) {
			if (level == 0 && symbolTable.symbols[i].level == 1) continue;  //外部变量和形参不必比较重名
			if (!strcmp(symbolTable.symbols[i].name, name))  return -1;
		}
	//填写符号表内容
	strcpy(symbolTable.symbols[symbolTable.index].name, name);
	strcpy(symbolTable.symbols[symbolTable.index].alias, alias);
	symbolTable.symbols[symbolTable.index].level = level;
	symbolTable.symbols[symbolTable.index].type = type;
	symbolTable.symbols[symbolTable.index].flag = flag;
	symbolTable.symbols[symbolTable.index].offset = offset;
	return symbolTable.index++; //返回的是符号在符号表中的位置序号，中间代码生成时可用序号取到符号别名
}

//填写临时变量到符号表，返回临时变量在符号表中的位置
int fill_Temp(char *name, int level, int type, char flag, int offset) {
	strcpy(symbolTable.symbols[symbolTable.index].name, "");
	strcpy(symbolTable.symbols[symbolTable.index].alias, name);
	symbolTable.symbols[symbolTable.index].level = level;
	symbolTable.symbols[symbolTable.index].type = type;
	symbolTable.symbols[symbolTable.index].flag = flag;
	symbolTable.symbols[symbolTable.index].offset = offset;
	return symbolTable.index++; //返回的是临时变量在符号表中的位置序号
}

/*处理变量列表*/
void ext_var_list(struct ASTNode *T)
{  //处理变量列表
	int rtn;
	switch (T->kind) {
	case EXT_DEC_LIST:
		T->Dec->type = T->type;                  //将类型属性向下传递变量结点
		T->Dec->offset = T->offset;				 //外部变量的偏移量向下传递
		if (T->DecList) {
			T->DecList->type = T->type;              //将类型属性向下传递变量结点
			T->DecList->offset = T->offset + T->width; //外部变量的偏移量向下传递
			T->DecList->width = T->width;
		}
		ext_var_list(T->Dec);
		if (T->DecList){
			ext_var_list(T->DecList);
			T->num = T->DecList->num + 1;
		}
		break;
	case ID:                                     //最后一个变量名
		rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'V', T->offset);
		if (rtn == -1)
			semantic_error(T->pos, T->type_id, "变量重复定义");
		else T->place = rtn;
		T->num = 1;
		break;
	case ARRAY_DEC:
		arr_index = 0;
		strcpy(array_name, T->type_id);
		rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'A', T->offset);
		if (rtn == -1) {
			semantic_error(T->pos, T->type_id, "数组名称重复定义");
		}
		else {
			T->place = rtn;
			T->num = compute_width(T->Exp1);
			ext_var_list(T->Exp1);
			arr_flag = 1;
		}
		break;
	case ARRAY_LIST:
		rtn = searchSymbolTable(array_name);
		if (rtn == -1) {
			semantic_error(T->pos, array_name, "数组未定义");
		}
		if (T->Exp1->type != INT) {
			semantic_error(T->pos, "", "数组定义维数需要用整型");
		}
		else {
			symbolTable.symbols[rtn].array[arr_index] = T->Exp1->type_int;
			arr_index++;
			T->num = compute_width(T->Exp2);
			ext_var_list(T->Exp2);
		}
		break;
	case ARRAY_LAST:
		rtn = searchSymbolTable(array_name);
		if (rtn == -1) {
			semantic_error(T->pos, array_name, "数组未定义");
		}
		if (T->Exp1->type != INT) {
			semantic_error(T->pos, "", "数组定义维数需要用整型");
		}
		else {
			symbolTable.symbols[rtn].array[arr_index] = T->Exp1->type_int;
		}
		break;
	}
}

/*检验函数传入时的传入参数是否类型对应、数量对应*/
int  match_param(int i, struct ASTNode *T)
{  //i代表函数名在符号表中的位置
	int j, num = symbolTable.symbols[i].paramnum;
	if (num == 0 && T == NULL) return 1;//无参函数
	int type1, type2, pos = T->pos;
	for (j = 1; j <= num; j++) {  //比较参数
		if (T==NULL) {
			semantic_error(pos, "", "函数调用参数太少!");
			return 0;
		}
		type1 = symbolTable.symbols[i + j].type;  //形参类型
		type2 = T->Exp1->type;
		if (type1 != type2) {
			semantic_error(pos, "", "参数类型不匹配");
			return 0;
		}
		T = T->Args;
	}
	if (T) { //num个参数已经匹配完，还有实参表达式
		semantic_error(pos, "", "函数调用参数太多!");
		return 0;
	}
	return 1;
}

/*处理布尔表达式的符号表定义*/
void boolExp(struct ASTNode *T)
{  //布尔表达式，参考文献[2]p84的思想
	struct opn opn1, opn2, result;
	int op, rtn;
	if (T)
	{
		switch (T->kind) {
		case INT:
			if (T->type_int != 0)
				T->code = genGoto(T->Etrue);
			else
				T->code = genGoto(T->Efalse);
			T->width = 4;
			break;
		case FLOAT:
			if (T->type_float != 0.0)
				T->code = genGoto(T->Etrue);
			else
				T->code = genGoto(T->Efalse);
			T->width = 8;
			break;
		case CHAR:
			T->width = 1;
			break;
		case ID:
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
				semantic_error(T->pos, T->type_id, "变量未定义");
			if (symbolTable.symbols[rtn].flag == 'F')
				semantic_error(T->pos, T->type_id, "是函数名，类型不匹配");
			else {
				opn1.kind = ID;
				strcpy(opn1.id, symbolTable.symbols[rtn].alias);
				opn1.offset = symbolTable.symbols[rtn].offset;
				opn2.kind = INT;
				opn2.const_int = 0;
				result.kind = ID;
				strcpy(result.id, T->Etrue);
				T->code = genIR(NEQ, opn1, opn2, result);
				T->code = merge(2, T->code, genGoto(T->Efalse));
			}
			T->width = 0;
			break;
		case RELOP: //处理关系运算表达式,2个操作数都按基本表达式处理
			T->Exp1->offset = T->Exp2->offset = T->offset;
			Exp(T->Exp1);
			T->width = T->Exp1->width;
			Exp(T->Exp2);
			if (T->width < T->Exp2->width) T->width = T->Exp2->width;
			opn1.kind = ID; strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias);
			opn1.offset = symbolTable.symbols[T->Exp1->place].offset;
			opn2.kind = ID; strcpy(opn2.id, symbolTable.symbols[T->Exp2->place].alias);
			opn2.offset = symbolTable.symbols[T->Exp2->place].offset;
			result.kind = ID; strcpy(result.id, T->Etrue);
			if (strcmp(T->type_id, "<") == 0)
				op = JLT;
			else if (strcmp(T->type_id, "<=") == 0)
				op = JLE;
			else if (strcmp(T->type_id, ">") == 0)
				op = JGT;
			else if (strcmp(T->type_id, ">=") == 0)
				op = JGE;
			else if (strcmp(T->type_id, "==") == 0)
				op = EQ;
			else if (strcmp(T->type_id, "!=") == 0)
				op = NEQ;
			T->code = genIR(op, opn1, opn2, result);
			T->code = merge(4, T->Exp1->code, T->Exp2->code, T->code, genGoto(T->Efalse));
			break;
		case AND:
		case OR:
			if (T->kind == AND)
			{
				strcpy(T->Exp1->Etrue, newLabel());
				strcpy(T->Exp2->Efalse, T->Efalse);
			}
			else
			{
				strcpy(T->Exp1->Etrue, T->Etrue);
				strcpy(T->Exp1->Efalse, newLabel());
			}
			strcpy(T->Exp2->Etrue, T->Etrue);
			strcpy(T->Exp2->Efalse, T->Efalse);
			T->Exp1->offset = T->Exp2->offset = T->offset;
			boolExp(T->Exp1);
			T->width = T->Exp1->width;
			boolExp(T->Exp2);
			if (T->width < T->Exp2->width) T->width = T->Exp2->width;
			if (T->kind == AND)
				T->code = merge(3, T->Exp1->code, genLabel(T->Exp1->Etrue), T->Exp2->code);
			else
				T->code = merge(3, T->Exp1->code, genLabel(T->Exp1->Efalse), T->Exp2->code);
			break;
		case NOT:
			strcpy(T->Exp1->Etrue, T->Efalse);
			strcpy(T->Exp1->Efalse, T->Etrue);
			boolExp(T->Exp1);
			T->code = T->Exp1->code;
			break;
		}
	}
}


/*处理基本表达式*/
void Exp(struct ASTNode *T)
{//处理基本表达式，参考文献[2]p82的思想
	int rtn, num, width;
	struct ASTNode *T0;
	struct opn opn1, opn2, result, result2;
	if (T)
	{
		switch (T->kind)
		{
		case ID:    //查符号表，获得符号表中的位置，类型送type
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
				semantic_error(T->pos, T->type_id, "变量未定义");
			else if (symbolTable.symbols[rtn].flag == 'F')
				semantic_error(T->pos, T->type_id, "是函数名，类型不匹配");
			else if (symbolTable.symbols[rtn].flag == 'A')
				semantic_error(T->pos, T->type_id, "是数组名，类型不匹配");
			else
			{
				T->place = rtn;       //结点保存变量在符号表中的位置
				T->code = NULL;       //标识符不需要生成TAC
				T->type = symbolTable.symbols[rtn].type;
				T->offset = symbolTable.symbols[rtn].offset;
				T->width = 0;         //未再使用新单元
			}
			break;
		case INT:
			//为整常量生成一个临时变量，T->place表示临时变量在符号表位置
			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
			T->type = INT;
			opn1.kind = INT;
			opn1.const_int = T->type_int;
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = genIR(ASSIGNOP, opn1, opn2, result);
			T->width = 4;
			break;
		case FLOAT://为浮点常量生成一个临时变量
			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
			T->type = FLOAT;
			opn1.kind = FLOAT; opn1.const_float = T->type_float;
			result.kind = ID; strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = genIR(ASSIGNOP, opn1, opn2, result);
			T->width = 8;
			break;
		case CHAR:
			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
			T->type = CHAR;
			opn1.kind = CHAR;
			opn1.const_float = T->type_char;
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = genIR(ASSIGNOP, opn1, opn2, result);
			T->width = 1;
			break;
		case ASSIGNOP:
			if (T->Exp1->kind != ID && T->Exp1->kind != EXP_ARRAY)
			{
				semantic_error(T->pos, "", "赋值语句需要左值");
			}
			else
			{
				T->Exp1->offset = T->offset;
				Exp(T->Exp1);   //处理左值，例中仅为变量
				T->offset += T->Exp1->width; //如果左值是下标变量，with会大于0
				//T->Exp2->offset = T->offset;
				Exp(T->Exp2);

				if (T->Exp1->type != T->Exp2->type) {
					semantic_error(T->pos, "", "赋值运算左右类型不匹配");
					return;
				}

				if (symbolTable.symbols[T->Exp1->place].type == INT) {
					symbolTable.symbols[T->Exp1->place].const_int = T->Exp2->type_int;
				}

				T->type = T->Exp1->type;
				T->width = T->Exp1->width + T->Exp2->width;
				T->code = merge(2, T->Exp1->code, T->Exp2->code);

				if (T->Exp2->kind != EXP_ARRAY) {
					opn1.kind = ID;
					strcpy(opn1.id, symbolTable.symbols[T->Exp2->place].alias); //右值一定是个变量或临时变量
					opn1.offset = symbolTable.symbols[T->Exp2->place].offset;
				}
				/*
				ID Arraylist  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=EXP_ARRAY; $$->pos=yylineno;   $$->Exp1=$2;strcpy($$->type_id,$1);}

				Arraylist: LS Exp RS {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=ARRAY_LAST;$$->Exp1=$2;$$->pos=yylineno;}
						| LS Exp RS Arraylist {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=ARRAY_LIST;$$->Exp1=$2;$$->pos=yylineno;$$->Exp2=$4;}

				   | ID                 {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ID;
							   $$->pos=yylineno;  strcpy($$->type_id,$1);}                                   //变量
					 | INT          {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=INT;
							   $$->pos=yylineno;  $$->type=INT;$$->type_int=$1;}    //整型常量
				*/
				else {
					opn1.kind = ID;
					char s[10];
					char str[80];
					strcpy(str, symbolTable.symbols[T->Exp2->place].alias);
					strcat(str, " offset ");
					sprintf(s, "%d", T->Exp2->offset);
					strcat(str, s);
					strcpy(opn1.id, str);
					opn1.offset = symbolTable.symbols[T->Exp2->place].offset + T->Exp2->offset;
					//here
					/*if (T->Exp2->checkID == 'I') {
						strcpy(str, symbolTable.symbols[T->Exp2->place].alias);
						strcat(str, " offset ");
						int temprtn = searchSymbolTable(T->Exp2->Exp1->Exp1->type_id);

						sprintf(s, "%s", symbolTable.symbols[temprtn].alias);
						strcat(str, s);
						strcpy(opn1.id, str);
						opn1.arrIDFlag = 1;
						opn1.offset = symbolTable.symbols[T->Exp2->place].offset;
						//offset取决于ID的值
						//opn1.offset = symbolTable.symbols[T->Exp2->place].offset + T->Exp2->offset;
					}
					else {
						strcpy(str, symbolTable.symbols[T->Exp2->place].alias);
						strcat(str, " offset ");
						sprintf(s, "%d", T->Exp2->offset);
						strcat(str, s);
						strcpy(opn1.id, str);
						opn1.offset = symbolTable.symbols[T->Exp2->place].offset + T->Exp2->offset;
					}*/
				}
				//opn1.kind = ID;   //右值一定是个变量或常量生成的临时变量
				//strcpy(opn1.id, symbolTable.symbols[T->Exp2->place].alias);
				//opn1.offset = symbolTable.symbols[T->Exp2->place].offset;
				if (T->Exp1->kind != EXP_ARRAY) {
					result.kind = ID;
					strcpy(result.id, symbolTable.symbols[T->Exp1->place].alias);
					result.offset = symbolTable.symbols[T->Exp1->place].offset;
				}
				else {
					result.kind = ID;
					char s[10];
					char str[80];
					strcpy(str, symbolTable.symbols[T->Exp1->place].alias);
					strcat(str, " offset ");
					sprintf(s, "%d", T->Exp1->offset);
					strcat(str, s);
					strcpy(result.id, str);
					result.offset = symbolTable.symbols[T->Exp1->place].offset + T->Exp1->offset;
					/*if (T->Exp1->checkID == 'I') {
						strcpy(str, symbolTable.symbols[T->Exp1->place].alias);
						strcat(str, " offset ");
						int temprtn = searchSymbolTable(T->Exp1->Exp1->Exp1->type_id);

						sprintf(s, "%s", symbolTable.symbols[temprtn].alias);
						strcat(str, s);
						strcpy(result.id, str);
						result.arrIDFlag = 1;
						result.offset = symbolTable.symbols[T->Exp1->place].offset;
						//offset取决于ID的值
						//opn1.offset = symbolTable.symbols[T->Exp1->place].offset + T->Exp1->offset;
					}
					else {
						strcpy(str, symbolTable.symbols[T->Exp1->place].alias);
						strcat(str, " offset ");
						sprintf(s, "%d", T->Exp1->offset);
						strcat(str, s);
						strcpy(result.id, str);
						result.offset = symbolTable.symbols[T->Exp1->place].offset + T->Exp1->offset;
					}*/
					
					
				}
				//result.kind = ID;
				//strcpy(result.id, symbolTable.symbols[T->Exp1->place].alias);
				//result.offset = symbolTable.symbols[T->Exp1->place].offset;
				T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));
			}
			break;
		case ADDASSIGNOP:
		case SUBASSIGNOP:
			if (T->Exp1->kind != ID && T->Exp1->kind != EXP_ARRAY) {
				semantic_error(T->pos, "", "不可参与运算的左值");
			}
			else {
				T->Exp1->offset = T->offset;
				Exp(T->Exp1);
				T->Exp2->offset = T->offset + T->Exp1->width;
				Exp(T->Exp2);
				T->type = T->Exp1->type;
				T->width = T->Exp2->width;
				T->code = merge(2, T->Exp1->code, T->Exp2->code);
				if (T->Exp1->kind != EXP_ARRAY) {
					result.kind = ID;
					strcpy(result.id, symbolTable.symbols[T->Exp1->place].alias);
					//result.type = T->type;
					result.offset = symbolTable.symbols[T->Exp1->place].offset;
					opn1.kind = ID;
					strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias); //右值一定是个变量或临时变量
					opn1.offset = symbolTable.symbols[T->Exp1->place].offset;
					
				}
				else {
					result.kind = ID;
					opn1.kind = ID;
					char s[10];
					char str[80];
					strcpy(str, symbolTable.symbols[T->Exp1->place].alias);
					strcat(str, " offset ");
					sprintf(s, "%d", T->Exp1->offset);
					strcat(str, s);
					strcpy(opn1.id, str);
					strcpy(result.id, str);
					result.offset = symbolTable.symbols[T->Exp1->place].offset + T->Exp1->offset;
					opn1.offset = symbolTable.symbols[T->Exp1->place].offset + T->Exp1->offset;
				}

				/*opn1.kind = ID;
				strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias); //右值一定是个变量或临时变量
				opn1.offset = symbolTable.symbols[T->Exp1->place].offset;

				opn2.kind = ID;
				strcpy(opn2.id, symbolTable.symbols[T->Exp2->place].alias);
				opn2.offset = symbolTable.symbols[T->Exp2->place].offset;

				result.kind = ID;
				strcpy(result.id, symbolTable.symbols[T->Exp1->place].alias);
				result.type = T->type;
				result.offset = symbolTable.symbols[T->Exp1->place].offset;*/

				if (T->Exp2->kind != EXP_ARRAY) {
					opn2.kind = ID;
					strcpy(opn2.id, symbolTable.symbols[T->Exp2->place].alias);
					opn2.offset = symbolTable.symbols[T->Exp2->place].offset;
				}
				else {
					opn2.kind = ID;
					char s[10];
					char str[80];
					strcpy(str, symbolTable.symbols[T->Exp2->place].alias);
					strcat(str, " offset ");
					sprintf(s, "%d", T->Exp2->offset);
					strcat(str, s);
					strcpy(opn2.id, str);
					opn2.offset = symbolTable.symbols[T->Exp2->place].offset + T->Exp2->offset;
				}
				if (T->kind == ADDASSIGNOP)
					T->code = merge(2, T->code, genIR(PLUS, opn1, opn2, result));
				else if (T->kind == SUBASSIGNOP)
					T->code = merge(2, T->code, genIR(MINUS, opn1, opn2, result));
			}
			break;
		case DPLUS_PREFIX:
		case DPLUS_SUFFIX:
		case DMINUS_PREFIX:
		case DMINUS_SUFFIX:
			if (T->Exp1->kind != ID && T->Exp1->kind != EXP_ARRAY) {
				semantic_error(T->pos, "", "错误的自增自减变量");
			}
			else {
				T->Exp1->offset = T->offset;
				Exp(T->Exp1);
				T->type = T->Exp1->type;
				T->width = T->Exp1->width;

				T->place = T->Exp1->place;

				opn1.kind = INT;
				opn1.const_int = 1;
				result.kind = ID;
				strcpy(result.id, newTemp());
				T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));//T1=OP1+OP2,OP1=1,OP2=0

				opn1.kind = ID;
				strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias);

				result2.kind = ID;
				strcpy(result2.id, newTemp());

				if (T->kind == DPLUS_PREFIX || T->kind == DPLUS_SUFFIX)
					T->code = merge(2, T->code, genIR(PLUS, opn1, result, result2));//T2=X1+T1,T1=1
				else if (T->kind == DMINUS_PREFIX || T->kind == DMINUS_SUFFIX)
					T->code = merge(2, T->code, genIR(MINUS, opn1, result, result2));//T2=X1-T1,T1=1

				T->code = merge(2, T->code, genIR(ASSIGNOP, result2, opn2, opn1));//X1=T2+OP2,OP2=0

			}
			break;
		case AND:   //按算术表达式方式计算布尔值，未写完
		case OR:    //按算术表达式方式计算布尔值，未写完
		case RELOP: //按算术表达式方式计算布尔值，未写完
			T->type = INT;
			T->Exp1->offset = T->Exp2->offset = T->offset;
			//Exp(T->Exp1);
			//Exp(T->Exp2);
			boolExp(T);
			break;
		case PLUS:
		case MINUS:
		case STAR:
		case DIV:
			T->Exp1->offset = T->offset;
			Exp(T->Exp1);
			T->Exp2->offset = T->offset + T->Exp1->width;
			Exp(T->Exp2);
			//判断T->Exp1，T->Exp2类型是否正确，可能根据运算符生成不同形式的代码，给T的type赋值
			//下面的类型属性计算，没有考虑错误处理情况
			if (T->Exp1->type == FLOAT && T->Exp2->type == FLOAT) {
				T->type = FLOAT;
				//T->width = T->Exp1->width + T->Exp2->width + 4;
			}
			else if (T->Exp1->type == INT && T->Exp2->type == INT){
				T->type = INT;
				//T->width = T->Exp1->width + T->Exp2->width + 2;
			}
			else if (T->Exp1->type == CHAR && T->Exp2->type == CHAR) {
				T->type = CHAR;
				//T->width = T->Exp1->width + T->Exp2->width + 1;
			}
			else {
				semantic_error(T->pos, "", "两个运算数的类型不统一");
				return;
			}

			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->Exp1->width + T->Exp2->width);

			if (T->Exp1->kind != EXP_ARRAY) {
				opn1.kind = ID;
				strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias); //右值一定是个变量或临时变量
				opn1.type = T->Exp1->type;
				opn1.offset = symbolTable.symbols[T->Exp1->place].offset;
			}
			else {
				opn1.kind = ID;
				char s[10];
				char str[80];
				strcpy(str, symbolTable.symbols[T->Exp1->place].alias);
				strcat(str, " offset ");
				sprintf(s, "%d", T->Exp1->offset);
				strcat(str, s);
				strcpy(opn1.id, str);
				opn1.offset = symbolTable.symbols[T->Exp1->place].offset + T->Exp1->offset;
			}
			/*opn1.kind = ID; 
			strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias);
			opn1.type = T->Exp1->type;
			opn1.offset = symbolTable.symbols[T->Exp1->place].offset;*/
			if (T->Exp2->kind != EXP_ARRAY) {
				opn2.kind = ID;
				strcpy(opn2.id, symbolTable.symbols[T->Exp2->place].alias); //右值一定是个变量或临时变量
				opn2.type = T->Exp2->type;
				opn2.offset = symbolTable.symbols[T->Exp2->place].offset;
			}
			else {
				opn2.kind = ID;
				char s[10];
				char str[80];
				strcpy(str, symbolTable.symbols[T->Exp2->place].alias);
				strcat(str, " offset ");
				sprintf(s, "%d", T->Exp2->offset);
				strcat(str, s);
				strcpy(opn2.id, str);
				opn2.offset = symbolTable.symbols[T->Exp2->place].offset + T->Exp2->offset;
			}
			/*opn2.kind = ID;
			strcpy(opn2.id, symbolTable.symbols[T->Exp2->place].alias);
			opn2.type = T->Exp2->type;
			opn2.offset = symbolTable.symbols[T->Exp2->place].offset;*/

			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.type = T->type;
			result.offset = symbolTable.symbols[T->place].offset;

			T->code = merge(3, T->Exp1->code, T->Exp2->code, genIR(T->kind, opn1, opn2, result));
			if (T->type == INT) {
				T->width = T->Exp1->width + T->Exp2->width + 4;
			}
			else if (T->type == FLOAT) {
				T->width = T->Exp1->width + T->Exp2->width + 8;
			}
			else if (T->type == CHAR) {
				T->width = T->Exp1->width + T->Exp2->width + 1;
			}
			break;
		case NOT:   //未写完整
			T->type = INT;
			T->Exp1->offset = T->offset;
			boolExp(T);
			break;
		case UMINUS://未写完整
			break;
		case FUNC_CALL: //根据T->type_id查出函数的定义，如果语言中增加了实验教材的read，write需要单独处理一下
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1) {
				semantic_error(T->pos, T->type_id, "函数未定义");
				break;
			}
			if (symbolTable.symbols[rtn].flag != 'F') {
				semantic_error(T->pos, T->type_id, "不是一个函数");
				break;
			}
			T->type = symbolTable.symbols[rtn].type;
			if (T->type == INT) {
				width = 4;
			}
			else if (T->type == FLOAT) {
				width = 8;
			}
			else if (T->type == CHAR) {
				width = 1;
			} //存放函数返回值的单数字节数
			if (T->Args) {
				T->Args->offset = T->offset;
				Exp(T->Args);       //处理所有实参表达式求值，及类型
				T->width = T->Args->width + width; //累加上计算实参使用临时变量的单元数
				T->code = T->Args->code;
			}
			else { 
				T->width = width; 
				T->code = NULL; 
			}
			
			match_param(rtn, T->Args);   //处理所有参数的匹配

				//处理参数列表的中间代码
			T0 = T->Args;
			while (T0)
			{  //用ARG依次列出实参表达式的值
				if (T0->Exp1->kind != EXP_ARRAY) {
					//opn1.kind = ID;
					//strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias); //右值一定是个变量或临时变量
					//opn1.offset = symbolTable.symbols[T->Exp1->place].offset;
					result.kind = ID;
					strcpy(result.id, symbolTable.symbols[T0->Exp1->place].alias);
					result.offset = symbolTable.symbols[T0->Exp1->place].offset;
				}
				else {
					result.kind = ID;
					char s[10];
					char str[80];
					strcpy(str, symbolTable.symbols[T0->Exp1->place].alias);
					strcat(str, " offset ");
					sprintf(s, "%d", T0->Exp1->offset);
					strcat(str, s);
					strcpy(result.id, str);
					result.offset = symbolTable.symbols[T0->Exp1->place].offset + T0->Exp1->offset;
				}
				
				T->code = merge(2, T->code, genIR(ARG, opn1, opn2, result));
				T0 = T0->Args;
			}
			//printf("T->offset: %d  T->width: %d  width: %d ", T->offset, T->width, width);
			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->width - width);
			opn1.kind = ID;
			strcpy(opn1.id, T->type_id);  //保存函数名
			opn1.offset = rtn;//用offset保存函数定义入口,在目标代码生成时，能获取相应信息
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = merge(2, T->code, genIR(CALL, opn1, opn2, result));//生成函数调用中间代码
			break;
		case ARGS:      //此处仅处理各实参表达式的求值的代码序列，不生成ARG的实参系列
			T->Exp1->offset = T->offset;
			Exp(T->Exp1);
			T->width = T->Exp1->width;
			T->code = T->Exp1->code;
			if (T->Args) {
				T->Args->offset = T->offset + T->Exp1->width;
				Exp(T->Args);
				T->width += T->Args->width;
				T->code = merge(2, T->code, T->Args->code);
			}
			break;
		case EXP_ARRAY:
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
				semantic_error(T->pos, T->type_id, "变量未定义");
			else if (symbolTable.symbols[rtn].flag != 'A')
				semantic_error(T->pos, T->type_id, "变量不是数组");
			else {
				int index = 0;
				T0 = T->Exp1;
				T->place = rtn;       //结点保存变量在符号表中的位置
				T->code = NULL;       //标识符不需要生成TAC
				T->type = symbolTable.symbols[rtn].type; // 标记ID类型
				
				//此处计算出了偏移地址，写死了
				//printf(": %d \n", T->Exp1->Exp1->kind);
				
				T->offset = (T->type == INT ? 4 : (T->type == FLOAT ? 8 : 1)) * (compute_width0(T->Exp1, symbolTable.symbols[rtn].array, 0) - 1);//
				
				//if (T->Exp1->Exp1->kind == ID)
					//T->checkID = 'I';//用ID表示下标时，每次使用需重新计算offset
				
				//printf(" %c \n", T->checkID);
				
				T->width = 0;   //未再使用新单元
				// T0->ptr[0]->offset = T->offset;
				// printf("!!%d\n", T0->ptr[0]->offset);
				while (T0->kind == ARRAY_LIST) {
					Exp(T0->Exp1);
					if (T0->Exp1->type != INT) {
						semantic_error(T->pos, "", "数组长度必须是整型");
						break;
					}
					if (index == 8) {
						semantic_error(T->pos, "", "数组维度过高");
						break;
					}
					else if (symbolTable.symbols[rtn].array[index] <= T0->type_int) {
						semantic_error(T->pos, "", "数组越界访问");
						break;
					}
					index++;
					T0 = T0->Exp2;
					T->width += 4;
				}
				//处理最后一维
				if (T0->kind == ARRAY_LAST) {
					Exp(T0->Exp1);
					if (T0->Exp1->type != INT) {
						semantic_error(T->pos, "", "数组长度必须是整型");
					}
					else if (index == 8) {
						semantic_error(T->pos, "", "数组维度过高");
					}
					if (T0->Exp1->kind == ID) {
						if (symbolTable.symbols[rtn].array[index] <= symbolTable.symbols[T0->Exp1->place].const_int) {
							semantic_error(T->pos, "", "数组越界访问");
						}
					}
					else {
						if (symbolTable.symbols[rtn].array[index] <= T0->Exp1->type_int) {
							semantic_error(T->pos, "", "数组越界访问");
						}
					}
					T->width += 4;
				}
			}
		}
		
	}
}

void semantic_Analysis(struct ASTNode *T)
{//对抽象语法树的先根遍历,按display的控制结构修改完成符号表管理和语义检查和TAC生成（语句部分）
	int rtn, num, width;
	struct ASTNode *T0;
	struct opn opn1, opn2, result;
	if (T)
	{
		switch (T->kind)
		{
		case EXT_DEF_LIST:
			if (!T->Def) break;
			T->Def->offset = T->offset;
			semantic_Analysis(T->Def);    //访问外部定义列表中的第一个
			T->code = T->Def->code;
			if (T->DefList) {
				T->DefList->offset = T->Def->offset + T->Def->width;
				semantic_Analysis(T->DefList); //访问该外部定义列表中的其它外部定义
				T->code = merge(2, T->code, T->DefList->code);
			}
			break;
		case EXT_VAR_DEF:   //处理外部说明,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
			if (!strcmp(T->Specifier->type_id, "int")){
				T->type = T->DecList->type = INT;
				T->DecList->width = 4;
			}
			else if (!strcmp(T->Specifier->type_id, "float")){
				T->type = T->DecList->type = FLOAT;
				T->DecList->width = 8;
			}
			else if (!strcmp(T->Specifier->type_id, "char")){
				T->type = T->DecList->type = CHAR;
				T->DecList->width = 1;
			}
			//T->type = T->DecList->type = !strcmp(T->Specifier->type_id, "int") ? INT : FLOAT;
			T->DecList->offset = T->offset;        //这个外部变量的偏移量向下传递
			//T->DecList->width = T->type == INT ? 4 : 8;  //将一个变量的宽度向下传递
			ext_var_list(T->DecList);            //处理外部变量说明中的标识符序列
			T->width = T->DecList->width*T->DecList->num; //计算这个外部变量说明的宽度
			T->code = NULL;                        //这里假定外部变量不支持初始化
			break;
		case FUNC_DEF:      //填写函数定义信息到符号表
			if (!strcmp(T->Specifier->type_id, "int")){
				T->FuncDec->type = INT;
			}
			else if (!strcmp(T->Specifier->type_id, "float")){
				T->FuncDec->type = FLOAT;
			}
			else if (!strcmp(T->Specifier->type_id, "char")){
				T->FuncDec->type = CHAR;
			}
			//T->FuncDec->type = !strcmp(T->Specifier->type_id, "int") ? INT : FLOAT;//获取函数返回类型送到含函数名、参数的结点
			T->width = 0;     //函数的宽度设置为0，不会对外部变量的地址分配产生影响
			T->offset = DX;   //设置局部变量在活动记录中的偏移量初值
			T->FuncDec->offset = DX;
			semantic_Analysis(T->FuncDec); //处理函数名和参数结点部分，这里不考虑用寄存器传递参数
			T->offset += T->FuncDec->width;   //用形参单元宽度修改函数局部变量的起始偏移量
			T->Body->offset = T->offset;
			strcpy(T->Body->Snext, newLabel());  //函数体语句执行结束后的位置属性
			semantic_Analysis(T->Body);         //处理函数体结点
			//计算活动记录大小,这里offset属性存放的是活动记录大小，不是偏移
			symbolTable.symbols[T->FuncDec->place].offset = T->offset + T->Body->width;
			T->code = merge(3, T->FuncDec->code, T->Body->code, genLabel(T->Body->Snext));          //函数体的代码作为函数的代码
			break;
		case FUNC_DEC:      //根据返回类型，函数名填写符号表
			rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'F', 0);//函数不在数据区中分配单元，偏移量为0
			if (rtn == -1) {
				semantic_error(T->pos, T->type_id, "函数重复定义");
				break;
			}
			else T->place = rtn;
			result.kind = ID;   strcpy(result.id, T->type_id);
			result.offset = rtn;
			T->code = genIR(FUNCTION, opn1, opn2, result);     //生成中间代码：FUNCTION 函数名
			T->offset = DX;   //设置形式参数在活动记录中的偏移量初值
			if (T->ParamList) { //判断是否有参数
				T->ParamList->offset = T->offset;
				semantic_Analysis(T->ParamList);  //处理函数参数列表
				T->width = T->ParamList->width;
				symbolTable.symbols[rtn].paramnum = T->ParamList->num;
				T->code = merge(2, T->code, T->ParamList->code);  //连接函数名和参数代码序列
			}
			else symbolTable.symbols[rtn].paramnum = 0, T->width = 0;
			break;
		case PARAM_LIST:    //处理函数形式参数列表
			T->Param->offset = T->offset;
			semantic_Analysis(T->Param);
			if (T->ParamList)
			{
				T->ParamList->offset = T->offset + T->Param->width;
				semantic_Analysis(T->ParamList);
				T->num = T->Param->num + T->ParamList->num;        //统计参数个数
				T->width = T->Param->width + T->ParamList->width;  //累加参数单元宽度
				T->code = merge(2, T->Param->code, T->ParamList->code);  //连接参数代码
			}
			else
			{
				T->num = T->Param->num;
				T->width = T->Param->width;
				T->code = T->Param->code;
			}
			break;
		case  PARAM_DEC:
			rtn = fillSymbolTable(T->ID->type_id, newAlias(), 1, T->Specifier->type, 'P', T->offset);
			if (rtn == -1)
				semantic_error(T->ID->pos, T->ID->type_id, "参数名重复定义");
			else T->ID->place = rtn;
			T->num = 1;       //参数个数计算的初始值
			if (T->Specifier->type == INT) {
				T->width = 4;
			}
			if (T->Specifier->type == FLOAT) {
				T->width = 8;
			}
			if (T->Specifier->type == CHAR) {
				T->width = 1;
			}
			//T->width = T->Specifier->type == INT ? 4 : 8;  //参数宽度
			result.kind = ID;   strcpy(result.id, symbolTable.symbols[rtn].alias);
			result.offset = T->offset;
			T->code = genIR(PARAM, opn1, opn2, result);     //生成：FUNCTION 函数名
			break;
		case COMP_STM:
			LEV++;
			//设置层号加1，并且保存该层局部变量在符号表中的起始位置在symbol_scope_TX
			symbol_scope_TX.TX[symbol_scope_TX.top++] = symbolTable.index;
			T->width = 0;
			T->code = NULL;
			if (T->DefList) {
				T->DefList->offset = T->offset;
				semantic_Analysis(T->DefList);  //处理该层的局部变量DEF_LIST
				T->width += T->DefList->width;
				T->code = T->DefList->code;
			}
			if (T->StmList) {
				T->StmList->offset = T->offset + T->width;
				strcpy(T->StmList->Snext, T->Snext);  //S.next属性向下传递
				semantic_Analysis(T->StmList);       //处理复合语句的语句序列
				T->width += T->StmList->width;
				T->code = merge(2, T->code, T->StmList->code);
			}
#if (DEBUG1)
			if (LEV == 1)
				printf("\n第%d行函数的函数体结束前符号表(共2层）：\n", T->pos);
			else printf("\n第%d行复合语句结束前符号表(共%d层)：\n", T->pos, LEV + 1);
			prn_symbol();       //c在退出一个复合语句前显示的符号表
			system("pause");
#endif
			LEV--;    //出复合语句，层号减1
			symbolTable.index = symbol_scope_TX.TX[--symbol_scope_TX.top]; //删除该作用域中的符号
			break;
		case DEF_LIST:
			T->code = NULL;
			if (T->Def) {
				T->Def->offset = T->offset;
				semantic_Analysis(T->Def);   //处理一个局部变量定义
				T->code = T->Def->code;
				T->width = T->Def->width;
			}
			if (T->DefList) {
				T->DefList->offset = T->offset + T->Def->width;
				semantic_Analysis(T->DefList);   //处理剩下的局部变量定义
				T->code = merge(2, T->code, T->DefList->code);
				T->width += T->DefList->width;
			}
			break;
		case VAR_DEF://处理一个局部变量定义,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
				 //类似于上面的外部变量EXT_VAR_DEF，换了一种处理方法
			T->code = NULL;
			if (!strcmp(T->Specifier->type_id, "int")){
				T->DecList->type = INT;
				width = 4;
			}
			else if (!strcmp(T->Specifier->type_id, "float")){
				T->DecList->type = FLOAT;
				width = 8;
			}
			else if (!strcmp(T->Specifier->type_id, "char")){
				T->DecList->type = CHAR;
				width = 1;
			}
			//T->DecList->type = !strcmp(T->Specifier->type_id, "int") ? INT : FLOAT;  //确定变量序列各变量类型
			T0 = T->DecList; //T0为变量名列表子树根指针，对ID、ASSIGNOP类结点在登记到符号表，作为局部变量
			num = 0;
			T0->offset = T->offset;
			T->width = 0;
			//width = T->DecList->type == INT ? 4 : 8;  //一个变量宽度
			while (T0)
			{  //处理所以DEC_LIST结点
				num++;
				T0->Dec->type = T0->type;  //类型属性向下传递
				if (T0->DecList) T0->DecList->type = T0->type;
				T0->Dec->offset = T0->offset;  //类型属性向下传递
				if (T0->DecList) T0->DecList->offset = T0->offset + width;
				if (T0->Dec->kind == ID)
				{
					rtn = fillSymbolTable(T0->Dec->type_id, newAlias(), LEV, T0->Dec->type, 'V', T->offset + T->width);//此处偏移量未计算，暂时为0
					if (rtn == -1)
						semantic_error(T0->Dec->pos, T0->Dec->type_id, "变量重复定义");
					else T0->Dec->place = rtn;
					T->width += width;
				}
				else if (T0->Dec->kind == ASSIGNOP)
				{
					rtn = fillSymbolTable(T0->Dec->Dec->type_id, newAlias(), LEV, T0->Dec->type, 'V', T->offset + T->width);//此处偏移量未计算，暂时为0
					if (rtn == -1)
						semantic_error(T0->Dec->Dec->pos, T0->Dec->Dec->type_id, "变量重复定义");
					else
					{
						T0->Dec->place = rtn;
						T0->Dec->Exp2->offset = T->offset + T->width + width;
						Exp(T0->Dec->Exp2);
						opn1.kind = ID;
						opn1.offset = symbolTable.symbols[T0->Dec->Exp2->place].offset;
						strcpy(opn1.id, symbolTable.symbols[T0->Dec->Exp2->place].alias);
						result.kind = ID; strcpy(result.id, symbolTable.symbols[T0->Dec->place].alias);
						result.offset = symbolTable.symbols[T0->Dec->place].offset;
						T->code = merge(3, T->code, T0->Dec->Exp2->code, genIR(ASSIGNOP, opn1, opn2, result));
					}
					T->width += width + T0->Dec->Exp2->width;
				}
				/*
				DecList: Dec {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=DEC_LIST;
                              $$->pos=yylineno;   $$->Dec=$1;$$->DecList=NULL;} //局部变量
				Dec:     VarDec  {$$=$1;}
					   | VarDec ASSIGNOP Exp  
					   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ASSIGNOP;
						$$->pos=yylineno;   $$->Dec=$1;$$->Exp2=$3;}
				VarDec:  ID   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ID;
							   $$->pos=yylineno; strcpy($$->type_id,$1);}                    //ID结点，标识符符号串存放结点的type_id
	|			ID Arraylist {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=ARRAY_DEC;
							  strcpy($$->type_id,$1);$$->Dec=$2;$$->pos=yylineno;}
				*/
				else if (T0->Dec->kind == ARRAY_DEC) {
					arr_index = 0;
					strcpy(array_name, T0->Dec->type_id);
					rtn = fillSymbolTable(T0->Dec->type_id, newAlias(), LEV, T0->Dec->type, 'A', T->offset + T->width);//此处偏移量未计算，暂时为0
					if (rtn == -1) {
						semantic_error(T0->Dec->pos, T0->Dec->type_id, "数组重复定义");
					}
					else {
						T0->Dec->place = rtn;
						T0->Dec->num = compute_width(T0->Dec->Dec);
						// printf("%d\n", T->num);
						semantic_Analysis(T0->Dec->Dec);
						
						arr_flag = 1;
					}
					T->width += (width * T0->Dec->num);
				}
				T0 = T0->DecList;
			}
			break;
		case ARRAY_LIST:
			rtn = searchSymbolTable(array_name);
			if (rtn == -1) {
				semantic_error(T->pos, array_name, "数组未定义");
			}
			if (T->Exp1->type != INT) {
				semantic_error(T->pos, "", "数组定义维数需要用整型");
			}
			else {
				symbolTable.symbols[rtn].array[arr_index] = T->Exp1->type_int;
				arr_index++;
				T->num = compute_width(T->Exp2);
				semantic_Analysis(T->Exp2);
			}
			break;
		case ARRAY_LAST:
			rtn = searchSymbolTable(array_name);
			if (rtn == -1) {
				semantic_error(T->pos, array_name, "数组未定义");
			}
			if (T->Exp1->type != INT) {
				semantic_error(T->pos, "", "数组定义维数需要用整型");
			}
			else {
				symbolTable.symbols[rtn].array[arr_index] = T->Exp1->type_int;
			}
			break;
		case STM_LIST:
			if (T->StmList) //2条以上语句连接，生成新标号作为第一条语句结束后到达的位置
				strcpy(T->Stm->Snext, newLabel());
			else     //语句序列仅有一条语句，S.next属性向下传递
				strcpy(T->Stm->Snext, T->Snext);
			T->Stm->offset = T->offset;
			semantic_Analysis(T->Stm);
			T->code = T->Stm->code;
			T->width = T->Stm->width;
			if (T->StmList)
			{     //2条以上语句连接,S.next属性向下传递
				strcpy(T->StmList->Snext, T->Snext);
				T->StmList->offset = T->offset;  //顺序结构共享单元方式
				semantic_Analysis(T->StmList);
				//序列中第1条为表达式语句，返回语句，复合语句时，第2条前不需要标号
				if (T->Stm->kind == RETURN || T->Stm->kind == EXP_STMT || T->Stm->kind == COMP_STM)
					//对返回语句、表达式语句、复合语句，免去和后续语句间的标号
					T->code = merge(2, T->code, T->StmList->code);
				else
					T->code = merge(3, T->code, genLabel(T->Stm->Snext), T->StmList->code);
				if (T->StmList->width > T->width) //后续语句需要更多单元时，更新这些
					T->width = T->StmList->width; //顺序语句的单元width，实现共享单元方式
			}
			break;
		case IF_THEN:
			strcpy(T->Cond->Etrue, newLabel());  //设置条件语句真假转移位置
			strcpy(T->Cond->Efalse, T->Snext);
			T->Cond->offset = T->IfStm->offset = T->offset;
			boolExp(T->Cond);
			T->width = T->Cond->width;
			strcpy(T->IfStm->Snext, T->Snext);
			semantic_Analysis(T->IfStm);      //if子句
			if (T->width < T->IfStm->width) 
				T->width = T->IfStm->width;
			T->code = merge(3, T->Cond->code, genLabel(T->Cond->Etrue), T->IfStm->code);
			break;  //控制语句都还没有处理offset和width属性
		case IF_THEN_ELSE:
			strcpy(T->Cond->Etrue, newLabel());  //设置条件语句真假转移位置
			strcpy(T->Cond->Efalse, newLabel());
			T->Cond->offset = T->IfStm->offset = T->ElseStm->offset = T->offset;
			boolExp(T->Cond);      //条件，要单独按短路代码处理
			T->width = T->Cond->width;
			strcpy(T->IfStm->Snext, T->Snext);
			semantic_Analysis(T->IfStm);      //if子句
			if (T->width < T->IfStm->width) 
				T->width = T->IfStm->width;
			strcpy(T->ElseStm->Snext, T->Snext);
			semantic_Analysis(T->ElseStm);      //else子句
			if (T->width < T->ElseStm->width) 
				T->width = T->ElseStm->width;
			T->code = merge(6, T->Cond->code, genLabel(T->Cond->Etrue), T->IfStm->code, \
				genGoto(T->Snext), genLabel(T->Cond->Efalse), T->ElseStm->code);
			break;
		case WHILE: 
			strcpy(T->Cond->Etrue, newLabel());  //子结点继承属性的计算
			strcpy(T->Cond->Efalse, T->Snext);
			T->Cond->offset = T->Body->offset = T->offset;
			boolExp(T->Cond);      //循环条件，要单独按短路代码处理
			T->width = T->Cond->width;
			strcpy(T->Body->Snext, newLabel());
			strcpy(break_label, T->Snext);//break执行while语句的一下个语句
			strcpy(continue_label, T->Body->Snext);//continue执行下一次循环体
			semantic_Analysis(T->Body);      //循环体
			if (T->width < T->Body->width) 
				T->width = T->Body->width;
			T->code = merge(5, genLabel(T->Body->Snext), T->Cond->code, \
				genLabel(T->Cond->Etrue), T->Body->code, genGoto(T->Body->Snext));
			break;
		case FOR:
			LEV++;
			/*FOR LP Exp SEMI Exp SEMI Exp RP Stm
			{ $$ = (ASTNode *)malloc(sizeof(ASTNode)); $$->kind = FOR;
				$$->pos = $3->pos;   $$->Exp1 = $3; $$->Exp2 = $5; 
				$$->Exp3 = $7; $$->Body = $9; }*/
			// Exp1
			T->Exp1->offset = T->offset;
			
			Exp(T->Exp1);
			T->width = T->Exp1->width;
			// Exp2
			strcpy(T->Exp2->Etrue, newLabel()); 
			strcpy(T->Exp2->Efalse, T->Snext);
			T->Exp2->offset = T->offset + T->width;
			boolExp(T->Exp2);
			T->width += T->Exp2->width;
			// Body
			strcpy(T->Body->Snext, newLabel());
			strcpy(break_label, T->Snext);
			strcpy(continue_label, T->Body->Snext);
			semantic_Analysis(T->Body);
			// Exp3
			T->Exp3->offset = T->offset + T->width;
			strcpy(T->Exp3->Snext, newLabel());
			Exp(T->Exp3);
			T->width += T->Exp3->width;
			T->width += T->Body->width;
			T->code = merge(8,	T->Exp1->code,	genLabel(T->Exp3->Snext),
								T->Exp2->code,	genLabel(T->Exp2->Etrue),
								T->Body->code,	genLabel(T->Body->Snext),
								T->Exp3->code,	genGoto(T->Exp3->Snext));
			break;
		case BREAK:
			T->code = merge(2, T->code, genGoto(break_label));
			break;
		case CONTINUE:
			T->code = merge(2, T->code, genGoto(continue_label));
			break;
		case EXP_STMT:
			T->Exp1->offset = T->offset;
			semantic_Analysis(T->Exp1);
			T->code = T->Exp1->code;
			T->width = T->Exp1->width;
			break;
		case RETURN:
			if (T->Exp1) {
				T->Exp1->offset = T->offset;
				Exp(T->Exp1);
				num = symbolTable.index;
				/*需要判断返回值类型是否匹配*/
				do
					num--;
				while (symbolTable.symbols[num].flag != 'F');
				if (T->Exp1->type != symbolTable.symbols[num].type){
					semantic_error(T->pos, "返回值类型错误", "");
					T->width = 0;
					T->code = NULL;
					return;
				}
				T->width = T->Exp1->width;
				result.kind = ID; strcpy(result.id, symbolTable.symbols[T->Exp1->place].alias);
				result.offset = symbolTable.symbols[T->Exp1->place].offset;
				T->code = merge(2, T->Exp1->code, genIR(RETURN, opn1, opn2, result));
			}
			else {
				T->width = 0;
				result.kind = 0;
				T->code = genIR(RETURN, opn1, opn2, result);
			}
			break;
		case ID:
		case INT:
		case FLOAT:
		case CHAR:
		case ASSIGNOP:
		case AND:
		case OR:
		case RELOP:
		case PLUS:
		case DPLUS_PREFIX:
		case DPLUS_SUFFIX:
		case DMINUS_PREFIX:
		case DMINUS_SUFFIX:
		case ADDASSIGNOP:
		case SUBASSIGNOP:
		case MINUS:
		case STAR:
		case DIV:
		case NOT:
		case UMINUS:
		case FUNC_CALL:
		case EXP_ARRAY:
			Exp(T);          //处理基本表达式
			break;
		}
	}
}

void semantic_Analysis0(struct ASTNode *T) {
	symbolTable.index = 0;
	fillSymbolTable("read", "", 0, INT, 'F', 4);
	symbolTable.symbols[0].paramnum = 0;//read的形参个数
	fillSymbolTable("write", "", 0, INT, 'F', 4);
	symbolTable.symbols[1].paramnum = 1;
	fillSymbolTable("x", "", 1, INT, 'P', 12);
	symbol_scope_TX.TX[0] = 0;  //外部变量在符号表中的起始序号为0
	symbol_scope_TX.top = 1;
	T->offset = 0;              //外部变量在数据区的偏移量
	semantic_Analysis(T);
	prnIR(T->code);				//生成中间代码
	objectCode(T->code);	//生成目标代码
}

// int searchSymbolTableByAlias(char *alias)
// {
// 	int i;
// 	for (i = symbolTable.index - 1; i >= 0; i--)
// 		if (!strcmp(symbolTable.symbols[i].alias, alias))
// 			return i;
// 	return -1;
// }

// //输出目标代码
// void objectCode(struct codenode *head)
// {
// 	int main_flag = 0;
// 	int call_flag = 0;
// 	int main_call = 0;
// 	int LEV;
// 	char opnstr1[32], opnstr2[32], resultstr[32];
// 	struct codenode *h = head, *p;
// 	int i,arrIDFlag;
// 	FILE *fp;
// 	fp = fopen("object.s", "w");
// 	fprintf(fp, ".data\n");
// 	fprintf(fp, "_Prompt: .asciiz \"Enter an integer:  \"\n");
// 	fprintf(fp, "_ret: .asciiz \"\\n\"\n");
// 	fprintf(fp, ".globl main\n");
// 	fprintf(fp, ".text\n");
// 	fprintf(fp, "j main\n");//跳转到main函数
// 	fprintf(fp, "read:\n");
// 	fprintf(fp, "  li $v0,4\n");
// 	fprintf(fp, "  la $a0,_Prompt\n");
// 	fprintf(fp, "  syscall\n");
// 	fprintf(fp, "  li $v0,5\n");
// 	fprintf(fp, "  syscall\n");
// 	fprintf(fp, "  jr $ra\n");
// 	fprintf(fp, "write:\n");
// 	fprintf(fp, "  li $v0,1\n");
// 	fprintf(fp, "  syscall\n");
// 	fprintf(fp, "  li $v0,4\n");
// 	fprintf(fp, "  la $a0,_ret\n");
// 	fprintf(fp, "  syscall\n");
// 	fprintf(fp, "  move $v0,$0\n");
// 	fprintf(fp, "  jr $ra\n");
// 	do { //采用朴素寄存器分配
// 		switch (h->op) {
// 		case ASSIGNOP:
// 			/*if (h->opn1.kind==INT)
// 				fprintf(fp, "  li $t3, %d\n", h->opn1.const_int);
// 			else {
// 				fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
// 				fprintf(fp, "  move $t3, $t1\n");
// 				}
// 			fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
// 			break;*/
// 			if (h->opn1.kind == INT) {
// 				fprintf(fp, "  li $t3, %d\n", h->opn1.const_int);
// 			}
// 			else if (h->opn1.kind == FLOAT) {
// 				fprintf(fp, "  li $t3, %f\n", h->opn1.const_float);
// 			}
// 			else if (h->opn1.kind == CHAR) {
// 				fprintf(fp, "  li $t3, %c\n", h->opn1.const_char);
// 			}
// 			else {
// 				int rtn;
// 				char arrName[10] = { '\0' };
// 				if (strstr(h->opn1.id, " offset ") != NULL) {
// 					for (int i = 0; i < strlen(h->opn1.id); i++) {
// 						if (h->opn1.id[i] != ' ') {
// 							arrName[i] = h->opn1.id[i];
// 						}
// 					}
// 					rtn = searchSymbolTableByAlias(arrName);
// 				}
// 				else
// 					rtn = searchSymbolTableByAlias(h->opn1.id);
				
// 				if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
// 					fprintf(fp, "  lw $t1, %d($gp)\n", h->opn1.offset);
// 					fprintf(fp, "  move $t3, $t1\n");
// 				}
// 				else  {
// 					fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
// 					fprintf(fp, "  move $t3, $t1\n");
// 				}
// 				/*if (h->opn1.arrIDFlag != 1) {//不是ID型下标
// 					if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
// 						fprintf(fp, "  lw $t1, %d($gp)\n", h->opn1.offset);
// 						fprintf(fp, "  move $t3, $t1\n");
// 					}
// 					else if (rtn != -1 && symbolTable.symbols[rtn].level  != 0) {
// 						fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
// 						fprintf(fp, "  move $t3, $t1\n");
// 					}
// 				}
// 				else {
// 					if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
// 						fprintf(fp, "  lw $t1, %d($gp)\n", h->opn1.offset);//此处应该计算offset，并应该由MIPS去计算，而不是由C
// 						fprintf(fp, "  move $t3, $t1\n");
// 					}
// 					else if (rtn != -1 && symbolTable.symbols[rtn].level != 0) {
// 						fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);//此处应该计算offset，并应该由MIPS去计算，而不是由C
// 						fprintf(fp, "  move $t3, $t1\n");
// 					}
// 				}*/
// 			}
// 			int rtn;
// 			char arrName[10] = { '\0' };
// 			if (strstr(h->result.id, " offset ") != NULL) {
// 				for (int i = 0; i < strlen(h->result.id); i++) {
// 					if (h->result.id[i] != ' ') {
// 						arrName[i] = h->result.id[i];
// 					}
// 				}
// 				rtn = searchSymbolTableByAlias(arrName);
// 			}
// 			else
// 				rtn = searchSymbolTableByAlias(h->result.id);
// 			// fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
// 			// printf("%s %d %d\n", h->result.id, symbolTable.symbols[rtn].level, LEV);
// 			if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
// 				fprintf(fp, "  sw $t3, %d($gp)\n", h->result.offset);
// 			}
// 			else {
// 				fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
// 			}
// 			/*if (h->result.arrIDFlag != 1) {//不是ID型下标
// 				if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
// 					fprintf(fp, "  sw $t3, %d($gp)\n", h->result.offset);
// 				}
// 				else {
// 					fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
// 				}
// 			}
// 			else {
// 				if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
// 					fprintf(fp, "  sw $t3, %d($gp)\n", h->result.offset);//此处应该计算offset，并应该由MIPS去计算，而不是由C
// 				}
// 				else {
// 					fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);//此处应该计算offset，并应该由MIPS去计算，而不是由C
// 				}
// 			}*/
// 			break;
// 		case PLUS:
// 		case MINUS:
// 		case STAR:
// 		case DIV:
// 			fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
// 			fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
// 			if (h->op == PLUS)       fprintf(fp, "  add $t3,$t1,$t2\n");
// 			else if (h->op == MINUS) fprintf(fp, "  sub $t3,$t1,$t2\n");
// 			else if (h->op == STAR)  fprintf(fp, "  mul $t3,$t1,$t2\n");
// 			else {
// 				fprintf(fp, "  div $t1, $t2\n");
// 				fprintf(fp, "  mflo $t3\n");
// 			}
// 			fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
// 			break;
// 		case FUNCTION:
// 			fprintf(fp, "\n%s:\n", h->result.id);
// 			if (!strcmp(h->result.id, "main")) {//特殊处理main
// 				main_flag = 1;
// 				LEV = 0;
// 				main_call = 0;
// 				fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->result.offset].offset);

// 			}
// 			break;
// 		case PARAM: //直接跳到后面一条
// 			break;
// 		case LABEL: fprintf(fp, "%s:\n", h->result.id);
// 			break;
// 		case GOTO:  fprintf(fp, "  j %s\n", h->result.id);
// 			break;
// 		case JLE:
// 		case JLT:
// 		case JGE:
// 		case JGT:
// 		case EQ:
// 		case NEQ:
// 			fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
// 			fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
// 			if (h->op == JLE) fprintf(fp, "  ble $t1,$t2,%s\n", h->result.id);
// 			else if (h->op == JLT) fprintf(fp, "  blt $t1,$t2,%s\n", h->result.id);
// 			else if (h->op == JGE) fprintf(fp, "  bge $t1,$t2,%s\n", h->result.id);
// 			else if (h->op == JGT) fprintf(fp, "  bgt $t1,$t2,%s\n", h->result.id);
// 			else if (h->op == EQ)  fprintf(fp, "  beq $t1,$t2,%s\n", h->result.id);
// 			else                 fprintf(fp, "  bne $t1,$t2,%s\n", h->result.id);
// 			break;
// 		case ARG:   //直接跳到后面一条,直到函数调用，回头反查参数。
// 			break;
// 		case CALL:  
// 			call_flag = 1;
// 			LEV++;
// 			if (!strcmp(h->opn1.id, "read")) { //特殊处理read
// 				fprintf(fp, "  addi $sp, $sp, -4\n");
// 				fprintf(fp, "  sw $ra,0($sp)\n"); //保留返回地址
// 				fprintf(fp, "  jal read\n"); //保留返回地址
// 				fprintf(fp, "  lw $ra,0($sp)\n"); //恢复返回地址
// 				fprintf(fp, "  addi $sp, $sp, 4\n");
// 				fprintf(fp, "  sw $v0, %d($sp)\n", h->result.offset);
// 				break;
// 			}
// 			if (!strcmp(h->opn1.id, "write")) { //特殊处理write
// 				fprintf(fp, "  lw $a0, %d($sp)\n", h->prior->result.offset);
// 				fprintf(fp, "  addi $sp, $sp, -4\n");
// 				fprintf(fp, "  sw $ra,0($sp)\n");
// 				fprintf(fp, "  jal write\n");
// 				fprintf(fp, "  lw $ra,0($sp)\n");
// 				fprintf(fp, "  addi $sp, $sp, 4\n");
// 				break;
// 			}

// 			for (p = h, i = 0; i < symbolTable.symbols[h->opn1.offset].paramnum; i++)  //定位到第一个实参的结点
// 				p = p->prior;
// 					//开活动记录空间
// 			fprintf(fp, "  move $t0,$sp\n"); //保存当前函数的sp到$t0中，为了取实参表达式的值
// 			fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->opn1.offset].offset);
// 			fprintf(fp, "  sw $ra,0($sp)\n"); //保留返回地址
// 			i = h->opn1.offset + 1;  //第一个形参变量在符号表的位置序号
// 			while (symbolTable.symbols[i].flag == 'P'){
// 				fprintf(fp, "  lw $t1, %d($t0)\n", p->result.offset); //取实参值
// 				fprintf(fp, "  move $t3,$t1\n");
// 				fprintf(fp, "  sw $t3,%d($sp)\n", symbolTable.symbols[i].offset); //送到被调用函数的形参单元
// 				p = p->next; i++;
// 			}
// 			fprintf(fp, "  jal %s\n", h->opn1.id); //恢复返回地址
// 			fprintf(fp, "  lw $ra,0($sp)\n"); //恢复返回地址
// 			fprintf(fp, "  addi $sp,$sp,%d\n", symbolTable.symbols[h->opn1.offset].offset); //释放活动记录空间
// 			fprintf(fp, "  sw $v0,%d($sp)\n", h->result.offset); //取返回值
// 			break;
// 		case RETURN:
// 			//fprintf(fp, "  lw $v0,%d($sp)\n", h->result.offset); //返回值送到$v0
// 			//fprintf(fp, "  jr $ra\n");
// 			if (!main_flag) {
// 				fprintf(fp, "  lw $v0,%d($sp)\n", h->result.offset);
// 				fprintf(fp, "  jr $ra\n");
// 			}
// 			else {
// 				fprintf(fp, "  li $v0, 10\n");
// 				fprintf(fp, "  syscall\n");
// 				main_flag = 0;
// 			}
// 			call_flag = 0;
// 			LEV--;
// 			break;

// 		}
// 		h = h->next;
// 	} while (h != head);
// 	fclose(fp);
// }