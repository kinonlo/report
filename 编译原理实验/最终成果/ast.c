#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "def.h"
#include "parser.tab.h"

#define DEBUG1 1
int arr_index = 0;
int arr_flag = 0;

void display(struct ASTNode *T, int indent)
{//�Գ����﷨�����ȸ�����
	int i = 1;
	struct ASTNode *T0;
	if (T)
	{
		switch (T->kind) {
		case EXT_DEF_LIST:  
			display(T->Def, indent);         //��ʾ���ⲿ���壨�ⲿ�����ͺ������б��еĵ�һ��
			display(T->DefList, indent);    //��ʾ���ⲿ�����б��е������ⲿ����
			break;
		case EXT_VAR_DEF:   
			printf("%*c�ⲿ�������壺(%d)\n", indent, ' ', T->pos);
			display(T->Specifier, indent + 3);        //��ʾ�ⲿ��������
			printf("%*c��������\n", indent + 3, ' ');
			display(T->DecList, indent + 6);          //��ʾ�����б�
			break;
		case TYPE:          
			printf("%*c���ͣ� %s\n", indent, ' ', T->type_id);
			break;
		case EXT_DEC_LIST:  
			/*if (T->Dec->Dec != NULL)
			{
				printf("%*c��������%s\n", indent, ' ', T->Dec->type_id);
				printf("%*c�����С��\n", indent, ' ');
			}*/
			display(T->Dec, indent);     //������ʾ�ⲿ��������
			display(T->DecList, indent); //����������ͬ�ģ�����ʾ�﷨���˴��������Ժ����ƴ���ϲ�
			break;
		case ARRAY_DEC:
			printf("%*c��������%s\n", indent, ' ', T->type_id);
			printf("%*c�����С��\n", indent, ' ');
			display(T->Dec, indent+3);
			break;
		case FUNC_DEF:      
			printf("%*c�������壺(%d)\n", indent, ' ', T->pos);
			display(T->Specifier, indent + 3);      //��ʾ������������
			display(T->FuncDec, indent + 3);         //��ʾ�������Ͳ���
			display(T->Body, indent + 3);      //��ʾ������
			break;
		case FUNC_DEC:      
			printf("%*c��������%s\n", indent, ' ', T->type_id);
			if (T->ParamList) {
				printf("%*c�����βΣ�\n", indent, ' ');
				display(T->ParamList, indent + 3);  //��ʾ���������б�
			}
			else printf("%*c�޲κ���\n", indent + 3, ' ');
			break;
		case PARAM_LIST:    
			display(T->Param, indent);     //������ʾȫ���������ͺ����ƣ�
			display(T->ParamList, indent);
			break;
		case PARAM_DEC:    
			if (T->Specifier->type == INT) {
				printf("%*c���ͣ�%s, ��������%s\n", indent, ' ', "int", T->ID->type_id);
			}
			else if (T->Specifier->type == FLOAT) {
				printf("%*c���ͣ�%s, ��������%s\n", indent, ' ', "float", T->ID->type_id);
			}
			else {
				printf("%*c���ͣ�%s, ��������%s\n", indent, ' ', "char", T->ID->type_id);
			}
			break;
		case EXP_STMT:      
			printf("%*c���ʽ��䣺(%d)\n", indent, ' ', T->pos);
			display(T->Exp1, indent + 3);
			break;
		case RETURN:        
			printf("%*c������䣺(%d)\n", indent, ' ', T->pos);
			display(T->Exp1, indent + 3);
			break;
		case COMP_STM:      
			printf("%*c������䣺(%d)\n", indent, ' ', T->pos);
			if (T->DefList)
			{
				printf("%*c�������ı������岿�֣�\n", indent + 3, ' ');
				display(T->DefList, indent + 6);      //��ʾ���岿��
			}
			if (T->StmList)
			{
				printf("%*c����������䲿�֣�\n", indent + 3, ' ');
				display(T->StmList, indent + 6);      //��ʾ��䲿��
			}
			break;
		case STM_LIST:      
			display(T->Stm, indent);      //��ʾ��һ�����
			display(T->StmList, indent);        //��ʾʣ�����
			break;
		case WHILE:         
			printf("%*cѭ����䣺(%d)\n", indent, ' ', T->pos);
			printf("%*cѭ��������\n", indent + 3, ' ');
			display(T->Cond, indent + 6);      //��ʾѭ������
			printf("%*cѭ���壺(%d)\n", indent + 3, ' ', T->pos);
			display(T->Body, indent + 6);      //��ʾѭ����
			break;
		case FOR:
			printf("%*cFORѭ����䣺(%d)\n", indent, ' ', T->pos);
			printf("%*cѭ���������壺\n", indent + 3, ' ');
			display(T->Exp1, indent + 6);      //������ֵ
			printf("%*cѭ��������\n", indent + 3, ' ');
			display(T->Exp2, indent + 6);      //ѭ������
			printf("%*c������䣺\n", indent + 3, ' ');
			display(T->Exp3, indent + 6);      //�������
			printf("%*cѭ���壺(%d)\n", indent + 3, ' ', T->pos);
			display(T->Body, indent + 6);      //ѭ����
			break;
		case BREAK:
			printf("%*cBREAK�� (%d)\n", indent, ' ',T->pos);
			break;
		case CONTINUE:
			printf("%*cCONTINUE�� (%d)\n", indent, ' ',T->pos);
			break;
		case IF_THEN:       
			printf("%*c�������(IF_THEN)��(%d)\n", indent, ' ', T->pos);
			printf("%*c������\n", indent + 3, ' ');
			display(T->Cond, indent + 6);      //��ʾ����
			printf("%*cIF�Ӿ䣺(%d)\n", indent + 3, ' ', T->pos);
			display(T->IfStm, indent + 6);      //��ʾif�Ӿ�
			break;
		case IF_THEN_ELSE:  
			printf("%*c�������(IF_THEN_ELSE)��(%d)\n", indent, ' ', T->pos);
			printf("%*c������\n", indent + 3, ' ');
			display(T->Cond, indent + 6);      //��ʾ����
			printf("%*cIF�Ӿ䣺(%d)\n", indent + 3, ' ', T->pos);
			display(T->IfStm, indent + 6);      //��ʾif�Ӿ�
			printf("%*cELSE�Ӿ䣺(%d)\n", indent + 3, ' ', T->pos);
			display(T->ElseStm, indent + 6);      //��ʾelse�Ӿ�
			break;
		case DEF_LIST:      
			display(T->Def, indent);    //��ʾ�þֲ����������б��еĵ�һ��
			display(T->DefList, indent);    //��ʾ�����ֲ���������
			break;
		case VAR_DEF:       
			printf("%*c�ֲ��������壺(%d)\n", indent, ' ', T->pos);
			display(T->Specifier, indent + 3);   //��ʾ��������
			display(T->DecList, indent + 3);   //��ʾ�ö����ȫ��������
			break;
		case DEC_LIST:      
			printf("%*c��������\n", indent, ' ');
			T0 = T;
			while (T0) {
				if (T0->Dec->kind == ID)
					printf("%*c %s\n", indent + 6, ' ', T0->Dec->type_id);
				else if (T0->Dec->kind == ASSIGNOP)
				{
					printf("%*c %s ASSIGNOP\n ", indent + 6, ' ', T0->Dec->Dec->type_id);
					display(T0->Dec->Exp1, indent + strlen(T0->Dec->Dec->type_id) + 7);        //��ʾ��ʼ�����ʽ
				}
				else if (T0->Dec->kind == ARRAY_DEC) {
					printf("%*c��������%s\n", indent+3, ' ', T0->Dec->type_id);
					printf("%*c�����С��\n", indent+3, ' ');
					display(T0->Dec->Dec, indent + 3);
				}
				T0 = T0->DecList;
			}
			break;
		case ID:	        
			printf("%*cID�� %s\n", indent, ' ', T->type_id);
			break;
		/*case ARRAY:         
			display(T->Dec, indent);
			printf("%*c ά�ȴ�С[%d]\n", indent, ' ', T->arrsize);
			break;*/
		case ARRAY_LIST:
			display(T->Exp1, indent);
			display(T->Exp2, indent);
			break;
		case ARRAY_LAST:
			display(T->Exp1, indent);
			break;
		case INT:	        
			printf("%*cINT��%d\n", indent, ' ', T->type_int);
			break;
		case FLOAT:	        
			printf("%*cFLAOT��%f\n", indent, ' ', T->type_float);
			break;
		case CHAR:	        
			printf("%*cCHAR��%c\n", indent, ' ', T->type_char);
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
			printf("%*c�������� %s\n", indent, ' ', T->type_id);
			printf("%*c�����±꣺\n", indent, ' ');
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
			printf("%*c�������ã�(%d)\n", indent, ' ', T->pos);
			printf("%*c��������%s\n", indent + 3, ' ', T->type_id);
			if (T->Args)
				display(T->Args, indent + 3);
			else printf("%*c �޲���\n", indent + 3, ' ');
			break;
		case ARGS:      
			i = 1;
			while (T) {  //ARGS��ʾʵ�ʲ������ʽ���н�㣬���һ������Ϊ��һ��ʵ�ʲ������ʽ���ڶ�������Ϊʣ�µ�
				struct ASTNode *T0 = T->Exp1;
				printf("%*c��%d��ʵ�ʲ������ʽ��\n", indent, ' ', i++);
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

/*��������char����*/
char *strcat0(char *s1, char *s2) {
	static char result[10];
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

/*���ɱ������*/
char *newAlias() {
	static int no = 1;
	char s[10];
	itoa(no++, s, 10);
	return strcat0("v", s);
}

/*����label���*/
char *newLabel() {
	static int no = 1;
	char s[10];
	itoa(no++, s, 10);
	return strcat0("label", s);
}

/*����temp���*/
char *newTemp() {
	static int no = 1;
	char s[10];
	itoa(no++, s, 10);
	return strcat0("temp", s);
}

//�м�������ɣ�����һ��TAC����Ľ����ɵ�˫��ѭ����������ͷָ��
struct codenode *genIR(int op, struct opn opn1, struct opn opn2, struct opn result) {
	struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
	h->op = op;
	h->opn1 = opn1;
	h->opn2 = opn2;
	h->result = result;
	h->next = h->prior = h;
	return h;
}

//�м�������ɣ�����һ�������䣬����ͷָ��
struct codenode *genLabel(char *label) {
	struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
	h->op = LABEL;
	strcpy(h->result.id, label);
	h->next = h->prior = h;
	return h;
}

//�м�������ɣ�����GOTO��䣬����ͷָ��
struct codenode *genGoto(char *label) {
	struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
	h->op = GOTO;
	strcpy(h->result.id, label);
	h->next = h->prior = h;
	return h;
}

//�м�������ɣ��ϲ�����м�����˫��ѭ��������β����
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

//�м�������ɣ�����м����
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
	//�������ֻ�ռ�������Ϣ�����һ����ʾ
	printf("��%d��,%s %s\n", line, msg1, msg2);
}

void prn_symbol() { //��ʾ���ű�
	int i = 0;
	char tempType[10];
	printf("%6s %6s %6s  %6s %4s %6s\n", "������", "�� ��", "�� ��", "��  ��", "���", "ƫ����");
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

/*���ĳ��ID�Ƿ�����ڷ��ű��У������ڷ���-1*/
int searchSymbolTable(char *name) {
	int i, flag = 0;
	for (i = symbolTable.index - 1; i >= 0; i--) {
		if (symbolTable.symbols[i].level == 0)
			flag = 1;
		if (flag && symbolTable.symbols[i].level == 1)
			continue;   //����ǰ�溯������ʽ��������
		if (!strcmp(symbolTable.symbols[i].name, name))  return i;
	}
	return -1;
}

/*���һ�з��ŵ����ű�*/
int fillSymbolTable(char *name, char *alias, int level, int type, char flag, int offset)
{
	//���ȸ���name����ű������ظ����� �ظ����巵��-1
	int i;
	/*���Ų��أ������ⲿ��������ǰ�к������壬
	���β������ڷ��ű��У���ʱ���ⲿ������ǰ�������β������������*/
	if (name)
		for (i = symbolTable.index - 1; i >= 0 && (symbolTable.symbols[i].level == level || level == 0); i--) {
			if (level == 0 && symbolTable.symbols[i].level == 1) continue;  //�ⲿ�������ββ��رȽ�����
			if (!strcmp(symbolTable.symbols[i].name, name))  return -1;
		}
	//��д���ű�����
	strcpy(symbolTable.symbols[symbolTable.index].name, name);
	strcpy(symbolTable.symbols[symbolTable.index].alias, alias);
	symbolTable.symbols[symbolTable.index].level = level;
	symbolTable.symbols[symbolTable.index].type = type;
	symbolTable.symbols[symbolTable.index].flag = flag;
	symbolTable.symbols[symbolTable.index].offset = offset;
	return symbolTable.index++; //���ص��Ƿ����ڷ��ű��е�λ����ţ��м��������ʱ�������ȡ�����ű���
}

//��д��ʱ���������ű�������ʱ�����ڷ��ű��е�λ��
int fill_Temp(char *name, int level, int type, char flag, int offset) {
	strcpy(symbolTable.symbols[symbolTable.index].name, "");
	strcpy(symbolTable.symbols[symbolTable.index].alias, name);
	symbolTable.symbols[symbolTable.index].level = level;
	symbolTable.symbols[symbolTable.index].type = type;
	symbolTable.symbols[symbolTable.index].flag = flag;
	symbolTable.symbols[symbolTable.index].offset = offset;
	return symbolTable.index++; //���ص�����ʱ�����ڷ��ű��е�λ�����
}

/*��������б�*/
void ext_var_list(struct ASTNode *T)
{  //��������б�
	int rtn;
	switch (T->kind) {
	case EXT_DEC_LIST:
		T->Dec->type = T->type;                  //�������������´��ݱ������
		T->Dec->offset = T->offset;				 //�ⲿ������ƫ�������´���
		if (T->DecList) {
			T->DecList->type = T->type;              //�������������´��ݱ������
			T->DecList->offset = T->offset + T->width; //�ⲿ������ƫ�������´���
			T->DecList->width = T->width;
		}
		ext_var_list(T->Dec);
		if (T->DecList){
			ext_var_list(T->DecList);
			T->num = T->DecList->num + 1;
		}
		break;
	case ID:                                     //���һ��������
		rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'V', T->offset);
		if (rtn == -1)
			semantic_error(T->pos, T->type_id, "�����ظ�����");
		else T->place = rtn;
		T->num = 1;
		break;
	case ARRAY_DEC:
		arr_index = 0;
		strcpy(array_name, T->type_id);
		rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'A', T->offset);
		if (rtn == -1) {
			semantic_error(T->pos, T->type_id, "���������ظ�����");
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
			semantic_error(T->pos, array_name, "����δ����");
		}
		if (T->Exp1->type != INT) {
			semantic_error(T->pos, "", "���鶨��ά����Ҫ������");
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
			semantic_error(T->pos, array_name, "����δ����");
		}
		if (T->Exp1->type != INT) {
			semantic_error(T->pos, "", "���鶨��ά����Ҫ������");
		}
		else {
			symbolTable.symbols[rtn].array[arr_index] = T->Exp1->type_int;
		}
		break;
	}
}

/*���麯������ʱ�Ĵ�������Ƿ����Ͷ�Ӧ��������Ӧ*/
int  match_param(int i, struct ASTNode *T)
{  //i���������ڷ��ű��е�λ��
	int j, num = symbolTable.symbols[i].paramnum;
	if (num == 0 && T == NULL) return 1;//�޲κ���
	int type1, type2, pos = T->pos;
	for (j = 1; j <= num; j++) {  //�Ƚϲ���
		if (T==NULL) {
			semantic_error(pos, "", "�������ò���̫��!");
			return 0;
		}
		type1 = symbolTable.symbols[i + j].type;  //�β�����
		type2 = T->Exp1->type;
		if (type1 != type2) {
			semantic_error(pos, "", "�������Ͳ�ƥ��");
			return 0;
		}
		T = T->Args;
	}
	if (T) { //num�������Ѿ�ƥ���꣬����ʵ�α��ʽ
		semantic_error(pos, "", "�������ò���̫��!");
		return 0;
	}
	return 1;
}

/*���������ʽ�ķ��ű���*/
void boolExp(struct ASTNode *T)
{  //�������ʽ���ο�����[2]p84��˼��
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
				semantic_error(T->pos, T->type_id, "����δ����");
			if (symbolTable.symbols[rtn].flag == 'F')
				semantic_error(T->pos, T->type_id, "�Ǻ����������Ͳ�ƥ��");
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
		case RELOP: //�����ϵ������ʽ,2�������������������ʽ����
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


/*����������ʽ*/
void Exp(struct ASTNode *T)
{//����������ʽ���ο�����[2]p82��˼��
	int rtn, num, width;
	struct ASTNode *T0;
	struct opn opn1, opn2, result, result2;
	if (T)
	{
		switch (T->kind)
		{
		case ID:    //����ű���÷��ű��е�λ�ã�������type
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1)
				semantic_error(T->pos, T->type_id, "����δ����");
			else if (symbolTable.symbols[rtn].flag == 'F')
				semantic_error(T->pos, T->type_id, "�Ǻ����������Ͳ�ƥ��");
			else if (symbolTable.symbols[rtn].flag == 'A')
				semantic_error(T->pos, T->type_id, "�������������Ͳ�ƥ��");
			else
			{
				T->place = rtn;       //��㱣������ڷ��ű��е�λ��
				T->code = NULL;       //��ʶ������Ҫ����TAC
				T->type = symbolTable.symbols[rtn].type;
				T->offset = symbolTable.symbols[rtn].offset;
				T->width = 0;         //δ��ʹ���µ�Ԫ
			}
			break;
		case INT:
			//Ϊ����������һ����ʱ������T->place��ʾ��ʱ�����ڷ��ű�λ��
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
		case FLOAT://Ϊ���㳣������һ����ʱ����
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
				semantic_error(T->pos, "", "��ֵ�����Ҫ��ֵ");
			}
			else
			{
				T->Exp1->offset = T->offset;
				Exp(T->Exp1);   //������ֵ�����н�Ϊ����
				T->offset += T->Exp1->width; //�����ֵ���±������with�����0
				//T->Exp2->offset = T->offset;
				Exp(T->Exp2);

				if (T->Exp1->type != T->Exp2->type) {
					semantic_error(T->pos, "", "��ֵ�����������Ͳ�ƥ��");
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
					strcpy(opn1.id, symbolTable.symbols[T->Exp2->place].alias); //��ֵһ���Ǹ���������ʱ����
					opn1.offset = symbolTable.symbols[T->Exp2->place].offset;
				}
				/*
				ID Arraylist  {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=EXP_ARRAY; $$->pos=yylineno;   $$->Exp1=$2;strcpy($$->type_id,$1);}

				Arraylist: LS Exp RS {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=ARRAY_LAST;$$->Exp1=$2;$$->pos=yylineno;}
						| LS Exp RS Arraylist {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=ARRAY_LIST;$$->Exp1=$2;$$->pos=yylineno;$$->Exp2=$4;}

				   | ID                 {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ID;
							   $$->pos=yylineno;  strcpy($$->type_id,$1);}                                   //����
					 | INT          {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=INT;
							   $$->pos=yylineno;  $$->type=INT;$$->type_int=$1;}    //���ͳ���
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
						//offsetȡ����ID��ֵ
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
				//opn1.kind = ID;   //��ֵһ���Ǹ������������ɵ���ʱ����
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
						//offsetȡ����ID��ֵ
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
				semantic_error(T->pos, "", "���ɲ����������ֵ");
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
					strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias); //��ֵһ���Ǹ���������ʱ����
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
				strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias); //��ֵһ���Ǹ���������ʱ����
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
				semantic_error(T->pos, "", "����������Լ�����");
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
		case AND:   //���������ʽ��ʽ���㲼��ֵ��δд��
		case OR:    //���������ʽ��ʽ���㲼��ֵ��δд��
		case RELOP: //���������ʽ��ʽ���㲼��ֵ��δд��
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
			//�ж�T->Exp1��T->Exp2�����Ƿ���ȷ�����ܸ�����������ɲ�ͬ��ʽ�Ĵ��룬��T��type��ֵ
			//������������Լ��㣬û�п��Ǵ��������
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
				semantic_error(T->pos, "", "���������������Ͳ�ͳһ");
				return;
			}

			T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->Exp1->width + T->Exp2->width);

			if (T->Exp1->kind != EXP_ARRAY) {
				opn1.kind = ID;
				strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias); //��ֵһ���Ǹ���������ʱ����
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
				strcpy(opn2.id, symbolTable.symbols[T->Exp2->place].alias); //��ֵһ���Ǹ���������ʱ����
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
		case NOT:   //δд����
			T->type = INT;
			T->Exp1->offset = T->offset;
			boolExp(T);
			break;
		case UMINUS://δд����
			break;
		case FUNC_CALL: //����T->type_id��������Ķ��壬���������������ʵ��̲ĵ�read��write��Ҫ��������һ��
			rtn = searchSymbolTable(T->type_id);
			if (rtn == -1) {
				semantic_error(T->pos, T->type_id, "����δ����");
				break;
			}
			if (symbolTable.symbols[rtn].flag != 'F') {
				semantic_error(T->pos, T->type_id, "����һ������");
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
			} //��ź�������ֵ�ĵ����ֽ���
			if (T->Args) {
				T->Args->offset = T->offset;
				Exp(T->Args);       //��������ʵ�α��ʽ��ֵ��������
				T->width = T->Args->width + width; //�ۼ��ϼ���ʵ��ʹ����ʱ�����ĵ�Ԫ��
				T->code = T->Args->code;
			}
			else { 
				T->width = width; 
				T->code = NULL; 
			}
			
			match_param(rtn, T->Args);   //�������в�����ƥ��

				//��������б���м����
			T0 = T->Args;
			while (T0)
			{  //��ARG�����г�ʵ�α��ʽ��ֵ
				if (T0->Exp1->kind != EXP_ARRAY) {
					//opn1.kind = ID;
					//strcpy(opn1.id, symbolTable.symbols[T->Exp1->place].alias); //��ֵһ���Ǹ���������ʱ����
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
			strcpy(opn1.id, T->type_id);  //���溯����
			opn1.offset = rtn;//��offset���溯���������,��Ŀ���������ʱ���ܻ�ȡ��Ӧ��Ϣ
			result.kind = ID;
			strcpy(result.id, symbolTable.symbols[T->place].alias);
			result.offset = symbolTable.symbols[T->place].offset;
			T->code = merge(2, T->code, genIR(CALL, opn1, opn2, result));//���ɺ��������м����
			break;
		case ARGS:      //�˴��������ʵ�α��ʽ����ֵ�Ĵ������У�������ARG��ʵ��ϵ��
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
				semantic_error(T->pos, T->type_id, "����δ����");
			else if (symbolTable.symbols[rtn].flag != 'A')
				semantic_error(T->pos, T->type_id, "������������");
			else {
				int index = 0;
				T0 = T->Exp1;
				T->place = rtn;       //��㱣������ڷ��ű��е�λ��
				T->code = NULL;       //��ʶ������Ҫ����TAC
				T->type = symbolTable.symbols[rtn].type; // ���ID����
				
				//�˴��������ƫ�Ƶ�ַ��д����
				//printf(": %d \n", T->Exp1->Exp1->kind);
				
				T->offset = (T->type == INT ? 4 : (T->type == FLOAT ? 8 : 1)) * (compute_width0(T->Exp1, symbolTable.symbols[rtn].array, 0) - 1);//
				
				//if (T->Exp1->Exp1->kind == ID)
					//T->checkID = 'I';//��ID��ʾ�±�ʱ��ÿ��ʹ�������¼���offset
				
				//printf(" %c \n", T->checkID);
				
				T->width = 0;   //δ��ʹ���µ�Ԫ
				// T0->ptr[0]->offset = T->offset;
				// printf("!!%d\n", T0->ptr[0]->offset);
				while (T0->kind == ARRAY_LIST) {
					Exp(T0->Exp1);
					if (T0->Exp1->type != INT) {
						semantic_error(T->pos, "", "���鳤�ȱ���������");
						break;
					}
					if (index == 8) {
						semantic_error(T->pos, "", "����ά�ȹ���");
						break;
					}
					else if (symbolTable.symbols[rtn].array[index] <= T0->type_int) {
						semantic_error(T->pos, "", "����Խ�����");
						break;
					}
					index++;
					T0 = T0->Exp2;
					T->width += 4;
				}
				//�������һά
				if (T0->kind == ARRAY_LAST) {
					Exp(T0->Exp1);
					if (T0->Exp1->type != INT) {
						semantic_error(T->pos, "", "���鳤�ȱ���������");
					}
					else if (index == 8) {
						semantic_error(T->pos, "", "����ά�ȹ���");
					}
					if (T0->Exp1->kind == ID) {
						if (symbolTable.symbols[rtn].array[index] <= symbolTable.symbols[T0->Exp1->place].const_int) {
							semantic_error(T->pos, "", "����Խ�����");
						}
					}
					else {
						if (symbolTable.symbols[rtn].array[index] <= T0->Exp1->type_int) {
							semantic_error(T->pos, "", "����Խ�����");
						}
					}
					T->width += 4;
				}
			}
		}
		
	}
}

void semantic_Analysis(struct ASTNode *T)
{//�Գ����﷨�����ȸ�����,��display�Ŀ��ƽṹ�޸���ɷ��ű������������TAC���ɣ���䲿�֣�
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
			semantic_Analysis(T->Def);    //�����ⲿ�����б��еĵ�һ��
			T->code = T->Def->code;
			if (T->DefList) {
				T->DefList->offset = T->Def->offset + T->Def->width;
				semantic_Analysis(T->DefList); //���ʸ��ⲿ�����б��е������ⲿ����
				T->code = merge(2, T->code, T->DefList->code);
			}
			break;
		case EXT_VAR_DEF:   //�����ⲿ˵��,����һ������(TYPE���)�е������͵��ڶ������ӵ�������
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
			T->DecList->offset = T->offset;        //����ⲿ������ƫ�������´���
			//T->DecList->width = T->type == INT ? 4 : 8;  //��һ�������Ŀ�����´���
			ext_var_list(T->DecList);            //�����ⲿ����˵���еı�ʶ������
			T->width = T->DecList->width*T->DecList->num; //��������ⲿ����˵���Ŀ��
			T->code = NULL;                        //����ٶ��ⲿ������֧�ֳ�ʼ��
			break;
		case FUNC_DEF:      //��д����������Ϣ�����ű�
			if (!strcmp(T->Specifier->type_id, "int")){
				T->FuncDec->type = INT;
			}
			else if (!strcmp(T->Specifier->type_id, "float")){
				T->FuncDec->type = FLOAT;
			}
			else if (!strcmp(T->Specifier->type_id, "char")){
				T->FuncDec->type = CHAR;
			}
			//T->FuncDec->type = !strcmp(T->Specifier->type_id, "int") ? INT : FLOAT;//��ȡ�������������͵����������������Ľ��
			T->width = 0;     //�����Ŀ������Ϊ0��������ⲿ�����ĵ�ַ�������Ӱ��
			T->offset = DX;   //���þֲ������ڻ��¼�е�ƫ������ֵ
			T->FuncDec->offset = DX;
			semantic_Analysis(T->FuncDec); //���������Ͳ�����㲿�֣����ﲻ�����üĴ������ݲ���
			T->offset += T->FuncDec->width;   //���βε�Ԫ����޸ĺ����ֲ���������ʼƫ����
			T->Body->offset = T->offset;
			strcpy(T->Body->Snext, newLabel());  //���������ִ�н������λ������
			semantic_Analysis(T->Body);         //����������
			//������¼��С,����offset���Դ�ŵ��ǻ��¼��С������ƫ��
			symbolTable.symbols[T->FuncDec->place].offset = T->offset + T->Body->width;
			T->code = merge(3, T->FuncDec->code, T->Body->code, genLabel(T->Body->Snext));          //������Ĵ�����Ϊ�����Ĵ���
			break;
		case FUNC_DEC:      //���ݷ������ͣ���������д���ű�
			rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'F', 0);//���������������з��䵥Ԫ��ƫ����Ϊ0
			if (rtn == -1) {
				semantic_error(T->pos, T->type_id, "�����ظ�����");
				break;
			}
			else T->place = rtn;
			result.kind = ID;   strcpy(result.id, T->type_id);
			result.offset = rtn;
			T->code = genIR(FUNCTION, opn1, opn2, result);     //�����м���룺FUNCTION ������
			T->offset = DX;   //������ʽ�����ڻ��¼�е�ƫ������ֵ
			if (T->ParamList) { //�ж��Ƿ��в���
				T->ParamList->offset = T->offset;
				semantic_Analysis(T->ParamList);  //�����������б�
				T->width = T->ParamList->width;
				symbolTable.symbols[rtn].paramnum = T->ParamList->num;
				T->code = merge(2, T->code, T->ParamList->code);  //���Ӻ������Ͳ�����������
			}
			else symbolTable.symbols[rtn].paramnum = 0, T->width = 0;
			break;
		case PARAM_LIST:    //��������ʽ�����б�
			T->Param->offset = T->offset;
			semantic_Analysis(T->Param);
			if (T->ParamList)
			{
				T->ParamList->offset = T->offset + T->Param->width;
				semantic_Analysis(T->ParamList);
				T->num = T->Param->num + T->ParamList->num;        //ͳ�Ʋ�������
				T->width = T->Param->width + T->ParamList->width;  //�ۼӲ�����Ԫ���
				T->code = merge(2, T->Param->code, T->ParamList->code);  //���Ӳ�������
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
				semantic_error(T->ID->pos, T->ID->type_id, "�������ظ�����");
			else T->ID->place = rtn;
			T->num = 1;       //������������ĳ�ʼֵ
			if (T->Specifier->type == INT) {
				T->width = 4;
			}
			if (T->Specifier->type == FLOAT) {
				T->width = 8;
			}
			if (T->Specifier->type == CHAR) {
				T->width = 1;
			}
			//T->width = T->Specifier->type == INT ? 4 : 8;  //�������
			result.kind = ID;   strcpy(result.id, symbolTable.symbols[rtn].alias);
			result.offset = T->offset;
			T->code = genIR(PARAM, opn1, opn2, result);     //���ɣ�FUNCTION ������
			break;
		case COMP_STM:
			LEV++;
			//���ò�ż�1�����ұ���ò�ֲ������ڷ��ű��е���ʼλ����symbol_scope_TX
			symbol_scope_TX.TX[symbol_scope_TX.top++] = symbolTable.index;
			T->width = 0;
			T->code = NULL;
			if (T->DefList) {
				T->DefList->offset = T->offset;
				semantic_Analysis(T->DefList);  //����ò�ľֲ�����DEF_LIST
				T->width += T->DefList->width;
				T->code = T->DefList->code;
			}
			if (T->StmList) {
				T->StmList->offset = T->offset + T->width;
				strcpy(T->StmList->Snext, T->Snext);  //S.next�������´���
				semantic_Analysis(T->StmList);       //�����������������
				T->width += T->StmList->width;
				T->code = merge(2, T->code, T->StmList->code);
			}
#if (DEBUG1)
			if (LEV == 1)
				printf("\n��%d�к����ĺ��������ǰ���ű�(��2�㣩��\n", T->pos);
			else printf("\n��%d�и���������ǰ���ű�(��%d��)��\n", T->pos, LEV + 1);
			prn_symbol();       //c���˳�һ���������ǰ��ʾ�ķ��ű�
			system("pause");
#endif
			LEV--;    //��������䣬��ż�1
			symbolTable.index = symbol_scope_TX.TX[--symbol_scope_TX.top]; //ɾ�����������еķ���
			break;
		case DEF_LIST:
			T->code = NULL;
			if (T->Def) {
				T->Def->offset = T->offset;
				semantic_Analysis(T->Def);   //����һ���ֲ���������
				T->code = T->Def->code;
				T->width = T->Def->width;
			}
			if (T->DefList) {
				T->DefList->offset = T->offset + T->Def->width;
				semantic_Analysis(T->DefList);   //����ʣ�µľֲ���������
				T->code = merge(2, T->code, T->DefList->code);
				T->width += T->DefList->width;
			}
			break;
		case VAR_DEF://����һ���ֲ���������,����һ������(TYPE���)�е������͵��ڶ������ӵ�������
				 //������������ⲿ����EXT_VAR_DEF������һ�ִ�����
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
			//T->DecList->type = !strcmp(T->Specifier->type_id, "int") ? INT : FLOAT;  //ȷ���������и���������
			T0 = T->DecList; //T0Ϊ�������б�������ָ�룬��ID��ASSIGNOP�����ڵǼǵ����ű���Ϊ�ֲ�����
			num = 0;
			T0->offset = T->offset;
			T->width = 0;
			//width = T->DecList->type == INT ? 4 : 8;  //һ���������
			while (T0)
			{  //��������DEC_LIST���
				num++;
				T0->Dec->type = T0->type;  //�����������´���
				if (T0->DecList) T0->DecList->type = T0->type;
				T0->Dec->offset = T0->offset;  //�����������´���
				if (T0->DecList) T0->DecList->offset = T0->offset + width;
				if (T0->Dec->kind == ID)
				{
					rtn = fillSymbolTable(T0->Dec->type_id, newAlias(), LEV, T0->Dec->type, 'V', T->offset + T->width);//�˴�ƫ����δ���㣬��ʱΪ0
					if (rtn == -1)
						semantic_error(T0->Dec->pos, T0->Dec->type_id, "�����ظ�����");
					else T0->Dec->place = rtn;
					T->width += width;
				}
				else if (T0->Dec->kind == ASSIGNOP)
				{
					rtn = fillSymbolTable(T0->Dec->Dec->type_id, newAlias(), LEV, T0->Dec->type, 'V', T->offset + T->width);//�˴�ƫ����δ���㣬��ʱΪ0
					if (rtn == -1)
						semantic_error(T0->Dec->Dec->pos, T0->Dec->Dec->type_id, "�����ظ�����");
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
                              $$->pos=yylineno;   $$->Dec=$1;$$->DecList=NULL;} //�ֲ�����
				Dec:     VarDec  {$$=$1;}
					   | VarDec ASSIGNOP Exp  
					   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ASSIGNOP;
						$$->pos=yylineno;   $$->Dec=$1;$$->Exp2=$3;}
				VarDec:  ID   {$$=(ASTNode *)malloc(sizeof(ASTNode)); $$->kind=ID;
							   $$->pos=yylineno; strcpy($$->type_id,$1);}                    //ID��㣬��ʶ�����Ŵ���Ž���type_id
	|			ID Arraylist {$$=(ASTNode *)malloc(sizeof(ASTNode));$$->kind=ARRAY_DEC;
							  strcpy($$->type_id,$1);$$->Dec=$2;$$->pos=yylineno;}
				*/
				else if (T0->Dec->kind == ARRAY_DEC) {
					arr_index = 0;
					strcpy(array_name, T0->Dec->type_id);
					rtn = fillSymbolTable(T0->Dec->type_id, newAlias(), LEV, T0->Dec->type, 'A', T->offset + T->width);//�˴�ƫ����δ���㣬��ʱΪ0
					if (rtn == -1) {
						semantic_error(T0->Dec->pos, T0->Dec->type_id, "�����ظ�����");
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
				semantic_error(T->pos, array_name, "����δ����");
			}
			if (T->Exp1->type != INT) {
				semantic_error(T->pos, "", "���鶨��ά����Ҫ������");
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
				semantic_error(T->pos, array_name, "����δ����");
			}
			if (T->Exp1->type != INT) {
				semantic_error(T->pos, "", "���鶨��ά����Ҫ������");
			}
			else {
				symbolTable.symbols[rtn].array[arr_index] = T->Exp1->type_int;
			}
			break;
		case STM_LIST:
			if (T->StmList) //2������������ӣ������±����Ϊ��һ���������󵽴��λ��
				strcpy(T->Stm->Snext, newLabel());
			else     //������н���һ����䣬S.next�������´���
				strcpy(T->Stm->Snext, T->Snext);
			T->Stm->offset = T->offset;
			semantic_Analysis(T->Stm);
			T->code = T->Stm->code;
			T->width = T->Stm->width;
			if (T->StmList)
			{     //2�������������,S.next�������´���
				strcpy(T->StmList->Snext, T->Snext);
				T->StmList->offset = T->offset;  //˳��ṹ����Ԫ��ʽ
				semantic_Analysis(T->StmList);
				//�����е�1��Ϊ���ʽ��䣬������䣬�������ʱ����2��ǰ����Ҫ���
				if (T->Stm->kind == RETURN || T->Stm->kind == EXP_STMT || T->Stm->kind == COMP_STM)
					//�Է�����䡢���ʽ��䡢������䣬��ȥ�ͺ�������ı��
					T->code = merge(2, T->code, T->StmList->code);
				else
					T->code = merge(3, T->code, genLabel(T->Stm->Snext), T->StmList->code);
				if (T->StmList->width > T->width) //���������Ҫ���൥Ԫʱ��������Щ
					T->width = T->StmList->width; //˳�����ĵ�Ԫwidth��ʵ�ֹ���Ԫ��ʽ
			}
			break;
		case IF_THEN:
			strcpy(T->Cond->Etrue, newLabel());  //��������������ת��λ��
			strcpy(T->Cond->Efalse, T->Snext);
			T->Cond->offset = T->IfStm->offset = T->offset;
			boolExp(T->Cond);
			T->width = T->Cond->width;
			strcpy(T->IfStm->Snext, T->Snext);
			semantic_Analysis(T->IfStm);      //if�Ӿ�
			if (T->width < T->IfStm->width) 
				T->width = T->IfStm->width;
			T->code = merge(3, T->Cond->code, genLabel(T->Cond->Etrue), T->IfStm->code);
			break;  //������䶼��û�д���offset��width����
		case IF_THEN_ELSE:
			strcpy(T->Cond->Etrue, newLabel());  //��������������ת��λ��
			strcpy(T->Cond->Efalse, newLabel());
			T->Cond->offset = T->IfStm->offset = T->ElseStm->offset = T->offset;
			boolExp(T->Cond);      //������Ҫ��������·���봦��
			T->width = T->Cond->width;
			strcpy(T->IfStm->Snext, T->Snext);
			semantic_Analysis(T->IfStm);      //if�Ӿ�
			if (T->width < T->IfStm->width) 
				T->width = T->IfStm->width;
			strcpy(T->ElseStm->Snext, T->Snext);
			semantic_Analysis(T->ElseStm);      //else�Ӿ�
			if (T->width < T->ElseStm->width) 
				T->width = T->ElseStm->width;
			T->code = merge(6, T->Cond->code, genLabel(T->Cond->Etrue), T->IfStm->code, \
				genGoto(T->Snext), genLabel(T->Cond->Efalse), T->ElseStm->code);
			break;
		case WHILE: 
			strcpy(T->Cond->Etrue, newLabel());  //�ӽ��̳����Եļ���
			strcpy(T->Cond->Efalse, T->Snext);
			T->Cond->offset = T->Body->offset = T->offset;
			boolExp(T->Cond);      //ѭ��������Ҫ��������·���봦��
			T->width = T->Cond->width;
			strcpy(T->Body->Snext, newLabel());
			strcpy(break_label, T->Snext);//breakִ��while����һ�¸����
			strcpy(continue_label, T->Body->Snext);//continueִ����һ��ѭ����
			semantic_Analysis(T->Body);      //ѭ����
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
				/*��Ҫ�жϷ���ֵ�����Ƿ�ƥ��*/
				do
					num--;
				while (symbolTable.symbols[num].flag != 'F');
				if (T->Exp1->type != symbolTable.symbols[num].type){
					semantic_error(T->pos, "����ֵ���ʹ���", "");
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
			Exp(T);          //����������ʽ
			break;
		}
	}
}

void semantic_Analysis0(struct ASTNode *T) {
	symbolTable.index = 0;
	fillSymbolTable("read", "", 0, INT, 'F', 4);
	symbolTable.symbols[0].paramnum = 0;//read���βθ���
	fillSymbolTable("write", "", 0, INT, 'F', 4);
	symbolTable.symbols[1].paramnum = 1;
	fillSymbolTable("x", "", 1, INT, 'P', 12);
	symbol_scope_TX.TX[0] = 0;  //�ⲿ�����ڷ��ű��е���ʼ���Ϊ0
	symbol_scope_TX.top = 1;
	T->offset = 0;              //�ⲿ��������������ƫ����
	semantic_Analysis(T);
	prnIR(T->code);				//�����м����
	objectCode(T->code);	//����Ŀ�����
}

// int searchSymbolTableByAlias(char *alias)
// {
// 	int i;
// 	for (i = symbolTable.index - 1; i >= 0; i--)
// 		if (!strcmp(symbolTable.symbols[i].alias, alias))
// 			return i;
// 	return -1;
// }

// //���Ŀ�����
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
// 	fprintf(fp, "j main\n");//��ת��main����
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
// 	do { //�������ؼĴ�������
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
// 				/*if (h->opn1.arrIDFlag != 1) {//����ID���±�
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
// 						fprintf(fp, "  lw $t1, %d($gp)\n", h->opn1.offset);//�˴�Ӧ�ü���offset����Ӧ����MIPSȥ���㣬��������C
// 						fprintf(fp, "  move $t3, $t1\n");
// 					}
// 					else if (rtn != -1 && symbolTable.symbols[rtn].level != 0) {
// 						fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);//�˴�Ӧ�ü���offset����Ӧ����MIPSȥ���㣬��������C
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
// 			/*if (h->result.arrIDFlag != 1) {//����ID���±�
// 				if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
// 					fprintf(fp, "  sw $t3, %d($gp)\n", h->result.offset);
// 				}
// 				else {
// 					fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
// 				}
// 			}
// 			else {
// 				if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
// 					fprintf(fp, "  sw $t3, %d($gp)\n", h->result.offset);//�˴�Ӧ�ü���offset����Ӧ����MIPSȥ���㣬��������C
// 				}
// 				else {
// 					fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);//�˴�Ӧ�ü���offset����Ӧ����MIPSȥ���㣬��������C
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
// 			if (!strcmp(h->result.id, "main")) {//���⴦��main
// 				main_flag = 1;
// 				LEV = 0;
// 				main_call = 0;
// 				fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->result.offset].offset);

// 			}
// 			break;
// 		case PARAM: //ֱ����������һ��
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
// 		case ARG:   //ֱ����������һ��,ֱ���������ã���ͷ���������
// 			break;
// 		case CALL:  
// 			call_flag = 1;
// 			LEV++;
// 			if (!strcmp(h->opn1.id, "read")) { //���⴦��read
// 				fprintf(fp, "  addi $sp, $sp, -4\n");
// 				fprintf(fp, "  sw $ra,0($sp)\n"); //�������ص�ַ
// 				fprintf(fp, "  jal read\n"); //�������ص�ַ
// 				fprintf(fp, "  lw $ra,0($sp)\n"); //�ָ����ص�ַ
// 				fprintf(fp, "  addi $sp, $sp, 4\n");
// 				fprintf(fp, "  sw $v0, %d($sp)\n", h->result.offset);
// 				break;
// 			}
// 			if (!strcmp(h->opn1.id, "write")) { //���⴦��write
// 				fprintf(fp, "  lw $a0, %d($sp)\n", h->prior->result.offset);
// 				fprintf(fp, "  addi $sp, $sp, -4\n");
// 				fprintf(fp, "  sw $ra,0($sp)\n");
// 				fprintf(fp, "  jal write\n");
// 				fprintf(fp, "  lw $ra,0($sp)\n");
// 				fprintf(fp, "  addi $sp, $sp, 4\n");
// 				break;
// 			}

// 			for (p = h, i = 0; i < symbolTable.symbols[h->opn1.offset].paramnum; i++)  //��λ����һ��ʵ�εĽ��
// 				p = p->prior;
// 					//�����¼�ռ�
// 			fprintf(fp, "  move $t0,$sp\n"); //���浱ǰ������sp��$t0�У�Ϊ��ȡʵ�α��ʽ��ֵ
// 			fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->opn1.offset].offset);
// 			fprintf(fp, "  sw $ra,0($sp)\n"); //�������ص�ַ
// 			i = h->opn1.offset + 1;  //��һ���βα����ڷ��ű��λ�����
// 			while (symbolTable.symbols[i].flag == 'P'){
// 				fprintf(fp, "  lw $t1, %d($t0)\n", p->result.offset); //ȡʵ��ֵ
// 				fprintf(fp, "  move $t3,$t1\n");
// 				fprintf(fp, "  sw $t3,%d($sp)\n", symbolTable.symbols[i].offset); //�͵������ú������βε�Ԫ
// 				p = p->next; i++;
// 			}
// 			fprintf(fp, "  jal %s\n", h->opn1.id); //�ָ����ص�ַ
// 			fprintf(fp, "  lw $ra,0($sp)\n"); //�ָ����ص�ַ
// 			fprintf(fp, "  addi $sp,$sp,%d\n", symbolTable.symbols[h->opn1.offset].offset); //�ͷŻ��¼�ռ�
// 			fprintf(fp, "  sw $v0,%d($sp)\n", h->result.offset); //ȡ����ֵ
// 			break;
// 		case RETURN:
// 			//fprintf(fp, "  lw $v0,%d($sp)\n", h->result.offset); //����ֵ�͵�$v0
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