.MODEL SMALL
.STACK 100H
.DATA
    prompt DB 'Enter 8 numbers (0-100), press Enter after each:', 13, 10, '$'
    error_msg DB 'Invalid input! Please enter a number between 0 and 100.', 13, 10, '$'
    newline DB 13, 10, '$'
    range1_msg DB 'Numbers in [0-59]: $'
    range2_msg DB 'Numbers in [60-79]: $'
    range3_msg DB 'Numbers in [80-100]: $'
    avg_msg DB 'Average: $'
    numbers DB 8 DUP(?)
    range1 DB 0
    range2 DB 0
    range3 DB 0
    sum DW 0
    count DB 0

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; 显示提示信息
    LEA DX, prompt
    MOV AH, 9
    INT 21H

    LEA SI, numbers

INPUT_LOOP:
    CALL READ_NUMBER
    JC INPUT_ERROR  ; 如果出错则跳转到错误处理

    MOV [SI], AL
    INC SI
    
    ; 累加数字和
    XOR AH, AH
    ADD sum, AX

    ; 对输入数字进行分类
    CMP AL, 60
    JL INCREMENT_RANGE1
    CMP AL, 80
    JL INCREMENT_RANGE2
    JMP INCREMENT_RANGE3

INCREMENT_RANGE1:
    INC range1
    JMP CONTINUE_INPUT

INCREMENT_RANGE2:
    INC range2
    JMP CONTINUE_INPUT

INCREMENT_RANGE3:
    INC range3

CONTINUE_INPUT:
    INC count
    CMP count, 8
    JL INPUT_LOOP
    JMP DISPLAY_RESULTS

INPUT_ERROR:
    LEA DX, error_msg
    MOV AH, 9
    INT 21H
    JMP INPUT_LOOP

DISPLAY_RESULTS:
    ; 显示分类结果
    CALL DISPLAY_NEWLINE
    
    LEA DX, range1_msg
    MOV AH, 9
    INT 21H
    MOV AL, range1
    CALL DISPLAY_NUMBER

    CALL DISPLAY_NEWLINE
    LEA DX, range2_msg
    MOV AH, 9
    INT 21H
    MOV AL, range2
    CALL DISPLAY_NUMBER

    CALL DISPLAY_NEWLINE
    LEA DX, range3_msg
    MOV AH, 9
    INT 21H
    MOV AL, range3
    CALL DISPLAY_NUMBER

    ; 显示平均值
    CALL DISPLAY_NEWLINE
    LEA DX, avg_msg
    MOV AH, 9
    INT 21H
    
    MOV AX, sum
    MOV BL, 8
    DIV BL
    CALL DISPLAY_NUMBER

    MOV AH, 4CH
    INT 21H
MAIN ENDP

READ_NUMBER PROC
    XOR BX, BX
    XOR CX, CX

READ_DIGIT:
    MOV AH, 1
    INT 21H
    
    CMP AL, 13
    JE END_READ
    
    CMP AL, '0'
    JL INVALID_INPUT
    CMP AL, '9'
    JG INVALID_INPUT
    
    SUB AL, '0'
    MOV AH, 0
    PUSH AX
    
    MOV AX, BX
    MOV DX, 10
    MUL DX
    MOV BX, AX
    
    POP AX
    ADD BX, AX
    
    INC CX
    CMP CX, 3
    JG INVALID_INPUT
    
    CMP BX, 100
    JG INVALID_INPUT
    
    JMP READ_DIGIT

INVALID_INPUT:
    STC
    RET

END_READ:
    MOV AL, BL
    CLC
    RET
READ_NUMBER ENDP

DISPLAY_NUMBER PROC
    XOR AH, AH
    MOV BL, 10
    DIV BL
    PUSH AX

    CMP AL, 0
    JE DISPLAY_SINGLE_DIGIT

    ADD AL, '0'
    MOV DL, AL
    MOV AH, 2
    INT 21H

DISPLAY_SINGLE_DIGIT:
    POP AX
    MOV AL, AH
    ADD AL, '0'
    MOV DL, AL
    MOV AH, 2
    INT 21H

    RET
DISPLAY_NUMBER ENDP

DISPLAY_NEWLINE PROC
    MOV AH, 2
    MOV DL, 13
    INT 21H
    MOV DL, 10
    INT 21H
    RET
DISPLAY_NEWLINE ENDP

END MAIN