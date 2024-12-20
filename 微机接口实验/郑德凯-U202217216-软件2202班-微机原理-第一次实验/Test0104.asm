DATA SEGMENT
    COUNT DW 8                    ; 数组中的元素数量
    NUMBERS DW 1234H, 5678H, 9ABCH, 0DEF0H, 1111H, 2222H, 3333H, 4444H  ; 数字数组
    RESULT DW ?                   ; 占位符，用于存放符合条件的数的个数
DATA ENDS

STACK SEGMENT
    DW 16 DUP(0)                  ; 栈初始化，分配16个字
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:STACK

START:
    MOV AX, DATA                  ; 初始化数据段
    MOV DS, AX
    MOV AX, STACK                 ; 初始化栈段
    MOV SS, AX
    MOV SP, 20H                   ; 设置堆栈指针

    ; 初始化 BX 指向数组的第一个元素
    MOV BX, OFFSET NUMBERS
    ADD BX, 2                     ; 跳过 COUNT，指向第一个数值

    ; 将 COUNT 的值加载到 CX 中，用于计数循环
    MOV CX, [OFFSET NUMBERS]

    ; 初始化 DI 指向 RESULT，用于存储符合条件的数的个数
    LEA DI, RESULT
    XOR DX, DX                    ; DX用于存储符合条件的数的个数，初始化为0

PROCESS:
    ; 将当前数字加载到 AX 中
    MOV AX, [BX]
    
    ; 检查 D3 位是否为1
    TEST AX, 0008H                ; 测试 D3 位（位3）
    JZ SKIP                        ; 如果D3位不为1，跳过

    ; D3位为1，增加计数
    INC DX

    ; 取反 D3 位
    XOR AX, 0008H                 ; 取反 D3 位
    MOV [BX], AX                  ; 将取反后的数存回原数组位置

SKIP:
    ; 移动到数组的下一个数字
    ADD BX, 2
    LOOP PROCESS                  ; 如果 CX 未减为 0，则继续循环

    ; 将计数结果存入 RESULT
    MOV [DI], DX

    ; 程序结束
    MOV AH, 4CH
    INT 21H

CODE ENDS
END START