DATA SEGMENT
    PROMPT DB 'Please enter a sentence: $'
    INPUT DB 80, ?, 80 DUP(' ')
    OUTPUT DB 80 DUP(' '), '$'
    CHANGEROW DB 0DH, 0AH, '$'
DATA ENDS

STACK SEGMENT
    DW 128 DUP(0)
STACK ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    MOV AX, DATA
    MOV DS, AX
    MOV AX, STACK
    MOV SS, AX
    MOV SP, 256

    ; 显示提示信息
    MOV AH, 09H
    LEA DX, PROMPT
    INT 21H

    ; 读取输入的句子
    LEA DX, INPUT
    MOV AH, 0AH
    INT 21H

    ; 处理句子，首字母大写，其他字母小写
    LEA SI, INPUT + 2
    LEA DI, OUTPUT
    MOV BL, ' '        
    MOV CL, [INPUT+1]  

PROCESS_LOOP:
    MOV AL, [SI]
    
    ; 检查是否为第一个字符
    CMP SI, OFFSET INPUT + 2
    JNE CHECK_SPACE
    
    ; 将首字母转换为大写
    CMP AL, 'a'
    JB STORE_CHAR
    CMP AL, 'z'
    JA STORE_CHAR
    SUB AL, 20H
    JMP STORE_CHAR

CHECK_SPACE:
    ; 如果前一个字符不是空格，将当前字符转换为小写
    CMP BL, ' '
    JE STORE_CHAR
    CMP AL, 'A'
    JB STORE_CHAR
    CMP AL, 'Z'
    JA STORE_CHAR
    ADD AL, 20H

STORE_CHAR:
    MOV [DI], AL
    INC DI
    MOV BL, AL
    INC SI
    LOOP PROCESS_LOOP

    ; 结束输出字符串
    MOV BYTE PTR [DI], '$'

    MOV AH, 09H
    LEA DX, CHANGEROW
    INT 21H

    ; 显示处理后的句子
    MOV AH, 09H
    LEA DX, OUTPUT
    INT 21H

    MOV AH, 4CH
    INT 21H

CODE ENDS
END START