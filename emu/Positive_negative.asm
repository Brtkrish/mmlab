DATA SEGMENT
    ARRAY     DW 0005H, 0FFF0H, 0003H, 0FFFEH, 0007H
    COUNT     DW 05H
    POS_ARRAY DW 5 DUP(?)
    NEG_ARRAY DW 5 DUP(?)
    POS_COUNT DW 0
    NEG_COUNT DW 0
    MSG1      DB 'Positive numbers:$'
    MSG2      DB 0DH,0AH,'Negative numbers:$'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, @DATA
    MOV DS, AX

    LEA SI, ARRAY
    LEA DI, POS_ARRAY
    LEA BP, NEG_ARRAY
    MOV CX, COUNT

LOOP1:
    MOV AX, [SI]
    TEST AX, 8000H
    JZ POSITIVE

    MOV [BP], AX
    ADD BP, 2
    INC WORD PTR NEG_COUNT
    JMP NEXT_NUM

POSITIVE:
    MOV [DI], AX
    ADD DI, 2
    INC WORD PTR POS_COUNT

NEXT_NUM:
    ADD SI, 2
    LOOP LOOP1

    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    LEA SI, POS_ARRAY
    MOV CX, POS_COUNT
POS_DISP:
    MOV AX, [SI]
    CALL DISP_NUM
    ADD SI, 2
    LOOP POS_DISP

    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    LEA SI, NEG_ARRAY
    MOV CX, NEG_COUNT
NEG_DISP:
    MOV AX, [SI]
    CALL DISP_NUM
    ADD SI, 2
    LOOP NEG_DISP

    MOV AH, 4CH
    INT 21H

DISP_NUM PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    MOV BX, 10
    XOR CX, CX
CONVERT:
    XOR DX, DX
    DIV BX
    PUSH DX
    INC CX
    TEST AX, AX
    JNZ CONVERT
PRINT:
    POP DX
    ADD DL, 30H
    MOV AH, 02H
    INT 21H
    LOOP PRINT
    MOV DL, ' '
    MOV AH, 02H
    INT 21H
    POP DX
    POP CX
    POP BX
    POP AX
    RET
DISP_NUM ENDP

CODE ENDS
END START
