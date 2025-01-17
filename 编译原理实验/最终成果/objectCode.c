#include "def.h"

int searchSymbolTableByAlias(char *alias)
{
	int i;
	for (i = symbolTable.index - 1; i >= 0; i--)
		if (!strcmp(symbolTable.symbols[i].alias, alias))
			return i;
	return -1;
}
//输出目标代码
void objectCode(struct codenode *head)
{
    char opnstr1[32],opnstr2[32],resultstr[32];
    struct codenode *h=head,*p;
    int i;
    FILE *fp;
    fp=fopen("object.s","w");
    fprintf(fp,".data\n");
    fprintf(fp,"_Prompt: .asciiz \"Enter an integer:  \"\n");
    fprintf(fp,"_ret: .asciiz \"\\n\"\n");
    fprintf(fp,".globl main\n");
    fprintf(fp,".text\n");
	fprintf(fp, "j main\n");//跳转到main函数
    fprintf(fp,"read:\n");
    fprintf(fp,"  li $v0,4\n");
    fprintf(fp,"  la $a0,_Prompt\n");
    fprintf(fp,"  syscall\n");
    fprintf(fp,"  li $v0,5\n");
    fprintf(fp,"  syscall\n");
    fprintf(fp,"  jr $ra\n");
    fprintf(fp,"write:\n");
    fprintf(fp,"  li $v0,1\n");
    fprintf(fp,"  syscall\n");
    fprintf(fp,"  li $v0,4\n");
    fprintf(fp,"  la $a0,_ret\n");
    fprintf(fp,"  syscall\n");
    fprintf(fp,"  move $v0,$0\n");
    fprintf(fp,"  jr $ra\n");
    do { //采用朴素寄存器分配
        switch (h->op) {
            case ASSIGNOP:
                        /*if (h->opn1.kind==INT)
                            fprintf(fp, "  li $t3, %d\n", h->opn1.const_int);
                        else {
                            fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                            fprintf(fp, "  move $t3, $t1\n");
                            }
                        fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
                        break;*/
				if (h->opn1.kind == INT) {
					fprintf(fp, "  li $t3, %d\n", h->opn1.const_int);
				}
				else if (h->opn1.kind == FLOAT) {
					fprintf(fp, "  li $t3, %f\n", h->opn1.const_float);
				}
				else if (h->opn1.kind == CHAR) {
					fprintf(fp, "  li $t3, %c\n", h->opn1.const_char);
				}
				else {
					int rtn;
					char arrName[10] = { '\0' };
					if (strstr(h->opn1.id, " offset ") != NULL) {
						for (int i = 0; i < strlen(h->result.id); i++) {
							if (h->result.id[i] != ' ') {
								arrName[i] = h->result.id[i];
							}
						}
						rtn = searchSymbolTableByAlias(arrName);
					}
					else
						rtn = searchSymbolTableByAlias(h->opn1.id);
					// printf("%d %s %d %d\n", rtn, , symbolTable.symbols[rtn].level, LEV);
					if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
						fprintf(fp, "  lw $t1, %d($gp)\n", h->opn1.offset);
						fprintf(fp, "  move $t3, $t1\n");
					}
					else if (rtn != -1 && symbolTable.symbols[rtn].level != 0) {
						fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);//此处应该计算offset，并应该由MIPS去计算，而不是由C
						fprintf(fp, "  move $t3, $t1\n");
					}
				}
				int rtn;
				char arrName[10] = { '\0' };
				if (strstr(h->result.id, " offset ") != NULL) {
					for (int i = 0; i < strlen(h->result.id); i++) {
						if (h->result.id[i] != ' ') {
							arrName[i] = h->result.id[i];
						}
					}
					rtn = searchSymbolTableByAlias(arrName);
				}
				else
					rtn = searchSymbolTableByAlias(h->result.id);
				// fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
				// printf("%s %d %d\n", h->result.id, symbolTable.symbols[rtn].level, LEV);
				if (rtn != -1 && symbolTable.symbols[rtn].level == 0) {
					fprintf(fp, "  sw $t3, %d($gp)\n", h->result.offset);//此处应该计算offset，并应该由MIPS去计算，而不是由C
				}
				else {
					fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
				}
				break;
            case PLUS:
            case MINUS:
            case STAR:
            case DIV:
                       fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                       fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
                       if (h->op==PLUS)       fprintf(fp, "  add $t3,$t1,$t2\n");
                       else if (h->op==MINUS) fprintf(fp, "  sub $t3,$t1,$t2\n");
                            else if (h->op==STAR)  fprintf(fp, "  mul $t3,$t1,$t2\n");
                                 else  {fprintf(fp, "  div $t1, $t2\n");
                                        fprintf(fp, "  mflo $t3\n");
                                        }
                        fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
                        break;
            case FUNCTION:
                        fprintf(fp, "\n%s:\n", h->result.id);
                        if (!strcmp(h->result.id,"main")) //特殊处理main
                            fprintf(fp, "  addi $sp, $sp, -%d\n",symbolTable.symbols[h->result.offset].offset);
                        break;
            case PARAM: //直接跳到后面一条
                        break;
            case LABEL: fprintf(fp, "%s:\n", h->result.id);
                        break;
            case GOTO:  fprintf(fp, "  j %s\n", h->result.id);
                        break;
            case JLE:
            case JLT:
            case JGE:
            case JGT:
            case EQ:
            case NEQ:
                        fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                        fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
                        if (h->op==JLE) fprintf(fp, "  ble $t1,$t2,%s\n", h->result.id);
                        else if (h->op==JLT) fprintf(fp, "  blt $t1,$t2,%s\n", h->result.id);
                        else if (h->op==JGE) fprintf(fp, "  bge $t1,$t2,%s\n", h->result.id);
                        else if (h->op==JGT) fprintf(fp, "  bgt $t1,$t2,%s\n", h->result.id);
                        else if (h->op==EQ)  fprintf(fp, "  beq $t1,$t2,%s\n", h->result.id);
                        else                 fprintf(fp, "  bne $t1,$t2,%s\n", h->result.id);
                        break;
            case ARG:   //直接跳到后面一条,直到函数调用，回头反查参数。
                        break;
            case CALL:  if (!strcmp(h->opn1.id,"read")){ //特殊处理read
                            fprintf(fp, "  addi $sp, $sp, -4\n");
                            fprintf(fp, "  sw $ra,0($sp)\n"); //保留返回地址
                            fprintf(fp, "  jal read\n"); //保留返回地址
                            fprintf(fp, "  lw $ra,0($sp)\n"); //恢复返回地址
                            fprintf(fp, "  addi $sp, $sp, 4\n");
                            fprintf(fp, "  sw $v0, %d($sp)\n",h->result.offset);
                            break;
                            }
                        if (!strcmp(h->opn1.id,"write")){ //特殊处理write
                            fprintf(fp, "  lw $a0, %d($sp)\n",h->prior->result.offset);
                            fprintf(fp, "  addi $sp, $sp, -4\n");
                            fprintf(fp, "  sw $ra,0($sp)\n");
                            fprintf(fp, "  jal write\n");
                            fprintf(fp, "  lw $ra,0($sp)\n");
                            fprintf(fp, "  addi $sp, $sp, 4\n");
                            break;
                            }

                        for(p=h,i=0;i<symbolTable.symbols[h->opn1.offset].paramnum;i++)  //定位到第一个实参的结点
                                p=p->prior;
                        //开活动记录空间
                        fprintf(fp, "  move $t0,$sp\n"); //保存当前函数的sp到$t0中，为了取实参表达式的值
                        fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->opn1.offset].offset);
                        fprintf(fp, "  sw $ra,0($sp)\n"); //保留返回地址
                        i=h->opn1.offset+1;  //第一个形参变量在符号表的位置序号
                        while (symbolTable.symbols[i].flag=='P')
                            {
                            fprintf(fp, "  lw $t1, %d($t0)\n", p->result.offset); //取实参值
                            fprintf(fp, "  move $t3,$t1\n");
                            fprintf(fp, "  sw $t3,%d($sp)\n",  symbolTable.symbols[i].offset); //送到被调用函数的形参单元
                            p=p->next; i++;
                            }
                        fprintf(fp, "  jal %s\n",h->opn1.id); //恢复返回地址
                        fprintf(fp, "  lw $ra,0($sp)\n"); //恢复返回地址
                        fprintf(fp, "  addi $sp,$sp,%d\n",symbolTable.symbols[h->opn1.offset].offset); //释放活动记录空间
                        fprintf(fp, "  sw $v0,%d($sp)\n", h->result.offset); //取返回值
                        break;
            case RETURN:fprintf(fp, "  lw $v0,%d($sp)\n",h->result.offset); //返回值送到$v0
                        fprintf(fp, "  jr $ra\n");
                        break;

        }
    h=h->next;
    } while (h!=head);
fclose(fp);
}
