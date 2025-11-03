DATA SEGMENT
    NUM       DB 10110010B
    ONE_COUNT DB ?
    MSG       DB 'Number of 1 bits = $'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, @DATA
    MOV DS, AX

    MOV AL, NUM
    MOV CX, 8
    MOV BL, 0

LOOP1:
    SHL AL, 1
    JNC NEXT_BIT
    INC BL

NEXT_BIT:
    LOOP LOOP1

    MOV ONE_COUNT, BL

    LEA DX, MSG
    MOV AH, 09H
    INT 21H

    MOV AL, ONE_COUNT
    ADD AL, 30H
    MOV DL, AL
    MOV AH, 02H
    INT 21H

    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
