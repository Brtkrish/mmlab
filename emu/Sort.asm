DATA SEGMENT
    ARRAY DW 5
          DW 20, 8, 55, 2, 16
    MSG1 DB 10,13,'Sorted array: $'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX

    LEA SI, ARRAY
    MOV CX, [SI]
    DEC CX

OUTER_LOOP:
    MOV DX, CX
    LEA SI, ARRAY
    ADD SI, 2

INNER_LOOP:
    MOV AX, [SI]
    CMP AX, [SI+2]
    JBE NO_SWAP
    XCHG AX, [SI+2]
    MOV [SI], AX
NO_SWAP:
    ADD SI, 2
    DEC DX
    JNZ INNER_LOOP
    LOOP OUTER_LOOP

    LEA DX, MSG1
    MOV AH, 9
    INT 21H

    LEA SI, ARRAY
    MOV CX, [SI]
    ADD SI, 2

PRINT_LOOP:
    MOV AX, [SI]
    CALL PRINT_NUM
    MOV DL, ' '
    MOV AH, 02H
    INT 21H
    ADD SI, 2
    LOOP PRINT_LOOP

    MOV AH, 4CH
    INT 21H

PRINT_NUM PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    MOV CX, 0
    MOV BX, 10
REPEAT1:
    XOR DX, DX
    DIV BX
    PUSH DX
    INC CX
    CMP AX, 0
    JNE REPEAT1
PRINT_LOOP1:
    POP DX
    ADD DL, 30H
    MOV AH, 02H
    INT 21H
    LOOP PRINT_LOOP1
    POP DX
    POP CX
    POP BX
    POP AX
    RET
PRINT_NUM ENDP

CODE ENDS
END START
