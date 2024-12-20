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

    ; ��ʾ��ʾ��Ϣ
    MOV AH, 09H
    LEA DX, PROMPT
    INT 21H

    ; ��ȡ����ľ���
    LEA DX, INPUT
    MOV AH, 0AH
    INT 21H

    ; ������ӣ�����ĸ��д��������ĸСд
    LEA SI, INPUT + 2
    LEA DI, OUTPUT
    MOV BL, ' '        
    MOV CL, [INPUT+1]  

PROCESS_LOOP:
    MOV AL, [SI]
    
    ; ����Ƿ�Ϊ��һ���ַ�
    CMP SI, OFFSET INPUT + 2
    JNE CHECK_SPACE
    
    ; ������ĸת��Ϊ��д
    CMP AL, 'a'
    JB STORE_CHAR
    CMP AL, 'z'
    JA STORE_CHAR
    SUB AL, 20H
    JMP STORE_CHAR

CHECK_SPACE:
    ; ���ǰһ���ַ����ǿո񣬽���ǰ�ַ�ת��ΪСд
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

    ; ��������ַ���
    MOV BYTE PTR [DI], '$'

    MOV AH, 09H
    LEA DX, CHANGEROW
    INT 21H

    ; ��ʾ�����ľ���
    MOV AH, 09H
    LEA DX, OUTPUT
    INT 21H

    MOV AH, 4CH
    INT 21H

CODE ENDS
END START