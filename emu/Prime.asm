DATA SEGMENT
    NUM DW 0013H
    MSG_PRIME DB 10, 13, 'Number is Prime$'
    MSG_NOT_PRIME DB 10, 13, 'Number is Not Prime$'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, @DATA
    MOV DS, AX

    MOV AX, NUM
    CMP AX, 1
    JBE NOT_PRIME

    MOV BX, AX
    MOV CX, 2

CHECK_LOOP:
    MOV DX, 0
    MOV AX, BX
    DIV CX
    CMP DX, 0
    JE NOT_PRIME

    INC CX
    MOV AX, CX
    MUL AX
    CMP AX, BX
    JBE CHECK_LOOP

PRIME:
    LEA DX, MSG_PRIME
    MOV AH, 09H
    INT 21H
    JMP EXIT

NOT_PRIME:
    LEA DX, MSG_NOT_PRIME
    MOV AH, 09H
    INT 21H

EXIT:
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
