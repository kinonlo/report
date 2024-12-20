DATA SEGMENT
    NUMBERS DW 0001H, 0002H, 0003H, 0004H, 0005H, 0006H, 0007H, 0008H
            DW 0009H, 000AH, 000BH, 000CH, 000DH, 000EH, 000FH, 0010H
    SUM DW 0FFFFH           ; 用于存放和的变量
DATA ENDS

STACK SEGMENT
    DW 16 DUP(0)           ; 创建堆栈，大小为16字
STACK ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACK

START:
    ; 初始化数据段
    MOV AX, DATA
    MOV DS, AX

    ; 初始化堆栈段
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 20H             ; 设置栈指针

    ; 求和部分
    MOV AX, 0               ; 清零 AX，准备求和
    MOV BX, 0               ; BX 指向 NUMBERS 数组的起始地址
    MOV CX, 16              ; 计数器设置为 16

S1:
    ADD AX, [NUMBERS + BX]  ; 将 NUMBERS 中的值加到 AX
    PUSH [NUMBERS + BX]      ; 将当前值压入栈中
    ADD BX, 2                ; BX 增加 2，指向下一个字
    LOOP S1                  ; 循环，直到 CX 为 0

    ; 保存总和
    MOV SUM, AX              ; 将 AX 的值存入 SUM

    ; 逆序部分
    MOV BX, 0               ; BX 重置为 0
    MOV CX, 16              ; 计数器重新设置为 16

S2:
    POP AX                   ; 从栈中弹出值到 AX
    MOV [NUMBERS + BX], AX   ; 将 AX 的值存储回 NUMBERS 数组
    ADD BX, 2                ; BX 增加 2，指向下一个字
    LOOP S2                  ; 循环，直到 CX 为 0

    ; 程序结束
    MOV AX, 4C00h           ; 正常退出 DOS
    INT 21h

CODE ENDS
END START