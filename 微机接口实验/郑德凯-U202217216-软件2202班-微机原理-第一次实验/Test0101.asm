CODE SEGMENT
ASSUME CS:CODE, DS:CODE  ; 添加 DS 的定义

START:
    ; 给 AX、BX、CX、DX 赋初始值
    MOV AX, 1234H         ; AX = 1234H
    MOV BX, 5678H         ; BX = 5678H
    MOV CX, 9ABCH         ; CX = 9ABCH
    MOV DX, 4321H         ; DX = 4321H 

    ; 交换 AX 和 BX 的值
    PUSH AX
    MOV AX, BX
    POP BX

    ; 交换 CX 和 DX 的值
    PUSH CX
    MOV CX, DX
    POP DX

    ; 交换 AX 的高 8 位与 DX 的低 8 位的值
    XCHG AH, AL

    ; 程序结束
    MOV AX, 4C00h         ; 正常退出 DOS
    INT 21h

CODE ENDS
END START