DATA SEGMENT
    MSG1 DB 'Enter a string: $'
    MSG2 DB 10,13,'Reversed string is: $'
    BUFFER DB 20
           DB ?
           DB 20 DUP(?)
    REVERSE DB 20 DUP(?)
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX

    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    LEA DX, BUFFER
    MOV AH, 0AH
    INT 21H

    MOV CL, BUFFER+1
    MOV CH, 0
    MOV SI, OFFSET BUFFER+2
    MOV DI, OFFSET REVERSE
    ADD SI, CX
    DEC SI

REVERSE_LOOP:
    MOV AL, [SI]
    MOV [DI], AL
    INC DI
    DEC SI
    LOOP REVERSE_LOOP

    MOV AL, '$'
    MOV [DI], AL

    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    LEA DX, REVERSE
    MOV AH, 09H
    INT 21H

    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
