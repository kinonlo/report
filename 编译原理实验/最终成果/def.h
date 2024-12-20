#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#include "parser.tab.h"
#define MAXLENGTH   200
#define DX 3*sizeof(int)          /*���¼������Ϣ��Ҫ�ĵ�Ԫ�����������ʵ��ϵͳ����*/

int LEV;      //���

struct opn {
	int kind;    //��ʶ���ϳ�Ա������
	int type;    //��ʶ����������������
	union {
		int     const_int;      //������ֵ��������
		float   const_float;    //���㳣��ֵ��������
		char    const_char;     //�ַ�����ֵ��������
		char    id[33];         //��������ʱ�����ı��������ַ���
	};
	int level;                  //�����Ĳ�ţ�0��ʾ��ȫ�ֱ��������ݱ����ھ�̬������
	int offset;                 //ƫ������Ŀ���������ʱ��
	int arrIDFlag;				//������±�Ϊ���ʽ�����飬��Ϊ1
};

struct codenode {   //����ַTAC������,���õ��������м����Դ���
	int  op;
	struct opn opn1, opn2, result;
	struct codenode  *next, *prior;
};

typedef struct ASTNode {
	//���¶Խ�����Զ���û�п��Ǵ洢Ч�ʣ�ֻ�Ǽ򵥵��г�Ҫ�õ���һЩ����
	int kind;
	union {
		char type_id[33];        //�ɱ�ʶ�����ɵ�Ҷ���
		int type_int;            //�����������ɵ�Ҷ���
		float type_float;        //�ɸ��㳣�����ɵ�Ҷ���
		char type_char;			 //���ַ��������ɵ�Ҷ���
	};
	union {//��1ָ����
		struct ASTNode *Specifier; //˵����������
		struct ASTNode *Param;     //����˵��
		struct ASTNode *Cond;      //ѭ��������if�������
		struct ASTNode *Exp1;       //���ʽ
		struct ASTNode *Def;       //������䶨��
		struct ASTNode *Dec;       //�ⲿ��ֲ�����
		struct ASTNode *Stm;      //���
	};
	union {//��2ָ����
		struct ASTNode *DefList;    //�ⲿ��ֲ���������б�
		struct ASTNode *DecList;    //�ⲿ��ֲ������б�
		struct ASTNode *FuncDec;    //�������Ͳ������ָ��
		struct ASTNode *ParamList;  //�����б�
		struct ASTNode *Args;       //ʵ�α��ʽ�б�
		struct ASTNode *IfStm;      //if�Ӿ�
		struct ASTNode *RightExp;   //˫Ŀ����������������ʽ
		struct ASTNode *Exp2;       //���ʽ2
		struct ASTNode *ID;         //��ʶ��
	};
	union {//��3ָ����
		struct ASTNode *StmList;   //�������
		struct ASTNode *ElseStm;    //else�Ӿ�
		struct ASTNode *Exp3;       //��for�����ʽ3
	};
	union {//��4ָ����
		struct ASTNode *Body;
	};
	int place;                      //��ţ���ʱ�������ڷ��ű��λ�����
	char Etrue[15], Efalse[15];      //�Բ������ʽ�ķ���ʱ�����ת��Ŀ��ı��
	char Snext[15];                 //����Ӧ���Sִ�к����һ�����λ�ñ��
	struct codenode *code;          //�ý���м��������ͷָ��
	int type;                       //���Ա�ʶ���ʽ��������
	int pos;                        //�﷨��λ����λ���к�
	int offset;                     //ƫ����
	char checkID;					//�����±���ID��ʾʱ��ʹ��ƫ������ʱ�������¼���
	int width;                      //ռ�����ֽ���
	int num;                        //����������������ͳ���βθ���
	int arrsize;					//�����ά�ȵĳ���
} ASTNode;

struct symbol {     //����ֻ�г���һ�����ű���Ĳ������ԣ�û�������Լ�Ļ���
	char name[33];  //����������
	int level;      //���
	int type;       //�������ͻ�������ֵ����
	int  paramnum;  //�Ժ������ã���¼��ʽ��������
	char alias[10]; //������Ϊ���Ƕ�ײ��ʹ��
	char flag;      //���ű�ǣ�������'F'  ������'V'   ������'P'  ��ʱ������'T'
	unsigned int offset;    //�ⲿ�����;ֲ��������侲̬����������¼�е�ƫ���������¼�������¼��С��Ŀ���������ʱʹ��
	int array[10];
	int const_int;
	//�������...
};
//���ű�
struct symboltable {
	struct symbol symbols[MAXLENGTH];
	int index;
} symbolTable;

struct symbol_scope_begin {
	//��ǰ������ķ����ڷ��ű����ʼλ�����,���Ǹ�ջ�ṹ
	int TX[30];
	int top;
} symbol_scope_TX;

char break_label[30];
char continue_label[30];
char array_name[30];



struct ASTNode * mknode(int num, int kind, int pos, ...);
void semantic_Analysis0(struct ASTNode *T);
void semantic_Analysis(struct ASTNode *T);
void boolExp(struct ASTNode *T);
void Exp(struct ASTNode *T);
void objectCode(struct codenode *head);
int searchSymbolTable(char *name);