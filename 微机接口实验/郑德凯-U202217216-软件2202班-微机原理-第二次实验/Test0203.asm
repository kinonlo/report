.MODEL SMALL
.STACK 100H
.DATA
    prompt DB 'Enter angle (0, 30, 60, 90, 120, 150, 180): $'
    error_msg DB 'Invalid input! Please enter a valid angle.', 13, 10, '$'
    newline DB 13, 10, '$'

    angles DW 0, 30, 60, 90, 120, 150, 180
    sine_values DB 'sin(  0)=0    $'
                DB 'sin( 30)=0.5  $'
                DB 'sin( 60)=0.866$'
                DB 'sin( 90)=1    $'
                DB 'sin(120)=0.866$'
                DB 'sin(150)=0.5  $'
                DB 'sin(180)=0    $'

    value_length DB 15  ; 每个正弦值字符串的长度（包括$符号）

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

INPUT:
    ; 显示提示信息
    LEA DX, prompt
    MOV AH, 9
    INT 21H

    ; 读取角度
    CALL READ_NUMBER

    ; 验证输入
    LEA SI, angles
    MOV CX, 7  ; 有效角度的数量
    MOV BX, AX  ; 将输入存储在BX中

VALIDATE:
    CMP BX, [SI]
    JE VALID_INPUT
    ADD SI, 2
    LOOP VALIDATE

    ; 无效输入
    LEA DX, error_msg
    MOV AH, 9
    INT 21H
    JMP INPUT

VALID_INPUT:
    ; 计算正弦值的索引
    SUB SI, OFFSET angles
    MOV AX, SI
    MOV BL, 2
    DIV BL
    
    ; 计算sine_values中的偏移量
    MUL value_length
    LEA SI, sine_values
    ADD SI, AX

    ; 显示正弦值
    MOV DX, SI
    MOV AH, 9
    INT 21H

    ; 打印换行
    LEA DX, newline
    INT 21H

    ; 退出程序
    MOV AH, 4CH
    INT 21H
MAIN ENDP

READ_NUMBER PROC
    XOR BX, BX  ; 使用BX存储数字
    MOV CX, 3   ; 最多3位数字

READ_DIGIT:
    MOV AH, 1
    INT 21H
    
    CMP AL, 13  ; 检查回车键
    JE END_READ
    
    CMP AL, '0'
    JL INVALID_INPUT
    CMP AL, '9'
    JG INVALID_INPUT
    
    SUB AL, '0'
    MOV AH, 0
    PUSH AX
    
    MOV AX, 10
    MUL BX
    MOV BX, AX
    
    POP AX
    ADD BX, AX
    
    LOOP READ_DIGIT
    JMP END_READ

INVALID_INPUT:
    MOV BX, 1000  ; 设置一个无效值

END_READ:
    MOV AX, BX  ; 将结果移动到AX
    RET
READ_NUMBER ENDP

END MAIN