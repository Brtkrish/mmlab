DATA SEGMENT
    ARRAY   DW 0001H, 0002H, 0003H, 0004H, 0005H
    COUNT   DW 05H
    SUM     DW 0
    MSG1 DB 10,13, 'The sum is: $'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX

    LEA SI, ARRAY
    MOV CX, COUNT
    MOV AX, 0

LOOP1:
    ADD AX, [SI]
    ADD SI, 2
    DEC CX
    JNZ LOOP1

    MOV SUM, AX

    LEA DX, MSG1
    MOV AH, 9
    INT 21H

    MOV AX, SUM
    CALL PRINT_HEX

    MOV AH, 4CH
    INT 21H

PRINT_HEX PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    MOV CX, 4
HEX_LOOP:
    ROL AX, 4
    MOV BL, AL
    AND BL, 0FH
    CMP BL, 9
    JBE DIGIT
    ADD BL, 7
DIGIT:
    ADD BL, 30H
    MOV DL, BL
    MOV AH, 02H
    INT 21H
    LOOP HEX_LOOP
    POP DX
    POP CX
    POP BX
    POP AX
    RET
PRINT_HEX ENDP

CODE ENDS
END START
